//Calculator functions

#include <stdio.h>
#include<stdint.h>

double divide (double N1, double N2) {
	return N1 / N2;
}

double subtract (double N1, double N2) {
	return N1 - N2;
}

int8_t add(uint8_t *numbers_p[], uint8_t count) {

	double sum = 0;

	for (int i = 0; i < count; i++)
	{
		sum += numbers_p[i];
	}
	return sum;
}



int8_t multiply(uint8_t *numbers_p[], uint8_t count) {

	double sum = 1;

	for (int i = 0; i < count; i++)
	{
		sum *= numbers_p[i];
	}
	return sum;
}
