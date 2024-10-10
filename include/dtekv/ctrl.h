#ifndef CTRL_H
#define CTRL_H

#define CLKPIN  0
#define DATAPIN 1
#define TRANSFORM_SPEED QVAL(0.01f)

/*
 * Sets up GPIO pins for receiving controller data from Arduino.
 */
void ctrl_init(void);

/*
 * Receives a message from the Arduino board
 * and updates model transform.
 */
void ctrl_recv(void);

#endif
