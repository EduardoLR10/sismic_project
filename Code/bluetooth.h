#ifndef UART_H
#define UART_H

#include "configs.h"
#include <string.h>
#include <stdint.h>
#include <stdio.h>

extern uint8_t motors_byte;

#define _parity 1
#define _nonParity 0
#define _isEven 1
#define _isOdd 0
#define _isMSB 1
#define _isLSB 0
#define _is2Stops 1
#define _is1Stops 0
#define _isSync 1
#define _isnonSync 0

void configBluetooth(int parity, int isEven, int isMSB, int is2Stops, int mode, int isSync);
void bluetoothStop();

#endif // UART_H