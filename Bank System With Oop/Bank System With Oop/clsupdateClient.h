#pragma once

#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsString.h"

using namespace std;

class clsupdateClient : protected clsScreen
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

    static void _ReadClientInfo(clsBankClient& Client)
    {

        cout << "\nEnter FirstName: ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "\nEnter PinCode: ";
        Client.Pin = clsInputValidate::ReadString();

        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadFloatNumber();

    }

public:

    static void UpdateClient()
    {
        if (!CheckAccessAllowed(clsBankUser::enPermisstions::pUpdateClient))
            return;

        string AccountNumber = "";

        _DrawScreenHeader("Update Client");

        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _Print(Client1);

        cout << "Are you sure you want to update this client ? [Y/N] : ";
        char Answer;
        cin >> Answer;

        if ('Y' == toupper(Answer))
        {
            _ReadClientInfo(Client1);

            clsBankClient::enSaveResult SaveResult;

            SaveResult = Client1.Save();

            switch (SaveResult)
            {
            case clsBankClient::enSaveResult::svSucceded:
            {
                cout << "\nAccount Updated Successfully :-)\n";
                _Print(Client1);
                break;
            }
            case clsBankClient::enSaveResult::svFailedEmptyObject:
            {
                cout << "\nError account was not saved because it's Empty";
                break;
            }

            }
        }

        system("pause>0");
    }

};