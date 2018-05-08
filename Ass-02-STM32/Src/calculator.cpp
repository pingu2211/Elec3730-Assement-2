//Calculator functions

#include "Ass-02.h"

bool isNumber(char * str){												// checks input against ascii table
	for (int i=0;i<strlen(str);i++){									// makes sure input is a number
		if ( (str[i] < 48 || str[i] >57)&&!(str[i]==45||str[i]==46) ){
			if (USR_DBG)printf("is not a number\n");					// print debug messages
			return false;
		}
	}
	if (USR_DBG)printf("%s is %.5lf",str,atof(str));
	return true;
}


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
		sum += numbers[i];				// add each number to the sum of the previous numbers
	}									// where sum starts = 0
	printf("=%lf\n",sum);
	return 0;
}



int8_t multiply(char *numbers_p[], uint8_t count) {
	double * numbers =  malloc(count*sizeof(double));
	for (int i = 0; i < count; i++){
		if (!isNumber(numbers_p[i])){
			printf("Arguments must be real numbers");
			return -1;
		}else{
			numbers[i]=atof(numbers_p[i]);
		}
	}

	double sum = 1;
	for (int i = 0; i < count; i++)
	{

		sum *= numbers[i];
	}
	printf("=%lf\n",sum);
	return 0;
}


int8_t debug(char *args[], uint8_t count){
	if (count==0)USR_DBG=!USR_DBG;
	if (count==1){
		if (args[1]=="on"||args[1]=="ON"){

			USR_DBG=true;
		}else{
			USR_DBG=false;
		}
	}
	if (USR_DBG)printf("\nDEBUG ON\n");
	else printf("\nDEBUG OFF\n");
	return 0;
}


int8_t threshold(char *args[], uint8_t count){
	if(count == 0)printf("current threshold %i", _MOVEMENT_THRESHOLD);
	else if(count == 1){
		_MOVEMENT_THRESHOLD = atoi(args[0]);
	}

}













