#pragma once

#include "clsScreen.h"
#include "clsBankUser.h"
#include "clsInputValidate.h"
#include "Global.h"
#include "clsMainScreen.h"
#include <iostream>

using namespace std;

class clsLogInScreen :protected clsScreen
{
	static bool _LogIn()
	{
		string UserName, PassWord;

		bool LogInFaild = false;
		short FaildTrialsNumber = 0;

		do {

			if (LogInFaild)
			{
				cout << "\nInvalid UserName / PassWord !!! \n";
				FaildTrialsNumber++;
				cout << "You have " << 3 - FaildTrialsNumber << " trials to login \n";
				
			}

			if (FaildTrialsNumber == 3)
			{
				cout << "You are locked after 3 faild trials\n\n";
				return false;
			}

			cout << "\n\nUsername : ";
			UserName = clsInputValidate::ReadString();
			cout << "\nPassWord : ";
			PassWord = clsInputValidate::ReadString();

			CurrentUser = clsBankUser::Find(UserName, PassWord);

			cout << "\nSearching for: [" << UserName << "] [" << PassWord << "]\n";
		

			LogInFaild = CurrentUser.IsEmpty();

		} while (LogInFaild);


		
		CurrentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenu();
		return true;
	}

public:

	static bool ShowLogInScreen()
	{
		system("cls");
		_DrawScreenHeader("Log In");
		return _LogIn();
	}
};

