option casemap:none
includelib legacy_stdio_definitions.lib
extrn printf:near

.data
	g:
	DD 4
	
.code

;
;	Tutorial 2 - x64 Min, P and GCD
;
;	Author - Mark Noone
;

public	minx64

minx64:	mov		rax, rcx			; v = a
		cmp		rax, rdx
		jle		min1
		mov		rax, rdx
min1:	cmp		rax, r8
		jle		min2
		mov		rax, r8
min2:	ret		


public	px64

px64:	mov		r10,g
		mov		r12, r8

		mov		r8,  rdx
		mov		rdx, rcx
		mov		rcx, [r10]
		call	minx64

		mov		rcx, rax
		mov		rdx, r12
		mov		r8,	 r9
		call	minx64

		ret		
		

public	gcdx64

gcdx64:	xor		rax, rax
		cmp     rax, rdx
		jne		gcd1
		mov		rax, rcx
		ret 	

gcd1:	mov		rax, rcx 
		mov		rcx, rdx
		xor		rdx, rdx
		idiv	rcx    
		call	gcdx64

		ret 	


fxp2 db 'a = %I64d, b = %I64d, c = %I64d, d = %I64d, e = %I64d, a+b+c+d+e = %I64d', 0AH, 00H
public	qx64

qx64:	
		xor		r11, r11
		mov		r12, [rsp+40]
		add		r11, r12
		add		r11, r9
		add		r11, r8
		add		r11, rdx
		add		r11, rcx
		
		push	r11
		push	r12
		push	r9

		mov		r9, r8
		mov		r8, rdx
		mov		rdx, rcx
		lea		rcx, fxp2
		sub		rsp, 32
		call	printf	
		add		rsp, 48
		pop		rax
		ret


end