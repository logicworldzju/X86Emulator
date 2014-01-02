#include "debugcpu.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include "cpu/tostring/instructiontostring.h"
#include "cpu/decoder/instructionstreamfrommemory.h"
#include "cpu/decoder/instructiondecoder.h"
using namespace std;

static void hex2Ascii(const std::vector<u8>& hex,std::string& ascii)
{
    for(uint i=0; i<hex.size(); i++)
    {
        {
            u8 t=(hex[i]>>4);
            ascii+=t>9?t-10+'a':t+'0';
        }
        {
            u8 t=(hex[i]&0xf);
            ascii+=t>9?t-10+'a':t+'0';
        }
        ascii+=" ";
    }
}
static std::vector<u8> buffer2vector(u8 buffer[],u32 length)
{
    std::vector<u8> vec;
    for(u32 i=0; i<length; i++)
    {
        vec.push_back(buffer[i]);
    }
    return vec;
}

DebugCPU::DebugCPU(QObject *parent) :
    CPU(parent)
{
    _breakPointList.insert(0xffff0);//break when cpu starts.
    _stopAtNextInstruction=false;
    cout.fill('0');

    _instCount=0;
}

void DebugCPU::run()
{
    head();
    CPU::run();
    tail();
}

void DebugCPU::head()
{
    cout<<"Welcome to X86Emulator.You can debug the MS-DOS here."<<endl;
}

void DebugCPU::tail()
{
    cout<<"The X86Emulator exits now."<<endl;
}

void DebugCPU::help()
{
    cout<<"break address or b address           set a breakpoint at address"<<endl;
    cout<<"breaklist or bl                      list the break points."<<endl;
    cout<<"deletebreak address or db address    delete break point."<<endl;
    cout<<"c or continue                        continue execution."<<endl;
    cout<<"s or step                            execute the next instruction."<<endl;
    cout<<"r or register                        show the current register values."<<endl;
    cout<<"data address length                  show data of the size of length on the address."<<endl;
    cout<<"disasm address length                disasm the instruction between address and address+length"<<endl;
}
void DebugCPU::tip()
{
    cout<<dec<<_instCount<<">>>";
}

u32 DebugCPU::readInt(bool& isInt)
{
    u32 value;
//    cin>>value;
    string valueStr;
    cin>>valueStr;
    if(valueStr[valueStr.size()-1]=='h')
    {
        valueStr="0x"+valueStr.substr(0,valueStr.size()-1);
    }
    if(::sscanf(valueStr.c_str(),"%i",&value)==1)
    {
        isInt=true;
        return value;
    }
    else
    {
        cerr<<"Error:"<<valueStr<<" is not an integer."<<endl;
        value=0;
        isInt=false;
    }
    return value;
}

void DebugCPU::outputInstruction(u32 ip, const std::vector<u8> &bin, InstructionHighLevelFormat &highFormat)
{
    cout.width(8);
    cout<<hex<<ip<<"h    ";

    string ascii;
    ::hex2Ascii(bin,ascii);
    cout<<ascii<<"    ";

    InstructionToString instructionToString;
    string instString;
    instructionToString.toString(highFormat,instString);
    cout<<instString<<endl;
}

void DebugCPU::showDisasm(u32 address, u32 length)
{
    InstructionStreamFromMemory stream(*_memory,true);
    stream.setIP(address);
    while(stream.getIP()<address+length)
    {
        InstructionHighLevelFormat highFormat;
        InstructionLowLevelFormat lowFormat;

        stream.startReadOneInstruction();
        InstructionDecoder::decode(stream,ENV_16_BITS,lowFormat,highFormat);
        stream.endReadOneInstruction();

        outputInstruction(stream.getIP(),stream.readLastInstruction(),highFormat);
    }
}

void DebugCPU::showData(u32 address, u32 length)
{
    _memory->startAccess(_memory->DEBUG_ACCESS);
    for(u32 i=0; i<length; i+=16)
    {
        cout.width(8);
        cout<<hex<<(address+i)<<"h    ";

        {
            u8 buffer[8];
            _memory->getBytes(address+i,sizeof(buffer),buffer);
            string ascii;
            hex2Ascii(buffer2vector(buffer,8),ascii);
            cout<<ascii<<" ";
        }
        {
            u8 buffer[8];
            _memory->getBytes(address+i+8,sizeof(buffer),buffer);
            string ascii;
            hex2Ascii(buffer2vector(buffer,8),ascii);
            cout<<ascii<<endl;
        }
    }
    _memory->endAccess();
}

void DebugCPU::doStartInstruction(u32 addressIP)
{
    (void)addressIP;
}

void DebugCPU::doDecodeInstruction(u32 ip, const std::vector<u8> &bin, InstructionLowLevelFormat &lowFormat, InstructionHighLevelFormat &highFormat)
{
    (void)bin;(void)lowFormat;(void)highFormat;

    _instCount++;
    cout<<"InstructionCount:"<<dec<<_instCount<<"IP:"<<hex<<ip<<"h"<<endl;
    if(!highFormat.opcode->execFunc)
    {
        cerr<<"Error:highFormat.opcode->execFunc is null"<<endl;
        cout<<"InstructionCount:"<<dec<<_instCount<<endl;
        outputInstruction(ip,bin,highFormat);
        cout<<_registerFile.toString();
        ::exit(-1);
    }

    if(_breakPointList.find(ip)!=_breakPointList.end() || _stopAtNextInstruction==true)
    {
        _stopAtNextInstruction=false;

        outputInstruction(ip,bin,highFormat);

        while(true)
        {
            tip();
            string command;
            cin>>command;
            if(command=="break" || command=="b")
            {
                bool isInt;
                u32 address = readInt(isInt);
                if(!isInt) continue;
                 _breakPointList.insert(address);
            }
            else if(command=="breaklist" || command=="bl")
            {
                cout<<"Break at address:"<<endl;
                for(set<u32>::iterator it=_breakPointList.begin();
                    it!=_breakPointList.end();
                    ++it)
                {
                    cout.width(8);
                    cout<<hex<<*it<<"h"<<endl;
                }
            }
            else if(command=="deletebreak" || command=="db")
            {
                bool isInt;
                u32 address = readInt(isInt);
                if(!isInt) continue;
                set<u32>::iterator it=_breakPointList.find(address);
                if(it!=_breakPointList.end())
                {
                    _breakPointList.erase(it);
                }
                else
                {
                    cerr<<"Error:There is no this address ";
                    cerr.width(8);
                    cerr<<hex<<address<<"h"<<endl;
                }
            }
            else if(command=="continue" || command=="c")
            {
                break;
            }
            else if(command=="step" || command=="s")
            {
                _stopAtNextInstruction=true;
                break;
            }
            else if(command=="register" || command=="r")
            {
                cout<<_registerFile.toString();
            }
            else if(command=="data")
            {
                bool isInt;
                u32 address=readInt(isInt);
                if(!isInt) continue;
                u32 length=readInt(isInt);
                if(!isInt) continue;
                showData(address,length);
            }
            else if(command=="disasm")
            {
                bool isInt;
                u32 address=readInt(isInt);
                if(!isInt) continue;
                u32 length=readInt(isInt);
                if(!isInt) continue;
                showDisasm(address,length);
            }
            else if(command=="exit")
            {
                this->shouldExit=true;
                break;
            }
            else if(command=="h" || command=="help")
            {
                help();
            }
            else
            {
                cerr<<"Error:There is no such command "<<command<<endl;
            }
        }
    }
}
