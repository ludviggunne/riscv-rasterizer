#ifndef CTRL_H
#define CTRL_H

#define CLKPIN  0
#define DATAPIN 1

/*
 * Sets up GPIO pins for receiving controller data from Arduino.
 */
void ctrl_init(void);

/*
 * Receives a message from the Arduino board.
 * Should be called on interrupt recei
 */
void ctrl_recv(void);

#endif