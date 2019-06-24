#include <msp430.h>
#include <stdint.h>
#include "motors.h"
#include "configs.h"
#include "proximity_sensor.h"
#include "bluetooth.h"

uint8_t motors_byte = 0x80;

void main(void){

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~BIT0;

    SetPort(P1, DIR, 0);
    SetPort(P1, DIR, 1);

    ClearPort(P1, OUT, 0);
    ClearPort(P1, OUT, 1);

    SetPort(P8, DIR, 1);
    SetPort(P8, OUT, 1);

    configMotorsPINS();
    configSensor();
    configBluetooth(_nonParity, _isOdd, _isLSB, _is1Stops, 0, _isnonSync);

    __enable_interrupt();

    while(1){
        if(!(VerifyStop(motors_byte))){
            if(VerifyStart(motors_byte)){
                ClearPort(P1, OUT, 0);
                SetPort(P1, OUT, 1);
                if(!(checkDistance())){
                    if(VerifyGoDLeft(motors_byte) && VerifyGoForward(motors_byte)){
                        motor1_pwm(1.0, Forward);
                        motor2_pwm(0.47, Forward);
                    }else if(VerifyGoDRight(motors_byte) && VerifyGoForward(motors_byte)){
                        motor1_pwm(0.5, Forward);
                        motor2_pwm(0.94, Forward);
                    }else if(VerifyGoDLeft(motors_byte) && VerifyGoBack(motors_byte)){
                        motor1_pwm(1.0, Backward);
                        motor2_pwm(0.5, Backward);
                    }else if(VerifyGoDRight(motors_byte) && VerifyGoBack(motors_byte)){
                        motor1_pwm(0.5, Backward);
                        motor2_pwm(1.0, Backward);
                    }else if(VerifyGoForward(motors_byte)){
                        motor1_pwm(1.0, Forward);
                        motor2_pwm(0.94, Forward);
                    }else if(VerifyGoBack(motors_byte)){
                        motor1_pwm(1.0, Backward);
                        motor2_pwm(1.0, Backward);
                    }
                }else{
                    ClearPort(P1, OUT, 1);
                    SetPort(P1, OUT, 0);
                    stopMotors();
                    if(VerifyGoBack(motors_byte)){
                        motor1_pwm(1.0, Backward);
                        motor2_pwm(1.0, Backward);
                    }
                }
            }
        }else{
            ClearPort(P1, OUT, 1);
            SetPort(P1, OUT, 0);
            stopMotors();
        }

    }
}

