org 0xf0000

startOfTheFile:
int0:
	out 00h,al
	iret
int1:
	out 01h,al
	iret
int2:
	out 02h,al
	iret
int3:
	out 03h,al
	iret
int4:
	out 04h,al
	iret
int5:
	out 05h,al
	iret
int6:
	out 06h,al
	iret
int7:	
	out 07h,al
	iret
int8:
	out 08h,al
	iret
int9:
	out 09h,al
	iret
inta:
	out 0ah,al
	iret
intb:
	out 0bh,al
	iret
intc:
	out 0ch,al
	iret
intd:
	out 0dh,al
	iret
inte:
	out 0eh,al
	iret
intf:
	out 0fh,al
	iret
int10:
	out 10h,al
	iret
int11:
	out 11h,al
	iret
int12:
	out 12h,al
	iret
int13:
	out 13h,al
	iret
int14:
	out 14h,al
	iret
int15:
	out 15h,al
	iret
int16:
	out 16h,al
	iret
int17:
	out 17h,al
	iret
int18:
	out 18h,al
	iret
int19:
	out 19h,al
	iret
int1a:
	out 1ah,al
	iret
int1b:
	out 1bh,al
	iret
int1c:
	out 1ch,al
	iret
int1d:
	out 1dh,al
	iret
int1e:
	out 1eh,al
	iret
int1f:
	out 1fh,al
	iret
intnop:
	out 20h,al
	iret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;interrupt vector table.
THIS_SEGMENT equ 0xf000
startOFIVT:
dw int0,THIS_SEGMENT
dw int1,THIS_SEGMENT
dw int2,THIS_SEGMENT
dw int3,THIS_SEGMENT
dw int4,THIS_SEGMENT
dw int5,THIS_SEGMENT
dw int6,THIS_SEGMENT
dw int7,THIS_SEGMENT
dw int8,THIS_SEGMENT
dw int9,THIS_SEGMENT
dw inta,THIS_SEGMENT
dw intb,THIS_SEGMENT
dw intc,THIS_SEGMENT
dw intd,THIS_SEGMENT
dw inte,THIS_SEGMENT
dw intf,THIS_SEGMENT
dw int10,THIS_SEGMENT
dw int11,THIS_SEGMENT
dw int12,THIS_SEGMENT
dw int13,THIS_SEGMENT
dw int14,THIS_SEGMENT
dw int15,THIS_SEGMENT
dw int16,THIS_SEGMENT
dw int17,THIS_SEGMENT
dw int18,THIS_SEGMENT
dw int19,THIS_SEGMENT
dw int1a,THIS_SEGMENT
dw int1b,THIS_SEGMENT
dw int1c,THIS_SEGMENT
dw int1d,THIS_SEGMENT
dw int1e,THIS_SEGMENT
dw int1f,THIS_SEGMENT
times 0x100-0x20 dw intnop,THIS_SEGMENT
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
emulatorName: db "X86Emultor",0x0d,0x0a
url: db "http://github.com/logicworldzju/X86Emulator",0x0d,0x0a

separator: db 0x0d,0x0a,0x0d,0x0a
strEnd:

video:
	mov bh,0 ;page number(for text mode)
	mov bl,7 ;attribute for characters.(graphics mode)
	mov ah,0x13 ;function number.
	mov al,1 ;cursor mode.

	mov bp,emulatorName
	mov cx,strEnd-emulatorName
	mov dx,0
	int 10h

	ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
start:
	;init segment registers
	mov ax,cs
	mov ds,ax
	mov es,ax
	;init stack
	mov ax,0x1000
	mov ss,ax
	mov ax,0xf000
	mov sp,ax
	mov bp,ax
	;init interrupt vector table
	mov cx,0x400
	mov di,0
	xor ax,ax
	mov es,ax
	mov si,startOFIVT
	rep movsb
	mov ax,cs
	mov es,ax
	;init the video
	call video
	;read boot sector
	xor ax,ax
	mov es,ax
	mov ah,02h
	mov al,1
	mov cx,1
	mov dh,0
	mov dl,0
	mov bx,0x7c00
	int 13h
	;set registers
	xor ax,ax
	mov bx,0x0000
	mov dx,bx
	mov cx,1
	mov ss,ax
	mov ds,ax
	mov es,ax
	mov sp,ax
	sub sp,2
	mov bp,ax
	mov ax,0xaa55

	jmp 0x0:0x7c00
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
times 0xfff0-$+startOfTheFile  db 00h
firstInstruction:
	jmp 0xf000:start
times 0x10-$+firstInstruction db 00h
