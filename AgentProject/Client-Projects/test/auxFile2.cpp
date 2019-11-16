#include "auxFile2.h"

//Should be 165
int count2()
{
	int aux = 0;
	int res = 0;

	for (int i = 0; i < 10; ++i)
	{
		aux += i;
		res += aux;
	}

	return res;
}