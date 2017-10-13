.686                               		; create 32 bit code
.model flat, C                      	; 32 bit memory model
 option casemap:none                	; case sensitive

.data
	g DD 4
.code

public			min						; Function Begins

function_min0:
				push 	ebp				; Push Frame Pointer
				mov     ebp, esp        ; update ebp
				sub     esp, 4          ; space for local variables
				; Non Volatile registers to be saved here but non exist
				
				mov		eax, [esp+8]	; v=a
				mov 	[ebp-4], eax	;  "
				
				mov 	eax, [ebp+12]	; if(b < v)
				cmp 	eax, [ebp-4]
				jge 	function_min1
				mov 	eax, [ebp+12]	; v = b
				mov 	[ebp-4], eax
				
function_min1:	mov		eax, [ebp+16]	; if(c < v)
				cmp		eax, [ebp-4]
				jge		funciton_min2
				mov		eax, [abp+16]	; v = c
				mov		[ebp-4], eax

function_min2:	mov 	eax, [ebp-4]	; Function Exit
				mov 	esp, ebp
				pop 	ebp
				ret 	0




public			 p						; Function Begins

function_p0:	push 	ebp				; Push Frame Pointer
				mov     ebp, esp        ; update ebp
				sub     esp, 4          ; space for local variables 
				; Non Volatile registers to be saved here but non exist

				push    [ebp+12]		; min(g, i, j)
				push	[ebp+8]
				push	[g]
				call	function_min
				add		esp, 12
				mov		[ebp-4], eax

				push	[ebp+20]		; min(min(g, i, j), k, l)
				push	[ebp+16]
				push	[ebp-4]
				call	function_min
				add		esp, 12

				mov 	esp, ebp
				pop 	ebp
				ret 	0



public			gcd						; Function Begins

function_gcd0:	push 	ebp				; Push Frame Pointer
				mov     ebp, esp        ; update ebp
				sub     esp, 4          ; space for local variables
				; Non Volatile registers to be saved here but non exist

				mov		eax, [ebp+12]
				mov		[ebp-4], eax
				xor		eax, eax
				jne		function_gcd1
				mov		eax, [ebp+8]
				mov 	esp, ebp
				pop 	ebp
				ret 	0

function_gcd1:	xor		edx,edx
				mov		eax,[ebp+8]     ; eax = a
				mov		ecx,[ebp+12]    ; ecx = b
				div		ecx             ; a/b
				mov		eax,edx         ; remainder(a mod b)

				push	eax
				mov		ebx, [ebp+12]
				push	ebx
				call	function_gdc
				add		esp, 8

				mov 	esp, ebp
				pop 	ebp
				ret 	0