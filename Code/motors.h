#ifndef MOTORS_H
#define MOTORS_H

#include "configs.h"

void configMotorsPINS();
void motor1_pwm(double dutyCycle, int Direction);
void motor2_pwm(double dutyCycle, int Direction);
void increaseMotor1(double increment);
void decreaseMotor1(double increment);
void increaseMotor2(double increment);
void decreaseMotor2(double increment);
void stopMotors();

#endif //MOTORS_H