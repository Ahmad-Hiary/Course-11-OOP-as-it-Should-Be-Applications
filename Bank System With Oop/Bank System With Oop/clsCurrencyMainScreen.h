#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsShowCurrenciesList.h"
#include "Global.h"
#include "clsShowFindCurrencyScreen.h"
#include "clsShowUpdateCurrencyScreen.h"
#include "clsShowCurrencyCalculator.h"

using namespace std;

class clsCurrencyMainScreen : protected clsScreen
{
private:
    static enum _enOption { ShowList = 1, Find = 2, Update = 3, CurrencyCalculator = 4, Exit = 5 };

    static void _ShowCurrenciesListScreen()
    {
        clsShowCurrenciesList::ShowCurrenciesList();
    }

    static void _ShowFindCurrencyScreen()
    {
        clsShowFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void _ShowUpdateCurrencyRateScreen()
    {
        clsShowUpdateCurrencyScreen::ShowUpdateCurrencyScreen();
    }

    static void _ShowCurrencyCalculatorScreen()
    {
        clsShowCurrencyCalculator::ShowCurrencyCalculator();
    }

    static void _GoBackToCurrencyMenu()
    {
        cout << "\n";
        cout << setw(37) << left << "" << "Press Any Key To Go Back To Currencies Menu...";
        system("pause>0");
        ShowCurrenciesMenu();
    }

    static _enOption _ReadMenuOption(const short From, const short To)
    {
        cout << setw(37) << left << "" << "Please enter your choice [ " << From << "-" << To << " ] : ";
        short Choice = clsInputValidate::ReadShortNumberInRange(From, To);
        return (_enOption)Choice;
    }

    static void _PerformMenuOption(_enOption Chosen)
    {
        switch (Chosen)
        {
        case ShowList:
        {
            system("cls");
            _ShowCurrenciesListScreen();
            _GoBackToCurrencyMenu();
            break;
        }
        case Find:
        {
            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToCurrencyMenu();
            break;
        }
        case Update:
        {
            system("cls");
            _ShowUpdateCurrencyRateScreen();
            _GoBackToCurrencyMenu();
            break;
        }
        case CurrencyCalculator:
        {
            system("cls");
            _ShowCurrencyCalculatorScreen();
            _GoBackToCurrencyMenu();
            break;
        }
        case Exit:
        {
            system("cls");
            break;
        }
        default:
        {
            system("cls");
            cout << "\nWrong option.\n";
            _GoBackToCurrencyMenu();
            break;
        }
        }
    }

public:
    static void ShowCurrenciesMenu()
    {
        system("cls");
        _DrawScreenHeader("Currencies Exchange\t\t\t");

        cout << setw(37) << left << "" << "====================================\n";
        cout << setw(37) << left << "" << "\t  Currencies Menu\n";
        cout << setw(37) << left << "" << "====================================\n";
        cout << setw(37) << left << "" << "[1] Show Currencies List\n";
        cout << setw(37) << left << "" << "[2] Find Currency\n";
        cout << setw(37) << left << "" << "[3] Update Currency Rate\n";
        cout << setw(37) << left << "" << "[4] Currency Calculator\n";
        cout << setw(37) << left << "" << "[5] Exit\n";
        cout << setw(37) << left << "" << "====================================\n";

        _PerformMenuOption(_ReadMenuOption(1, 5));
    }
};