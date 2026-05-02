#pragma once

#include <iostream>
#include <iomanip>
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsBankUser.h"

using namespace std;

class clsAddNewUsertScreen : protected clsScreen
{
private:

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

        cout << "\nEnter PinCode: ";
        User.Password = clsInputValidate::ReadString();

        cout << "\n\tEnter Permission ";
        User.Permissions = _ReadPermissions();

    }

    static void _Print(clsBankUser User)
    {

        cout << "\nClient Card\n";
        cout << "----------------------------------------------\n";
        cout << "User Name      : " << User.UserName << endl;
        cout << "Full Name      : " << User.FullName << endl;
        cout << "Email          : " << User.Email << endl;
        cout << "Phone          : " << User.Phone << endl;
        cout << "PassWord       : " << User.Password << endl;
        cout << "Permissions    : " << User.Permissions << endl;
        cout << "----------------------------------------------\n";
        cout << endl;

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

            cout << "\Login Register list  Y/N : ";
            cin >> Answer;
            if (toupper(Answer) == 'Y')
                Permission += clsBankUser::enPermisstions::pLoginRegisterList;

            cout << "\nManage users client  Y/N : ";
            cin >> Answer;
            if (toupper(Answer) == 'Y')
                Permission += clsBankUser::enPermisstions::pManageUsers;
        }


        return Permission;
    }

public:

    static void AddNewUsertScreen()
    {

        clsScreen::_DrawScreenHeader("Add New User");

        string UserName = "";

        cout << "Please enter an User Name : ";
        UserName = clsString::ReadString();

        while (clsBankUser::IsUserExists(UserName))
        {
            cout << "\nUser Name is already exists ,Please enter a vaild user name : ";
            UserName = clsString::ReadString();
        }

        clsBankUser User = clsBankUser::GetAddNewClientObject(UserName);

        _ReadUserInfo(User);

        clsBankUser::enSaveResult Result = User.Save();

        switch (Result)
        {
        case clsBankUser::svFailedEmptyObject:
        {
            cout << "Update Failed it's an Empty Object .";
            break;
        }
        case clsBankUser::svSucceded:
        {
            cout << "Added Succesfully .";
            _Print(User);
            break;
        }
        case clsBankUser::svFaildUserNameExists:
        {
            cout << "Add Failed UserName Is already exists .";
            break;
        }
        }

    }

};