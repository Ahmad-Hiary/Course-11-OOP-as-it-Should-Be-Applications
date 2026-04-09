#include <iostream>
#include "clsInputValidate.h"

using namespace std;

int main()
{
	int Number = clsInputValidate::ReadIntNumber("Please enter an int number : ");

	cout << "\n" << clsInputValidate::IsDateBetween(clsDate(), clsDate(1, 1, 2030), clsDate(1, 1, 1999));
}
