#pragma once


#include <iomanip>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsString.h"
#include "clsUtil.h"

class clsTotalBalancesScreen : protected clsScreen
{
private:

    static void _PrintClientRecordTotalBalances(clsBankClient Client)
    {
        cout << setw(37) << left << "" << "| " << setw(15) << left << Client.AccountNumber;
        cout << "| " << setw(20) << left << Client.FullName();
        cout << "| " << setw(12) << left << Client.AccountBalance;
    }

public:

    static void ShowClientsTotalBalancesList()
    {
        
        system("cls");

        vector<clsBankClient> vClients = clsBankClient::GetClientsList();

        cout << setw(37) << left << "" << "\t\tClient List (" << vClients.size() << ") Client(s).\n";
        cout << setw(37) << left << "" << "_______________________________________";
        cout << "__________\n" << endl;

        cout << setw(37) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Balance\n";
        cout << setw(33) << left << "" << "_______________________________________";
        cout << "__________\n" << endl;

        double TotalBalances = clsBankClient::GetClientsTotalBalances();

        if (vClients.size() == 0)
            cout << setw(37) << left << "" << "\t\t\t\tNo Clients Available In the System!";
        else
        {
            for (clsBankClient& Client : vClients)
            {
                _PrintClientRecordTotalBalances(Client);
                cout << endl;
            }

            cout << "\n" << setw(37) << left << "" << "_______________________________________";
            cout << "__________\n" << endl;

            cout << setw(30) << left << "" << "Total Balances " << TotalBalances
                << " { " << clsUtil::ConvertNumberToText(TotalBalances) << " } \n\n";
        }
    }
};