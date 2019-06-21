#include <msp430.h>
#include <stdint.h>
#include "motors.h"
#include "configs.h"
#include "proximity_sensor.h"
#include "bluetooth.h"

uint8_t motors_byte;

void main(void){

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~BIT0;

    configMotorsPINS();
    configSensor();
    configBluetooth(_nonParity, _isOdd, _isMSB, _is1Stops, 0, _isnonSync);

}

