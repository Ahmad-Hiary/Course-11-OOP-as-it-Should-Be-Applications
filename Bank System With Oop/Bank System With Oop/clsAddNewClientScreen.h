#pragma once

#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

using namespace std;

class clsAddNewClientScreen : protected clsScreen
{
private:

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

    static void AddNewClientScreen()
    {
        if (!CheckAccessAllowed(clsBankUser::enPermisstions::pAddClient))
            return;

        clsScreen::_DrawScreenHeader("Add New Client Screen");

        string AccountNumber = "";

        cout << "Please enter an account number : ";
        AccountNumber = clsString::ReadString();

        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount Number already exists ,Please enter a new account number : ";
            AccountNumber = clsString::ReadString();
        }

        clsBankClient Client = clsBankClient::GetAddNewClientObject(AccountNumber);

        _ReadClientInfo(Client);

        clsBankClient::enSaveResult Result = Client.Save();

        switch (Result)
        {
        case clsBankClient::svFailedEmptyObject:
        {
            cout << "Update Failed its an Empty Object .";
            break;
        }
        case clsBankClient::svSucceded:
        {
            cout << "Added Succesfully .";
            _Print(Client);
            break;
        }
        }

    }

};