#include "configs.h"

void delay(long limit){
    volatile long cont=0;
    while (cont++ < limit);
}