#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

using namespace std;


class clsShowFindCurrencyScreen : protected clsScreen
{

private:

	static void _PrintCurrency(clsCurrency Currency)
	{
        cout << "\nCurrency\n";
        cout << "----------------------------------------------\n";
        cout << "Country  : " << Currency.Country << endl;
        cout << "Code     : " << Currency.Code << endl;
        cout << "Name     : " << Currency.Name << endl;
        cout << "Rate(1$) : " << Currency.Rate << endl;
        cout << "----------------------------------------------\n";
        cout << endl;
	}

    static void _ShowResult(clsCurrency Currency)
    {
        if (!Currency.IsEmpty())
        {
            cout << "\n\nCurrency Found\n";
            _PrintCurrency(Currency);
        }
        else
        {
            cout << "\nCurrency Not Found\n";
        }
    }

public:

    static void ShowFindCurrencyScreen()
    {

        clsScreen::_DrawScreenHeader("Find Currency");

        cout << "\n\nFind By [1] Code or [2] Country ? ";
        short Answer = clsInputValidate::ReadShortNumberInRange(1, 2, "Wrong Answer ,Please Reanswer 1 or 2 : ");


        if (Answer == 1)
        {
            cout << "\nPlease enter code to find currency : ";
            string Code = clsInputValidate::ReadString();

            clsCurrency Currency = Currency.FindByCode(Code);

            _ShowResult(Currency);
        }
        else
        {
            cout << "\nPlease enter Country to find currency : ";
            string Country = clsInputValidate::ReadString();

            clsCurrency Currency = Currency.FindByCountry(Country);

            _ShowResult(Currency);
        }
    }



};

