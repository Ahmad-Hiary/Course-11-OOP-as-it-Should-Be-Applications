#pragma once

#include <iostream>
#include <iomanip>
#include "clsDate.h"
#include "Global.h"
#include "clsBankUser.h"

using namespace std;
class clsScreen
{

protected:

    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << "\t\t\t\t______________________________________________";
        cout << "\n\n\t\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t______________________________________________\n";

        clsDate Date;
        cout << "\t\t\t\t\t\t "<< "User : " << CurrentUser.UserName;
        cout << "\n\t\t\t\t\t\t " << "Date : ";
        Date.Print();
        cout << "\n";
    }

    static bool CheckAccessAllowed(clsBankUser::enPermisstions OrderdToAccess)
    {
        if (!CurrentUser.CheckPermissionAccess(OrderdToAccess))
        {
            system("cls");
            _DrawScreenHeader("Acces Denied");
            return 0;
        }
        else
            return 1;
    }

};

