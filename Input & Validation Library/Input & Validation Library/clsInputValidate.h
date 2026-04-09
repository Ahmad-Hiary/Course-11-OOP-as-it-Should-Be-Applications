#pragma once
#include <iostream>
#include "clsDate.h"

using namespace std;


class clsInputValidate
{
public:


	static bool IsNumberBetween(const int Number, const int From, const int To)
	{
		return (Number >= From && Number <= To );
	}
	static bool IsNumberBetween(const short Number, const short From, const short To)
	{
		return (Number >= From && Number <= To);
	}
	static bool IsNumberBetween(const float Number, const float From, const float To)
	{
		return (Number >= From && Number <= To );
	}
	static bool IsNumberBetween(const double Number, const double From, const double To)
	{
		return (Number >= From && Number <= To );
	}
	static bool IsDateBetween( const clsDate Date,  clsDate From,  clsDate To)
	{
		if (clsDate::IsDate1BeforeDate2(To, From))
		{
			clsDate::Swap2Dates(From, To);
		}

		return !(clsDate::IsDate1BeforeDate2(To, Date) || clsDate::IsDate1AfterDate2(From, Date));
	}

	static int ReadIntNumber(string ErrorMessage)
	{
		int Number = 0;

		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << ErrorMessage;
		}
		return Number;
	}
	static int ReadIntNumberInRange(int from, int to,string Message="Number is Not within the range .")
	{
		int Number = ReadIntNumber("Invalid Number");

		while (!IsNumberBetween(Number, from, to))
		{
			cout << Message ;
			Number = ReadIntNumber("Invalid Number ,enter a valid number : ");
		} 

		return Number;
	}


	static double ReadDblNumber(string ErrorMessage)
	{
		double Number = 0;

		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << ErrorMessage;
			
			
		}

		return Number;
	}
	static double ReadDoubleNumberInRange(double from, double to, string ErrorMessage = "Number is Not within the range .")
	{
		double Number = 0;
		while (IsNumberBetween(Number,from,to))
		{
			cout << ErrorMessage ;
			Number = ReadDblNumber("Number is Not within the range .");
		} 

		return Number;
	}

	static bool IsValidDate(clsDate Date)
	{
		return clsDate::IsDateValid(Date);
	}

	static int ReadOddNumber(string Messege)
	{
		int Number = 0;
		do
		{
			cout << Messege << "\n";
			cin >> Number;
		} while (Number % 2 == 0);

		return Number;
	}
	static int ReadEvenNumber(string Messege)
	{
		int Number = 0;
		do
		{
			cout << Messege << "\n";
			cin >> Number;
		} while (Number % 2 != 0);

		return Number;
	}
};

