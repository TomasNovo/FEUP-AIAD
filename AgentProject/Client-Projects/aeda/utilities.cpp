#include "utilities.h"

using namespace std;

template <class T>
//Swap the value of two integers
void utilities::swap(T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
}

// Remove spaces at the beginning and at the end of a string
void utilities::trimString(string &input)
{	
	while (input[0] == ' ')
		input.erase(input.begin());

	while (input.back() == ' ')
		input.erase(input.end() - 1);
}

// Caluclates the length of a string
int utilities::intSize(int input)
{
	int res = 0;

	while (input)
	{
		res++;
		input /= 10;
	}

	return res;
}

bool utilities::isNumeric(string input)
{
	utilities::trimString(input);

	if (input.size() == 0)
		return false;

	for (size_t i = 0; i < input.size(); i++)
	{
		if (input[i] < '0' || input[i] > '9')
			return false;
	}

	return true;
}
