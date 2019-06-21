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

    while(1){
        if(!(VerifyStop(motors_byte))){
            if(VerifyStart(motors_byte)){
                if(!(checkDistance())){
                    if(VerifyGoDRight(motors_byte) & VerifyGoForward(motors_byte)){
                        motor1_pwm(1.0, Forward);
                        motor2_pwm(0.5, Forward);
                    }else if(VerifyGoDLeft(motors_byte) & VerifyGoForward(motors_byte)){
                        motor1_pwm(0.5, Forward);
                        motor2_pwm(1.0, Forward);
                    }else if(VerifyGoDRight(motors_byte) & VerifyGoBack(motors_byte)){
                        motor1_pwm(1.0, Backward);
                        motor2_pwm(0.5, Backward);
                    }else if(VerifyGoDLeft(motors_byte) & VerifyGoBack(motors_byte)){
                        motor1_pwm(0.5, Backward);
                        motor2_pwm(1.0, Backward);
                    }else if(VerifyGoForward(motors_byte)){
                        motor1_pwm(1.0, Forward);
                        motor2_pwm(1.0, Forward);
                    }else if(VerifyGoBack(motors_byte)){
                        motor1_pwm(1.0, Backward);
                        motor2_pwm(1.0, Backward);
                    }
                }else{
                    stopMotors();
                    if(VerifyGoBack(motors_byte)){
                        motor1_pwm(1.0, Backward);
                        motor2_pwm(1.0, Backward);
                    }
                }
            }
        }else{
            stopMotors();
        }

}

