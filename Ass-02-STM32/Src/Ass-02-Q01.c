//     $Date: 2018-03-26 08:32:18 +1100 (Mon, 26 Mar 2018) $
// $Revision: 1217 $
//   $Author: Peter $

#include "Ass-02.h"
#ifdef STM32F407xx
#include "usart.h"
#endif
#include <stdbool.h>
#include "calculator.h"
enum CONTROL_CHARS {NUL=0,SOH,STX,ETX,EOT,ENQ,ACK,BEL,BS,TAB,LF,VT,FF,CR,SO,SI,DLE,DC1,DC2,DC3,DC4,NAK,SYN,ETB,CAN,EM,SUB,ESC,FS,GS,RS,US=31,DEL=127};

int isControlChar(char c){
	if (c<32||c==127) return true;
	else return false;
}


int count=0;
char *array_of_inputs; // array which stores the characters

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
  if (HAL_UART_Receive(&huart2, &c, 1, 0x0) == HAL_OK) //Receive a new character and store in c
  {
	HAL_GPIO_TogglePin(GPIOD, LD4_Pin); // Toggle LED4
	if (!isControlChar(c)){
		printf("%c", c);
		// store in the next element of array and increes counter by 1

		array_of_inputs[count]=c;
		count++;
	} else {
		switch (c){
		case CR :
			printf("\n");
			// add \0 to the end of the string and then give it to q3 of assesment 1
			array_of_inputs[count] = NULL;
			break;
		case DEL:
			printf("\b");
			// subtract 1 from count
			break;

		default:
			printf(" %i ",c);
		}
	}

//checking the input
int8_t Command_Function(uint8_t num_count, uint8_t *Array_numbers[]);{
	typedef struct{
	int8_t *Command_string; 										// Command string
	int8_t (*Function_p)(uint8_t num_count, uint8_t *numbers_p[]);	// Function pointer				//
	int8_t *Help_s; 													// Help information
	} command_s;

	const command_s CommandList[] = {
	{"add", &add, 		"add <num 1> .. <num N>"},
	{"sub", &subtract, 	"sub <num 1> <num 2>"},
	{"mul", &multiply, 	"mul <num 1> .. <num N>"},
	{"div", &divide, 	"div <num 1> <num 2>"},
	{NULL, NULL, NULL}
	};
	//printf(%d,&result);


}

  }
#else
  c = getchar();
  printf("SERIAL: Got '%c'\n", c);
#endif
}
