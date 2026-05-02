#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "Global.h"
#include <vector>
using namespace std;

class clsShowTransferLogScreen : protected clsScreen
{
private:
    static void _PrintTransferRecordLine(clsBankClient::stTransferLogRecord Record)
    {
        cout << setw(8) << left << "" << "| " << setw(21) << left << Record.DateAndTime;
        cout << "| " << setw(13) << left << Record.SourceClient;
        cout << "| " << setw(13) << left << Record.DestinationClient;
        cout << "| " << setw(13) << left << Record.Amount;
        cout << "| " << setw(13) << left << Record.NewSourceClientBalance;
        cout << "| " << setw(13) << left << Record.NewDestinationClientBalance;
        cout << "| " << setw(13) << left << Record.UserName;
    }

public:
    static void ShowTransferLog()
    {

        system("cls");
        vector<clsBankClient::stTransferLogRecord> vRecords = clsBankClient::GetTrnsaferLogList();

        string Title = "Transfer Log Screen";
        string SubTitle = "\t (" + to_string(vRecords.size()) + ") Record(s).";
        clsScreen::_DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_________________________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(21) << "Date/Time";
        cout << "| " << left << setw(13) << "S.Account";
        cout << "| " << left << setw(13) << "D.Account";
        cout << "| " << left << setw(13) << "Amount";
        cout << "| " << left << setw(13) << "S.Balance";
        cout << "| " << left << setw(13) << "D.Balance";
        cout << "| " << left << setw(13) << "User";

        cout << setw(8) << left << "" << "\n\t_________________________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vRecords.size() == 0)
            cout << "\t\t\t\tNo Transfer Records Available!";
        else
        {
            for (clsBankClient::stTransferLogRecord Record : vRecords)
            {
                _PrintTransferRecordLine(Record);
                cout << endl;
            }
        }

        cout << setw(8) << left << "" << "\n\t_________________________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};