#pragma once
#include <iostream>
#include"clsInputValidate.h"
#include"clsString.h"
#include <vector>
#include "clsString.h"
#include <fstream>

using namespace std;


class clsCurrency
{
private:

    enum enMode { EmptyMode, UpdateMode };

    string _Country, _Code, _Name;
    float _Rate;
    enMode _Mode;

    static clsCurrency _ConvertLineToObject(string Line)
    {
        vector <string> SplitedLine = clsString::SplitString(Line);

        return clsCurrency(enMode::UpdateMode, SplitedLine[0], SplitedLine[1], SplitedLine[2], stof(SplitedLine[3]));
    }

    string _ConvertCurrencyToLine(clsCurrency Currency,string Separator="#//#")
    {
        string Line = "";
        Line += Currency.Country + Separator;
        Line += Currency.Code + Separator;
        Line += Currency.Name + Separator;
        Line += to_string(Currency.Rate);
        return Line;
    }

    static vector <clsCurrency> _LoadCurrenciesFromFile()
    {
        fstream File;

        vector <clsCurrency> vCurrencies;

        File.open("Currencies.txt", ios::in);

        if (File.is_open())
        {
    
            string Line;

            while (getline(File, Line))
            {
                vCurrencies.push_back(_ConvertLineToObject(Line));
            }

            File.close();
            return vCurrencies;
        }

        return vCurrencies;
    }
    

    void _SaveCurrenciesToFile(vector <clsCurrency> vCurrencies)
    {
        fstream File;
        File.open("Currencies.txt", ios::out);

        if (File.is_open())
        {
            for (clsCurrency& c : vCurrencies)
            {
                

                File << _ConvertCurrencyToLine(c) << endl;
                
            }
            File.close();
        }
    }

     void _Update(float NewRate)
    {
        vector <clsCurrency> vCurrencies = _LoadCurrenciesFromFile();

        for (clsCurrency& C : vCurrencies)
        {
            if (C.Code == Code)
            {
                C = *this;
            }
        }

        _SaveCurrenciesToFile(vCurrencies);
        
    }

public:


    clsCurrency(enMode Mode,string country, string code, string name, float Rate)
    {
        _Country = country;
        _Code = code;
        _Name = name;
        _Rate = Rate;
        _Mode = Mode;
    }

    static clsCurrency GetEmptyCurrency()
    {
        return clsCurrency(enMode::EmptyMode, "", "", "", 0);
    }


    // Country
   

    string GetCountry() const
    {
        return _Country;
    }

    __declspec(property(get = GetCountry)) string Country;


    // Code
    void SetCode(const string& Code)
    {
        _Code = Code;
    }

    string GetCode() const
    {
        return _Code;
    }

    __declspec(property(get = GetCode, put = SetCode)) string Code;


    // Name
    void SetName(const string& Name)
    {
        _Name = Name;
    }

    string GetName() const
    {
        return _Name;
    }

    __declspec(property(get = GetName, put = SetName)) string Name;


    // Rate
    void SetRate(short Rate)
    {
        _Rate = Rate;
    }

    float GetRate() const
    {
        return _Rate;
    }

    __declspec(property(get = GetRate, put = SetRate)) float Rate;


     
    static clsCurrency FindByCountry(string country)
    {

        country = clsString::UpperAllStirng(country);

        vector <clsCurrency> vCurrencies = _LoadCurrenciesFromFile();

        for (clsCurrency& C : vCurrencies)
        {
            if (clsString::UpperAllStirng(C.Country) == country)
            {
                clsCurrency Currency = C;

                return Currency;
            }
        }

        return GetEmptyCurrency();
    }

    static clsCurrency FindByCode(string Code)
    {

        Code = clsString::UpperAllStirng(Code);


        vector <clsCurrency> vCurrencies = _LoadCurrenciesFromFile();

        for (clsCurrency& C : vCurrencies)
        {
            if (C.Code == Code)
            {
                clsCurrency Currency = C;

                return Currency;
            }
        }

        return GetEmptyCurrency();
    }
   
    static vector <clsCurrency> GetCurrenciesList()
    {
        return _LoadCurrenciesFromFile();
    }

    bool IsEmpty()
    {
        return _Mode==enMode::EmptyMode;
    }

     bool IsCurrencyExists()
    {
         return (!IsEmpty());
    }

    void UpdateRate(float NewRate)
    {
        _Rate = NewRate;
        _Update(NewRate);
    }


    float ConvertToUsd(float Amount)
    {
        return Amount / Rate;
    }

    float ConvertToCurrency2(clsCurrency Currency2, float Amount)
    {
        float DollarRate = ConvertToUsd(Amount);
        return DollarRate * Currency2.Rate;
    }

};

