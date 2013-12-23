	org 100h
section .text
start:
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov al,12h
	mov ax,1234h
	mov eax,12345678h

	mov ds,dx

	mov al,[bx+si]
	mov al,[bx+di]
	mov al,[bp+si]
	mov al,[bp+di]
	mov al,[si]
	mov al,[di]
	mov al,[1234h]
	mov al,[bx]

	mov ax,[bx+si+11h]
	mov ax,[bx+di+22h]
	mov ax,[bp+si+33h]
	mov ax,[bp+di+44h]
	mov ax,[si+55h]
	mov ax,[di+66h]
	mov ax,[bp+77h]
	mov ax,[bx-10h]

	mov eax,[bx+si+1111h]
	mov eax,[bx+di+2222h]
	mov eax,[bp+si+3333h]
	mov eax,[bp+di+4444h]
	mov eax,[si+5555h]
	mov eax,[di+6666h]
	mov eax,[bp+7777h]
	mov eax,[bx-1h]

	
