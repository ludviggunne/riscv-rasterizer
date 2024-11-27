	.macro	nops n
	.rept	\n
	nop
	.endr
	.endm

;
; void joybus_client_recv(unsigned char pin,
;		void *recv_buf, unsigned char *recv_length)
;
	.global	joybus_client_recv
	.type	joybus_client_recv, @function
joybus_client_recv:
	; save status register
	in	r0, 0x3F	; 2c
	push	r0		; 2c

	; save frame pointer
	push	r29		; 2c
	push	r28		; 2c

	; save arguments
	; recv_length
	push	r21		; 2c
	push	r20		; 2c
	; recv_buf
	push	r23		; 2c
	push	r22		; 2c
	; pin
	push	r24		; 2c

	; load pin argument
	pop	r21		; 2c

	; set port address
	ldi	r30, 0x29	; 1c
	ldi	r31, 0x00	; 1c
	sbrc	r21, 3		; 2c taken, 1c not taken
	subi	r30, 0x06	; 1c
	andi	r21, 7		; 1c

	; set pin masks
	ldi	r22, 0		; 1c
	sec			; 1c
pin_shift_loop:
	rol	r22		; 1c
	dec	r21		; 1c
	brpl	pin_shift_loop	; 2c taken, 1c not taken
	mov	r23, r22	; 1c
	com	r23		; 1c

	; load recv arguments
	; recv_buf
	pop	r26		; 2c
	pop	r27		; 2c
	; recv_length
	pop	r28		; 2c
	pop	r29		; 2c

	; disable interrupts
	cli			; 1c

	; set pin as input
	ldd	r0, Z+2		; 2c
	or	r0, r22		; 1c
	std	Z+2, r0		; 2c
	ldd	r0, Z+1		; 2c
	and	r0, r23		; 1c
	std	Z+1, r0		; 2c

	; init byte counter
	ldi	r18, 0		; 1c
	; init byte
	ldi	r20, 0		; 1c

	; wait for initial falling edge
rx_start_loop:
	ldd	r0, Z+0		; 2c
	and	r0, r22		; 1c
	brne	rx_start_loop	; 2c taken, 1c not taken
	; lo 2c
	nops	10		; 10c

rx_byte_loop:
	; lo 12c
	; init bit counter
	ldi	r19, 8		; 1c

rx_bit_loop:
	; lo 13c
	lsl	r20		; 1c
	; lo 14c
	nops	18		; 18c
	; lo+data 32c (2µs)
	; sample bit
	ldd	r0, Z+0		; 2c
	and	r0, r22		; 1c
	breq	rx_0		; 2c taken, 1c not taken
	ori	r20, 1		; 1c
	rjmp	rx_1		; 2c

rx_0:
	; wait for line high
	ldd	r0, Z+0		; 2c
	and	r0, r22		; 1c
	breq	rx_0		; 2c taken, 1c not taken

rx_1:
	; wait for falling edge, ~3µs timeout
	ldi	r21, 7		; 1c

rx_fall_loop:
	dec	r21		; 1c
	breq	rx_tout		; 2c taken, 1c not taken
	ldd	r0, Z+0		; 2c
	and	r0, r22		; 1c
	brne	rx_fall_loop	; 2c taken, 1c not taken
	; bit loop latch
	; lo 4c
	dec	r19		; 1c
	; lo 5c
	breq	rx_bit_loop_end	; 2c taken, 1c not taken
	; lo 6c
	nops	5		; 5c
	; lo 11c
	rjmp	rx_bit_loop	; 2c

rx_bit_loop_end:
	; lo 7c
	; store byte
	st	X+, r20		; 2c
	; lo 9c
	; byte loop latch
	inc	r18		; 1c
	; lo 10c
	rjmp	rx_byte_loop	; 2c taken, 1c not taken

rx_tout:
	; store byte count
	st	Y, r18		; 2c

	; restore frame pointer
	pop	r28		; 2c
	pop	r29		; 2c

	; restore status register
	pop	r0		; 2c
	out	0x3F, r0	; 2c

	; return
	ret			; 4c
	.size	joybus_client_recv, . - joybus_client_recv
