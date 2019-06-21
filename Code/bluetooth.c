#include "bluetooth.h"
#include <msp430.h>

void configBluetooth(int parity, int isEven, int isMSB, int is2Stops, int mode, int isSync){

	SetFlag(UCA1CTLW0, UCSWRST);
	if(parity) SetFlag(UCA1CTLW0, UCPEN);
	if(isEven) SetFlag(UCA1CTLW0, UCPAR);
	if(isMSB) SetFlag(UCA1CTLW0, UCMSB);
	if(is2Stops) SetFlag(UCA1CTLW0, UCSPB);
	if(mode == 0) SetFlag(UCA1CTLW0, UCMODE0);
	if(mode == 1) SetFlag(UCA1CTLW0, UCMODE1);
	if(mode == 2) SetFlag(UCA1CTLW0, UCMODE_2);
	if(mode == 3) SetFlag(UCA1CTLW0, UCMODE_3);
	if(isSync) SetFlag(UCA1CTLW0, UCSYNC);
	
	SetFlag(UCA1CTLW0, UCSSEL__SMCLK);

	UCA1BRW = 6;
	UCA1MCTLW = UCBRF_8 | UCOS16;

	// Output PIN
    SetPort(P2, DIR, 5);
    SetPort(P2, SEL0, 5);
    ClearPort(P2, SEL1, 5);

    // Input PIN
    ClearPort(P2, DIR, 6);
    SetPort(P2, SEL0, 6);
    ClearPort(P2, SEL1, 6);

	ClearFlag(UCA1CTLW0, UCSWRST);
    
    SetFlag(UCA1IE, UCRXIE);

}

void bluetoothStop(){
  UCA1IE = 0;  // Stops all interrupts
  while(UCA1STATW & UCBUSY);  // Waits to finish all transactions
  SetFlag(UCA1CTLW0, UCSWRST);
}

#pragma vector=USCI_A1_VECTOR
__interrupt void UCA1_ISR() {

  switch (UCA1IV){
    case 0x00: break;
    case 0x02:  // RXIFG
      motors_byte = UCA1RXBUF;
      break;
    case 0x04:  // TXIFG

      break;
    default:
      break;
  }
}
