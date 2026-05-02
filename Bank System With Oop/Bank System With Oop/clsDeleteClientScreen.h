#pragma once

#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

using namespace std;

class clsDeleteClientScreen : protected clsScreen
{
private:

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

    static void DeleteClient()
    {
        if (!CheckAccessAllowed(clsBankUser::enPermisstions::pDeleteClient))
            return;

        string AccountNumber = "";

        _DrawScreenHeader("Delete Client");

        cout << "Please enter an account number : ";
        AccountNumber = clsString::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nWrong Account Number ,Please enter a valid account number : ";
            AccountNumber = clsString::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        _Print(Client);

        cout << setw(8) << left << "" << "Are you sure you want to delete this client ? Y/N : ";
        char Answer;
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {
            if (Client.Delete())
            {
                cout << setw(8) << left << "" << "\nDeleted Succesfully .";
            }
            else
            {
                cout << setw(8) << left << "" << "\nDelete Failed .";
            }
        }

    }

};