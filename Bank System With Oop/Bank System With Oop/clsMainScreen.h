#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsupdateClient.h"
#include "clsFindClient.h"
#include "clsTransactionsMenu.h"
#include "clsManageUsersScreen.h"
#include "Global.h"
#include "clsRegisterLoginScreen.h"
#include "clsShowTransferLogScreen.h"
#include "clsCurrencyMainScreen.h"

class clsMainScreen : protected clsScreen
{

private:

    static enum _enOption { Show=1, Add=2, Delete=3, Update =4, Find =5, Transactions=6, ManageUsers=7,LogInRegisterInfo=8
        ,CurrencyExchange=9, Exit=10 };

    static void _ShowAllClientScreen()
    {
        clsClientListScreen::ShowClientsList();
    }
                
    static void _ShowAddUsersScreen()
    {
        clsAddNewClientScreen::AddNewClientScreen();
    }
                
    static void _ShowDeleteUserScreen()
    {
        clsDeleteClientScreen::DeleteClient();
    }
                
    static void _ShowUpdateUpdateScreen()
    {
        clsupdateClient::UpdateClient();

    }

    static void _ShowCurrencyExchangeScreen()
    {

        clsCurrencyMainScreen::ShowCurrenciesMenu();

    }

    static void _ShowTransferLogScreen()
    {
        clsShowTransferLogScreen::ShowTransferLog();
    }
                
    static void _ShowFindClientScreen()
    {
        clsFindClient::FindClient();
    }
                
    static void _ShowTransactionsMenu()
    {
        clsTransactionsMenu::TransactionsMenu();
    }
                
    static void _ShowManageUsersScreen()
    {
        clsManageUsersScreen::ShowManageUsersMenu();
    }
    static void _ShowLogInRegisterScreen()
    {
        clsRegisterLoginScreen::RegisterLoginList();
    }
                
    static void _GoBackToMainMenu()
    {
        cout << "\n";
        cout << setw(37) << left << "" << "Press Any Key To Go Back To Main Menu...";
        system("pause>0");
        ShowMainMenu();
    }
                
    static void _LogOut()
    {
        CurrentUser = clsBankUser::Find("", "");
    }

    static _enOption ReadMenuOption(const short From , const short To)
    {
        cout << setw(37) << left << "" << "Please enter your choice [ " << From << "-" << To << " ] : ";
        short Choice = clsInputValidate::ReadShortNumberInRange(From, To);

        return (_enOption)Choice;
    }
                
	static void _PerformMainMenuOpstion(_enOption Chosen)
    {
        switch (Chosen)
        {
        case Show:
        {
            system("cls");
            _ShowAllClientScreen();
            _GoBackToMainMenu();
            break;
        }

        case Add:
        {
            system("cls");
            _ShowAddUsersScreen();
            _GoBackToMainMenu();
            break;
        }

        case Delete:
        {
            system("cls");

            _ShowDeleteUserScreen();
            _GoBackToMainMenu();
            break;
        }

        case Update:
        {
            system("cls");
            _ShowUpdateUpdateScreen();
            _GoBackToMainMenu();
            break;
        }

        case Find:
        {
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenu();
            break;
        }

        case Transactions:
        {
            system("cls");
            _ShowTransactionsMenu();
            _GoBackToMainMenu();
            break;
        }

        case ManageUsers:
        {
            system("cls");
            _ShowManageUsersScreen();
            _GoBackToMainMenu();
           
            break;
        }
        case LogInRegisterInfo:
        {
            system("cls");
            _ShowLogInRegisterScreen();
            _GoBackToMainMenu();

            break;
        }
        ;
        case CurrencyExchange:
        {
            system("cls");
            _ShowCurrencyExchangeScreen();
            ShowMainMenu();

        }
        case Exit:
        {

            system("cls");
            _LogOut();

            break;
        }
       
        default:
        {
            system("cls");
            cout << "\nWrong option.\n";

            _GoBackToMainMenu();
            break;
        }
        }
    }

public:

	static void ShowMainMenu()
	{
		system("cls");

		_DrawScreenHeader("Main Screen");

		cout << setw(37) << left << "" << "====================================\n";
		cout << setw(37) << left << "" << "\t\t  Main menu\n";
		cout << setw(37) << left << "" << "====================================\n";
		cout << setw(37) << left << "" << "[1] Show Clients List\n";
		cout << setw(37) << left << "" << "[2] Add Client \n";
		cout << setw(37) << left << "" << "[3] Delete Client \n";
		cout << setw(37) << left << "" << "[4] Update Client \n";
		cout << setw(37) << left << "" << "[5] Find Client \n";
		cout << setw(37) << left << "" << "[6] Transactions Menu \n";
		cout << setw(37) << left << "" << "[7] Manage Users  \n";
        cout << setw(37) << left << "" << "[8] Login Register Info  \n";
        cout << setw(37) << left << "" << "[9] Currencies Exchange  \n";
		cout << setw(37) << left << "" << "[10] Log Out \n";
		cout << setw(37) << left << "" << "====================================\n";
        _PerformMainMenuOpstion(ReadMenuOption(1, 10));

	}

};

