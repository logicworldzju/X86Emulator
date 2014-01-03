#include "cpu.h"
#include <assert.h>
#include "cpu/decoder/instructiondecoder.h"
#include "cpu/decoder/instructionstreamfrommemory.h"
#include "cpu/executer/instructionexecuter.h"
#include "cpu/executer/execute.h"

CPU::CPU(QObject *parent) :
    QThread(parent)
{
    _memory=NULL;
    _ioPortList=NULL;
    _interrupt=NULL;

    shouldExit=false;
}

static inline bool decRCX(RegisterFile& registerFile,EffectiveSize effectiveOperandSize)
{
    switch(effectiveOperandSize)
    {
    case EFFECTIVE_16_BITS:
        if(registerFile.getGPR16Bits(RCX)==0)
        {
            return true;
        }
        else
        {
            registerFile.setGPR16Bits(RCX,registerFile.getGPR16Bits(RCX)-1);
            return false;
        }
//        return registerFile.getGPR16Bits(RCX)==0;
        break;
    case EFFECTIVE_32_BITS:
        if(registerFile.getGPR32Bits(RCX)==0)
        {
            return true;
        }
        else
        {
            registerFile.setGPR32Bits(RCX,registerFile.getGPR32Bits(RCX)-1);
            return false;
        }
//        return registerFile.getGPR32Bits(RCX)==0;
        break;
    case EFFECTIVE_64_BITS:
        if(registerFile.getGPR64Bits(RCX)==0)
        {
            return true;
        }
        else
        {
            registerFile.setGPR64Bits(RCX,registerFile.getGPR64Bits(RCX)-1);
            return false;
        }
//            return registerFile.getGPR64Bits(RCX)==0;
        break;
    }
    assert(0);
    return true;
}

void CPU::run()
{
    assert(_memory && _ioPortList && _interrupt);

    //init
    InstructionStreamFromMemory instructionStream(*_memory,false);
    _registerFile.setSR(CS,0xffff);
    _registerFile.setSSR(CS,0xffff0);
    _registerFile.setIP(0x0);

    while(!shouldExit)
    {
        InstructionLowLevelFormat lowFormat;
        InstructionHighLevelFormat highFormat;

        //check the interrupt,but we can do nothing here.
        s32 intNumber=0;
        if(_registerFile.getFlagsBits().IF && (intNumber=_interrupt->get())>0)
        {
            assert(0);//should not happened now.
            _interrupt->clear();
            INTERRUPT(intNumber,EFFECTIVE_16_BITS,*_memory,_registerFile);
        }
        else if(_registerFile.getFlagsBits().TF)
        {
            INTERRUPT(1,EFFECTIVE_16_BITS,*_memory,_registerFile);
        }

        //start a instruction.
        u32 ip = _registerFile.getSSR(CS)+_registerFile.getIP();
        instructionStream.setIP(ip);
        doStartInstruction(ip);

        //instruction decode.
        instructionStream.startReadOneInstruction();
        InstructionDecoder::decode(instructionStream,ENV_16_BITS,lowFormat,highFormat);
        instructionStream.endReadOneInstruction();
        doDecodeInstruction(ip,instructionStream.readLastInstruction(),lowFormat,highFormat);

        u32 nextIP=(instructionStream.getIP()-ip)+_registerFile.getIP();
        assert(nextIP<0x10000);
        _registerFile.setIP(nextIP&0xffff);

        //deal with rep repz repnz.
        void* execFunc=highFormat.opcode->execFunc;
        if(highFormat.legacyPrefix.rep_repz || highFormat.legacyPrefix.repnz)
        {
            if(decRCX(_registerFile,highFormat.effectiveOperandSize))
            {
                continue;
            }
        }

        //instruction addressing.
        ExecOperands operands;
        InstructionExecuter::addressing(highFormat,_registerFile,*_memory,operands);
        doAddressing(operands);

        //instruction execute.
        InstructionExecuter::execute(highFormat,_registerFile,*_memory,*_ioPortList,operands);
        doExecuteInstruction();

        //deal with rep repz repnz.
        if(highFormat.legacyPrefix.rep_repz)
        {
            if(execFunc==(void*)executeLODS || execFunc==(void*)executeMOVS ||
                    execFunc==(void*)executeSTOS || execFunc==(void*)executeINS ||
                    execFunc==(void*)executeOUTS)
            {
                //rep
//                if(decRCX(_registerFile,highFormat.effectiveOperandSize))
//                {
//                    continue;
//                }
//                else
                {
                    _registerFile.setIP(_registerFile.getIP()-(instructionStream.getIP()-ip));
                }

            }
            else if(execFunc==(void*)executeCMPS || execFunc==(void*)executeSCAS)
            {
                //repz or repe
                if((/*decRCX(_registerFile,highFormat.effectiveOperandSize)||*/
                     _registerFile.getFlagsBits().ZF==0))
                {
                    continue;
                }
                else
                {
                    _registerFile.setIP(_registerFile.getIP()-(instructionStream.getIP()-ip));
                }
            }
            else
            {
                assert(0);
            }
        }
        if(highFormat.legacyPrefix.repnz)
        {
            if(execFunc==(void*)executeCMPS || execFunc==(void*)executeSCAS)
            {
                //repnz or repne

                if((/*decRCX(_registerFile,highFormat.effectiveOperandSize)||*/
                     _registerFile.getFlagsBits().ZF==1))
                {
                    continue;
                }
                else
                {
                    _registerFile.setIP(_registerFile.getIP()-(instructionStream.getIP()-ip));
                }
            }
            else
            {
                assert(0);
            }
        }

    }
}
