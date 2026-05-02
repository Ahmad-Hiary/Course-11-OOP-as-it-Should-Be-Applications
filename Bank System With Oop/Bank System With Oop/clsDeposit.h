#pragma once

#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsString.h"

using namespace std;

class clsDeposit : protected clsScreen
{
    static void _Print(clsBankClient Client)
    {
        cout << "\nClient Card\n";
        cout << "----------------------------------------------\n";
        cout << "Full Name      : " << Client.FullName() << endl;
        cout << "Email          : " << Client.Email << endl;
        cout << "Phone          : " << Client.Phone << endl;
        cout << "Account Number : " << Client.AccountNumber << endl;
        cout << "Balance        : " << Client.AccountBalance << endl;
        cout << "----------------------------------------------\n";
        cout << endl;
    }

public:

    static void Deposit()
    {
        

        system("cls");

        _DrawScreenHeader("Deposit");

        string AccountNumber;

        cout << "Please enter an Account Number : ";
        AccountNumber = clsString::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nThis account is not exist please enter a valid Account Number : ";
            AccountNumber = clsString::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        _Print(Client);

        cout << "\n\nPlease enter the Amount to deposit : ";
        double Amount = clsInputValidate::ReadDblNumber();

        char Answer;

        cout << "\nAre you sure you complete this transaction ? [Y/N] : ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {
            Client.Deposit(Amount);
            cout << "\nDeposit Succesfully :-)";

            cout << "\n\nThe new balance : " << Client.AccountBalance;
        }
        else
        {
            cout << "\nThe Action Canceled\n\n";
        }
    }
};