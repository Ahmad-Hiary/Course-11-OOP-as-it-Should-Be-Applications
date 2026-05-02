#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iostream>
#include "clsInputValidate.h"

using namespace std;

class clsTransferScreen : protected clsScreen
{
private:

    //The default parameter to know what to read , source or destination client .
    static clsBankClient  _ReadClient(bool From=true)
    {
        string AccountNumber = "";

        
        if (From)
            cout << "Please enter an account number to transfer from : ";
        else
            cout << "Please enter an account number to transfer To : ";

            AccountNumber = clsString::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found ,Please enter a vaild account number name : ";
            AccountNumber = clsString::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        return Client;
    }

    static void _Print(clsBankClient Client)
    {
        cout << "\nClient Card\n";
        cout << "----------------------------------------------\n";
        cout << "Full Name      : " << Client.FullName() << endl;
        cout << "Account Number : " << Client.AccountNumber << endl;
        cout << "Balance        : " << Client.AccountBalance << endl;
        cout << "----------------------------------------------\n";
        cout << endl;
    }

public:

    static void ShowTransferScreen()
    {
        system("cls");

        clsScreen::_DrawScreenHeader("Tranfer");

        
        cout << endl;
        clsBankClient SourceClient = _ReadClient();
        _Print(SourceClient);
        clsBankClient DestinationClient = _ReadClient(0);
        _Print(DestinationClient);



        cout << "\n\nPlease enter the amount to transfer : ";
        double Amount=clsInputValidate::ReadDoubleNumberInRange(0,SourceClient.AccountBalance,"The Amount Exeeds The Balance ,Please enter a valid amount : ");

        cout << "Are you sure you want to Apply this transfer ? [Y/N] : ";
        char Answer;
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {
            if (SourceClient.Transfer(DestinationClient,CurrentUser.UserName, Amount))
                cout << "Transfer Done Succesfully .";
            else
                cout << "Transfer Faild .";
        }

        _Print(SourceClient);
        _Print(DestinationClient);
        }
      



    

};

