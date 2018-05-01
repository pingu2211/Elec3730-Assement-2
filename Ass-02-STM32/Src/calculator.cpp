double divide (double N1, double N2) {
	return N1 / N2;
}

double subtract (double N1, double N2) {
	return N1 - N2;
}

double add(double *numbers_p, int count) {

	double sum = 0;

	for (int i = 0; i < count; i++)
	{
		sum += numbers_p[i];
	}
	return sum;
}



double multiply(double *numbers_p, int count) {

	double sum = 1;

	for (int i = 0; i < count; i++)
	{
		sum *= numbers_p[i];
	}
	return sum;
}
