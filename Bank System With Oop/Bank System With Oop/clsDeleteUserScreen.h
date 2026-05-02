#pragma once
#include <iostream>
#include <iomanip>
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsBankUser.h"
using namespace std;

class clsDeleteUserScreen : protected clsScreen
{
private:
    static void _Print(clsBankUser User)
    {
        cout << "\nUser Card\n";
        cout << "----------------------------------------------\n";
        cout << "First Name     : " << User.FirstName << endl;
        cout << "Last  Name     : " << User.LastName << endl;
        cout << "Full Name      : " << User.FullName << endl;
        cout << "Email          : " << User.Email << endl;
        cout << "Phone          : " << User.Phone << endl;
        cout << "User Name      : " << User.UserName << endl;
        cout << "PassWord       : " << User.Password << endl;
        cout << "Permissions    : " << User.Permissions << endl;
        cout << "----------------------------------------------\n";
        cout << endl;
    }

public:
    static void DeleteUser()
    {
        string UserName = "";
        _DrawScreenHeader("Delete User");
        cout << "Please enter a username : ";
        UserName = clsString::ReadString();

        while (!clsBankUser::IsUserExists(UserName))
        {
            cout << "\nWrong Username, Please enter a valid username : ";
            UserName = clsString::ReadString();
        }

        clsBankUser User = clsBankUser::Find(UserName);
        _Print(User);

        cout << setw(8) << left << "" << "Are you sure you want to delete this user ? Y/N : ";
        char Answer;
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {
            if (User.Delete())
            {
                cout << setw(8) << left << "" << "\nDeleted Successfully .";
            }
            else
            {
                cout << setw(8) << left << "" << "\nDelete Failed .";
            }
        }
    }
};