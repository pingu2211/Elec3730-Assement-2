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
int8_t *Command_string; 										// Command string
int8_t (*Function_p)(uint8_t *numbers_p[], uint8_t num_count);	// Function pointer				//
int8_t *Help_s; 													// Help information
} command_s;


const command_s CommandList[] = {
{"add", &add, 		"add <num 1> .. <num N>"},
{"sub", &subtract, 	"sub <num 1> <num 2>"},
{"mul", &multiply, 	"mul <num 1> .. <num N>"},
{"div", &divide, 	"div <num 1> <num 2>"},
{"debug", &debug,	"Togggles debug messages (Optional arg <on|off>)"},
{"threshold",&threshold, "Ajusts the movement threshold for the touch screen"},
{NULL, NULL, NULL}
};


int8_t help(char *args[], uint8_t count){
	if (USR_DBG)printf("%s\n",args[0]);
		char **Args = &args[1];
		for (int i=0;CommandList[i].Command_string!=NULL;i++){
			if(strcmp(CommandList[i].Command_string,args[0])==0){
				printf("\%s\n",CommandList[i].Help_s);
			}
		}
		return 0;
}

int string_parser (char *inp, char **array_of_words_p[]) {
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
}

int isControlChar(char c){
	if (c<32||c==127) return true;
	else return false;
}

int _count=0;
char *input_s; // array which stores the characters
char **words;

void CommandLineParserInit(void)
{
  // Print welcome message
  printf("\014");
  printf("ELEC3730 Assignment 2\n");
  printf("Command Line Parser Example\n");
}

int Command_Function(int num_count, char **Array_numbers){
	if (USR_DBG)printf("%s\n",Array_numbers[0]);
	char **Args = &Array_numbers[1];
	for (int i=0;CommandList[i].Command_string!=NULL;i++){
		if(strcmp(CommandList[i].Command_string,Array_numbers[0])==0){
			if (USR_DBG)printf("first arg = %s\n",Args[0]);
			CommandList[i].Function_p(Args,num_count-1);
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
	HAL_GPIO_TogglePin(GPIOD, LD4_Pin); 				// Toggle LED4
	if (!isControlChar(c)){			// check that user entered a character and not a control character
		input_s=realloc(input_s, _count+1);
		printf("%c", c);
		input_s[_count]=c;	// store in the next element of array
		_count++;					// increase counter by 1
	} else {
		switch (c){
		case CR :			// case 1: if user presses "enter"
			printf("\n");
			// add \0 to the end of the string and then give it to q3 of assesment 1
			if (_count>0){
				input_s[_count] = '\0';	// add \0 to the end of the string
				wordcount = string_parser (input_s, &words);
				Command_Function(wordcount, words);
				if(USR_DBG)printf("%s\n",input_s);
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

	//new string passer 2 function - Will's edit

}


#else
  c = getchar();
  printf("SERIAL: Got '%c'\n", c);
#endif
}


int string_parser2(char *input_string, char **array_of_strings[])
	{
		 	 	 	 	 	 	 	 	// declare all the things
			int inp_count=0;			// this counts the number of strings entered separated by ' ' (space)
			int input_length = strlen (input_string);			// make sure the input string actually has something in it
			if (input_length <= 0) return 0;					// if input is empty return error
			for (int i=0; i<input_length; i++){
					if (input_string[i]==' '){
						input_string[i] = '\0';
					}
					if (i==0){
						*array_of_strings[input_length]=&input_string[i];
						inp_count++;
					}
					else if(input_string[i-1]=='\0'&&input_string[i]!=' '){
						array_of_strings[inp_count]=&input_string[i];
						inp_count++;
					}
			}
		return inp_count;
}


