//Calculator functions

#include "Ass-02.h"

bool isNumber(char * str){
	for (int i=0;i<strlen(str);i++){
		if ( (str[i] < 48 || str[i] >57)&&!(str[i]==45||str[i]==46) ){
			if (USR_DBG)printf("is not a number\n");
			return false;
		}
	}
	if (USR_DBG)printf("%s is %.5lf",str,atof(str));
	return true;
}


int8_t divide (char *numbers_p[], uint8_t count) {
	double * numbers =  malloc(count*sizeof(double));
		for (int i = 0; i < count; i++){
			if (!isNumber(numbers_p[i])){
				printf("Arguments must be real numbers");
				return -1;
			}else{
				numbers[i]=atof(numbers_p[i]);
			}
		}
		printf("=%lf",numbers[0]/numbers[1]);
		return (0);
}

int8_t subtract (char *numbers_p[], uint8_t count) {

	double * numbers =  malloc(count*sizeof(double));
	if (count!=2) return -1;
	for (int i = 0; i < count; i++){
		if (!isNumber(numbers_p[i])){
			printf("Arguments must be real numbers");
			return -1;
		}else{
			numbers[i]=atof(numbers_p[i]);
		}
	}
	printf("=%lf",numbers[0]-numbers[1]);
	return (0);
}

int8_t add(char *numbers_p[], uint8_t count) {
	double * numbers =  malloc(count*sizeof(double));
	for (int i = 0; i < count; i++){
		if (!isNumber(numbers_p[i])){
			printf("Arguments must be real numbers");
			return -1;
		}else{
			numbers[i]=atof(numbers_p[i]);
		}
	}


	double sum = 0;
	for (int i = 0; i < count; i++)
	{
		sum += numbers[i];
	}
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













