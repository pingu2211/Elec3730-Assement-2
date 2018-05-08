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
int8_t help(char *args[], uint8_t count);
int string_parser (char *input_string, char **array_of_strings[]);

typedef struct{
int8_t *Command_string; 											// Command string
int8_t (*Function_p)(uint8_t *numbers_p[], uint8_t num_count);		// Function pointer				//
int8_t *Help_s; 													// Help information
} command_s;

const command_s CommandList[] = {												// structure holding list of commands and their help displays.
{"add", 		&add, 		"add <num 1> .. <num N>"},							// addition function
{"sub", 		&subtract, 	"subtract <num 1> <num 2>"},						// subtraction function
{"mul", 		&multiply, 	"multiply <num 1> .. <num N>"},						// multiplication function
{"div", 		&divide, 	"divide <num 1> <num 2>"},							// division function
{"debug", 		&debug,		"Togggles debug messages (Optional arg <on|off>)"},	// debug messages on and off
{NULL, 			NULL, 		NULL}
};


int8_t help(char *args[], uint8_t count){ 		// help function to display command help messages
	if (USR_DBG)printf("%s\n",args[0]);
		for (int i=0;CommandList[i].Command_string!=NULL;i++){  	// compare the help command

			if(strcmp(CommandList[i].Command_string,args[0])==0){
				printf("\%s\n",CommandList[i].Help_s);
			}
			if (count==0){												// when user types 'help' and no command
				for (int h=0;CommandList[h].Command_string!=NULL;h++)
				printf("\%s\n",CommandList[h].Help_s);					// print ALL command help messages
			}
		}
		return 0;
}


/*int string_parser2 (char *inp, char **array_of_words_p[]) {
=======
int string_parser (char *inp, char **array_of_words_p[]) {
>>>>>>> 3696a74a3131e8dd6c76137fb058e939147580bf
	int word_count=0;
	int j = 0;
	int input_lenght = strlen (inp);
	if (input_lenght == 0) { return 0; }
	char** array_of_words;
	array_of_words = (char**)malloc(sizeof( *array_of_words) * input_lenght);
	array_of_words[word_count] = (char*)malloc(input_lenght);

	if (*array_of_words){
		for (int i = 0; inp[i] != NULL; i++) {
			if (inp[i]!=' ') {
				array_of_words[word_count][j] = inp[i];
				j++;
			}
			else if (j>0) {
				array_of_words[word_count][j] = '\0';
				array_of_words[word_count] = (char*)realloc(array_of_words[word_count],j+1);
				if (!array_of_words[word_count]) {
					printf ("Error in String Passer\nerror reallocsting memmory");
					return -1;
				}
				word_count++;
				array_of_words[word_count] = (char*)malloc (input_lenght);
				j = 0;
			}
			else {
				continue;
			}
		}

		array_of_words[word_count][j] = '\0';
		array_of_words[word_count] = (char*)realloc (array_of_words[word_count], j + 1);

		if (!array_of_words[word_count]) {
			printf ("Error in String Passer\nerror reallocsting memmory");
			return -1;
		}
		word_count++;
		array_of_words[word_count] = (char*)malloc (input_lenght);
		j = 0;

	}
	else {
		printf ("Error in String Passer\nerror allocsting memmory");
		return -1;
	}
	array_of_words = (char**)realloc (array_of_words, sizeof (*array_of_words) * word_count);
	*array_of_words_p = array_of_words;
	if (USR_DBG)printf ("WordCount = %d\n", word_count);
	return word_count;
}*/

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

int Command_Function(int num_count, char **Array_numbers){				// function takes input from user and compares the command with list of commands
	if (USR_DBG)printf("%s\n",Array_numbers[0]);						// each command references a particular function (add, multiply, etc.)
	char **Args = &Array_numbers[1];
	for (int i=0;CommandList[i].Command_string!=NULL;i++){
		if(strcmp(CommandList[i].Command_string,Array_numbers[0])==0){	// compare input string to command list
			if (USR_DBG)printf("first arg = %s\n",Args[0]);				// implemented debug messages
			CommandList[i].Function_p(Args,num_count-1);				// reference to function the user has entered.
		}
	}
	return 0;
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
				wordcount = string_parser2 (input_s, &words); 	// call string parser function
				Command_Function(wordcount, words);
				if(USR_DBG)printf("%s\n",input_s);				// prints debug messages
				_count = 0;
			}
			break;
		case DEL:			// case 2: if user presses "backspace"
			printf("\b");
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


int string_parser2(char *input_string, char **array_of_strings[])
	{
			int inp_count=0;							// this counts the number of strings entered separated by ' ' (space)
			int input_length = strlen (input_string);	// make sure the input string actually has something in it
			if (input_length <= 0) return 0;			// if input is empty return error
			for (int i=0; i<input_length; i++){
					if (input_string[i]==' '){			// if input array element 'i' is a 'space', make that array element \0
						input_string[i] = '\0';
					}
					if (i==0){												//if it is the first input element make pointer to first word in input string
						*array_of_strings[input_length]=&input_string[i];
						inp_count++;										// increase the word count by 1
					}
					else if(input_string[i-1]=='\0'&&input_string[i]!=' '){	// if previous element of the input string is a space (or now \0)
						array_of_strings[inp_count]=&input_string[i];		// make pointer to new string inside the array
						inp_count++;
					}														// then increase word count by 1
			}
		return inp_count;
}


