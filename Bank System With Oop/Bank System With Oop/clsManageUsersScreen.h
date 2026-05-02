#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsFindUserScreen.h"
#include "clsUpdateUserScreen.h"

using namespace std;

class clsManageUsersScreen : protected clsScreen
{

private:

    static enum _enOption { Show = 1, Add = 2, Delete = 3, Update = 4, Find = 5, Exit = 6 };

    static void _ShowUsersListScreen()
    {
        clsUsersListScreen::ShowUsersList();
    }

    static void _ShowAddUsersScreen()
    {
        clsAddNewUsertScreen::AddNewUsertScreen();
    }

    static void _ShowDeleteUserScreen()
    {
        clsDeleteUserScreen::DeleteUser();
    }

    static void _ShowUpdateScreen()
    {
        clsUpdateUser::UpdateUser();
    }

    static void _ShowFindUserScreen()
    {
        clsFindUser::FindUser();
    }

    static void _ShowManageUsersScreen()
    {
    }

    static void _GoBackToManageUsersMenu()
    {
        cout << "\n";
        cout << setw(37) << left << "" << "Press Any Key To Go Back To Manage Menu...";
        system("pause>0");
        ShowManageUsersMenu();
    }

    static void _MainMenu()
    {
        
    }

    static _enOption ReadMenuOption(const short From, const short To)
    {
        cout << setw(37) << left << "" << "Please enter your choice [ " << From << "-" << To << " ] : ";
        short Choice = clsInputValidate::ReadShortNumberInRange(From, To);

        return (_enOption)Choice;
    }

    static void _PerformMenuOption(_enOption Chosen)
    {
        switch (Chosen)
        {
        case Show:
        {
            system("cls");
            _ShowUsersListScreen();
            _GoBackToManageUsersMenu();
            break;
        }

        case Add:
        {
            system("cls");
            _ShowAddUsersScreen();
            _GoBackToManageUsersMenu();
            break;
        }

        case Delete:
        {
            system("cls");

            _ShowDeleteUserScreen();
            _GoBackToManageUsersMenu();
            break;
        }

        case Update:
        {
            system("cls");
            _ShowUpdateScreen();
            _GoBackToManageUsersMenu();
            break;
        }

        case Find:
        {
            system("cls");
            _ShowFindUserScreen();
            _GoBackToManageUsersMenu();
            break;
        }
        case Exit:
        {

            system("cls");
            _MainMenu();

            break;
        }

        default:
        {
            system("cls");
            cout << "\nWrong option.\n";

            _GoBackToManageUsersMenu();
            break;
        }
        }
    }

public:

    static void ShowManageUsersMenu()
    {
        if (!CheckAccessAllowed(clsBankUser::enPermisstions::pManageUsers))
            return;
        system("cls");

        _DrawScreenHeader("Manage Users Screen");

        cout << setw(37) << left << "" << "====================================\n";
        cout << setw(37) << left << "" << "\t\t  Manage menu\n";
        cout << setw(37) << left << "" << "====================================\n";
        cout << setw(37) << left << "" << "[1] Show Users List\n";
        cout << setw(37) << left << "" << "[2] Add User \n";
        cout << setw(37) << left << "" << "[3] Delete User \n";
        cout << setw(37) << left << "" << "[4] Update User \n";
        cout << setw(37) << left << "" << "[5] Find User \n";
        cout << setw(37) << left << "" << "[6] Main Menu  \n";
        cout << setw(37) << left << "" << "====================================\n";
        _PerformMenuOption(ReadMenuOption(1, 6));

    }

};


