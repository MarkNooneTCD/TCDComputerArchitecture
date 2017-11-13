// Non-optimised

		add		r0, #4, r3

min:		add		r0, r26, r1
		sub		r27, r16, r0{C}
		jge		min1
		xor 	r0, r0, r0
		add		r0, r27, r1
		
min1:		sub		r0, r28, r1
		jge		min2
		xor 	r0, r0, r0
		add		r0, r28, r1
		
min2:		ret		r25, r0
		xor 	r0, r0, r0

		
p:		add 	r0, r3, r10
		add 	r0, r26, r11
		add 	r0, r27, r12
		callr	r25, min
		xor 	r0, r0, r0
		add 	r0, r1, r10
		add 	r0, r28, r11
		add 	r0, r29, r12
		callr 	r25, min
		xor		r0, r0, r0
		ret		r25, r0
		xor 	r0, r0, r0
		
		
gcd:	sub		r27, r0, r0{C}
		jeq		gcd1
		xor		r0, r0, r0
		add 	r0, r26, r1
		ret		r25, r0
		xor		r0, r0, r0
gdc1:	add		r0, r27, r11
		add		r0, r26, r10
		callr	r25, mod
		xor 	r0, r0, r0
		add		r0, r1, r11
		add		r0, r27, r10
		callr	r25, gcd
		xor 	r0, r0, r0
		ret 	r25, r0
		xor 	r0, r0, r0
		

// Optimised

add		r0, #4, r3

min:		add		r0, r26, r1
		sub		r27, r16, r0{C}
		jge		min1
		xor 	r0, r0, r0
		add		r0, r27, r1
		
min1:		sub		r0, r28, r1
		jge		min2
		xor 	r0, r0, r0
		add		r0, r28, r1
		
min2:		ret		r25, r0
		xor 	r0, r0, r0

		
p:		add 	r0, r3, r10
		add 	r0, r26, r11
		callr	r25, min
		add 	r0, r27, r12
		add 	r0, r1, r10
		add 	r0, r28, r11
		callr 	r25, min
		add 	r0, r29, r12
		ret		r25, r0
		xor 	r0, r0, r0
		
		
gcd:		sub		r27, r0, r0{C}
		jeq		gcd1
		xor		r0, r0, r0
		ret		r25, r0
		add 	r0, r26, r1
gdc1:		add		r0, r27, r11
		callr	r25, mod
		add		r0, r26, r10
		add		r0, r1, r11
		callr	r25, gcd
		add		r0, r27, r10
		ret 	r25, r0
		xor 	r0, r0, r0
		
		
		