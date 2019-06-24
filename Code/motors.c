#include "motors.h"
#include <msp430.h>

void configMotorsPINS(){
    // Motor 1 Pins
    SetPort(P3, DIR, 6);
    SetPort(P3, DIR, 7);

    // Select TIMERS for Motor 1
    SetPort(P3, SEL0, 6);
    ClearPort(P3, SEL1, 6);
    SetPort(P3, SEL0, 7);
    ClearPort(P3, SEL1, 7);

    // Motor 2 Pins
    SetPort(P3, DIR, 4);
    SetPort(P3, DIR, 5);

    // Select TIMERS for Motor 2
    SetPort(P3, SEL0, 4);
    ClearPort(P3, SEL1, 4);
    SetPort(P3, SEL0, 5);
    ClearPort(P3, SEL1, 5);

    // Config Timer for Motors
    SetFlag(TB0CTL, TASSEL__SMCLK);
    SetFlag(TB0CTL, MC__UP);
    SetFlag(TB0CTL, TACLR);

    // 50 Hz
    TB0CCR0 = 20000;
}

void motor2_pwm(double dutyCycle, int Direction){

    if(Direction == Forward){

        // Check if the motor was going BACKWARD
        if(CompareFlagEQ(TB0CCTL3, OUTMOD_7, OUTMOD_7)){

            // Wait ending of last state
            TB0CCTL3 = OUTMOD_5;
            delay(400);
        }

        TB0CCTL4 = OUTMOD_7;

        TB0CCR4 = dutyCycle * TB0CCR0 - 1;
    }
    if(Direction == Backward){

        // Check if the motor was going FORWARD
        if(CompareFlagEQ(TB0CCTL4, OUTMOD_7, OUTMOD_7)){
            
            // Wait ending of last state
            TB0CCTL4 = OUTMOD_5;
            delay(400);
        }

        TB0CCTL3 = OUTMOD_7;

        TB0CCR3 = dutyCycle * TB0CCR0 - 1;
    }
}

void motor1_pwm(double dutyCycle, int Direction){

    if(Direction == Backward){

        // Check if the motor was going FORWARD
        if(CompareFlagEQ(TB0CCTL6, OUTMOD_7, OUTMOD_7)){

            // Wait ending of last state
            TB0CCTL6 = OUTMOD_5;
            delay(400);
        }

        TB0CCTL5 = OUTMOD_7;

        TB0CCR5 = dutyCycle * TB0CCR0 - 1;
    }
    if(Direction == Forward){

        // Check if the motor was going BACKWARD
        if(CompareFlagEQ(TB0CCTL5, OUTMOD_7, OUTMOD_7)){
            
            // Wait ending of last state
            TB0CCTL5 = OUTMOD_5;
            delay(400);
        }

        TB0CCTL6 = OUTMOD_7;

        TB0CCR6 = dutyCycle * TB0CCR0 - 1;
    }
}

void increaseMotor1(double increment){
    // Going Forward
    if(CompareFlagEQ(TB0CCTL6, OUTMOD_7, OUTMOD_7)){
        if((TB0CCR6 + (TB0CCR0 * increment)) > TB0CCR0){
            TB0CCR6 = TB0CCR0 - 1;
        }else{
            TB0CCR6 += (TB0CCR0 * increment);
            TB0CTL |= TBCLR;
        }
    }
    // Going Backward
    if(CompareFlagEQ(TB0CCTL5, OUTMOD_7, OUTMOD_7)){
        if((TB0CCR5 + (TB0CCR0 * increment)) > TB0CCR0){
            TB0CCR5 = TB0CCR0 - 1;
        }else{
            TB0CCR5 += (TB0CCR0 * increment);
            TB0CTL |= TBCLR;
        }    
    }
}

void decreaseMotor1(double increment){
    // Going Forward
    if(CompareFlagEQ(TB0CCTL6, OUTMOD_7, OUTMOD_7)){
        if((TB0CCR6 - (TB0CCR0 * increment)) <= 0){
            TB0CCR6 = TB0CCR0 * 0.25 - 1;
        }else{
            TB0CCR6 -= (TB0CCR0 * increment);
            TB0CTL |= TBCLR;
        }
    }
    // Going Backward
    if(CompareFlagEQ(TB0CCTL5, OUTMOD_7, OUTMOD_7)){
        if((TB0CCR5 - (TB0CCR0 * increment)) <= 0){
            TB0CCR5 = TB0CCR0 * 0.25 - 1;
        }else{
            TB0CCR5 -= (TB0CCR0 * increment);
            TB0CTL |= TBCLR;
        }    
    }
}

void increaseMotor2(double increment){
    // Goind Forward
    if(CompareFlagEQ(TB0CCTL3, OUTMOD_7, OUTMOD_7)){
        if((TB0CCR3 + (TB0CCR0 * increment)) > TB0CCR0){
            TB0CCR3 = TB0CCR0 - 1;
        }else{
            TB0CCR3 += (TB0CCR0 * increment);
            TB0CTL |= TBCLR;
        }
    }
    // Going Backward
    if(CompareFlagEQ(TB0CCTL4, OUTMOD_7, OUTMOD_7)){
        if((TB0CCR4 + (TB0CCR0 * increment)) > TB0CCR0){
            TB0CCR4 = TB0CCR0 - 1;
        }else{
            TB0CCR4 += (TB0CCR0 * increment);
            TB0CTL |= TBCLR;
        }
    }
}

void decreaseMotor2(double increment){
    // Goind Forward
    if(CompareFlagEQ(TB0CCTL3, OUTMOD_7, OUTMOD_7)){
        if((TB0CCR3 - (TB0CCR0 * increment)) <= 0){
            TB0CCR3 = TB0CCR0 * 0.25 - 1;
        }else{
            TB0CCR3 -= (TB0CCR0 * increment);
            TB0CTL |= TBCLR;
        }
    }
    // Going Backward
    if(CompareFlagEQ(TB0CCTL4, OUTMOD_7, OUTMOD_7)){
        if((TB0CCR4 - (TB0CCR0 * increment)) <= 0){
            TB0CCR4 = TB0CCR0 * 0.25 - 1;
        }else{
            TB0CCR4 -= (TB0CCR0 * increment);
            TB0CTL |= TBCLR;
        }
    }
}

void stopMotors(){
    TB0CCTL3 = OUTMOD_5;
    TB0CCTL4 = OUTMOD_5;
    TB0CCTL5 = OUTMOD_5;
    TB0CCTL6 = OUTMOD_5;
}

