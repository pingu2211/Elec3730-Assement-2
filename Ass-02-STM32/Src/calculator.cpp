//Calculator functions

#include "Ass-02.h"

bool isNumber(char * str){
	if (USR_DBG)printf("%s ",str);
	for (int i=0;i<strlen(str);i++){
		if ( (str[i] < 48 || str[i] >57)&&(str[i]!=45||str[i]!=46) ){
			if (USR_DBG)printf("is not a number\n");
			return false;
		}
	}
	if (USR_DBG)printf("is a number\n");
	printf("%s is %.5lf",str,atof(str));
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
	printf("adding %i numbers: ", count);
	for (int i = 0; i < count; i++)
		{
			printf("%s ",numbers_p[i]);
		}

	double sum = 0;

	for (int i = 0; i < count; i++)
	{
		if (isNumber(numbers_p[i])){
			sum += atof(numbers_p[i]);
		}else{

			printf("Arguments must be real numbers");
			return -1;
		}
	}
	printf("%i\n",sum);
	return 0;
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
	return 0;
}

















