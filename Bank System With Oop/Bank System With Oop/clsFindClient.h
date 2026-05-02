#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsString.h"
using namespace std;

class clsFindClient : protected clsScreen
{
    static void _Print(clsBankClient Client)
    {
        cout << "\nClient Card\n";
        cout << "----------------------------------------------\n";
        cout << "First Name     : " << Client.FirstName << endl;
        cout << "Last  Name     : " << Client.LastName << endl;
        cout << "Full Name      : " << Client.FullName() << endl;
        cout << "Email          : " << Client.Email << endl;
        cout << "Phone          : " << Client.Phone << endl;
        cout << "Account Number : " << Client.AccountNumber << endl;
        cout << "PassWord       : " << Client.Pin << endl;
        cout << "Balance        : " << Client.AccountBalance << endl;
        cout << "----------------------------------------------\n";
        cout << endl;
    }

public:
    static void FindClient()
    {
        if (!CheckAccessAllowed(clsBankUser::enPermisstions::pFindClient))
            return;

        _DrawScreenHeader("Find Client");
        string AccountNumber = "";

        cout << "\nEnter account number : ";
        AccountNumber = clsString::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nThis account was not found, Enter another account number : ";
            AccountNumber = clsString::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        if (clsBankClient::IsEmpty(Client))
        {
            cout << "\nClient is empty .";
        }
        else
        {
            cout << "\nClient Found .";
        }

        _Print(Client);
    }
};