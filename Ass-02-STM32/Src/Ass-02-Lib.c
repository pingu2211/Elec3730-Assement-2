//     $Date: 2018-03-26 08:32:18 +1100 (Mon, 26 Mar 2018) $
// $Revision: 1217 $
//   $Author: Peter $

#include "Ass-02.h"

// STEPIEN: Added two touch panel functions to make the interface more
//          consistent with the LCD BSP.
bool USR_DBG = false;


#ifdef STM32F407xx
uint8_t BSP_TP_Init(void)
{
  // Initialise the interface and calibrate
  TP_Init(); // This is an empty function since done by STM32CubeMX
  TouchPanel_Calibrate();
  return 0;
}
/************************************************************************************************/
uint8_t BSP_TP_GetDisplayPoint(Coordinate *pDisplay)
{
  Coordinate *pScreen;

  pScreen = Read_Ads7846();
  if (pScreen == NULL)
  {
    return 1; // Error reading the touch panel
  }
  if (getDisplayPoint(pDisplay, pScreen, &matrix ) == DISABLE)
  {
	printf("Error in LCD\n");
    return -1; // Error in LCD
  }
  return 0;
}
/************************************************************************************************/
#endif

//Calculator functions
/************************************************************************************************/
bool isNumber(char * str){												// checks input against ascii table
	for (int i=0;i<strlen(str);i++){									// makes sure input is a number
		if ( (str[i] < 48 || str[i] >57)&&!(str[i]==45||str[i]==46) ){
			if (USR_DBG)printf("is not a number\n");					// print debug messages
			return false;
		}
	}
	if (USR_DBG)printf("\n|%s|string is |%lf|double\n",str,atof(str));
	return true;
}
/************************************************************************************************/
int8_t divide (char *numbers_p[], uint8_t count) {			// function divides 2 numbers returns answer
	double * numbers =  malloc(count*sizeof(double));		// allocate memory for input numbers
	if (count!=2) return -1;								// make sure user entered 2 numbers (no more no less)
		for (int i = 0; i < count; i++){
			if (!isNumber(numbers_p[i])){					// if input is not a number
				printf("Arguments must be real numbers");	// return a message to user that the input was not a number
				return -1;
			}else{
				numbers[i]=atof(numbers_p[i]);				// take the input number that is a string of characters and convert to a double
			}
		}
		printf("=%lf",numbers[0]/numbers[1]);				// divide the 1st input number by the 2nd and print result
		return (0);
}
/************************************************************************************************/
int8_t subtract (char *numbers_p[], uint8_t count) {		// function subtracts 1 number from another

	double * numbers =  malloc(count*sizeof(double));		// allocate memory for input numbers
	if (count!=2) return -1;								// make sure user entered 2 numbers (no more no less)
	for (int i = 0; i < count; i++){
		if (!isNumber(numbers_p[i])){						// if input is not a number
			printf("Arguments must be real numbers");		// return a message to user that the input was not a number
			return -1;
		}else{
			numbers[i]=atof(numbers_p[i]);					// take the input number that is a string of characters and convert to a double
		}
	}
	printf("=%lf",numbers[0]-numbers[1]);					// subtract 2nd number from 1st and print result
	return (0);
}
/************************************************************************************************/
int8_t add(char *numbers_p[], uint8_t count) {				// function adds 2 or more numbers

	double * numbers =  malloc(count*sizeof(double));		// allocate memory for input numbers
	for (int i = 0; i < count; i++){
		if (!isNumber(numbers_p[i])){						// if input is not a number
			printf("Arguments must be real numbers");		// return a message to user that the input was not a number
			return -1;
		}else{
			numbers[i]=atof(numbers_p[i]);					// take the input number that is a string of characters and convert to a double
		}
	}
	double sum = 0;
	for (int i = 0; i < count; i++)
	{
		sum += numbers[i];				// add each number to the sum of the previous numbers where sum starts = 0
	}
	printf("=%lf\n",sum);				// print the result of all numbers summed together
	return 0;
}
/************************************************************************************************/
int8_t multiply(char *numbers_p[], uint8_t count) {			// function multiplies 2 or more numbers together
	printf("\ncount:%i\n",count);
	double * numbers =  malloc(count*sizeof(double));		// allocate memory for input numbers
	for (int i = 0; i < count; i++){
		if (!isNumber(numbers_p[i])){						// if input is not a number
			printf("Arguments must be real numbers");		// return a message to user that the input was not a number
			return -1;
		}else if (strlen(numbers_p[i])>0){
			numbers[i]=atof(numbers_p[i]);					// take the input number that is a string of characters and convert to a double
		}
	}

	double sum = 1;
	for (int i = 0; i < count; i++)
	{
		sum *= numbers[i];				// multiply each number together with first number multiplied by 1
	}
	printf("=%lf\n",sum);				// print result
	return 0;
}
/************************************************************************************************/
int8_t debug(char *args[], uint8_t count){		// function that is used to turn debug messages on and off
	if (count==0)USR_DBG=!USR_DBG;				// if user enters only debug (1 word), switch debug status. ie if ON then switch to OFF
	if (count==1){
		if (strcmp(args[1],"on")==0||strcmp(args[1],"ON")==0){	// checks if user entered the command 'debug on (or ON)'
			USR_DBG=true;										// if so, turn debug messages on
		}else{
			USR_DBG=false;										// if user types anything else, ie 'debug off'
		}														// switch debug messages off
	}
	if (USR_DBG)printf("\nDEBUG ON\n");		// print ON or OFF when debug message settings are switched
	else printf("\nDEBUG OFF\n");
	return 0;
}
/************************************************************************************************/
int8_t clear(char *args[], uint8_t count){	// function clears the terminal window

	printf("\nclear\n");
	printf("\e[1;1H\e[2J");
	return 0;
}
/************************************************************************************************/

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
{"clear",       &clear,      "clears the terminal"},
{NULL, 			NULL, 		NULL}
};


int8_t help(char *args[], uint8_t count){   // help function to display command help messages
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
/************************************************************************************************/
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
/************************************************************************************************/
int string_parser (char *inp, char **array_of_words_p[]) {
	int word_count=0;								// counts amount of input strings
	int j = 0;										// counts number of characters in each string
	int input_lenght = strlen (inp);
	if (input_lenght == 0) { return 0; }			// end if the input was empty
	char** array_of_words;							// pointer to array of input strings
	array_of_words = (char**)malloc(sizeof( *array_of_words) * input_lenght);	// allocate memory for array of strings
	array_of_words[word_count] = (char*)malloc(input_lenght);					// allocate memory for each individual string in the input string

	if (*array_of_words){
		for (int i = 0; inp[i] != NULL; i++) {				// for loop that goes through each character of the input and checks it
			if (inp[i]!=' ') {								// if the input character is not a space
				array_of_words[word_count][j] = inp[i];		// element j of the current string = the input character
				j++;										// increase word letter counter by 1
			}
			else if (j>0) {									// if input character is a space
				array_of_words[word_count][j] = '\0';		// end the string with a NULL
				array_of_words[word_count] = (char*)realloc(array_of_words[word_count],j+1); // allocate memory for the NULL
				if (!array_of_words[word_count]) {
					printf ("Error in String Passer\nerror reallocating memory"); 	// print error if error occurred allocating memory
					return -1;
				}
				word_count++;												// increase the word counter by 1
				array_of_words[word_count] = (char*)malloc (input_lenght);	// allocate memory for string
				j = 0;

			}else{
				j=0;
				continue;
			}

		array_of_words[word_count][j] = '\0';												// end string with NULL
		array_of_words[word_count] = (char*)realloc (array_of_words[word_count], j + 1); 	// allocate memory for the NULL

		if (!array_of_words[word_count]) {
			printf ("Error in String Passer\nerror reallocating memory");	// print error if memory allocation failed
			return -1;
		}
		word_count++;													// increase word count by 1
		array_of_words[word_count] = (char*)malloc (input_lenght);		// allocate memory for size of input string
		j = 0;
		}

		if(j>0){
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
	}
	else {
		printf ("Error in String Passer\nerror allocating memory");		// print error message if memory allocation failed
		return -1;
	}
	array_of_words = (char**)realloc (array_of_words, sizeof (*array_of_words) * word_count); // allocate memory for size of array of strings
	*array_of_words_p = array_of_words;							// pointer to array of words
	if (USR_DBG)printf ("WordCount = %d\n", word_count);		// debug messages
	return word_count;
}
