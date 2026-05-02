#pragma once

#include <iostream>
#include "clsDate.h"
#include "clsString.h"
#include "clsPerson.h"
#include <vector>
#include <fstream>


using namespace std;

class clsBankClient : public clsPerson
{

public:

    struct stTransferLogRecord
    {
        //The user name for the user who did the operation .

        string UserName, SourceClient, DestinationClient, DateAndTime;
        double Amount, NewSourceClientBalance, NewDestinationClientBalance;
    };

private:

    enum enMode { EmptyMode, UpdateMode, AddNewMode };

    enMode _Mode;
    string _AccountNumber, _Pin;
    float _AccountBalance;
    bool _IsMarkedForDelete = false;

    static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {
        string stClientRecord = "";
        stClientRecord += Client.FirstName + Seperator;
        stClientRecord += Client.LastName + Seperator;
        stClientRecord += Client.Email + Seperator;
        stClientRecord += Client.Phone + Seperator;
        stClientRecord += Client.AccountNumber + Seperator;
        stClientRecord += Client.Pin + Seperator;
        stClientRecord += to_string(Client.AccountBalance);

        return stClientRecord;
    }

    static clsBankClient _ConvertClientRecordToObject(string str, string Delim = "#//#")
    {
        vector<string> vSplitedString = clsString::SplitString(str, Delim);

        return clsBankClient(enMode::UpdateMode,
            vSplitedString[0], vSplitedString[1], vSplitedString[2],
            vSplitedString[3], vSplitedString[4],
            vSplitedString[5], stof(vSplitedString[6]));
    }

    static stTransferLogRecord _ConvertTransferLogLineToObject(string str, string Delim = "#//#")
    {
        vector<string> vSplitedString = clsString::SplitString(str, Delim);

        stTransferLogRecord Info;
        Info.DateAndTime = vSplitedString[0];
        Info.SourceClient = vSplitedString[1];
        Info.DestinationClient = vSplitedString[2];
        Info.Amount = stod(vSplitedString[3]);
        Info.NewSourceClientBalance = stod(vSplitedString[4]);
        Info.NewDestinationClientBalance = stod(vSplitedString[5]);
        Info.UserName = vSplitedString[6];

        return Info;

    }

    void _SaveClientToFile(vector<clsBankClient> vClients)
    {
        fstream File;
        File.open("Clients Data.txt", ios::out);

        if (File.is_open())
        {
            for (clsBankClient& c : vClients)
            {
                if (!c._IsMarkedForDelete)
                {
                    File << _ConvertClientObjectToLine(c) << endl;
                }
            }
            File.close();
        }
    }

    string _ConvertTransferInfoToLine(clsBankClient DestinationClient, string UserName, double Amount, string Seperator = "#//#")
    {

        string Line;

        Line = clsDate::SystemDateAndTime() + Seperator;
        Line += AccountNumber + Seperator;
        Line += DestinationClient.AccountNumber + Seperator;
        Line += to_string(Amount) + Seperator;
        Line += to_string(AccountBalance) + Seperator;
        Line += to_string(DestinationClient.AccountBalance) + Seperator;
        Line += UserName;

        return Line;
    }

    void _RegisterTransferLog(clsBankClient DestinationClient,string UserName,double Amount)
    {
        fstream File;

        File.open("Transfers Log.txt", ios::app);

        if (File.is_open())
        {
            string Line = _ConvertTransferInfoToLine(DestinationClient,UserName,Amount);

            File << Line << endl;
        }

        File.close();
    }


    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    static vector<clsBankClient> _LoadClientsDataFromFile()
    {
        vector<clsBankClient> vClients;
        fstream File("Clients Data.txt", ios::in);

        if (File.is_open())
        {
            string Line;
            while (getline(File, Line))
            {
                vClients.push_back(_ConvertClientRecordToObject(Line));
            }
            File.close();
        }

        return vClients;
    }

    static vector<stTransferLogRecord> _LoadTransferLogDataFromFile()
    {
        vector<stTransferLogRecord> vInfo;
        fstream File("Transfers Log.txt", ios::in);

        if (File.is_open())
        {
            string Line;
            while (getline(File, Line))
            {
                vInfo.push_back(_ConvertTransferLogLineToObject(Line));
            }
            File.close();
        }

        return vInfo;
    }

    void _Update()
    {
        vector<clsBankClient> vClients = _LoadClientsDataFromFile();

        for (clsBankClient& c : vClients)
        {
            if (c.AccountNumber == AccountNumber)
            {
                c = *this;
                break;
            }
        }

        _SaveClientToFile(vClients);
    }

    void _AddNewLineToFile(string Record)
    {
        fstream File("Clients Data.txt", ios::out | ios::app);

        if (File.is_open())
        {
            File << Record << endl;
            File.close();
        }
    }

    void _AddNew()
    {
        _AddNewLineToFile(_ConvertClientObjectToLine(*this));
    }

public:

    clsBankClient(enMode mode, string firstname, string lastname, string email, string phone,
        string accountnumber, string pin, float accountbalance)
        : clsPerson(firstname, lastname, email, phone)
    {
        _Mode = mode;
        _AccountNumber = accountnumber;
        _AccountBalance = accountbalance;
        _Pin = pin;
    }

    static bool IsEmpty(clsBankClient client)
    {
        return (client._Mode == enMode::EmptyMode);
    }

    // Account Number
    string GetAccountNumber() const { return _AccountNumber; }

    // Pin
    void SetPin(const string& Pin) { _Pin = Pin; }
    string GetPin() const { return _Pin; }

    // Balance
    void SetAccountBalance(float Balance) { _AccountBalance = Balance; }
    float GetAccountBalance() const { return _AccountBalance; }

    string FullName()
    {
        return FirstName + " " + LastName;
    }

    __declspec(property(get = GetAccountNumber)) string AccountNumber;
    __declspec(property(get = GetPin, put = SetPin)) string Pin;
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

    static clsBankClient Find(string AccountNumber)
    {
        vector<clsBankClient> vClients = _LoadClientsDataFromFile();

        for (clsBankClient& Client : vClients)
        {
            if (Client.AccountNumber == AccountNumber)
                return Client;
        }

        return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccountNumber, string PassWord)
    {
        vector<clsBankClient> vClients = _LoadClientsDataFromFile();

        for (clsBankClient& Client : vClients)
        {
            if (Client.AccountNumber == AccountNumber && Client.Pin == PassWord)
                return Client;
        }

        return _GetEmptyClientObject();
    }

    bool Delete()
    {
        vector<clsBankClient> vClients = _LoadClientsDataFromFile();

        for (clsBankClient& c : vClients)
        {
            if (c.AccountNumber == AccountNumber)
            {
                c._IsMarkedForDelete = true;
                _SaveClientToFile(vClients);
                *this = _GetEmptyClientObject();
                return true;
            }
        }
        return false;
    }

    void Deposit(double Amount)
    {
        _AccountBalance += Amount;
        Save();
    }

    bool Withdraw(double Amount)
    {
        if (Amount > _AccountBalance)
            return false;

        _AccountBalance -= Amount;
        Save();
        return true;
    }

   

    static bool IsClientExist(string AccountNumber)
    {
        return !IsEmpty(Find(AccountNumber));
    }

    static clsBankClient GetAddNewClientObject(string accountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", accountNumber, "", 0);
    }

    enum enSaveResult { svFailedEmptyObject, svSucceded, svFailedAccountExists ,svFaildInvalidAmount };

    bool Transfer(clsBankClient& DestinationClient,string UserName, double Amount)
    {
        if (Amount > AccountBalance || DestinationClient.AccountNumber == AccountNumber)
            return 0;
 
        DestinationClient.Deposit(Amount);
        Withdraw(Amount);

        _RegisterTransferLog(DestinationClient,UserName,Amount);

        return 1;

    }

    

    enSaveResult Save()
    {
        switch (_Mode)
        {
        case EmptyMode:
            return svFailedEmptyObject;

        case UpdateMode:
            _Update();
            return svSucceded;

        case AddNewMode:
            if (IsClientExist(_AccountNumber))
                return svFailedAccountExists;

            _AddNew();
            _Mode = UpdateMode;
            return svSucceded;
        }

        return svFailedEmptyObject;
    }

    static vector<clsBankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }

    static vector<stTransferLogRecord> GetTrnsaferLogList()
    {
        return _LoadTransferLogDataFromFile();
    }

    static double GetClientsTotalBalances()
    {
        vector<clsBankClient> vClients = _LoadClientsDataFromFile();

        double Total = 0;
        for (clsBankClient& c : vClients)
        {
            Total += c.AccountBalance;
        }
        return Total;
    }
};