#pragma once


#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsString.h"
#include "clsDeposit.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsShowTransferLogScreen.h"

using namespace std;


class clsTransactionsMenu:protected clsScreen
{
private:

	enum _enTransOptions{eDeposit=1,eWithdraw,eTotalBalances,eTransfer,eTranferLog,eMainMenu};

    static void _ShowDepositScreen() {
        clsDeposit::Deposit();
    }

    static void _GoBackTransactionsMenu() {

        cout << "\nPress Any Key To Go Back Transactions Menu...";
        system("pause>0");
        TransactionsMenu();
    }

    static void _ShowWithdrawScreen() {
        clsWithdrawScreen::Withdraw();
    }

    static void _ShowTransferLogScreen() {
        clsShowTransferLogScreen::ShowTransferLog();
    }

    static void _ShowTransferScreen() 
    {
        clsTransferScreen::ShowTransferScreen();
    }

    static void _ShowTotalBalancesScreen() {
        clsTotalBalancesScreen::ShowClientsTotalBalancesList();
    }

    static void _GoToMainMenu() {
        cout << "--- Go To Main Menu ---" << endl;
    }

    static void _PerformTranOption(_enTransOptions Chosen)
    {
        switch (Chosen) {
        case eDeposit:
            _ShowDepositScreen();
            _GoBackTransactionsMenu();
            break;
        case eWithdraw:
            _ShowWithdrawScreen();
            _GoBackTransactionsMenu();
            break;
        case eTotalBalances:
            _ShowTotalBalancesScreen();
            _GoBackTransactionsMenu();
            break;
        case eTranferLog:
            _ShowTransferLogScreen();
            _GoBackTransactionsMenu();
            break;
        case eMainMenu:
           
            break;
        case eTransfer:
            _ShowTransferScreen();
            _GoBackTransactionsMenu();
        default:
            cout << "Invalid choice! Please enter a number between 1 and 4." << endl;
            break;
        }

        
    }

    static _enTransOptions _ReadTransOption(const short From, const short To)
    {
        cout << setw(37) << left << "" << "Please enter your choice [ " << From << "-" << To << " ] : ";
        short Choice = clsInputValidate::ReadShortNumberInRange(From, To);

        return (_enTransOptions)Choice;
    }
    

public:

    static void TransactionsMenu()
    {

        if (!CheckAccessAllowed(clsBankUser::enPermisstions::pTransations))
            return;
        system("cls");

        _DrawScreenHeader("Transactions");

        cout << setw(37) << left << "" << "====================================\n";
        cout << setw(37) << left << "" << "\t\t  Transactions menu\n";
        cout << setw(37) << left << "" << "====================================\n";
        cout << setw(37) << left << "" << "[1] Depsit\n";
        cout << setw(37) << left << "" << "[2] Withdraw \n";
        cout << setw(37) << left << "" << "[3] Total Balances \n";
        cout << setw(37) << left << "" << "[4] Transfer \n";
        cout << setw(37) << left << "" << "[5] Transfer Log \n";
        cout << setw(37) << left << "" << "[6] Main Menu \n";
        cout << setw(37) << left << "" << "====================================\n";
        _PerformTranOption(_ReadTransOption(1, 6));
    }


};

