#include "testinstructionexecuter.h"
#include "cpu/decoder/instructiondecoder.h"
#include "cpu/encoder/instructionencoder.h"
#include "cpu/decoder/instructionstreamfromfile.h"
#include "cpu/tostring/instructiontostring.h"
#include <iostream>
#include "cpu/executer/instructionexecuter.h"
#include "memory/debugmemory.h"

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
    InstructionStreamFromFile fromFile("../asm/1.com");

    std::ofstream fout("../asm/1.txt");

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

//        add ax,[3]	;0x03

//        add al,4	;0x04
//        add ax,5	;0x05

//        push es	;0x06
//        pop es	;0x07

//        or al,al 	;0x08
//        or [0],al 	;0x08

//        or ax,ax 	;0x09
//        or [1],ax 	;0x09

//        or al,[2] 	;0x0a

//        or ax,[3]	;0x0b

//        or al,4	;0x0c
//        or ax,5	;0x0d

//        push cs	;0x0e
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//        adc al,al 	;0x10
//        adc [0],al 	;0x10

//        adc ax,ax 	;0x11
//        adc [1],ax 	;0x11

//        adc al,[2] 	;0x12

//        adc ax,[3]	;0x13

//        adc al,4	;0x14
//        adc ax,5	;0x15

//        push ss	;0x16
//        pop ss	;0x17

//        sbb al,al 	;0x18
//        sbb [0],al 	;0x18

//        sbb ax,ax 	;0x19
//        sbb [1],ax 	;0x19

//        sbb al,[2] 	;0x1a

//        sbb ax,[3]	;0x1b

//        sbb al,4	;0x1c
//        sbb ax,5	;0x1d

//        push ds	;0x1e
//        pop ds	;0x1f
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//        and al,al 	;0x20
//        and [0],al 	;0x20

//        and ax,ax 	;0x21
//        and [1],ax 	;0x21

//        and al,[2] 	;0x22

//        and ax,[3]	;0x23

//        and al,4	;0x24
//        and ax,5	;0x25

//        and [es:0],al	;0x26
//        DAA	;0x27

//        sub al,al 	;0x28
//        sub [0],al 	;0x28

//        sub ax,ax 	;0x29
//        sub [1],ax 	;0x29

//        sub al,[2] 	;0x2a

//        sub ax,[3]	;0x2b

//        sub al,4	;0x2c
//        sub ax,5	;0x2d

//        sub al,[cs:2]	;0x2e
//        DAS	;0x2f
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//        xor al,al 	;0x30
//        xor [0],al 	;0x30

//        xor ax,ax 	;0x31
//        xor [1],ax 	;0x31

//        xor al,[2] 	;0x32

//        xor ax,[3]	;0x33

//        xor al,4	;0x34
//        xor ax,5	;0x35

//        xor ax,[ss:3]	;0x36
//        AAA	;0x37

//        cmp al,al 	;0x38
//        cmp [0],al 	;0x38

//        cmp ax,ax 	;0x39
//        cmp [1],ax 	;0x39

//        cmp al,[2] 	;0x3a

//        cmp ax,[3]	;0x3b

//        cmp al,4	;0x3c
//        cmp ax,5	;0x3d

//        cmp al,[ds:2]	;0x3e
//        AAS	;0x3f
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//        inc ax	;0x40
//        inc cx	;0x41
//        inc dx	;0x42
//        inc bx	;0x43
//        inc sp	;0x44
//        inc bp	;0x45
//        inc si	;0x46
//        inc di	;0x47

//        dec ax	;0x48
//        dec cx	;0x49
//        dec dx	;0x4a
//        dec bx	;0x4b
//        dec sp	;0x4c
//        dec bp	;0x4d
//        dec si	;0x4e
//        dec di	;0x4f
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//        push ax	;0x50
//        push cx	;0x51
//        push dx	;0x52
//        push bx	;0x53
//        push sp	;0x54
//        push bp	;0x55
//        push si	;0x56
//        push di	;0x57

//        pop ax	;0x58
//        pop cx	;0x59
//        pop dx	;0x5a
//        pop bx	;0x5b
//        pop sp	;0x5c
//        pop bp	;0x5d
//        pop si	;0x5e
//        pop di	;0x5f
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//        pusha	;0x60
//        popa	;0x61
//        bound ax,[0x62]	;0x62
//        arpl ax,ax	;0x63
//        bound ax,[fs:0x64]	;0x64
//        bound ax,[gs:0x65]	;0x65
//        bound eax,[0x66]	;0x66
//        bound ax,[eax+0x67]	;0x67

//        push 0x6868	;0x68
//        imul ax,[0x69],0x6969	;0x69
//        push 0x6a	;0x6a
//        imul ax,[0x6b],0x6b	;0x6b
//        insb	;0x6c
//        insw	;0x6d
//        outsb	;0x6e
//        outsw	;0x6f
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//    label:
//        jo label	;0x70
//        jno label	;0x71
//        jb label	;0x72
//        jnb label	;0x73
//        jz label	;0x74
//        jnz label	;0x75
//        jbe label	;0x76
//        jnbe label	;0x77

//        js label	;0x78
//        jns label	;0x79
//        jp label	;0x7a
//        jnp label	;0x7b
//        jl label	;0x7c
//        jnl label	;0x7d
//        jle label	;0x7e
//        jnle label	;0x7f
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//        ;Group 1 0x80
//        add byte[0x80],byte 0x80	;000b
//        or  byte[0x80],byte 0x80	;001b
//        adc byte[0x80],byte 0x80	;010b
//        sbb byte[0x80],byte 0x80	;011b
//        and byte[0x80],byte 0x80	;100b
//        sub byte[0x80],byte 0x80	;101b
//        xor byte[0x80],byte 0x80	;110b
//        cmp byte[0x80],byte 0x80	;111b
//        ;Group 1 0x81
//        add word[0x81],0x8181	;000b
//        or  word[0x81],0x8181	;001b
//        adc word[0x81],0x8181	;010b
//        sbb word[0x81],0x8181	;011b
//        and word[0x81],0x8181	;100b
//        sub word[0x81],0x8181	;101b
//        xor word[0x81],0x8181	;110b
//        cmp word[0x81],0x8181	;111b
//        ;Group 1 0x82
//        ;Group 1 0x83
//        add word[0x80],byte -0x80	;000b
//        or  word[0x80],byte -0x80	;001b
//        adc word[0x80],byte -0x80	;010b
//        sbb word[0x80],byte -0x80	;011b
//        and word[0x80],byte -0x80	;100b
//        sub word[0x80],byte -0x80	;101b
//        xor word[0x80],byte -0x80	;110b
//        cmp word[0x80],byte -0x80	;111b

//        test byte[0x84],al	;0x84
//        test word[0x85],ax	;0x85
//        xchg byte[0x86],bl	;0x86
//        xchg word[0x87],bx	;0x87

//        mov [0x88],bl	;0x88
//        mov [0x89],cx	;0x89
//        mov dl,[0x8a]	;0x8a
//        mov ax,[0x8b]	;0x8b
//        mov [0x8c],cs	;0x8c
//        lea si,[bx+si+0x8d]	;0x8d
//        mov ds,[0x8e]	;0x8e
//        ;Group 1a
//        pop bp	;000b
//        pop	word[0x8f]	;000b
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//        nop	;0x90
//        pause	;0x90
//        xchg cx,ax	;0x91
//        xchg dx,ax	;0x92
//        xchg bx,ax	;0x93
//        xchg sp,ax	;0x94
//        xchg bp,ax	;0x95
//        xchg si,ax	;0x96
//        xchg di,ax	;0x97

//        cbw	;0x98
//        cwd	;0x99
//        call 0x9a:0x9a9a	;0x9a
//        wait	;0x9b
//        pushf	;0x9c
//        popf	;0x9d
//        sahf	;0x9e
//        lahf	;0x9f
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//        mov al,[0xa0]	;0xa0
//        mov ax,[0xa1a1]	;0xa1
//        mov [0xa2],al	;0xa2
//        mov	[0xa3a3],ax	;0xa3

//        movsb	;0xa4
//        movsw	;0xa5
//        cmpsb	;0xa6
//        cmpsw	;0xa7

//        test al,0xa8	;0xa8
//        test ax,0xa9a9	;0xa9
//        stosb 	;0xaa
//        stosw 	;0xab
//        lodsb 	;0xac
//        lodsw 	;0xad
//        scasb 	;0xae
//        scasw 	;0xaf
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//        mov al,0xb0	;0xb0
//        mov cl,0xb1	;0xb1
//        mov dl,0xb2	;0xb2
//        mov bl,0xb3	;0xb3
//        mov ah,0xb4	;0xb4
//        mov ch,0xb5	;0xb5
//        mov dh,0xb6	;0xb6
//        mov bh,0xb7	;0xb7

//        mov ax,0xb8b8	;0xb8
//        mov cx,0xb9b9	;0xb9
//        mov dx,0xbaba	;0xba
//        mov bx,0xbbbb	;0xbb
//        mov sp,0xbcbc	;0xbc
//        mov bp,0xbdbd	;0xbd
//        mov si,0xbebe	;0xbe
//        mov di,0xbfbf	;0xbf
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//        ;group 2 0xc0
//        rol al,10	;000b
//        ror al,10	;001b
//        rcl al,10	;010b
//        rcr al,10	;011b
//        shl al,10	;100b
//        shr al,10	;101b
//        shl al,10	;110b
//        sar al,10	;111b
//        ;group 2 0xc1
//        rol ax,10	;000b
//        ror ax,10	;001b
//        rcl ax,10	;010b
//        rcr ax,10	;011b
//        shl ax,10	;100b
//        shr ax,10	;101b
//        shl ax,10	;110b
//        sar ax,10	;111b

//        ret 0xc2c2	;0xc2
//        ret	;0xc3
//        les di,[0xc4c4]	;0xc4
//        lds si,[0xc5c5]	;0xc5

//        ;group 11 ;0xc6
//        mov al,0xc6
//        ;group 11 0xc7
//        mov dx,0xc7c7

//        enter 0xc8c8,0xc8	;0xc8
//        leave	;0xc9
//        retf 0xcaca	;0xca
//        retf ;0xcb

//        int3	;0xcc
//        int 0xcd	;0xcd
//        into	;0xce
//        iret	;0xcf
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//        ;Group 2 d0
//        rol al,1	;000b
//        ror al,1	;001b
//        rcl al,1	;010b
//        rcr al,1	;011b
//        shl al,1	;100b
//        shr al,1	;101b
//        shl al,1	;110b
//        sar al,1	;111b
//        ;Group 2 d1
//        rol ax,1	;000b
//        ror ax,1	;001b
//        rcl ax,1	;010b
//        rcr ax,1	;011b
//        shl ax,1	;100b
//        shr ax,1	;101b
//        shl ax,1	;110b
//        sar ax,1	;111b
//        ;Group 2 d2
//        rol al,cl	;000b
//        ror al,cl	;001b
//        rcl al,cl	;010b
//        rcr al,cl	;011b
//        shl al,cl	;100b
//        shr al,cl	;101b
//        shl al,cl	;110b
//        sar al,cl	;111b
//        ;Group 2 d3
//        rol bx,cl	;000b
//        ror bx,cl	;001b
//        rcl bx,cl	;010b
//        rcr bx,cl	;011b
//        shl bx,cl	;100b
//        shr bx,cl	;101b
//        shl bx,cl	;110b
//        sar bx,cl	;111b

//        aam	;0xd4
//        aad	;0xd5
//        salc	;0xd6
//        xlat	;0xd7
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//    label2:
//        loopnz label2	;0xe0
//        loopz label2	;0xe1
//        loop label2		;0xe2
//        jcxz label2		;0xe3

//        in al,0xe4		;0xe4
//        in ax,0xe5		;0xe5

//        out 0xe6,al		;0xe6
//        out 0xe7,ax		;0xe7

//        call label2		;0xe8
//        jmp label		;0xe9
//        jmp 0xeaea:0xeaea	;0xea
//        jmp label2		;0xeb

//        in al,dx	;0xec
//        in ax,dx	;0xed
//        out dx,al	;0xee
//        out dx,ax	;0xef
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//        lock add [0xf0f0],ax	;0xf0
//        int1	;0xf1
//        repnz insd	;0xf2
//        rep	insd	;0xf3
//        hlt			;0xf4
//        cmc			;0xf5
//        ;Group 3 0xf6
//        test byte[0xf6f6],0xf6	;000b
//        not byte[0xf6f6]	;010b
//        neg byte[0xf6f6]	;011b
//        mul byte[0xf6f6]	;100b
//        imul byte[0xf6f6]	;101b
//        div byte[0xf6f6]	;110b
//        idiv byte[0xf6f6]	;111b
//        ;Group 3 0xf7
//        test word[0xf6f6],0xf6	;000b
//        not word[0xf6f6]	;010b
//        neg word[0xf6f6]	;011b
//        mul word[0xf6f6]	;100b
//        imul word[0xf6f6]	;101b
//        div word[0xf6f6]	;110b
//        idiv word[0xf6f6]	;111b
//        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//        clc	;0xf8
//        stc	;0xf9
//        cli	;0xfa
//        sti	;0xfb
//        cld	;0xfc
//        std	;0xfd
//        ;Group 4 0xfe
//        inc byte[0xfefe]
//        dec byte[0xfefe]
//        ;Group 5 0xff
//        inc word[0xffff]	;000b
//        dec word[0xffff]	;001b
//        call word[0xffff]	;010b
//        call far[0xffff]	;011b
//        jmp word[0xffff]	;100b
//        jmp far[0xffff]		;101b
//        push word[0xffff]	;110b
        default:
            break;
        }
        count++;
    }
}
