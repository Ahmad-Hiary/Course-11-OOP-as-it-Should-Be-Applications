#pragma once
#include<iostream>
#include "clsCurrency.h"
#include "clsScreen.h"

using namespace std;


class clsShowCurrenciesList : public clsScreen
{

    static void _PrintCurrencyRecord(clsCurrency Record)
    {
        cout << setw(8) << left << "" << "| " << setw(30) << left << Record.Country;
        cout << "| " << setw(13) << left << Record.Code;
        cout << "| " << setw(45) << left << Record.Name;
        cout << "| " << setw(13) << left << Record.Rate;
       
    }

public:

    static void ShowCurrenciesList()
    {

        system("cls");
        vector<clsCurrency> vRecords = clsCurrency::GetCurrenciesList();

        string Title = "Currencies List";
        string SubTitle = "\t (" + to_string(vRecords.size()) + ") Currency(s).";
        clsScreen::_DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_________________________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
        cout << "| " << left << setw(13) << "Code";
        cout << "| " << left << setw(45) << "Name";
        cout << "| " << left << setw(13) << "Rate";
       

        cout << setw(8) << left << "" << "\n\t_________________________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vRecords.size() == 0)
            cout << "\t\t\t\tNo Currencies Available!";
        else
        {
            for (clsCurrency Currency : vRecords)
            {
                _PrintCurrencyRecord(Currency);
                cout << endl;
            }
        }

        cout << setw(8) << left << "" << "\n\t_________________________________________________________________";
        cout << "_________________________________________\n" << endl;
    }


};

