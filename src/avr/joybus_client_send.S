	.macro	nops n
	.rept	\n
	nop
	.endr
	.endm

;
; void joybus_client_send(unsigned char pin,
;		void *send_buf, unsigned char send_length)
;
	.global	joybus_client_send
	.type	joybus_client_send, @function
joybus_client_send:
	; save status register
	in	r0, 0x3F	; 2c
	push	r0		; 2c

	; save arguments
	; send_length
	push	r20		; 2c
	; send_buf
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

	; load send arguments
	; send_buf
	pop	r26		; 2c
	pop	r27		; 2c
	; send_length
	pop	r18		; 2c

	; set pin set/clr port values
	ldd	r24, Z+2	; 2c
	mov	r25, r24	; 1c
	or	r24, r22	; 1c
	and	r25, r23	; 1c

	; disable interrupts
	cli			; 1c

	; set pin as output
	std	Z+2, r24	; 2c
	ldd	r0, Z+1		; 2c
	or	r0, r22		; 1c
	std	Z+1, r0		; 2c

tx_byte_loop:
	; hi 42c / 10c
	; init bit counter
	ldi	r19, 8		; 1c
	; hi 43c / 11c
	; read next byte
	ld	r20, X+		; 2c

tx_bit_loop:
	; hi 45c / 13c
	rol	r20		; 1c
	; hi 46c / 14c
	brcc	tx_0		; 2c taken, 1c not taken

	; hi 47c / 15c
	nops	1		; 1c
	; hi 48c / 16c (3µs / 1µs)
	; transmit 1 bit
	std	Z+2, r25	; 2c
	; lo 2c
	nops	14		; 14c
	; lo 16c (1µs)
	std	Z+2, r24	; 2c
	; hi 2c
	nops	31		; 31c
	; hi 33c
	rjmp	tx_1		; 2c

tx_0:
	; hi 48c / 16c (3µs / 1µs)
	; transmit 0 bit
	std	Z+2, r25	; 2c
	; lo 2c
	nops	46		; 46c
	; lo 48c (3µs)
	std	Z+2, r24	; 2c
	; hi 2c
	nops	1		; 1c

tx_1:
	; hi 35c / 3c
	; bit loop latch
	dec	r19		; 1c
	; hi 36c / 4c
	breq	tx_bit_loop_end	; 2c taken, 1c not taken
	; hi 37c / 5c
	nops	6		; 6c
	; hi 43c / 11c
	rjmp	tx_bit_loop	; 2c

tx_bit_loop_end:
	; hi 38c / 6c
	; byte loop latch
	dec	r18		; 1c
	; hi 39c / 7c
	breq	tx_byte_loop_end; 2c taken, 1c not taken
	; hi 40c / 8c
	rjmp	tx_byte_loop	; 2c

tx_byte_loop_end:
	; hi 41c / 9c
	nops	7		; 7c
	; hi 48c / 16c (3µs / 1µs)
	; transmit stop bit
	std	Z+2, r25	; 2c
	; lo 2c
	nops	30		; 30c
	; lo 32c (2µs)
	std	Z+2, r24	; 2c

	; restore status register
	pop	r0		; 2c
	out	0x3F, r0	; 2c

	; return
	ret			; 4c
	.size	joybus_client_send, . - joybus_client_send
