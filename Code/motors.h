#ifndef MOTORS_H
#define MOTORS_H

#include "configs.h"

#define Forward 1
#define Backward 0

#define VerifyStart(byte) (byte&0x01)
#define VerifyStop(byte) (byte&0x80)
#define VerifyGoForward(byte) (byte&0x02)
#define VerifyGoBack(byte) (byte&0x04)
#define VerifyGoDRight(byte) (byte&0x08)
#define VerifyGoDLeft(byte) (byte&0x10)
#define VerifyTurnRight(byte) (byte&0x20)
#define VerifyTurnLeft(byte) (byte&0x40)
#define VerifyNonSense(byte) ((byte&0x07) | (byte&0x19) | (byte&0x61))

void configMotorsPINS();
void motor1_pwm(double dutyCycle, int Direction);
void motor2_pwm(double dutyCycle, int Direction);
void increaseMotor1(double increment);
void decreaseMotor1(double increment);
void increaseMotor2(double increment);
void decreaseMotor2(double increment);
void stopMotors();

#endif //MOTORS_H