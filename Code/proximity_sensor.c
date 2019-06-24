#include <msp430.h>
#include "proximity_sensor.h"

void configSensor(){

    ClearPort(P1, DIR, 2);

    SetFlag(TA0CTL, TASSEL__SMCLK);
    SetFlag(TA0CTL, MC_1);

    TA0CCR0 = 20-1;

    ClearPort(P3, OUT, 3);
    SetPort(P3, DIR, 3);

    SetFlag(TA1CTL, TASSEL__SMCLK);
    SetFlag(TA1CTL, MC_2);

    TA1CCTL1 = CAP;
    SetFlag(TA1CCTL1, CM__BOTH);
    SetFlag(TA1CCTL1, CCIS_0);

    ClearPort(P1, SEL1, 2);
    SetPort(P1, SEL0, 2);

}

int checkDistance(){

    unsigned int t1;
    unsigned int t2;

    SetFlag(TA0CTL, TACLR);
    SetFlag(TA1CTL, TACLR);

    SetPort(P3, OUT, 3);

    while(!(TA0CTL & TAIFG));

    ClearFlag(TA0CTL, TAIFG);
    ClearPort(P3, OUT, 3);

    while(!(TA1CCTL1 & CCIFG));

    ClearFlag(TA1CCTL1, CCIFG);

    t1 = TA1CCR1;

    while(!(TA1CCTL1 & CCIFG));

    ClearFlag(TA1CCTL1, CCIFG);

    t2 = TA1CCR1;

    if((t2 - t1) <= 1740){
        return STOP;
    }else{
        return OK;
    }
}
