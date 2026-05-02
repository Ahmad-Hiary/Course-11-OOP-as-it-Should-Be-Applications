#pragma once
#include <iostream>
#include "clsCurrency.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;


class clsShowUpdateCurrencyScreen : protected clsScreen
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

public:

    static void ShowUpdateCurrencyScreen()
    {

        _DrawScreenHeader("Update Currency");

        cout << "\n\nEnter curreny code to update : ";
        clsCurrency Currency = clsCurrency::FindByCode(clsInputValidate::ReadString());

        if (Currency.IsCurrencyExists())
        {
            cout << "\n\nCurrency Found .\n";
            _PrintCurrency(Currency);

            cout << "\nEnter The New Rate : ";
            float NewRate = clsInputValidate::ReadFloatNumber();


            Currency.UpdateRate(NewRate);

            _PrintCurrency(Currency);
        }
    }
};

