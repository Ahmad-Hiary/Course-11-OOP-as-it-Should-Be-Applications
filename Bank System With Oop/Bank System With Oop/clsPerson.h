#pragma once

#include <iostream>
#include "clsInterfaceCommunication.h"

using namespace std;

class clsPerson : public clsInterfaceCommunication
{
private:

	string _FirstName, _LastName, _Email, _Phone,_FullName;

public:

    clsPerson(string firstname, string lastname, string email, string phone)
    {
        _FirstName = firstname;
        _LastName = lastname;
        _Email = email;
        _Phone = phone;
    }
   

    // First Name
    void SetFirstName(string FirstName)
    {
        _FirstName = FirstName;
    }

    string GetFirstName()
    {
        return _FirstName;
    }

    // Last Name
    void SetLastName(string LastName)
    {
        _LastName = LastName;
    }

    string GetLastName()
    {
        return _LastName;
    }

    // Email
    void SetEmail(string Email)
    {
        _Email = Email;
    }

    string GetEmail()
    {
        return _Email;
    }

    // Phone
    void SetPhone(string Phone)
    {
        _Phone = Phone;
    }

    string GetPhone()
    {
        return _Phone;
    }

    

    string GetFullName()
    {
        return FirstName+" "+LastName;
    }

    __declspec(property(get = GetFullName)) string FullName;
    __declspec(property(get = GetFirstName, put = SetFirstName)) string FirstName;
    __declspec(property(get = GetLastName,put = SetLastName))  string LastName;
    __declspec(property(get = GetEmail, put = SetEmail))     string Email;
    __declspec(property(get = GetPhone, put = SetPhone))     string Phone;



    void SendEmail(string Title, string Body)
    {

    }
    void SendFax(string Title, string Body)
    {

    }
    void SendSmS(string Title, string Body)
    {

    }

};

