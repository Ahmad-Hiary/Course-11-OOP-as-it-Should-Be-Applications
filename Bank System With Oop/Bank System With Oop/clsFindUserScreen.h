#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankUser.h"
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsString.h"
using namespace std;

class clsFindUser : protected clsScreen
{
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
    static void FindUser()
    {
        _DrawScreenHeader("Find User");
        string UserName = "";

        cout << "Please enter an user name : ";
        UserName = clsInputValidate::ReadString();

        while (!clsBankUser::IsUserExists(UserName))
        {
            cout << "\n\nThis user was not found, Enter another username : ";
            UserName = clsString::ReadString();
        }

        clsBankUser User = clsBankUser::Find(UserName);

        if (clsBankUser::IsEmpty(User))
        {
            cout << "\nUser is empty .";
        }
        else
        {
            cout << "\nUser Found .";
        }

        _Print(User);
    }
};