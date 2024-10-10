.macro  nops n
  .rept   \n
    nop
  .endr
.endm


;
; void pif_host_transmit(uint8_t pin,
;                        void *send_buf, uint8_t send_length,
;                        void *recv_buf, uint8_t recv_length);
;
.global	pif_host_transmit
.type	  pif_host_transmit, @function
pif_host_transmit:
  ; save status register
  in      r0, 0x3F              ; 2c
  push    r0                    ; 2c

  ; save arguments
  ; recv_length
  push    r16                   ; 2c
  ; recv_buf
  push    r19                   ; 2c
  push    r18                   ; 2c
  ; send_length
  push    r20                   ; 2c
  ; send_buf
  push    r23                   ; 2c
  push    r22                   ; 2c
  ; pin
  push    r24                   ; 2c

  ; load pin argument
  pop     r21                   ; 2c

  ; set port address
  ldi     r30, 0x29             ; 1c
  ldi     r31, 0x00             ; 1c
  sbrc    r21, 3                ; 2c taken, 1c not taken
  subi    r30, 0x06             ; 1c
  andi    r21, 7                ; 1c

  ; set pin masks
  ldi     r22, 0                ; 1c
  sec                           ; 1c
  Lh_pin_shift_loop:
    rol     r22                 ; 1c
    dec     r21                 ; 1c
    brpl    Lh_pin_shift_loop   ; 2c taken, 1c not taken
  mov     r23, r22              ; 1c
  com     r23                   ; 1c

  ; load send arguments
  ; send_buf
  pop     r26                   ; 2c
  pop     r27                   ; 2c
  ; send_length
  pop     r18                   ; 2c

  ; set pin set/clr port values
  ldd     r24, Z+2              ; 2c
  mov     r25, r24              ; 1c
  or      r24, r22              ; 1c
  and     r25, r23              ; 1c

  ; disable interrupts
  cli                           ; 1c

  ; set pin as output
  std     Z+2, r24              ; 2c
  ldd     r0, Z+1               ; 2c
  or      r0, r22               ; 1c
  std     Z+1, r0               ; 2c

  Lh_tx_byte_loop:
  ; hi 42c / 10c
  ; init bit counter
    ldi     r19, 8              ; 1c
  ; hi 43c / 11c
  ; read next byte
    ld      r20, X+             ; 2c
    Lh_tx_bit_loop:
    ; hi 45c / 13c
      rol     r20               ; 1c
    ; hi 46c / 14c
      brcc    Lho_tx_0          ; 2c taken, 1c not taken
      ; hi 47c / 15c
        nops    1               ; 1c
      ; hi 48c / 16c (3µs / 1µs)
      ; transmit 1 bit
        std     Z+2, r25        ; 2c
      ; lo 2c
        nops    14              ; 14c
      ; lo 16c (1µs)
        std     Z+2, r24        ; 2c
      ; hi 2c
        nops    31              ; 31c
      ; hi 33c
        rjmp    Lho_tx_1        ; 2c
      Lho_tx_0:
      ; hi 48c / 16c (3µs / 1µs)
      ; transmit 0 bit
        std     Z+2, r25        ; 2c
      ; lo 2c
        nops    46              ; 46c
      ; lo 48c (3µs)
        std     Z+2, r24        ; 2c
      ; hi 2c
        nops    1               ; 1c
      Lho_tx_1:
    ; hi 35c / 3c
    ; bit loop latch
      dec     r19               ; 1c
    ; hi 36c / 4c
      breq    Lh_tx_bit_loop_end; 2c taken, 1c not taken
      ; hi 37c / 5c
        nops    6               ; 6c
      ; hi 43c / 11c
        rjmp    Lh_tx_bit_loop  ; 2c
      Lh_tx_bit_loop_end:
  ; hi 38c / 6c
  ; byte loop latch
    dec     r18                 ; 1c
  ; hi 39c / 7c
    breq    Lh_tx_byte_loop_end ; 2c taken, 1c not taken
    ; hi 40c / 8c
      rjmp    Lh_tx_byte_loop   ; 2c
    Lh_tx_byte_loop_end:
  ; hi 41c / 9c
  nops    7                     ; 7c
  ; hi 48c / 16c (3µs / 1µs)
  ; transmit stop bit
  std     Z+2, r25              ; 2c
  ; lo 2c
  nops    14                    ; 14c
  ; lo 16c (1µs)
  std     Z+2, r24              ; 2c

  ; load recv arguments
  ; recv_buf
  pop     r26                   ; 2c
  pop     r27                   ; 2c
  ; recv_length
  pop     r18                   ; 2c

  ; set pin as input
  ldd     r0, Z+1               ; 2c
  and     r0, r23               ; 1c
  std     Z+1, r0               ; 2c

  Lh_rx_byte_loop:
  ; init bit counter
    ldi     r19, 8              ; 1c
  ; init byte
    ldi     r20, 0              ; 1c
    Lh_rx_bit_loop:
      lsl     r20               ; 1c
    ; wait for falling edge
      Lh_rx_fall_loop:
        ldd     r0, Z+0         ; 2c
        and     r0, r22         ; 1c
        brne    Lh_rx_fall_loop ; 2c taken, 1c not taken
    ; lo 4c
    ; wait 2µs
      nops      28              ; 28c
    ; sample signal
      ldd     r0, Z+0           ; 2c
      and     r0, r22           ; 1c
      breq    Lh_rx_0           ; 2c taken, 1c not taken
        ori     r20, 1          ; 1c
        rjmp    Lh_rx_1         ; 2c
      Lh_rx_0:
      ; wait for rising edge
        ldd     r0, Z+0         ; 2c
        and     r0, r22         ; 1c
        breq    Lh_rx_0         ; 2c taken, 1c not taken
      Lh_rx_1:
    ; bit loop latch
      dec     r19               ; 1c
      brne    Lh_rx_bit_loop    ; 2c taken, 1c not taken
  ; store byte
    st      X+, r20             ; 2c
  ; byte loop latch
    dec     r18                 ; 1c
    brne    Lh_rx_byte_loop     ; 2c taken, 1c not taken

  ; restore status register
  pop     r0                    ; 2c
  out     0x3F, r0              ; 2c

  ; return
  ret                           ; 4c
.size	  pif_host_transmit, . - pif_host_transmit


;
; void pif_client_recv(uint8_t pin, void *recv_buf, uint8_t *recv_length);
;
.global	pif_client_recv
.type	  pif_client_recv, @function
pif_client_recv:
  ; save status register
  in      r0, 0x3F              ; 2c
  push    r0                    ; 2c

  ; save frame pointer
  push    r29                   ; 2c
  push    r28                   ; 2c

  ; save arguments
  ; recv_length
  push    r21                   ; 2c
  push    r20                   ; 2c
  ; recv_buf
  push    r23                   ; 2c
  push    r22                   ; 2c
  ; pin
  push    r24                   ; 2c

  ; load pin argument
  pop     r21                   ; 2c

  ; set port address
  ldi     r30, 0x29             ; 1c
  ldi     r31, 0x00             ; 1c
  sbrc    r21, 3                ; 2c taken, 1c not taken
  subi    r30, 0x06             ; 1c
  andi    r21, 7                ; 1c

  ; set pin masks
  ldi     r22, 0                ; 1c
  sec                           ; 1c
  Lc_rx_pin_shift_loop:
    rol     r22                 ; 1c
    dec     r21                 ; 1c
    brpl    Lc_rx_pin_shift_loop; 2c taken, 1c not taken
  mov     r23, r22              ; 1c
  com     r23                   ; 1c

  ; load recv arguments
  ; recv_buf
  pop     r26                   ; 2c
  pop     r27                   ; 2c
  ; recv_length
  pop     r28                   ; 2c
  pop     r29                   ; 2c

  ; disable interrupts
  cli                           ; 1c

  ; set pin as input
  ldd     r0, Z+2               ; 2c
  or      r0, r22               ; 1c
  std     Z+2, r0               ; 2c
  ldd     r0, Z+1               ; 2c
  and     r0, r23               ; 1c
  std     Z+1, r0               ; 2c

  ; init byte counter
  ldi     r18, 0                ; 1c
  ; init byte
  ldi     r20, 0                ; 1c

  ; wait for initial falling edge
  Lc_rx_start_loop:
    ldd     r0, Z+0             ; 2c
    and     r0, r22             ; 1c
    brne    Lc_rx_start_loop    ; 2c taken, 1c not taken
  ; lo 2c
  nops    10                    ; 10c

  Lc_rx_byte_loop:
  ; lo 12c
  ; init bit counter
    ldi     r19, 8              ; 1c
    Lc_rx_bit_loop:
    ; lo 13c
      lsl     r20               ; 1c
    ; lo 14c
      nops    18                ; 18c
    ; lo+data 32c (2µs)
    ; sample bit
      ldd     r0, Z+0           ; 2c
      and     r0, r22           ; 1c
      breq    Lc_rx_0           ; 2c taken, 1c not taken
        ori     r20, 1          ; 1c
        rjmp    Lc_rx_1         ; 2c
      Lc_rx_0:
      ; wait for line high
        ldd     r0, Z+0         ; 2c
        and     r0, r22         ; 1c
        breq    Lc_rx_0         ; 2c taken, 1c not taken
      Lc_rx_1:
    ; wait for falling edge, ~3µs timeout
      ldi     r21, 7            ; 1c
      Lc_rx_fall_loop:
        dec     r21             ; 1c
        breq    Lc_rx_tout      ; 2c taken, 1c not taken
        ldd     r0, Z+0         ; 2c
        and     r0, r22         ; 1c
        brne    Lc_rx_fall_loop ; 2c taken, 1c not taken
    ; bit loop latch
    ; lo 4c
      dec     r19               ; 1c
    ; lo 5c
      breq    Lc_rx_bit_loop_end; 2c taken, 1c not taken
      ; lo 6c
        nops    5               ; 5c
      ; lo 11c
        rjmp    Lc_rx_bit_loop  ; 2c
      Lc_rx_bit_loop_end:
  ; lo 7c
  ; store byte
    st      X+, r20             ; 2c
  ; lo 9c
  ; byte loop latch
    inc     r18                 ; 1c
  ; lo 10c
    rjmp    Lc_rx_byte_loop     ; 2c taken, 1c not taken
    Lc_rx_tout:

  ; store byte count
  st      Y, r18                ; 2c

  ; restore frame pointer
  pop     r28                   ; 2c
  pop     r29                   ; 2c

  ; restore status register
  pop     r0                    ; 2c
  out     0x3F, r0              ; 2c

  ; return
  ret                           ; 4c
.size	  pif_client_recv, . - pif_client_recv


;
; void pif_client_send(uint8_t pin, void *send_buf, uint8_t send_length);
;
.global	pif_client_send
.type	  pif_client_send, @function
pif_client_send:
  ; save status register
  in      r0, 0x3F              ; 2c
  push    r0                    ; 2c

  ; save arguments
  ; send_length
  push    r20                   ; 2c
  ; send_buf
  push    r23                   ; 2c
  push    r22                   ; 2c
  ; pin
  push    r24                   ; 2c

  ; load pin argument
  pop     r21                   ; 2c

  ; set port address
  ldi     r30, 0x29             ; 1c
  ldi     r31, 0x00             ; 1c
  sbrc    r21, 3                ; 2c taken, 1c not taken
  subi    r30, 0x06             ; 1c
  andi    r21, 7                ; 1c

  ; set pin masks
  ldi     r22, 0                ; 1c
  sec                           ; 1c
  Lc_tx_pin_shift_loop:
    rol     r22                 ; 1c
    dec     r21                 ; 1c
    brpl    Lc_tx_pin_shift_loop; 2c taken, 1c not taken
  mov     r23, r22              ; 1c
  com     r23                   ; 1c

  ; load send arguments
  ; send_buf
  pop     r26                   ; 2c
  pop     r27                   ; 2c
  ; send_length
  pop     r18                   ; 2c

  ; set pin set/clr port values
  ldd     r24, Z+2              ; 2c
  mov     r25, r24              ; 1c
  or      r24, r22              ; 1c
  and     r25, r23              ; 1c

  ; disable interrupts
  cli                           ; 1c

  ; set pin as output
  std     Z+2, r24              ; 2c
  ldd     r0, Z+1               ; 2c
  or      r0, r22               ; 1c
  std     Z+1, r0               ; 2c

  Lc_tx_byte_loop:
  ; hi 42c / 10c
  ; init bit counter
    ldi     r19, 8              ; 1c
  ; hi 43c / 11c
  ; read next byte
    ld      r20, X+             ; 2c
    Lc_tx_bit_loop:
    ; hi 45c / 13c
      rol     r20               ; 1c
    ; hi 46c / 14c
      brcc    Lc_tx_0           ; 2c taken, 1c not taken
      ; hi 47c / 15c
        nops    1               ; 1c
      ; hi 48c / 16c (3µs / 1µs)
      ; transmit 1 bit
        std     Z+2, r25        ; 2c
      ; lo 2c
        nops    14              ; 14c
      ; lo 16c (1µs)
        std     Z+2, r24        ; 2c
      ; hi 2c
        nops    31              ; 31c
      ; hi 33c
        rjmp    Lc_tx_1         ; 2c
      Lc_tx_0:
      ; hi 48c / 16c (3µs / 1µs)
      ; transmit 0 bit
        std     Z+2, r25        ; 2c
      ; lo 2c
        nops    46              ; 46c
      ; lo 48c (3µs)
        std     Z+2, r24        ; 2c
      ; hi 2c
        nops    1               ; 1c
      Lc_tx_1:
    ; hi 35c / 3c
    ; bit loop latch
      dec     r19               ; 1c
    ; hi 36c / 4c
      breq    Lc_tx_bit_loop_end; 2c taken, 1c not taken
      ; hi 37c / 5c
        nops    6               ; 6c
      ; hi 43c / 11c
        rjmp    Lc_tx_bit_loop  ; 2c
      Lc_tx_bit_loop_end:
  ; hi 38c / 6c
  ; byte loop latch
    dec     r18                 ; 1c
  ; hi 39c / 7c
    breq    Lc_tx_byte_loop_end ; 2c taken, 1c not taken
    ; hi 40c / 8c
      rjmp    Lc_tx_byte_loop   ; 2c
    Lc_tx_byte_loop_end:
  ; hi 41c / 9c
  nops    7                     ; 7c
  ; hi 48c / 16c (3µs / 1µs)
  ; transmit stop bit
  std     Z+2, r25              ; 2c
  ; lo 2c
  nops    30                    ; 30c
  ; lo 32c (2µs)
  std     Z+2, r24              ; 2c

  ; restore status register
  pop     r0                    ; 2c
  out     0x3F, r0              ; 2c

  ; return
  ret                           ; 4c
.size	  pif_client_send, . - pif_client_send
