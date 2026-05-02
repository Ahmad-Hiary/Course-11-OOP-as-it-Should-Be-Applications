#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

using namespace std;

class clsShowCurrencyCalculator : protected clsScreen
{
    static void _PrintCurrency(clsCurrency Currency)
    {
        
        cout << "----------------------------------------------\n";
        cout << "Country  : " << Currency.Country << endl;
        cout << "Code     : " << Currency.Code << endl;
        cout << "Name     : " << Currency.Name << endl;
        cout << "Rate(1$) : " << Currency.Rate << endl;
        cout << "----------------------------------------------\n";
        cout << endl;
    }

    static clsCurrency _GetCurrency(string Message)
    {
        clsCurrency Currency = clsCurrency::FindByCode("");

        do
        {
            cout << Message;
            Currency = clsCurrency::FindByCode(clsInputValidate::ReadString());
        } while (!Currency.IsCurrencyExists());

            return Currency;
    }

    static float _GetAmount(string Message)
    {
        cout << Message;
        float Amount = clsInputValidate::ReadFloatNumber();

        return Amount;
    }

    static void _GetConvertResult(clsCurrency Currency1, clsCurrency Currency2, float Amount)
    {
        if (Currency2.Code == "USD")
        {
            cout << "\nConvert From : \n";
            _PrintCurrency(Currency1);

            cout << "From " << Currency1.Code << " To USD : " << Currency1.ConvertToUsd(Amount);
        }
        else
        {
            cout << "\nConvert From : \n";
            _PrintCurrency(Currency1);

            cout << "\nFrom " << Currency1.Code << " To " << Currency2.Code << " : " << Currency1.ConvertToCurrency2(Currency2, Amount);
        }
    }

public :

    static void ShowCurrencyCalculator()
    {

        _DrawScreenHeader("Currency Exchange");

        clsCurrency Currency1 = _GetCurrency("\nEnter Currency [1] : ");
        _PrintCurrency(Currency1);

        clsCurrency Currency2 = _GetCurrency("\nEnter Currency [2] : ");
        _PrintCurrency(Currency2);

        float Amount = _GetAmount("\n\nEnter The Amount : ");

        _GetConvertResult(Currency1, Currency2, Amount);
        
    }
};

