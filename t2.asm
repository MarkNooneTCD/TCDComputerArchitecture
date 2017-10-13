option casemap:none

.data
	g DD 4
.code

;
;	Tutorial 2 - x64 Min, P and GCD
;
;	Author - Mark Noone
;

public	minx64

min0:	mov		rax, rcx			; v = a
		cmp		rax, rdx
		jge		min1
		mov		rax, rdx
min1:	cmp		rax, r8
		jge		min2
		mov		rax, r8
min2:	ret		0


;public	p

;p0:		push	rbp
;		mov		rbp, rsp
;		sub		rsp, 32
;		mov		r10, rcx
;		mov		r11, rdx
;		mov		r12, r8
;
;		mov		r8,  rdx
;		mov		rdx, rcx
;		mov		rcx, [g]
;		call	min
;
;		mov		rcx, rax
;		mov		rdx, r12
;		mov		r8,	 r9
;		call	min
;		ret		0
		

;public	gcd
;
;gcd0:	push 	ebp				; Push Frame Pointer
;		mov     ebp, esp        ; update ebp
;		sub     esp, 4          ; space for local variables
;
;		xor		eax, eax
;		jne		function_gcd1
;		mov		eax, [ebp+8]
;		mov 	esp, ebp
;		pop 	ebp
;		ret 	0
;
;gcd1:	xor		edx,edx
;		mov		eax,[ebp+8]     ; eax = a
;		mov		ecx,[ebp+12]    ; ecx = b
;		div		ecx             ; a/b
;		mov		eax,edx         ; remainder(a mod b)
;
;		push	eax
;		mov		ebx, [ebp+12]
;		push	ebx
;		call	function_gdc
;		add		esp, 8
;
;		mov 	esp, ebp
;		pop 	ebp
;		ret 	0
;
;
;public	q
;
;q0:		


end