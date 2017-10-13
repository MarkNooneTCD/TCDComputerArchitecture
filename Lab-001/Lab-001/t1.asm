.686                               		; create 32 bit code
.model flat, C                      	; 32 bit memory model
 option casemap:none                	; case sensitive

.data
	g DD 4
.code

public			min						; Function Begins

min:
				push 	ebp				; Push Frame Pointer
				mov     ebp, esp        ; update ebp
				sub     esp, 4          ; space for local variables
				; Non Volatile registers to be saved here but non exist
				
				mov		eax, [ebp+8]	; v=a
				mov 	[ebp-4], eax	;  "
				
				mov 	eax, [ebp+12]	; if(b < v)
				cmp 	eax, [ebp-4]
				jge 	min1
				mov 	eax, [ebp+12]	; v = b
				mov 	[ebp-4], eax
				jmp		min1
				
min1:			
				mov		eax, [ebp+16]	; if(c < v)
				cmp		eax, [ebp-4]
				jge		min2
				mov		eax, [ebp+16]	; v = c
				mov		[ebp-4], eax
				jmp		min2

min2:			
				mov 	eax, [ebp-4]	; Function Exit
				mov 	esp, ebp
				pop 	ebp
				ret 	0




public			 p						; Function Begins

p:	
				push 	ebp				; Push Frame Pointer
				mov     ebp, esp        ; update ebp
				sub     esp, 4          ; space for local variables 
				; Non Volatile registers to be saved here but non exist

				push    [ebp+12]		; min(g, i, j)
				push	[ebp+8]
				push	[g]
				call	min
				add		esp, 12
				mov		[ebp-4], eax

				push	[ebp+20]		; min(min(g, i, j), k, l)
				push	[ebp+16]
				push	[ebp-4]
				call	min
				add		esp, 12

				mov 	esp, ebp
				pop 	ebp
				ret 	0



public			gcd						; Function Begins

gcd:	
				push 	ebp				; Push Frame Pointer
				mov     ebp, esp        ; update ebp
				sub     esp, 4          ; space for local variables
				; Non Volatile registers to be saved here but non exist

				mov		eax, [ebp+12]
				mov		[ebp-4], eax
				xor		eax, eax
				cmp		eax, [ebp-4]
				jne		gcd1
				mov		eax, [ebp+8]
				mov 	esp, ebp
				pop 	ebp
				ret 	0

gcd1:	
				
				mov		eax, [ebp+12]
				push	eax
				mov		eax, [ebp+8]
				push	eax
				call	modulus
				add		esp, 8

				push	eax
				mov		eax, [ebp+12]
				push	eax
				call	gcd
				add		esp, 8

				mov 	esp, ebp
				pop 	ebp
				ret 	0


public			modulus

modulus:
				push 	ebp				; Push Frame Pointer
				mov     ebp, esp        ; update ebp
				sub     esp, 4          ; space for local variables

				xor		edx,edx
				mov		eax,[ebp+8]     ; eax = a
				mov		ecx,[ebp+12]    ; ecx = b
				div		ecx             ; a/b
				mov		eax,edx         ; remainder(a mod b)

				mov 	esp, ebp
				pop 	ebp
				ret 	0

end