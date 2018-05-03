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
	HAL_GPIO_TogglePin(GPIOD, LD4_Pin); 				// Toggle LED4
	if (!isControlChar(c)){			// check that user entered a character and not a control character
		printf("%c", c);
		array_of_inputs[count]=c;	// store in the next element of array
		count++;					// increase counter by 1

	} else {
		switch (c){
		case CR :			// case 1: if user presses "enter"
			printf("\n");
			// add \0 to the end of the string and then give it to q3 of assesment 1
			array_of_inputs[count] = NULL;	// add \0 to the end of the string

			break;
		case DEL:			// case 2: if user presses "backspace"
			printf("\b");
			count--;		// subtract 1 from count

			break;

		default:				// when a control character is entered that is NOT enter or backspace
			printf(" %i ",c);	// print the askii number of the control character that was entered
		}
	}
	int string_parser(char *array_of_inputs, char **array_of_strings_p[])
	{
		/* declare all the things */
			int inp_count=0;
			int j = 0;
			char **array_of_strings;	// this particular one helps me wrap my head arround pointers to pointers to pointers.....

			int input_length = strlen (array_of_inputs);			// make sure the input string actually has something in it
			if (input_length <= 0) return -1;						// if input is empty return error

			array_of_strings = (char**)malloc(sizeof( *array_of_strings) * input_length);	// allocate some memory, for now we'll assume ever character is its own word and trim it down later
			if (!array_of_strings) {														//make sure  memory was allocated successfully
				printf ("\nError in String Passer\nError reallocating memory");
				return -1;
			}
			array_of_strings[inp_count] = (char*)malloc(input_length);	// allocate some memory to the first word, and assume its going to be as long as the entire input string
			if (!array_of_strings[inp_count]) { 						//make sure memory was allocated successfully
				printf ("\nError in String Passer\nError reallocating memory");
				return -1;
			}

			for (int i = 0; array_of_inputs[i] != NULL; i++) {				// start at the start of the input string, stop at the null terminator, move along by 1 each time
				if (array_of_inputs[i]!=' ') {								// if this character is NOT a space, put it in the current word
					array_of_strings[inp_count][j] = array_of_inputs[i];
					j++;										// j is for keeping track of how long the current word is
				}
				else if (j>0) {									// if the current character in the input is a space, AND the last character wasnt a space either
					array_of_strings[inp_count][j] = '\0';											// add a null terminator
					array_of_strings[inp_count] = (char*)realloc(array_of_strings[inp_count],j+1);	// trim the array down, save some memmory, we didnt always have thousands of bits to play with laddy
					if (!array_of_strings[inp_count]) {												// make sure that went ok.... or fail gracefully
						printf ("\nError in String Passer\nError reallocating memory");
						return -1;
					}
					inp_count++;													// HEY!! we just got to the end of the word!! should keep an eye on how many we've got so far
					array_of_strings[inp_count] = (char*)malloc (input_length-i);	//allocate some memory,and we wont ever need more than the lengh of the input array less what we've already dealt with
					if (!array_of_strings[inp_count]) { //make sure that went ok or fail gracefully
						printf ("\nError in String Passer\nError reallocating memory");
						return -1;
					}
					j = 0;																			// and make sure the other bit back up there ^^ knows we started a new word
				}
				else {
					continue;	// if we got here there was more than one space in a row sooooo... ignore that and carry on
				}
			}
			// HEY were at the end of the input string!!
			array_of_strings[inp_count][j] = '\0';	// dont forget the null terminator on the last word!!
			array_of_strings[inp_count] = (char*)realloc (array_of_strings[inp_count], j + 1);	//or to trim down the last word, remember what i said about saving bits,
			if (!array_of_strings[inp_count]) {	// if that didnt go well, probbly tell some one about it
				printf ("\nError in String Passer\nError reallocating memory\n");
				return -1;
			}
			if (strlen(array_of_strings[inp_count])>0){
				inp_count++; //make sure not to forget that last word!! Just be careful the last character wasn't a space
			}



			array_of_strings = (char**)realloc (array_of_strings, sizeof (*array_of_strings) * inp_count);// OH and remember how we thought every character might be its own word?? well it wasnt, so lets shrink this chunk of memmory down a bit
			if (!array_of_strings[inp_count]) {	// if that didnt go well... why not we were making the damn thing smaller????????? still tell some one though
				printf ("\nError in String Passer\nError reallocating memory\n");
				return -1;
			}


			*array_of_strings_p = array_of_strings; // let the boss upstrairs know where we put all of those words so he can find'm later
			return inp_count;					// and we should probably report how many we did so he doesnt go looking for too many

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
