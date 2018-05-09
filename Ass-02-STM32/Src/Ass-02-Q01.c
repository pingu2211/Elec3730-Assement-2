//     $Date: 2018-03-26 08:32:18 +1100 (Mon, 26 Mar 2018) $
// $Revision: 1217 $
//   $Author: Peter $

#include "Ass-02.h"
#ifdef STM32F407xx
#include "usart.h"
#endif
#include <stdbool.h>


enum CONTROL_CHARS {NUL=0,SOH,STX,ETX,EOT,ENQ,ACK,BEL,BS,TAB,LF,VT,FF,CR,SO,SI,DLE,DC1,DC2,DC3,DC4,NAK,SYN,ETB,CAN,EM,SUB,ESC,FS,GS,RS,US=31,DEL=127};

int isControlChar(char c){				// checks input character against the ascii table
	if (c<32||c==127) return true;		// returns true if input is a valid character
	else return false;					// valid characters are 32-127 on ascii table
}

int _count=0;	// universal counter
char *input_s; 	// array which stores the characters
char **words;	// pointer to array of strings

void CommandLineParserInit(void)
{
  // Print welcome message
  printf("\014");
  printf("ELEC3730 Assignment 2\n");
  printf("Command Line Parser Example\n");
}


void CommandLineParserProcess(void)
{
  int wordcount=0;
  uint8_t c;
  // Check for input and echo back
#ifdef STM32F407xx
  if (HAL_UART_Receive(&huart2, &c, 1, 0x0) == HAL_OK) //Receive a new character and store in c
  {
	HAL_GPIO_TogglePin(GPIOD, LD4_Pin); 		// Toggle LED4
	if (!isControlChar(c)){						// check that user entered a character and not a control character
		input_s=realloc(input_s, _count+1);
		printf("%c", c);
		input_s[_count]=c;						// store in the next element of array
		_count++;								// increase counter by 1
	} else {
		switch (c){
		case CR :												// case 1: if user presses "enter"
			printf("\n");
			if (_count>0){
				input_s[_count] = '\0';							// add \0 to the end of the string
				wordcount = string_parser (input_s, &words); 	// call string parser function
				Command_Function(wordcount, words);
				if(USR_DBG)printf("%s\n",input_s);				// prints debug messages
				_count = 0;
			}
			break;
		case DEL:			// case 2: if user presses "backspace"
			printf("\b \b");
			_count--;		// subtract 1 from count
			break;

		default:				// when a control character is entered that is NOT enter or backspace
			printf(" %i ",c);	// print the ascii number of the control character that was entered
		}
	}
}


#else
  c = getchar();
  printf("SERIAL: Got '%c'\n", c);
#endif
}

