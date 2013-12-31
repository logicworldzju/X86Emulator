#include "testinstructionexecuter.h"
#include "cpu/decoder/instructiondecoder.h"
#include "cpu/encoder/instructionencoder.h"
#include "cpu/decoder/instructionstreamfromfile.h"
#include "cpu/tostring/instructiontostring.h"
#include <iostream>
#include "cpu/executer/instructionexecuter.h"
#include "memory/debugmemory.h"
#include <stdlib.h>

TestInstructionExecuter::TestInstructionExecuter(QObject *parent) :
    QObject(parent)
{
}

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
void TestInstructionExecuter::testAll()
{
    InstructionStreamFromFile fromFile("test/asm/1.com");

    std::ofstream fout("test/asm/1.txt");

    RegisterFile registerFile;
    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);
    int count=0;
    while(!fromFile.eof())
    {

        InstructionLowLevelFormat lowFormat;
        InstructionHighLevelFormat highFormat;

        fromFile.startReadOneInstruction();
        InstructionDecoder::decode(fromFile,ENV_16_BITS,lowFormat,highFormat);
        fromFile.endReadOneInstruction();

        std::vector<u8> instOriginal=fromFile.readLastInstruction();
        std::vector<u8> instCreated;

        InstructionEncoder::encode(lowFormat,instCreated);

        {
            std::string ascii;
            hex2Ascii(instOriginal,ascii);
            fout<<"OriginalBinary:"<<ascii<<std::endl;
            std::cout<<"OriginalBinary:"<<ascii<<std::endl;;
        }
        {
            std::string ascii;
            hex2Ascii(instCreated,ascii);
            fout<<"OriginalCreated:"<<ascii<<std::endl;
            std::cout<<"OriginalCreated:"<<ascii<<std::endl;
        }

        QCOMPARE(instCreated.size(),instOriginal.size());
        for(uint i=0; i<instCreated.size(); i++)
        {
            QCOMPARE(instCreated[i],instOriginal[i]);
        }

        {
            InstructionToString toString;
            std::string inst;
            toString.toString(highFormat,inst);
            fout<<"ASM:"<<inst<<std::endl;
            std::cout<<"ASM:"<<inst<<std::endl;
        }

//        InstructionExecuter executer;
        ExecOperands operands;

        switch(count)
        {
//        start:
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//        add al,al 	;0x00
        case 0:
        {
            registerFile.setGPR8Bits(RAX,0x80);
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);
//            QCOMPARE(u32(registerFile.getFlagsBits().))
            QCOMPARE(int(registerFile.getGPR8Bits(RAX)),0x00);
            QCOMPARE(registerFile.getFlagsBits().CF,(unsigned int)(1));
            QCOMPARE(registerFile.getFlagsBits().PF,(unsigned int)(1));
            QCOMPARE(registerFile.getFlagsBits().AF,(unsigned int)(0));
            QCOMPARE(registerFile.getFlagsBits().ZF,(unsigned int)(1));
            QCOMPARE(registerFile.getFlagsBits().SF,(unsigned int)(0));
            QCOMPARE(registerFile.getFlagsBits().OF,(unsigned int)(1));
            break;
        }
//        add [0],al 	;0x00
        case 1:
        {
            registerFile.setGPR8Bits(RAX,0xcc);
            memory.startAccess(memory.DEBUG_ACCESS);
            memory.set8Bits(registerFile.getSSR(DS),0x11);
            memory.endAccess();
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            memory.startAccess(memory.DEBUG_ACCESS);
            QCOMPARE(u32(memory.get8Bits(registerFile.getSSR(DS))),u32(0xdd));
            memory.endAccess();
            QCOMPARE(registerFile.getFlagsBits().CF,(unsigned int)(0));
            QCOMPARE(registerFile.getFlagsBits().PF,(unsigned int)(1));
            QCOMPARE(registerFile.getFlagsBits().AF,(unsigned int)(0));
            QCOMPARE(registerFile.getFlagsBits().ZF,(unsigned int)(0));
            QCOMPARE(registerFile.getFlagsBits().SF,(unsigned int)(1));
            QCOMPARE(registerFile.getFlagsBits().OF,(unsigned int)(0));
            break;
        }
//        add ax,ax 	;0x01
        case 2:
        {
            registerFile.setGPR16Bits(RAX,0xcc);
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            QCOMPARE(registerFile.getGPR16Bits(RAX),u16(0x198));

            QCOMPARE(registerFile.getFlagsBits().CF,(unsigned int)(0));
            QCOMPARE(registerFile.getFlagsBits().PF,(unsigned int)(0));
            QCOMPARE(registerFile.getFlagsBits().AF,(unsigned int)(1));
            QCOMPARE(registerFile.getFlagsBits().ZF,(unsigned int)(0));
            QCOMPARE(registerFile.getFlagsBits().SF,(unsigned int)(0));
            QCOMPARE(registerFile.getFlagsBits().OF,(unsigned int)(0));
            break;
        }
//        add [1],ax 	;0x01
        case 3:
        {
            registerFile.setGPR16Bits(RAX,0xcc);
            registerFile.setSR(DS,1);
            registerFile.setSSR(DS,1<<4);
            memory.startAccess(memory.DEBUG_ACCESS);
            memory.set16Bits(registerFile.getSSR(DS)+1,0x1111);
            memory.endAccess();

            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            memory.startAccess(memory.DEBUG_ACCESS);
            QCOMPARE(u32(memory.get16Bits(registerFile.getSSR(DS)+1)),u32(0x11dd));
            memory.endAccess();
            QCOMPARE(registerFile.getFlagsBits().CF,(unsigned int)(0));
            QCOMPARE(registerFile.getFlagsBits().PF,(unsigned int)(1));
            QCOMPARE(registerFile.getFlagsBits().AF,(unsigned int)(0));
            QCOMPARE(registerFile.getFlagsBits().ZF,(unsigned int)(0));
            QCOMPARE(registerFile.getFlagsBits().SF,(unsigned int)(0));
            QCOMPARE(registerFile.getFlagsBits().OF,(unsigned int)(0));
            break;
        }
//        add al,[2] 	;0x02
        case 4:
        {
            registerFile.setGPR8Bits(RAX,0xcd);
            memory.startAccess(memory.DEBUG_ACCESS);
            memory.set8Bits(registerFile.getSSR(DS)+2,0x11);
            memory.endAccess();
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            QCOMPARE(u32(registerFile.getGPR8Bits(RAX)),u32(0xde));
            QCOMPARE(registerFile.getFlagsBits().CF,(unsigned int)(0));
            QCOMPARE(registerFile.getFlagsBits().PF,(unsigned int)(1));
            QCOMPARE(registerFile.getFlagsBits().AF,(unsigned int)(0));
            QCOMPARE(registerFile.getFlagsBits().ZF,(unsigned int)(0));
            QCOMPARE(registerFile.getFlagsBits().SF,(unsigned int)(1));
            QCOMPARE(registerFile.getFlagsBits().OF,(unsigned int)(0));
            break;
        }
//        add ax,[3]	;0x03
        case 5:
        {
            registerFile.setGPR16Bits(RAX,0xcc);
            registerFile.setSR(DS,1);
            registerFile.setSSR(DS,1<<4);
            memory.startAccess(memory.DEBUG_ACCESS);
            memory.set16Bits(registerFile.getSSR(DS)+3,0x1111);
            memory.endAccess();

            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            memory.startAccess(memory.DEBUG_ACCESS);
            QCOMPARE(u32(registerFile.getGPR16Bits(RAX)),u32(0x11dd));
            memory.endAccess();
            QCOMPARE(registerFile.getFlagsBits().CF,(unsigned int)(0));
            QCOMPARE(registerFile.getFlagsBits().PF,(unsigned int)(1));
            QCOMPARE(registerFile.getFlagsBits().AF,(unsigned int)(0));
            QCOMPARE(registerFile.getFlagsBits().ZF,(unsigned int)(0));
            QCOMPARE(registerFile.getFlagsBits().SF,(unsigned int)(0));
            QCOMPARE(registerFile.getFlagsBits().OF,(unsigned int)(0));
            break;
        }
//        add al,4	;0x04
        case 6:
        {
            registerFile.setGPR8Bits(RAX,0xcd);
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            QCOMPARE(u32(registerFile.getGPR8Bits(RAX)),u32(0xd1));
            QCOMPARE(registerFile.getFlagsBits().CF,(unsigned int)(0));
            QCOMPARE(registerFile.getFlagsBits().PF,(unsigned int)(1));
            QCOMPARE(registerFile.getFlagsBits().AF,(unsigned int)(1));
            QCOMPARE(registerFile.getFlagsBits().ZF,(unsigned int)(0));
            QCOMPARE(registerFile.getFlagsBits().SF,(unsigned int)(1));
            QCOMPARE(registerFile.getFlagsBits().OF,(unsigned int)(0));
            break;
        }
//        add ax,5	;0x05
        case 7:
        {
            registerFile.setGPR16Bits(RAX,0xcc);

            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            QCOMPARE(u32(registerFile.getGPR16Bits(RAX)),u32(0xd1));
            QCOMPARE(registerFile.getFlagsBits().CF,(unsigned int)(0));
            QCOMPARE(registerFile.getFlagsBits().PF,(unsigned int)(1));
            QCOMPARE(registerFile.getFlagsBits().AF,(unsigned int)(1));
            QCOMPARE(registerFile.getFlagsBits().ZF,(unsigned int)(0));
            QCOMPARE(registerFile.getFlagsBits().SF,(unsigned int)(0));
            QCOMPARE(registerFile.getFlagsBits().OF,(unsigned int)(0));
            break;
        }
//        push es	;0x06
        case 8:
        {
            //stack setup.
            registerFile.setSR(SS,0x100);
            registerFile.setSSR(SS,0x1000);

            registerFile.setGPR16Bits(RSP,0);

            //init.
            registerFile.setSR(ES,0xcccc);
            registerFile.setSSR(ES,0xcccc0);

            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            QCOMPARE(registerFile.getGPR16Bits(RSP),u16(0xfffe));

            memory.startAccess(memory.DEBUG_ACCESS);
            QCOMPARE(u32(memory.get16Bits(registerFile.getSSR(SS)+0xfffe)),u32(0xcccc));
            memory.endAccess();


            break;
        }
//        pop es	;0x07
        case 9:
        {
            //init.
            registerFile.setSR(ES,0x0);
            registerFile.setSSR(ES,0x00);
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            QCOMPARE(registerFile.getGPR16Bits(RSP),u16(0x0));
            QCOMPARE((u16)registerFile.getSR(ES),(u16)0xcccc);
            QCOMPARE((u32)registerFile.getSSR(ES),(u32)0xcccc0);

            break;
        }
//        or al,al 	;0x08
        case 10:
        {
            //init.
            registerFile.setGPR8Bits(RAX,0x22);
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            QCOMPARE(registerFile.getGPR8Bits(RAX),u8(0x22));

            break;
        }
//        or [0],al 	;0x08
        case 11:
        {

            //init.
            registerFile.setSR(DS,0x100);
            registerFile.setSSR(DS,0x1000);
            registerFile.setGPR8Bits(RAX,0x22);

            memory.startAccess(memory.DEBUG_ACCESS);
            memory.set8Bits(0x1000+0,0x11);
            memory.endAccess();

            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            memory.startAccess(memory.DEBUG_ACCESS);
            QCOMPARE(u32(memory.get8Bits(0x1000+0)),u32(0x33));
            memory.endAccess();

            break;
        }
//        or ax,ax 	;0x09
        case 12:
        {
            //init.
            registerFile.setGPR16Bits(RAX,0x1122);
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            QCOMPARE(registerFile.getGPR16Bits(RAX),u16(0x1122));

            break;
        }
//        or [1],ax 	;0x09
        case 13:
        {

            //init.
            registerFile.setSR(DS,0x100);
            registerFile.setSSR(DS,0x1000);
            registerFile.setGPR16Bits(RAX,0x3322);

            memory.startAccess(memory.DEBUG_ACCESS);
            memory.set16Bits(0x1000+1,0x4411);
            memory.endAccess();

            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            memory.startAccess(memory.DEBUG_ACCESS);
            QCOMPARE(u32(memory.get16Bits(0x1000+1)),u32(0x7733));
            memory.endAccess();

            break;
        }
//        or al,[2] 	;0x0a
        case 14:
        {
            //init.
            registerFile.setSR(DS,0x100);
            registerFile.setSSR(DS,0x1000);
            registerFile.setGPR8Bits(RAX,0x22);

            memory.startAccess(memory.DEBUG_ACCESS);
            memory.set8Bits(0x1000+2,0x11);
            memory.endAccess();

            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            QCOMPARE(u32(registerFile.getGPR8Bits(RAX)),u32(0x33));

            break;
        }
//        or ax,[3]	;0x0b
        case 15:
        {
            //init.
            registerFile.setSR(DS,0x100);
            registerFile.setSSR(DS,0x1000);
            registerFile.setGPR16Bits(RAX,0x1122);

            memory.startAccess(memory.DEBUG_ACCESS);
            memory.set16Bits(0x1000+3,0xff11);
            memory.endAccess();

            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            QCOMPARE(u32(registerFile.getGPR16Bits(RAX)),u32(0xff33));

            break;
        }
//        or al,4	;0x0c
        case 16:
        {
            //init.
            registerFile.setGPR8Bits(RAX,0x22);

            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            QCOMPARE(u32(registerFile.getGPR8Bits(RAX)),u32(0x26));

            break;
        }
//        or ax,5	;0x0d
        case 17:
        {
            //init.
            registerFile.setGPR16Bits(RAX,0x1122);

            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            QCOMPARE(u32(registerFile.getGPR16Bits(RAX)),u32(0x1127));

            break;
        }
//        push cs	;0x0e
        case 18:
        {
            //stack setup.
            registerFile.setSR(SS,0x100);
            registerFile.setSSR(SS,0x1000);

            registerFile.setGPR16Bits(RSP,0);

            //init.
            registerFile.setSR(CS,0xcccd);
            registerFile.setSSR(CS,0xcccd0);

            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            QCOMPARE(registerFile.getGPR16Bits(RSP),u16(0xfffe));

            memory.startAccess(memory.DEBUG_ACCESS);
            QCOMPARE(u32(memory.get16Bits(registerFile.getSSR(SS)+0xfffe)),u32(0xcccd));
            memory.endAccess();


            break;
        }
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//        adc al,al 	;0x10
        case 19:
//        adc [0],al 	;0x10
        case 20:
//        adc ax,ax 	;0x11
        case 21:
//        adc [1],ax 	;0x11
        case 22:
//        adc al,[2] 	;0x12
        case 23:
//        adc ax,[3]	;0x13
        case 24:
//        adc al,4	;0x14
        case 25:
//        adc ax,5	;0x15
        case 26:
//        push ss	;0x16
        case 27:
//        pop ss	;0x17
        case 28:
//        sbb al,al 	;0x18
        case 29:
//        sbb [0],al 	;0x18
        case 30:
//        sbb ax,ax 	;0x19
        case 31:
//        sbb [1],ax 	;0x19
        case 32:
//        sbb al,[2] 	;0x1a
        case 33:
//        sbb ax,[3]	;0x1b
        case 34:
//        sbb al,4	;0x1c
        case 35:
//        sbb ax,5	;0x1d
        case 36:
//        push ds	;0x1e
        case 37:
//        pop ds	;0x1f
        case 38:
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//        and al,al 	;0x20
        case 39:
//        and [0],al 	;0x20
        case 40:
//        and ax,ax 	;0x21
        case 41:
//        and [1],ax 	;0x21
        case 42:
//        and al,[2] 	;0x22
        case 43:
//        and ax,[3]	;0x23
        case 44:
//        and al,4	;0x24
        case 45:
//        and ax,5	;0x25
        case 46:
//        and [es:0],al	;0x26
        case 47:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);
            break;
        }
//        DAA	;0x27
        case 48:
        {
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            break;
        }
//        sub al,al 	;0x28
        case 49:
//        sub [0],al 	;0x28
        case 50:


//        sub ax,ax 	;0x29
        case 51:
//        sub [1],ax 	;0x29
        case 52:

//        sub al,[2] 	;0x2a
        case 53:

//        sub ax,[3]	;0x2b
        case 54:

//        sub al,4	;0x2c
        case 55:
//        sub ax,5	;0x2d
        case 56:

//        sub al,[cs:2]	;0x2e
        case 57:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);
            break;
        }
//        DAS	;0x2f
        case 58:
        {
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            break;
        }
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//        xor al,al 	;0x30
        case 59:
//        xor [0],al 	;0x30
        case 60:

//        xor ax,ax 	;0x31
        case 61:
//        xor [1],ax 	;0x31
        case 62:

//        xor al,[2] 	;0x32
        case 63:

//        xor ax,[3]	;0x33
        case 64:

//        xor al,4	;0x34
        case 65:

//        xor ax,5	;0x35
        case 66:

//        xor ax,[ss:3]	;0x36
        case 67:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);
            break;
        }
//        AAA	;0x37
        case 68:
        {
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            break;
        }
//        cmp al,al 	;0x38
        case 69:
//        cmp [0],al 	;0x38
        case 70:

//        cmp ax,ax 	;0x39
        case 71:
//        cmp [1],ax 	;0x39
        case 72:

//        cmp al,[2] 	;0x3a
        case 73:

//        cmp ax,[3]	;0x3b
        case 74:

//        cmp al,4	;0x3c
        case 75:
//        cmp ax,5	;0x3d
        case 76:

//        cmp al,[ds:2]	;0x3e
        case 77:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);
            break;
        }
//        AAS	;0x3f
        case 78:
        {
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            break;
        }
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//        inc ax	;0x40
        case 79:
//        inc cx	;0x41
        case 80:
//        inc dx	;0x42
        case 81:
//        inc bx	;0x43
        case 82:
//        inc sp	;0x44
        case 83:
//        inc bp	;0x45
        case 84:
//        inc si	;0x46
        case 85:
//        inc di	;0x47
        case 86:

//        dec ax	;0x48
        case 87:
//        dec cx	;0x49
        case 88:
//        dec dx	;0x4a
        case 89:
//        dec bx	;0x4b
        case 90:
//        dec sp	;0x4c
        case 91:
//        dec bp	;0x4d
        case 92:
//        dec si	;0x4e
        case 93:
//        dec di	;0x4f
        case 94:
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//        push ax	;0x50
        case 95:
//        push cx	;0x51
        case 96:
//        push dx	;0x52
        case 97:
//        push bx	;0x53
        case 98:
//        push sp	;0x54
        case 99:
//        push bp	;0x55
        case 100:
//        push si	;0x56
        case 101:
//        push di	;0x57
        case 102:

//        pop ax	;0x58
        case 103:
//        pop cx	;0x59
        case 104:
//        pop dx	;0x5a
        case 105:
//        pop bx	;0x5b
        case 106:
//        pop sp	;0x5c
        case 107:
//        pop bp	;0x5d
        case 108:
//        pop si	;0x5e
        case 109:
//        pop di	;0x5f
        case 110:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);
            break;
        }
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//        pusha	;0x60
        case 111:
//        popa	;0x61
        case 112:
//        bound ax,[0x62]	;0x62
        case 113:
//        arpl ax,ax	;0x63
        case 114:
//        bound ax,[fs:0x64]	;0x64
        case 115:
//        bound ax,[gs:0x65]	;0x65
        case 116:
//        bound eax,[0x66]	;0x66
        case 117:
//        bound ax,[eax+0x67]	;0x67
        case 118:
        {
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            break;
        }
//        push 0x6868	;0x68
        case 119:
//        imul ax,[0x69],0x6969	;0x69
        case 120:
//        push 0x6a	;0x6a
        case 121:
//        imul ax,[0x6b],0x6b	;0x6b
        case 122:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);
            break;
        }
//        insb	;0x6c
        case 123:
//        insw	;0x6d
        case 124:
//        outsb	;0x6e
        case 125:
//        outsw	;0x6f
        case 126:
        {
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            break;
        }
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//    label:
//        jo label	;0x70
        case 127:
//        jno label	;0x71
        case 128:
//        jb label	;0x72
        case 129:
//        jnb label	;0x73
        case 130:
//        jz label	;0x74
        case 131:
//        jnz label	;0x75
        case 132:
//        jbe label	;0x76
        case 133:
//        jnbe label	;0x77
        case 134:

//        js label	;0x78
        case 135:
//        jns label	;0x79
        case 136:
//        jp label	;0x7a
        case 137:
//        jnp label	;0x7b
        case 138:
//        jl label	;0x7c
        case 139:
//        jnl label	;0x7d
        case 140:
//        jle label	;0x7e
        case 141:
//        jnle label	;0x7f
        case 142:
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//        ;Group 1 0x80
//        add byte[0x80],byte 0x80	;000b
        case 143:
//        or  byte[0x80],byte 0x80	;001b
        case 144:
//        adc byte[0x80],byte 0x80	;010b
        case 145:
//        sbb byte[0x80],byte 0x80	;011b
        case 146:
//        and byte[0x80],byte 0x80	;100b
        case 147:
//        sub byte[0x80],byte 0x80	;101b
        case 148:
//        xor byte[0x80],byte 0x80	;110b
        case 149:
//        cmp byte[0x80],byte 0x80	;111b
        case 150:
//        ;Group 1 0x81
//        add word[0x81],0x8181	;000b
        case 151:
//        or  word[0x81],0x8181	;001b
        case 152:
//        adc word[0x81],0x8181	;010b
        case 153:
//        sbb word[0x81],0x8181	;011b
        case 154:
//        and word[0x81],0x8181	;100b
        case 155:
//        sub word[0x81],0x8181	;101b
        case 156:
//        xor word[0x81],0x8181	;110b
        case 157:
//        cmp word[0x81],0x8181	;111b
        case 158:
//        ;Group 1 0x82
//        ;Group 1 0x83
//        add word[0x80],byte -0x80	;000b
        case 159:
//        or  word[0x80],byte -0x80	;001b
        case 160:
//        adc word[0x80],byte -0x80	;010b
        case 161:
//        sbb word[0x80],byte -0x80	;011b
        case 162:
//        and word[0x80],byte -0x80	;100b
        case 163:
//        sub word[0x80],byte -0x80	;101b
        case 164:
//        xor word[0x80],byte -0x80	;110b
        case 165:
//        cmp word[0x80],byte -0x80	;111b
        case 166:

//        test byte[0x84],al	;0x84
        case 167:
//        test word[0x85],ax	;0x85
        case 168:
//        xchg byte[0x86],bl	;0x86
        case 169:
//        xchg word[0x87],bx	;0x87
        case 170:

//        mov [0x88],bl	;0x88
        case 171:
//        mov [0x89],cx	;0x89
        case 172:
//        mov dl,[0x8a]	;0x8a
        case 173:
//        mov ax,[0x8b]	;0x8b
        case 174:
//        mov [0x8c],cs	;0x8c
        case 175:
//        lea si,[bx+si+0x8d]	;0x8d
        case 176:
//        mov ds,[0x8e]	;0x8e
        case 177:
//        ;Group 1a
//        pop bp	;000b
        case 178:
//        pop	word[0x8f]	;000b
        case 179:
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//        nop	;0x90
        case 180:
//        pause	;0x90
        case 181:
//        xchg cx,ax	;0x91
        case 182:
//        xchg dx,ax	;0x92
        case 183:
//        xchg bx,ax	;0x93
        case 184:
//        xchg sp,ax	;0x94
        case 185:
//        xchg bp,ax	;0x95
        case 186:
//        xchg si,ax	;0x96
        case 187:
//        xchg di,ax	;0x97
        case 188:

//        cbw	;0x98
        case 189:
//        cwd	;0x99
        case 190:
//        call 0x9a:0x9a9a	;0x9a
        case 191:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);
            break;
        }
//        wait	;0x9b
        case 192:
        {
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            break;
        }
//        pushf	;0x9c
        case 193:
//        popf	;0x9d
        case 194:
//        sahf	;0x9e
        case 195:
//        lahf	;0x9f
        case 196:
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//        mov al,[0xa0]	;0xa0
        case 197:
//        mov ax,[0xa1a1]	;0xa1
        case 198:
//        mov [0xa2],al	;0xa2
        case 199:
//        mov	[0xa3a3],ax	;0xa3
        case 200:

//        movsb	;0xa4
        case 201:
//        movsw	;0xa5
        case 202:
//        cmpsb	;0xa6
        case 203:
//        cmpsw	;0xa7
        case 204:

//        test al,0xa8	;0xa8
        case 205:
//        test ax,0xa9a9	;0xa9
        case 206:
//        stosb 	;0xaa
        case 207:
//        stosw 	;0xab
        case 208:
//        lodsb 	;0xac
        case 209:
//        lodsw 	;0xad
        case 210:
//        scasb 	;0xae
        case 211:
//        scasw 	;0xaf
        case 212:
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//        mov al,0xb0	;0xb0
        case 213:
//        mov cl,0xb1	;0xb1
        case 214:
//        mov dl,0xb2	;0xb2
        case 215:
//        mov bl,0xb3	;0xb3
        case 216:
//        mov ah,0xb4	;0xb4
        case 217:
//        mov ch,0xb5	;0xb5
        case 218:
//        mov dh,0xb6	;0xb6
        case 219:
//        mov bh,0xb7	;0xb7
        case 220:

//        mov ax,0xb8b8	;0xb8
        case 221:
//        mov cx,0xb9b9	;0xb9
        case 222:
//        mov dx,0xbaba	;0xba
        case 223:
//        mov bx,0xbbbb	;0xbb
        case 224:
//        mov sp,0xbcbc	;0xbc
        case 225:
//        mov bp,0xbdbd	;0xbd
        case 226:
//        mov si,0xbebe	;0xbe
        case 227:
//        mov di,0xbfbf	;0xbf
        case 228:
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//        ;group 2 0xc0
//        rol al,10	;000b
        case 229:
//        ror al,10	;001b
        case 230:
//        rcl al,10	;010b
        case 231:
//        rcr al,10	;011b
        case 232:
//        shl al,10	;100b
        case 233:
//        shr al,10	;101b
        case 234:
//        shl al,10	;110b
        case 235:
//        sar al,10	;111b
        case 236:
//        ;group 2 0xc1
//        rol ax,10	;000b
        case 237:
//        ror ax,10	;001b
        case 238:
//        rcl ax,10	;010b
        case 239:
//        rcr ax,10	;011b
        case 240:
//        shl ax,10	;100b
        case 241:
//        shr ax,10	;101b
        case 242:
//        shl ax,10	;110b
        case 243:
//        sar ax,10	;111b
        case 244:

//        ret 0xc2c2	;0xc2
        case 245:
//        ret	;0xc3
        case 246:
//        les di,[0xc4c4]	;0xc4
        case 247:
//        lds si,[0xc5c5]	;0xc5
        case 248:

//        ;group 11 ;0xc6
//        mov al,0xc6
        case 249:
//        ;group 11 0xc7
//        mov dx,0xc7c7
        case 250:

//        enter 0xc8c8,0xc8	;0xc8
        case 251:
//        leave	;0xc9
        case 252:
//        retf 0xcaca	;0xca
        case 253:
//        retf ;0xcb
        case 254:

//        int3	;0xcc
        case 255:
//        int 0xcd	;0xcd
        case 256:
//        into	;0xce
        case 257:
//        iret	;0xcf
        case 258:
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//        ;Group 2 d0
//        rol al,1	;000b
        case 259:
//        ror al,1	;001b
        case 260:
//        rcl al,1	;010b
        case 261:
//        rcr al,1	;011b
        case 262:
//        shl al,1	;100b
        case 263:
//        shr al,1	;101b
        case 264:
//        shl al,1	;110b
        case 265:
//        sar al,1	;111b
        case 266:
//        ;Group 2 d1
//        rol ax,1	;000b
        case 267:
//        ror ax,1	;001b
        case 268:
//        rcl ax,1	;010b
        case 269:
//        rcr ax,1	;011b
        case 270:
//        shl ax,1	;100b
        case 271:
//        shr ax,1	;101b
        case 272:
//        shl ax,1	;110b
        case 273:
//        sar ax,1	;111b
        case 274:
//        ;Group 2 d2
//        rol al,cl	;000b
        case 275:
//        ror al,cl	;001b
        case 276:
//        rcl al,cl	;010b
        case 277:
//        rcr al,cl	;011b
        case 278:
//        shl al,cl	;100b
        case 279:
//        shr al,cl	;101b
        case 280:
//        shl al,cl	;110b
        case 281:
//        sar al,cl	;111b
        case 282:
//        ;Group 2 d3
//        rol bx,cl	;000b
        case 283:
//        ror bx,cl	;001b
        case 284:
//        rcl bx,cl	;010b
        case 285:
//        rcr bx,cl	;011b
        case 286:
//        shl bx,cl	;100b
        case 287:
//        shr bx,cl	;101b
        case 288:
//        shl bx,cl	;110b
        case 289:
//        sar bx,cl	;111b
        case 290:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);
            break;
        }
//        aam	;0xd4
        case 291:
//        aad	;0xd5
        case 292:
//        salc	;0xd6
        case 293:
        {
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            break;
        }
//        xlat	;0xd7
        case 294:
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//    label2:
//        loopnz label2	;0xe0
        case 295:
//        loopz label2	;0xe1
        case 296:
//        loop label2		;0xe2
        case 297:
//        jcxz label2		;0xe3
        case 298:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);
            break;
        }
//        in al,0xe4		;0xe4
        case 299:
//        in ax,0xe5		;0xe5
        case 300:

//        out 0xe6,al		;0xe6
        case 301:
//        out 0xe7,ax		;0xe7
        case 302:
        {
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            break;
        }

//        call label2		;0xe8
        case 303:
//        jmp label		;0xe9
        case 304:
//        jmp 0xeaea:0xeaea	;0xea
        case 305:
//        jmp label2		;0xeb
        case 306:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);
            break;
        }
//        in al,dx	;0xec
        case 307:
//        in ax,dx	;0xed
        case 308:
//        out dx,al	;0xee
        case 309:
//        out dx,ax	;0xef
        case 310:
        {
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            break;
        }
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//        lock add [0xf0f0],ax	;0xf0
        case 311:
//        int1	;0xf1
        case 312:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);
            break;
        }
//        repnz insd	;0xf2
        case 313:
//        rep	insd	;0xf3
        case 314:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            break;
        }
//        hlt			;0xf4
        case 315:
        {
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            break;
        }
//        cmc			;0xf5
        case 316:
//        ;Group 3 0xf6
//        test byte[0xf6f6],0xf6	;000b
        case 317:
//        not byte[0xf6f6]	;010b
        case 318:
//        neg byte[0xf6f6]	;011b
        case 319:
//        mul byte[0xf6f6]	;100b
        case 320:
//        imul byte[0xf6f6]	;101b
        case 321:
//        div byte[0xf6f6]	;110b
        case 322:
//        idiv byte[0xf6f6]	;111b
        case 323:
//        ;Group 3 0xf7
//        test word[0xf6f6],0xf6	;000b
        case 324:
//        not word[0xf6f6]	;010b
        case 325:
//        neg word[0xf6f6]	;011b
        case 326:
//        mul word[0xf6f6]	;100b
        case 327:
//        imul word[0xf6f6]	;101b
        case 328:
//        div word[0xf6f6]	;110b
        case 329:
//        idiv word[0xf6f6]	;111b
        case 330:
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//        clc	;0xf8
        case 331:
//        stc	;0xf9
        case 332:
//        cli	;0xfa
        case 333:
//        sti	;0xfb
        case 334:
//        cld	;0xfc
        case 335:
//        std	;0xfd
        case 336:
//        ;Group 4 0xfe
//        inc byte[0xfefe]
        case 337:
//        dec byte[0xfefe]
        case 338:
//        ;Group 5 0xff
//        inc word[0xffff]	;000b
        case 339:
//        dec word[0xffff]	;001b
        case 340:
//        call word[0xffff]	;010b
        case 341:
//        call far[0xffff]	;011b
        case 342:
//        jmp word[0xffff]	;100b
        case 343:
//        jmp far[0xffff]		;101b
        case 345:
//        push word[0xffff]	;110b
        case 346:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);
            break;
        }
        default:
            break;
        }
        count++;
    }
}

void TestInstructionExecuter::testAll2()
{
    InstructionStreamFromFile fromFile("test/asm/2.com");

    std::ofstream fout("test/asm/2.txt");

    RegisterFile registerFile;
    DebugMemory memory;
    IOPortList ioPortList(memory,registerFile);
    int count=0;
    while(!fromFile.eof())
    {

        InstructionLowLevelFormat lowFormat;
        InstructionHighLevelFormat highFormat;

        fromFile.startReadOneInstruction();
        InstructionDecoder::decode(fromFile,ENV_16_BITS,lowFormat,highFormat);
        fromFile.endReadOneInstruction();

        std::vector<u8> instOriginal=fromFile.readLastInstruction();
        std::vector<u8> instCreated;

        InstructionEncoder::encode(lowFormat,instCreated);

        {
            std::string ascii;
            hex2Ascii(instOriginal,ascii);
            fout<<"OriginalBinary:"<<ascii<<std::endl;
            std::cout<<"OriginalBinary:"<<ascii<<std::endl;;
        }
        {
            std::string ascii;
            hex2Ascii(instCreated,ascii);
            fout<<"OriginalCreated:"<<ascii<<std::endl;
            std::cout<<"OriginalCreated:"<<ascii<<std::endl;
        }

        QCOMPARE(instCreated.size(),instOriginal.size());
        for(uint i=0; i<instCreated.size(); i++)
        {
            QCOMPARE(instCreated[i],instOriginal[i]);
        }

        {
            InstructionToString toString;
            std::string inst;
            toString.toString(highFormat,inst);
            fout<<"ASM:"<<inst<<std::endl;
            std::cout<<"ASM:"<<inst<<std::endl;
        }

//        InstructionExecuter executer;
        ExecOperands operands;

        switch(count)
        {
//        org 100h
//    section .text
//    start:
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//        mov al,12h
        case 0:
        {
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            QCOMPARE(u32(registerFile.getGPR8Bits(RAX)),(u32)0x12);
            break;
        }
//        mov ax,1234h
        case 1:
        {
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            QCOMPARE(u32(registerFile.getGPR16Bits(RAX)),(u32)0x1234);
            break;
        }
//        mov eax,12345678h
        case 2:
        {
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            QCOMPARE(u32(registerFile.getGPR32Bits(RAX)),(u32)0x12345678);
            break;
        }
//        mov ds,dx
        case 3:
        {
            registerFile.setGPR16Bits(RDX,0x3321);

            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            QCOMPARE(u32(registerFile.getSR(DS)),(u32)0x3321);
            QCOMPARE(u32(registerFile.getSSR(DS)),(u32)0x33210);
            break;
        }

//        mov al,[bx+si]
        case 4:
        {
            //init.
            registerFile.setSR(DS,0x100);
            registerFile.setSSR(DS,0x1000);

            registerFile.setSR(SS,0x50);
            registerFile.setSSR(SS,0x500);

            registerFile.setGPR16Bits(RBX,0x100);
            registerFile.setGPR16Bits(RBP,0x200);

            registerFile.setGPR16Bits(RSI,0x10);
            registerFile.setGPR16Bits(RDI,0x20);

            memory.startAccess(memory.DEBUG_ACCESS);
            ::srand(0);
            for(u32 i=0; i<0x2000; i++)
            {
                memory.set8Bits(i,rand()&0xff);
            }
            memory.endAccess();

            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            memory.startAccess(memory.DEBUG_ACCESS);
            QCOMPARE(u32(registerFile.getGPR8Bits(RAX)),(u32)memory.get8Bits(0x1000+0x100+0x10));
            memory.endAccess();
            break;
        }
//        mov al,[bx+di]
        case 5:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            memory.startAccess(memory.DEBUG_ACCESS);
            QCOMPARE(u32(registerFile.getGPR8Bits(RAX)),(u32)memory.get8Bits(0x1000+0x100+0x20));
            memory.endAccess();
            break;
        }
//        mov al,[bp+si]
        case 6:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            memory.startAccess(memory.DEBUG_ACCESS);
            QCOMPARE(u32(registerFile.getGPR8Bits(RAX)),(u32)memory.get8Bits(0x500+0x200+0x10));
            memory.endAccess();
            break;
        }
//        mov al,[bp+di]
        case 7:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            memory.startAccess(memory.DEBUG_ACCESS);
            QCOMPARE(u32(registerFile.getGPR8Bits(RAX)),(u32)memory.get8Bits(0x500+0x200+0x20));
            memory.endAccess();
            break;
        }
//        mov al,[si]
        case 8:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            memory.startAccess(memory.DEBUG_ACCESS);
            QCOMPARE(u32(registerFile.getGPR8Bits(RAX)),(u32)memory.get8Bits(0x1000+0x10));
            memory.endAccess();
            break;
        }
//        mov al,[di]
        case 9:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            memory.startAccess(memory.DEBUG_ACCESS);
            QCOMPARE(u32(registerFile.getGPR8Bits(RAX)),(u32)memory.get8Bits(0x1000+0x20));
            memory.endAccess();
            break;
        }
//        mov al,[1234h]
        case 10:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            memory.startAccess(memory.DEBUG_ACCESS);
            QCOMPARE(u32(registerFile.getGPR8Bits(RAX)),(u32)memory.get8Bits(0x1000+0x1234));
            memory.endAccess();
            break;
        }
//        mov al,[bx]
        case 11:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            memory.startAccess(memory.DEBUG_ACCESS);
            QCOMPARE(u32(registerFile.getGPR8Bits(RAX)),(u32)memory.get8Bits(0x1000+0x100));
            memory.endAccess();
            break;
        }
//        mov ax,[bx+si+11h]
        case 12:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            memory.startAccess(memory.DEBUG_ACCESS);
            QCOMPARE(u32(registerFile.getGPR16Bits(RAX)),(u32)memory.get16Bits(0x1000+0x100+0x10+0x11));
            memory.endAccess();
            break;
        }
//        mov ax,[bx+di+22h]
        case 13:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            memory.startAccess(memory.DEBUG_ACCESS);
            QCOMPARE(u32(registerFile.getGPR16Bits(RAX)),(u32)memory.get16Bits(0x1000+0x100+0x20+0x22));
            memory.endAccess();
            break;
        }
//        mov ax,[bp+si+33h]
        case 14:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            memory.startAccess(memory.DEBUG_ACCESS);
            QCOMPARE(u32(registerFile.getGPR16Bits(RAX)),(u32)memory.get16Bits(0x500+0x200+0x10+0x33));
            memory.endAccess();
            break;
        }
//        mov ax,[bp+di+44h]
        case 15:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            memory.startAccess(memory.DEBUG_ACCESS);
            QCOMPARE(u32(registerFile.getGPR16Bits(RAX)),(u32)memory.get16Bits(0x500+0x200+0x20+0x44));
            memory.endAccess();
            break;
        }
//        mov ax,[si+55h]
        case 16:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            memory.startAccess(memory.DEBUG_ACCESS);
            QCOMPARE(u32(registerFile.getGPR16Bits(RAX)),(u32)memory.get16Bits(0x1000+0x10+0x55));
            memory.endAccess();
            break;
        }
//        mov ax,[di+66h]
        case 17:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            memory.startAccess(memory.DEBUG_ACCESS);
            QCOMPARE(u32(registerFile.getGPR16Bits(RAX)),(u32)memory.get16Bits(0x1000+0x20+0x66));
            memory.endAccess();
            break;
        }
//        mov ax,[bp+77h]
        case 18:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            memory.startAccess(memory.DEBUG_ACCESS);
            QCOMPARE(u32(registerFile.getGPR16Bits(RAX)),(u32)memory.get16Bits(0x500+0x200+0x77));
            memory.endAccess();
            break;
        }
//        mov ax,[bx-10h]
        case 19:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            memory.startAccess(memory.DEBUG_ACCESS);
            QCOMPARE(u32(registerFile.getGPR16Bits(RAX)),(u32)memory.get16Bits(0x1000+0x100-0x10));
            memory.endAccess();
            break;
        }
//        mov eax,[bx+si+1111h]
        case 20:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            memory.startAccess(memory.DEBUG_ACCESS);
            QCOMPARE(u32(registerFile.getGPR32Bits(RAX)),(u32)memory.get32Bits(0x1000+0x100+0x10+0x1111));
            memory.endAccess();
            break;
        }
//        mov eax,[bx+di+2222h]
        case 21:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            memory.startAccess(memory.DEBUG_ACCESS);
            QCOMPARE(u32(registerFile.getGPR32Bits(RAX)),(u32)memory.get32Bits(0x1000+0x100+0x20+0x2222));
            memory.endAccess();
            break;
        }
//        mov eax,[bp+si+3333h]
        case 22:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            memory.startAccess(memory.DEBUG_ACCESS);
            QCOMPARE(u32(registerFile.getGPR32Bits(RAX)),(u32)memory.get32Bits(0x500+0x200+0x10+0x3333));
            memory.endAccess();
            break;
        }
//        mov eax,[bp+di+4444h]
        case 23:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            memory.startAccess(memory.DEBUG_ACCESS);
            QCOMPARE(u32(registerFile.getGPR32Bits(RAX)),(u32)memory.get32Bits(0x500+0x200+0x20+0x4444));
            memory.endAccess();
            break;
        }
//        mov eax,[si+5555h]
        case 24:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            memory.startAccess(memory.DEBUG_ACCESS);
            QCOMPARE(u32(registerFile.getGPR32Bits(RAX)),(u32)memory.get32Bits(0x1000+0x10+0x5555));
            memory.endAccess();
            break;
        }
//        mov eax,[di+6666h]
        case 25:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            memory.startAccess(memory.DEBUG_ACCESS);
            QCOMPARE(u32(registerFile.getGPR32Bits(RAX)),(u32)memory.get32Bits(0x1000+0x20+0x6666));
            memory.endAccess();
            break;
        }
//        mov eax,[bp+7777h]
        case 26:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            memory.startAccess(memory.DEBUG_ACCESS);
            QCOMPARE(u32(registerFile.getGPR32Bits(RAX)),(u32)memory.get32Bits(0x500+0x100+0x7777));
            memory.endAccess();
            break;
        }
//        mov eax,[bx-1h]
        case 27:
        {
            //execute
            InstructionExecuter::addressing(highFormat,registerFile,memory,operands);
            InstructionExecuter::execute(highFormat,registerFile,memory,ioPortList,operands);

            //verify
            memory.startAccess(memory.DEBUG_ACCESS);
            QCOMPARE(u32(registerFile.getGPR32Bits(RAX)),(u32)memory.get32Bits(0x1000+0x100-0x1));
            memory.endAccess();
            break;
        }
        default:
            break;
        }
        count++;
    }
}
