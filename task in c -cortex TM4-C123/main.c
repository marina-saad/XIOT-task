#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "C:\Keil_v5\TExaSware\tm4c123gh6pm.h"

void PortF_Init(void){ volatile uint32_t delay;
  SYSCTL_RCGCGPIO_R |= 0x00000020;  // 1) activate clock for Port F
  delay = SYSCTL_RCGCGPIO_R;        // allow time for clock to start
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0
  // only PF0 needs to be unlocked, other bits can't be locked
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog on PF
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
  GPIO_PORTF_DIR_R = 0x08;          // 5) PF4,PF0 in, PF3-1 out
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
  GPIO_PORTF_PUR_R = 0x10;          // enable pull-up on PF0 and PF4
  GPIO_PORTF_DEN_R = 0x18;          // 7) enable digital I/O on PF4-0
}
uint32_t PortF_Input(void){
  return (GPIO_PORTF_DATA_R&0x11);  // read PF4,PF0 inputs
}

void Setup_UART0() // UART Setting=115200,8N1
{
    int BRDI = 8;
    int BRDF = 44;
 
    // 1. Enable clock to UART Module (SYSCTL_RCGCUART)
    SYSCTL_RCGCUART_R |= 0x01;
    // allow time for clock to stabilize
    while ((SYSCTL_PRUART_R & 0x01) != 0x01){};
 
    // 2. Select the baud clock source for UART module
    UART0_CC_R = 0x0;  // Buad clock source from system clock
    // 3. Disable UART by clearing UARTEN in UARTCTL register
    UART0_CTL_R &= ~(0x00000001);
    // 4. Write BRD to UARTIBRD and UARTFBRD register
    UART0_IBRD_R = BRDI;
    UART0_FBRD_R = BRDF;
    // 5. Write UART Line Control, High Byte (UARTLCRH register)
    //    8bit, No parity, 1-stop bit, no FIFO = 0x00000060
    UART0_LCRH_R = 0x60;
    // 6. Configure the UART clock source (UARTCC register)
    UART0_CC_R = 0x00;   // Clock Source from System Clock
    // 7. Enable UART by clearing UARTEN in UARTCTL register
    UART0_CTL_R = 0x301; // Enable UART0, TXE, RXE
}



void PortF_Output(uint32_t data){ // write PF3-PF1 outputs
  GPIO_PORTF_DATA_R = data;
}

void UART_outchar(char Data)
{
	while ((UART0_FR_R&0x0020)!=0)
	{};
		UART0_DR_R=Data;
}
int main()
{
	unsigned int value;
	PortF_Init();
	while(1)
	{
   	value = GPIO_PORTF_DATA_R;
		value = ~value; 
		UART_outchar('O'); //O means LED is OFF
    value = value >> 1;
		if(value!=0)
{

	UART_outchar('P'); //p means pressed
}	
		GPIO_PORTF_DATA_R = value;
UART_outchar('N'); //N means LED is ON

	}

}
