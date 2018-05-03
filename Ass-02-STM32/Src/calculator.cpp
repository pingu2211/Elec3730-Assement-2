//Calculator functions

#include "Ass-02.h"

bool isNumber(char * str){
	for (int i=0;str[i]!='\0';i++){
		if ( (str[i] < 48 || str[i] >57)&&(str[i]!=45||str[i]!=46) )return false;
	}
	return true;
}


int8_t divide (char *numbers_p[], uint8_t count) {
	if (count < 2){
		printf("Too Few Arguments, got %i, expected 2",count);
		return NULL;
	}
	if (count > 2){
			printf("Too Many Arguments, got %i, expected 2", count);
			return NULL;
		}
	if (!isNumber(numbers_p[0])||!isNumber(numbers_p[1])){
		printf("Arguments must be real numbers");
		return NULL;
	}

	return (atof(numbers_p[0])/atof(numbers_p[1]));
}

int8_t subtract (char *numbers_p[], uint8_t count) {
	if (count < 2){
		printf("Too Few Arguments, got %i, expected 2",count);
		return NULL;
	}
	if (count > 2){
			printf("Too Many Arguments, got %i, expected 2", count);
			return NULL;
		}
	if (!isNumber(numbers_p[0])||!isNumber(numbers_p[1])){
		printf("Arguments must be real numbers");
		return NULL;
	}

	return (atof(numbers_p[0])-atof(numbers_p[1]));
}

int8_t add(char *numbers_p[], uint8_t count) {

	double sum = 0;

	for (int i = 0; i < count; i++)
	{
		if (!isNumber(numbers_p[i])){
				printf("Arguments must be real numbers");
				return NULL;
			}
		sum += atof(numbers_p[i]);
	}
	return sum;
}



int8_t multiply(char *numbers_p[], uint8_t count) {

	double sum = 1;

	for (int i = 0; i < count; i++)
	{
		if (!isNumber(numbers_p[i])){
				printf("Arguments must be real numbers");
				return NULL;
			}
		sum += atof(numbers_p[i]);
	}
	return sum;
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
}

















