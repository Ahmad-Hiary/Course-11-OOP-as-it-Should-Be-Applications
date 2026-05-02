#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankUser.h"
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsString.h"
using namespace std;

class clsUpdateUser : protected clsScreen
{
private:
    static void _Print(clsBankUser User)
    {
        cout << "\nUser Card\n";
        cout << "----------------------------------------------\n";
        cout << "First Name     : " << User.FirstName << endl;
        cout << "Last  Name     : " << User.LastName << endl;
        cout << "Full Name      : " << User.FullName << endl;
        cout << "Email          : " << User.Email << endl;
        cout << "Phone          : " << User.Phone << endl;
        cout << "User Name      : " << User.UserName << endl;
        cout << "PassWord       : " << User.Password << endl;
        cout << "Permissions    : " << User.Permissions << endl;
        cout << "----------------------------------------------\n";
        cout << endl;
    }

    static void _ReadUserInfo(clsBankUser& User)
    {
        cout << "\nEnter FirstName: ";
        User.FirstName = clsInputValidate::ReadString();
        cout << "\nEnter LastName: ";
        User.LastName = clsInputValidate::ReadString();
        cout << "\nEnter Email: ";
        User.Email = clsInputValidate::ReadString();
        cout << "\nEnter Phone: ";
        User.Phone = clsInputValidate::ReadString();
        cout << "\nEnter Password: ";
        User.Password = clsInputValidate::ReadString();
        cout << "\nEnter Permissions: ";
        User.Permissions = _ReadPermissions();
    }

    static short _ReadPermissions()
    {
        short Permission = 0;

        char Answer = 'y';

        cout << "Please Choose what access you want to give .\n\n ";

        cout << "Do you want to five full access Y/N : ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
            Permission = -1;
        else
        {
            cout << "\n\nShow client list Y/N : ";
            cin >> Answer;
            if (toupper(Answer) == 'Y')
                Permission += clsBankUser::enPermisstions::pShowList;

            cout << "\nAdd client Y/N : ";
            cin >> Answer;
            if (toupper(Answer) == 'Y')
                Permission += clsBankUser::enPermisstions::pAddClient;

            cout << "\nUpdate client Y/N : ";
            cin >> Answer;
            if (toupper(Answer) == 'Y')
                Permission += clsBankUser::enPermisstions::pUpdateClient;

            cout << "\nDelete client  Y/N : ";
            cin >> Answer;
            if (toupper(Answer) == 'Y')
                Permission += clsBankUser::enPermisstions::pDeleteClient;

            cout << "\nFind client  Y/N : ";
            cin >> Answer;
            if (toupper(Answer) == 'Y')
                Permission += clsBankUser::enPermisstions::pFindClient;

            cout << "\nTransaction client  Y/N : ";
            cin >> Answer;
            if (toupper(Answer) == 'Y')
                Permission += clsBankUser::enPermisstions::pTransations;

            cout << "\nManage users client  Y/N : ";
            cin >> Answer;
            if (toupper(Answer) == 'Y')
                Permission += clsBankUser::enPermisstions::pManageUsers;
        }


        return Permission;
    }

public:
    static void UpdateUser()
    {
        string UserName = "";
        _DrawScreenHeader("Update User");
        cout << "\nPlease Enter Username: ";
        UserName = clsInputValidate::ReadString();

        while (!clsBankUser::IsUserExists(UserName))
        {
            cout << "\nUsername is not found, choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsBankUser User1 = clsBankUser::Find(UserName);
        _Print(User1);

        cout << "Are you sure you want to update this user ? [Y/N] : ";
        char Answer;
        cin >> Answer;

        if ('Y' == toupper(Answer))
        {
            _ReadUserInfo(User1);
            clsBankUser::enSaveResult SaveResult;
            SaveResult = User1.Save();

            switch (SaveResult)
            {
            case clsBankUser::enSaveResult::svSucceded:
            {
                cout << "\nUser Updated Successfully :-)\n";
                _Print(User1);
                break;
            }
            case clsBankUser::enSaveResult::svFailedEmptyObject:
            {
                cout << "\nError user was not saved because it's Empty";
                break;
            }
            }
        }
    }
};