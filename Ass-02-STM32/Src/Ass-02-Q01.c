//     $Date: 2018-03-26 08:32:18 +1100 (Mon, 26 Mar 2018) $
// $Revision: 1217 $
//   $Author: Peter $

#include "Ass-02.h"
#ifdef STM32F407xx
#include "usart.h"
#endif
#include <stdbool.h>
enum CONTROL_CHARS {NUL=0,SOH,STX,ETX,EOT,ENQ,ACK,BEL,BS,TAB,LF,VT,FF,CR,SO,SI,DLE,DC1,DC2,DC3,DC4,NAK,SYN,ETB,CAN,EM,SUB,ESC,FS,GS,RS,US=31,DEL=127};

int isControlChar(char c){
	int code;
	if (c<32||c==127) return true;
	else return false;
}


void CommandLineParserInit(void)
{
  // Print welcome message
  printf("\014");
  printf("ELEC3730 Assignment 2\n");
  printf("Command Line Parser Example\n");
}

void CommandLineParserProcess(void)
{
  uint8_t c;

  // Check for input and echo back
#ifdef STM32F407xx
  if (HAL_UART_Receive(&huart2, &c, 1, 0x0) == HAL_OK)
  {

	HAL_GPIO_TogglePin(GPIOD, LD4_Pin); // Toggle LED4
	if (!isControlChar(c)){
		printf("%c", c);
	} else {
		switch (c){
		case CR :
			printf("\n");
			break;
		case DEL:
			printf("\b");
			break;
		default:
			printf(" %i ",c);
		}

	}

// this be the Tweedale
	// another testing comment
// test-icles
  }
#else
  c = getchar();
  printf("SERIAL: Got '%c'\n", c);
#endif
}
