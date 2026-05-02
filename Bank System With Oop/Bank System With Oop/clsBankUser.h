#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <string>
#include <fstream>
#include "Global.h"

using namespace std;

class clsBankUser : public clsPerson
{

public:

	struct stLogInRegisterRecord
	{
		string UserName, DateAndTime, PassWord;
		short Permission;
	};


private:


	enum enMode { EmptyMode, UpdateMode, AddNewMode };

	enMode _Mode;
	string _UserName, _Password;
	short _Permissions;
	bool _IsMarkedForDelete = false;

	static string _ConvertUserObjectToLine(clsBankUser User, string Seperator = "#//#")
	{

		string Line = "";
		Line += User.FirstName + Seperator;
		Line += User.LastName + Seperator;
		Line += User.Email + Seperator;
		Line += User.Phone + Seperator;
		Line += User._UserName + Seperator;
		Line += clsUtil::EncryptText(User.Password) + Seperator;
		Line += to_string(User.Permissions);

		return Line;

	}

	static clsBankUser _ConvertLineToObject(string str, string Delim = "#//#")
	{
		vector <string> vSplitedString = clsString::SplitString(str, Delim);

		return clsBankUser(enMode::UpdateMode, vSplitedString[0], vSplitedString[1], vSplitedString[2], vSplitedString[3], vSplitedString[4], clsUtil::DecryptText(vSplitedString[5]), stoi(vSplitedString[6]));
	}

	
	static stLogInRegisterRecord _ConvertLogInInfoLineToObject(string str, string Delim = "#//#")
	{

		vector <string> vSplitedString = clsString::SplitString(str, Delim);

		stLogInRegisterRecord Record;

		Record.DateAndTime = vSplitedString[0];
		Record.UserName = vSplitedString[1];
		Record.PassWord = clsUtil::DecryptText(vSplitedString[2]);
		Record.Permission = stoi(vSplitedString[3]);

		return Record;
	}




	void _SaveUserToFile(vector <clsBankUser> vUsers)
	{
		fstream File;

		File.open("Users Data.txt", ios::out);

		if (File.is_open())
		{
			string Line = "";

			for (clsBankUser& c : vUsers)
			{
				if (!c._IsMarkedForDelete)
				{
					Line = _ConvertUserObjectToLine(c, "#//#");

					File << Line << endl;
				}
			}

			File.close();
		}
	}

	static clsBankUser _GetEmptyUserObject()
	{
		return clsBankUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector <clsBankUser> _LoadUsersDataFromFile()
	{
		fstream File;
		vector <clsBankUser> vUsers;

		File.open("Users Data.txt", ios::in);

		string Line;

		if (File.is_open())
		{


			while (getline(File, Line))
			{
				clsBankUser User = _ConvertLineToObject(Line);

				vUsers.push_back(User);
			}
			File.close();
		}

		return vUsers;
	}

	static vector <stLogInRegisterRecord> _LoadLoginInfoFromFile()
	{
		fstream File;
		vector <stLogInRegisterRecord> vInfo;

		File.open("Login Register.txt", ios::in);

		string Line;

		if (File.is_open())
		{


			while (getline(File, Line))
			{
				stLogInRegisterRecord Info = _ConvertLogInInfoLineToObject(Line);

				vInfo.push_back(Info);
			}
			File.close();
		}

		return vInfo;
	}

	 string _PrepareLofInRecord()
	{
		string Seperator = "#//#";
		string Line = "";
		string Date = clsDate::SystemDate().ConvertDateToString();

		Line = Date + " - " + clsDate::GetCurrentTime() + Seperator;
		Line += UserName + Seperator;
		Line += clsUtil::EncryptText(Password) + Seperator;
		Line += to_string (Permissions);

		return Line;

	}


	void _Update()
	{

		vector <clsBankUser> vUsers = _LoadUsersDataFromFile();

		for (clsBankUser& c : vUsers)
		{
			if (c._UserName == _UserName)
			{
				c = *this;
				break;
			}

		}


		_SaveUserToFile(vUsers);


	}


	void _AddNewLineToFile(string Record)
	{
		fstream File;

		File.open("Users Data.txt", ios::out | ios::app);

		if (File.is_open())
		{
			File << Record << endl;

			File.close();
		}
		else
			File.close();

	}
	void _AddNew()
	{
		_AddNewLineToFile(_ConvertUserObjectToLine(*this));
	}

	public:


		enum enPermisstions { pAll = -1, pShowList = 1, pAddClient = 2, pDeleteClient = 4, pUpdateClient = 8, pFindClient = 16, pTransations = 32, pLoginRegisterList = 64, pManageUsers = 128 };




		clsBankUser(enMode mode, string firstname, string lastname, string email, string phone,
			string username, string password, short permissions) :
			clsPerson(firstname, lastname, email, phone)
		{
			_Mode = mode;
			_UserName = username;
			_Permissions = permissions;
			_Password = password;
		}

		// Mode
		void SetMode(enMode Mode)
		{
			_Mode = Mode;
		}
		enMode GetMode() const
		{
			return _Mode;
		}

		// UserName
		void SetUserName(const string& UserName)
		{
			_UserName = UserName;
		}
		string GetUserName() const
		{
			return _UserName;
		}

		// Password
		void SetPassword(const string& Password)
		{
			_Password = Password;
		}
		string GetPassword() const
		{
			return _Password;
		}

		// Permissions
		void SetPermissions(short Permissions)
		{
			_Permissions = Permissions;
		}
		short GetPermissions() const
		{
			return _Permissions;
		}

		// IsMarkedForDelete
		void SetIsMarkedForDelete(bool Value)
		{
			_IsMarkedForDelete = Value;
		}
		bool GetIsMarkedForDelete()
		{
			return _IsMarkedForDelete;
		}


		__declspec(property(get = GetMode, put = SetMode)) enMode Mode;

		__declspec(property(get = GetUserName, put = SetUserName)) string UserName;

		__declspec(property(get = GetPassword, put = SetPassword)) string Password;

		__declspec(property(get = GetPermissions, put = SetPermissions)) short Permissions;

		__declspec(property(get = GetIsMarkedForDelete, put = SetIsMarkedForDelete)) bool IsMarkedForDelete;





		static clsBankUser Find(string UserName)
		{
			vector <clsBankUser> vUsers;

			fstream file;
			file.open("Users Data.txt", ios::in);

			if (file.is_open())
			{
				string Line;
				while (getline(file, Line))
				{
					clsBankUser User = _ConvertLineToObject(Line);

					if (User.UserName == UserName)
					{
						file.close();
						return User;
					}
					vUsers.push_back(User);
				}


			}

			file.close();
			return _GetEmptyUserObject();
		}
		static clsBankUser Find(string username, string password)
		{
			vector <clsBankUser> vUsers;

			fstream file;
			file.open("Users Data.txt", ios::in);

			if (file.is_open())
			{
				string Line;
				while (getline(file, Line))
				{
					clsBankUser User = _ConvertLineToObject(Line);
					
					if (User.UserName == username && User.Password == password)
					{
						file.close();
						return User;
					}
					vUsers.push_back(User);
				}


			}

			file.close();
			return _GetEmptyUserObject();
		}

		bool Delete()
		{
			vector <clsBankUser> vUsers = _LoadUsersDataFromFile();
			bool Found = false;

			for (clsBankUser& c : vUsers)
			{
				if (c.UserName == UserName)
				{
					c._IsMarkedForDelete = true;
					Found = true;
					break;
				}


			}

			if (!Found)
				return false;

			_SaveUserToFile(vUsers);

			*this = _GetEmptyUserObject();

			return true;
		}

		static bool IsEmpty(clsBankUser User)
		{
			return (User._Mode == enMode::EmptyMode);
		}
		bool IsEmpty()
		{
			return (_Mode == enMode::EmptyMode);
		}
	
		static bool IsUserExists(string UserName)
		{
			clsBankUser User = clsBankUser::Find(UserName);

			return (!IsEmpty(User));
		}

		static clsBankUser GetAddNewClientObject(string UserName)
		{
			return clsBankUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
		}

		enum enSaveResult { svFailedEmptyObject, svSucceded, svFaildUserNameExists };

		enSaveResult Save()
		{
			switch (_Mode)
			{
			case enMode::EmptyMode:
			{
				return enSaveResult::svFailedEmptyObject;
			}

			case enMode::UpdateMode:
			{
				_Update();

				return enSaveResult::svSucceded;
			}
			case enMode::AddNewMode:
			{
				if (clsBankUser::IsUserExists(UserName))
					return svFaildUserNameExists;

				_AddNew();

				_Mode = UpdateMode;

				return svSucceded;
			}
			}
		}

		static vector <clsBankUser> GetUsersList()
		{
			vector <clsBankUser> vUsers = _LoadUsersDataFromFile();
			return vUsers;
		}

		static vector < stLogInRegisterRecord > GetLogInInfoList()
		{
			vector <stLogInRegisterRecord> vInfo = _LoadLoginInfoFromFile();
			return vInfo;
		}

		bool CheckPermissionAccess(enPermisstions AccessTo)
		{
			if (this->Permissions == -1)
				return true;

			if ((this->Permissions & AccessTo) == AccessTo)
				return 1;
			else
				return 0;

		}

		 void RegisterLogIn()
		{
			fstream File;

			File.open("Login Register.txt", ios::app);

			if (File.is_open())
			{
				string Line = _PrepareLofInRecord();

				File << Line << endl;

				File.close();
			}
		}

		 
};

