#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankUser.h"
#include "Global.h"
#include <vector>
using namespace std;

class clsRegisterLoginScreen : protected clsScreen
{
private:
    static void _PrintLoginRecordLine(clsBankUser::stLogInRegisterRecord Record)
    {
        cout << setw(8) << left << "" << "| " << setw(30) << left << Record.DateAndTime;
        cout << "| " << setw(15) << left << Record.UserName;
        cout << "| " << setw(10) << left << Record.PassWord;
        cout << "| " << setw(12) << left << Record.Permission;
    }

public:
    static void RegisterLoginList()
    {

        if (!CheckAccessAllowed(clsBankUser::enPermisstions::pLoginRegisterList))
            return;
        vector<clsBankUser::stLogInRegisterRecord> vRecords = clsBankUser::GetLogInInfoList();

        string Title = "Login Register Screen";
        string SubTitle = "\t (" + to_string(vRecords.size()) + ") Record(s).";
        clsScreen::_DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(30) << "Date/Time";
        cout << "| " << left << setw(15) << "UserName";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vRecords.size() == 0)
            cout << "\t\t\t\tNo Login Records Available!";
        else
        {
            for (clsBankUser::stLogInRegisterRecord Record : vRecords)
            {
                _PrintLoginRecordLine(Record);
                cout << endl;
            }
        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};