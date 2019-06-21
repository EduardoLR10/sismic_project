#ifndef CONFIGS_H
#define CONFIGS_H

#define ClearPort(port, type, pin) ((port##type) &= ~(BIT##pin))
#define ComparePortEQ(port, type, pin, value) (((port##type) & (BIT##pin)) == value)
#define ComparePortNE(port, type, pin, value) (((port##type) & (BIT##pin)) != value)
#define CompareFlagEQ(_register, flag, value) (((_register) & (flag)) == value)
#define CompareFlagNE(_register, flag, value) (((_register) & (flag)) != value)
#define ReadPort(port, type, pin) ((port##type) & (BIT##pin))  
#define SetPort(port, type, pin) ((port##type) |= (BIT##pin))
#define SetFlag(_register, flag)  ((_register) |= (flag))
#define ClearFlag(_register, flag)  ((_register) &= ~(flag))
#define TogglePort(port, type, pin) ((port##type) ^= (BIT##pin))

#define BR10K 10
#define BR50K 50
#define BR100K 100

#define BIT_BL BIT3
#define BIT_E BIT2
#define BIT_RW BIT1
#define BIT_RS BIT0

void delay(long limit);

#endif // CONFIGS_h