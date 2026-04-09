#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;


class clsDate
{
private:

	short _Day, _Month, _Year;

public:

    clsDate()
	{   
        time_t t = time(0);
        tm* now = localtime(&t);
        _Day = now->tm_mday;
        _Month = now->tm_mon+1;
        _Year = now ->tm_year+1900;
	}
    clsDate(short Day, short Month, short Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}
    clsDate(short Days, short Year)
    {
        _Year = Year;
        _Month = 1;
        _Day = 1;
        AddDaysToDate(Days);
    }
    clsDate(string Date)
    {
        ConvertStringToDate(Date);
    }
    // 🔹 Setters
    void SetDay(short Day)
    {
        _Day = Day;
    }

    void SetMonth(short Month)
    {
        _Month = Month;
    }

    void SetYear(short Year)
    {
        _Year = Year;
    }

    // 🔹 Getters
    short GetDay() 
    {
        return _Day;
    }

    short GetMonth() 
    {
        return _Month;
    }

    short GetYear() 
    {
        return _Year;
    }




    static short GetDayNumber(clsDate Date)
    {
        if (Date._Month > 12 || Date._Month < 1)
            return 7;

        short a = (14 - Date._Month) / 12;
        short y = Date._Year - a;
        short m = Date._Month + (12 * a) - 2;

        return (Date._Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    }
    static short GetDayNumber(short Year, short Month, short Day)
    {
        return GetDayNumber(clsDate(Day, Month, Year));
    }

    static string GetMonthName(short Month)
    {
        string Months[12] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };

        return Months[Month - 1];
    }
    string GetMonthName()
    {
        string Months[12] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };

        return Months[_Month - 1];
    }



    static string GetDayName(short Day)
    {
        string arrDays[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

        return arrDays[Day];
    }
    string GetDayName()
    {
        string arrDays[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

        return arrDays[GetDayNumber(*this)];
    }

    //Note
    static clsDate ConvertStringToDate(string Str)
    {
        vector <string> vDateParts = SplitString(Str, "/");
        
        return clsDate(
            stoi(vDateParts[2]),
            stoi(vDateParts[1]),
            stoi(vDateParts[0])
            );

    }

    static string ConvertDateToString(const clsDate Date)
    {
        return to_string(Date._Day) + "/" + to_string(Date._Month) + "/" + to_string(Date._Year);
    }
    string ConvertDateToString()
    {
        return to_string(_Day) + "/" + to_string(_Month) + "/" + to_string(_Year);
    }


    static clsDate AddDaysToDate( clsDate Date,short Days)
    {
        short RemainingDays = Days + CountDaysFromFirstOfYearToDate(Date._Year, Date._Month, Date._Day) -1 ;
        short MonthsDays = 0;

        Date._Month = 1;

        while (true)
        {
            MonthsDays = DaysInaMonth(Date._Month, Date._Year);

            if (RemainingDays > MonthsDays)
            {
                RemainingDays -= MonthsDays;
                Date._Month++;

                if (Date._Month > 12)
                {
                    Date._Month = 1;
                    Date._Year++;
                }
            }
            else
            {
                Date._Day = RemainingDays;

                return Date;
            }


        }



    }
    void AddDaysToDate(short Days)
    {
        short RemainingDays = Days + CountDaysFromFirstOfYearToDate(_Year, _Month, _Day) - 1;
        short MonthsDays = 0;

        _Month = 1;

        while (true)
        {
            MonthsDays = DaysInaMonth(_Month, _Year);

            if (RemainingDays > MonthsDays)
            {
                RemainingDays -= MonthsDays;
                _Month++;

                if (_Month > 12)
                {
                    _Month = 1;
                    _Year++;
                }
            }
            else
            {
                _Day = RemainingDays;

                return;
            }


        }



    }

    
    static clsDate GetDateFromDaysAndYear(short Year, short Days)
    {
        clsDate Date;

        short RemainingDays = Days;
        short MonthsDays = 0;

        Date._Year = Year;
        Date._Month = 1;

        while (true)
        {
            MonthsDays = DaysInaMonth(Date._Month, Year);

            if (RemainingDays > MonthsDays)
            {
                RemainingDays -= MonthsDays;
                Date._Month++;
            }
            else
            {
                Date._Day = RemainingDays;
                break;
            }
        }

        return Date;

    }
    void GetDateFromDays(short Days)
    {
        

        short RemainingDays = Days;
        short MonthsDays = 0;

        
        _Month = 1;

        while (true)
        {
            MonthsDays = DaysInaMonth(_Month, _Year);

            if (RemainingDays > MonthsDays)
            {
                RemainingDays -= MonthsDays;
                _Month++;
            }
            else
            {
                _Day = RemainingDays;
                break;
            }
        }
    }

    static short CountDaysFromFirstOfYearToDate(short Year, short Month, short Day)
    {
        short TotalDays = 0;

        for (short i = 1; i <= Month - 1; i++)
        {
            TotalDays += DaysInaMonth(i, Year);
        }

        TotalDays += Day;

        return TotalDays;
    }
    short CountDaysFromFirstOfYearToDate()
    {
        short TotalDays = 0;

        for (short i = 1; i <= _Month - 1; i++)
        {
            TotalDays += DaysInaMonth(i, _Year);
        }

        TotalDays += _Day;

        return TotalDays;
    }

    static short DaysInaMonth(short Month, short Year)
    {
        if (Month < 1 || Month>12)
            return 0;

        short MonthsDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

        return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : MonthsDays[Month - 1];

    }
    short DaysInaMonth()
    {
        if (_Month < 1 || _Month>12)
            return 0;

        short MonthsDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

        return (_Month == 2) ? (IsLeapYear(_Year) ? 29 : 28) : MonthsDays[_Month - 1];

    }

    static short DaysInYear(short Year)
    {
        return IsLeapYear(Year) ? 366 : 365;
    }
    short DaysInYear()
    {
        return IsLeapYear(_Year) ? 366 : 365;
    }

    static int HoursInYear(short Year)
    {
        return DaysInYear(Year) * 24;
    }
    int HoursInYear()
    {
        return DaysInYear(_Year) * 24;
    }

    static long int MinutsInYear(short Year)
    {
        return HoursInYear(Year) * 60;
    }
    long int MinutsInYear()
    {
        return HoursInYear(_Year) * 60;
    }

    static long long int SecondsInYear(short Year)
    {
        return MinutsInYear(Year) * 60;
    }
    long long int SecondsInYear()
    {
        return MinutsInYear(_Year) * 60;
    }

    static int HoursInaMonth(short Month, short Year)
    {
        return DaysInaMonth(Month, Year) * 24;
    }
    int HoursInaMonth()
    {
        return DaysInaMonth(_Month, _Year) * 24;
    }

    static long int MinutesInaMonth(short Month, short Year)
    {
        return HoursInaMonth(Month, Year) * 60;
    }
    long int MinutesInaMonth()
    {
        return HoursInaMonth(_Month, _Year) * 60;
    }

    static long long int SecondsInaMonth(short Month, short Year)
    {
        return MinutesInaMonth(Month, Year) * 60;
    }
    long long int SecondsInaMonth()
    {
        return MinutesInaMonth(_Month, _Year) * 60;
    }

    static void PrintMonthCalendar(short Year, short Month)
    {
        short Current = GetDayNumber(Year, Month, 1);
        short DaysInTheMonth = DaysInaMonth(Month, Year);

        printf("\n _______________%s________________\n\n", GetMonthName(Month).c_str());

        printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

        short i;
        for (i = 0; i < Current; i++)
            printf("     ");

        for (short j = 1; j <= DaysInTheMonth; j++)
        {
            printf("%5d", j);

            if (++i == 7)
            {
                printf("\n");
                i = 0;
            }
        }

        printf("\n __________________________________\n");
    }
    void PrintMonthCalendar()
    {
        short Current = GetDayNumber(_Year, _Month, 1);
        short DaysInTheMonth = DaysInaMonth(_Month, _Year);

        printf("\n _______________%s________________\n\n", GetMonthName(_Month).c_str());

        printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

        short i;
        for (i = 0; i < Current; i++)
            printf("     ");

        for (short j = 1; j <= DaysInTheMonth; j++)
        {
            printf("%5d", j);

            if (++i == 7)
            {
                printf("\n");
                i = 0;
            }
        }

        printf("\n __________________________________\n");
    }

    static void PrintYearCalendar(short Year)
    {
        printf("\n\n          Calendar %d \n\n", Year);

        for (short i = 1; i <= 12; i++)
        {
            PrintMonthCalendar(Year, i);
            cout << "\n\n";
        }
    }
    void PrintYearCalendar()
    {
        printf("\n\n          Calendar %d \n\n", _Year);

        for (short i = 1; i <= 12; i++)
        {
            PrintMonthCalendar(_Year, i);
            cout << "\n\n";
        }
    }

    static bool IsLeapYear(short Year)
    {
        return (Year % 4 == 0 && Year % 100 != 0 || Year % 400 == 0);

    }
    bool IsLeapYear()
    {
        return (_Year % 4 == 0 && _Year % 100 != 0 || _Year % 400 == 0);

    }

    static vector <string> SplitString(string str, string Delim)
    {
        vector <string> vWords;
        string Word = "";

        short Pos = 0;

        while ((Pos = str.find(Delim)) != std::string::npos)
        {
            Word = str.substr(0, Pos);

            if (Word != "")
            {
                vWords.push_back(Word);
            }

            str.erase(0, Pos + Delim.length());
        }

        if (str != "")
        {
            vWords.push_back(str);
        }

        return vWords;
    }

    static bool IsDateBeforeDate2(clsDate Date1, clsDate Date2)
    {
        if (Date1._Year != Date2._Year)
            return Date1._Year < Date2._Year;
        else if (Date1._Month != Date2._Month)
            return Date1._Month < Date2._Month;
        else
            return Date1._Day < Date2._Day;

        //return (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);

    }
    bool IsDateBeforeDate2(clsDate Date2)
    {
        if (_Year != Date2._Year)
            return _Year < Date2._Year;
        else if (_Month != Date2._Month)
            return _Month < Date2._Month;
        else
            return _Day < Date2._Day;

        //return (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);

    }

    static bool AreDatesEqual(clsDate Date1, clsDate Date2)
    {
        return (Date1._Year == Date2._Year) ? ((Date1._Month == Date2._Month) ? (Date1._Day == Date2._Day) : false) : false;
    }
    bool AreDatesEqual(clsDate Date2)
    {
        return (_Year == Date2._Year) ? ((_Month == Date2._Month) ? (_Day == Date2._Day) : false) : false;
    }

    static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
    {
        return (!IsDateBeforeDate2(Date1, Date2) && (!AreDatesEqual(Date1, Date2)));
    }
    bool IsDateAfterDate2(clsDate Date2)
    {
        return (!IsDateBeforeDate2(Date2) && (!AreDatesEqual(Date2)));
    }






    enum enCompResult { Before = -1, Equla = 0, After = 1 };

    static enCompResult GetDatesCompareResult(clsDate Date, clsDate Date2)    {
        return AreDatesEqual(Date,Date2) ? enCompResult::Equla : (IsDateBeforeDate2(Date,Date2) ? enCompResult::Before : enCompResult::After);
    }
    enCompResult GetDatesCompareResult(clsDate Date2)
    {
        return AreDatesEqual(Date2) ? enCompResult::Equla : (IsDateBeforeDate2(Date2) ? enCompResult::Before : enCompResult::After);
    }

    static bool IsLastDayInaMonth(clsDate Date)
    {
        return (Date._Day == DaysInaMonth(Date._Month, Date._Year));
    }
    bool IsLastDayInaMonth()
    {
        return (_Day == DaysInaMonth(_Month, _Year));
    }

    static bool IsLastMonthInaYear(clsDate Date)
    {
        return (Date._Month == 12);
    }
    bool IsLastMonthInaYear()
    {
        return (_Month == 12);
    }

    static bool IsFirstDayInAMonth(clsDate Date)
    {
        return Date._Day == 1;
    }
    bool IsFirstDayInAMonth()
    {
        return _Day == 1;
    }

    static bool IsFirstMonthInAYear(clsDate Date)
    {
        return Date._Month == 1;
    }
    bool IsFirstMonthInAYear()
    {
        return _Month == 1;
    }


    static clsDate IncreaseDateByOneDay(clsDate Date)
    {
        if (IsLastDayInaMonth(Date))
        {
            if (IsLastMonthInaYear(Date))
            {
                Date._Month = 1;
                Date._Day = 1;

                Date._Year++;
            }
            else
            {
                Date._Day = 1;
                Date._Month++;
            }
        }
        else
            Date._Day++;

        return Date;
    }
    clsDate IncreaseDateByOneDay()
    {
        if (IsLastDayInaMonth(*this))
        {
            if (IsLastMonthInaYear(*this))
            {
                _Month = 1;
                _Day = 1;

                _Year++;
            }
            else
            {
                _Day = 1;
                _Month++;
            }
        }
        else
            _Day++;
    }


    static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
    {
        int Days = 0;
        short Sign = 1;

        if (!IsDateBeforeDate2(Date1, Date2))
        {
            SwapDates(Date1, Date2);
            Sign = -1;
        }

        while (IsDateBeforeDate2(Date1, Date2))
        {
            Days++;
            Date1 = IncreaseDateByOneDay(Date1);
        }
        return IncludeEndDay ? ++Days * Sign : Days * Sign;
    }
    int GetDifferenceBetweenDatesInDays(clsDate Date2, bool IncludeEndDay = false)
    {
        int Days = 0;
        short Sign = 1;

        if (!IsDateBeforeDate2(*this, Date2))
        {
            SwapDates(*this, Date2);
            Sign = -1;
        }

        while (IsDateBeforeDate2(*this, Date2))
        {
            Days++;
            *this = IncreaseDateByOneDay(*this);
        }
        return IncludeEndDay ? ++Days * Sign : Days * Sign;
    }

    static clsDate SystemDate()
    {
        time_t t = time(0);
        tm* now = localtime(&t);

        clsDate Date;

        Date._Year = now->tm_year + 1900;
        Date._Month = now->tm_mon + 1;
        Date._Day = now->tm_mday;

        return Date;
    }

    static short ReadDay()
    {
        short Day;
        cout << "\nPlease enter a Day? ";
        cin >> Day;
        return Day;
    }
    
    static void SwapDates(clsDate& Date1, clsDate& Date2)
    {
        clsDate TempDate = Date2;
        Date2 = Date1;
        Date1 = TempDate;
    }
   
    static bool IsDateValid(const clsDate Date)
    {
        return (Date._Month <= 12 && Date._Month >= 1 && Date._Day <= DaysInaMonth(Date._Month, Date._Year) && Date._Day >= 1 && Date._Year >= 1);
    }
    bool IsDateValid()
    {
        return (_Month <= 12 && _Month >= 1 && _Day <= DaysInaMonth(_Month, _Year) && _Day >= 1 && _Year >= 1);
    }


    static short GetVacationDaysNumber(clsDate DateFrom, clsDate DateTo)
    {
        short DaysCounter = 0;

        while (IsDateBeforeDate2(DateFrom, DateTo))
        {
            if (IsBusinessDay(DateFrom))
                DaysCounter++;

            DateFrom = IncreaseDateByOneDay(DateFrom);
        }

        return DaysCounter;
    }
    short GetVacationDaysNumber(clsDate DateTo)
    {
        short DaysCounter = 0;

        while (IsDateBeforeDate2(*this, DateTo))
        {
            if (IsBusinessDay(*this))
                DaysCounter++;

            *this = IncreaseDateByOneDay(*this);
        }

        return DaysCounter;
    }

    // This is not the best solution. It is used for learning purposes.
    // My simpler solution is commented below.
    static clsDate GetTheVacationEnd(clsDate Date, short VacationDays)
    {
        short WeekEndCounter = 0;

        while (IsWeekEnd(Date))
        {
            Date = IncreaseDateByOneDay(Date);
        }

        for (short i = 1; i <= VacationDays + WeekEndCounter; i++)
        {
            if (IsWeekEnd(Date))
                WeekEndCounter++;
            Date = IncreaseDateByOneDay(Date);
        }

        while (IsWeekEnd(Date))
        {
            Date = IncreaseDateByOneDay(Date);
        }

        return Date;
    }
    //this is my real answer .
    // strDate GetTheVacationEnd(strDate Date,short VacationDays)
    //{
    //    
    //    short i = 0;
    //    while(i<VacationDays)
    //    {
    //        if (IsBusinessDay(Date))
    //        {
    //            i++;
    //        }
    //        Date = IncreaseDateByOneDay(Date);
    //    }
    //
    //    return Date;
    //}
    clsDate GetTheVacationEnd(short VacationDays)
    {
        short WeekEndCounter = 0;

        while (IsWeekEnd(*this))
        {
            *this = IncreaseDateByOneDay(*this);
        }

        for (short i = 1; i <= VacationDays + WeekEndCounter; i++)
        {
            if (IsWeekEnd(*this))
                WeekEndCounter++;
            *this = IncreaseDateByOneDay(*this);
        }

        while (IsWeekEnd(*this))
        {
            *this = IncreaseDateByOneDay(*this);
        }

        return *this;
    }

    static bool IsEndOfWeek(const clsDate Date)
    {
        return GetDayNumber(Date) == 6;
    }
    bool IsEndOfWeek()
    {
        return GetDayNumber(*this) == 6;
    }

    static bool IsWeekEnd(clsDate Date)
    {
        short CurrentDay = GetDayNumber(Date);

        return CurrentDay == 6 || CurrentDay == 5;
    }
    bool IsWeekEnd()
    {
        short CurrentDay = GetDayNumber(*this);

        return CurrentDay == 6 || CurrentDay == 5;
    }

    static bool IsBusinessDay(clsDate Date)
    {
        return !IsWeekEnd(Date);
    }
    bool IsBusinessDay()
    {
        return !IsWeekEnd(*this);
    }

    static short GetDaysUntilEndOfWeek(clsDate Date)
    {

        return 6 - GetDayNumber(Date);
    }
    short GetDaysUntilEndOfWeek()
    {
        return 6 - GetDayNumber(*this);
    }

    static short GetDaysUntilEndOfMonth(clsDate Date)
    {
        clsDate NewDate;

        NewDate._Day = DaysInaMonth(Date._Month, Date._Year);
        NewDate._Month = Date._Month;
        NewDate._Year = Date._Year;

        return GetDifferenceInDays(Date, NewDate, true);
    }
    short GetDaysUntilEndOfMonth()
    {
        clsDate NewDate;

        NewDate._Day = DaysInaMonth(_Month,_Year);
        NewDate._Month = _Month;
        NewDate._Year = _Year;

        return GetDifferenceInDays(*this, NewDate, true);
    }

    static int GetDaysUntilEndOfYear(clsDate Date)
    {
        clsDate NewDate;

        NewDate._Day = 31;
        NewDate._Month = 12;
        NewDate._Year = Date._Year;

        return GetDifferenceInDays(Date, NewDate, true);
    }
    int GetDaysUntilEndOfYear()
    {
        clsDate NewDate;

        NewDate._Day = 31;
        NewDate._Month = 12;
        NewDate._Year = _Year;

        return GetDifferenceInDays(*this, NewDate, true);
    }


   static clsDate DecreaseDateByOneDay(clsDate Date)
    {
        if (IsFirstDayInAMonth(Date))
        {
            if (IsFirstMonthInAYear(Date))
            {
                Date._Year--;
                Date._Month = 12;
                Date._Day = 31;
            }
            else
            {
                Date._Month--;
                Date._Day = DaysInaMonth(Date._Month, Date._Year);
            }

        }
        else
            Date._Day--;

        return Date;
    }
   void DecreaseDateByOneDay()
   {
       if (IsFirstDayInAMonth(*this))
       {
           if (IsFirstMonthInAYear(*this))
           {
              _Year--;
              _Month = 12;
              _Day = 31;
           }
           else
           {
               _Month--;
               _Day = DaysInaMonth(_Month, _Year);
           }

       }
       else
           _Day--;
   }


   static clsDate DecreaseDateByOneWeek(clsDate Date)
    {
        for (short i = 0; i < 7; i++)
        {
            Date = DecreaseDateByOneDay(Date);
        }

        return Date;
    }
   void DecreaseDateByOneWeek()
   {
       for (short i = 0; i < 7; i++)
       {
           *this = DecreaseDateByOneDay(*this);
       }
   }

   static clsDate DecreaseDateByXWeek(clsDate Date, short Number)
    {
        for (short i = 0; i < Number; i++)
        {
            Date = DecreaseDateByOneWeek(Date);
        }

        return Date;
    }
   void DecreaseDateByXWeek( short Number)
   {
       for (short i = 0; i < Number; i++)
       {
           *this = DecreaseDateByOneWeek(*this);
       }
   }

   static clsDate DecreaseDateByOneMonth(clsDate Date)
    {
        if (Date._Month == 1)
        {
            Date._Year--;
            Date._Month = 12;
        }
        else
            Date._Month--;

        short NewMonthsDays = DaysInaMonth(Date._Month, Date._Year);

        if (Date._Day > NewMonthsDays)
            Date._Day = NewMonthsDays;

        return Date;
    }
   clsDate DecreaseDateByOneMonth()
   {
       if (_Month == 1)
       {
           _Year--;
           _Month = 12;
       }
       else
           _Month--;

       short NewMonthsDays = DaysInaMonth(_Month, _Year);

       if (_Day > NewMonthsDays)
           _Day = NewMonthsDays;
   }

   static clsDate DecreaseDateByXMonth(clsDate Date, short Number)
    {
        for (short i = 0; i < Number; i++)
        {
            Date = DecreaseDateByOneMonth(Date);
        }
        return Date;
    }
   void DecreaseDateByXMonth(short Number)
   {
       for (short i = 0; i < Number; i++)
       {
           *this = DecreaseDateByOneMonth(*this);
       }
       
   }

   static clsDate DecreaseDateByOneYear(clsDate Date)
    {
        Date._Year--;

        short MaxDay = DaysInaMonth(Date._Month, Date._Year);

        if (Date._Day > MaxDay)
            Date._Day = MaxDay;

        return Date;
    }
   void DecreaseDateByOneYear()
   {
       _Year--;

       short MaxDay = DaysInaMonth(_Month, _Year);

       if (_Day > MaxDay)
           _Day = MaxDay;

       
   }

   static clsDate DecreaseDateByXYear(clsDate Date, short Number)
    {
        Date._Year -= Number;

        short MaxDay = DaysInaMonth(Date._Month, Date._Year);

        if (Date._Day > MaxDay)
            Date._Day = MaxDay;

        return Date;
    }
   void DecreaseDateByXYear(short Number)
   {
       _Year -= Number;

       short MaxDay = DaysInaMonth(_Month, _Year);

       if (_Day > MaxDay)
           _Day = MaxDay;

       
   }

   static clsDate DecreaseDateByOneDecade(clsDate Date)
    {
        Date._Year -= 10;
        return Date;
    }
   void DecreaseDateByOneDecade()
   {
       _Year -= 10;
   }


   static clsDate DecreaseDateByXDecade(clsDate Date, short Number)
    {
        Date._Year -= Number * 10;
        return Date;

        //There is another way using for loop , But this is better . 
    }
   clsDate DecreaseDateByXDecade( short Number)
   {
       _Year -= Number * 10;
       

       //There is another way using for loop , But this is better . 
   }

   static clsDate DecreaseDateByOneCentury(clsDate Date)
    {
        Date._Year -= 100;
        return Date;
    }
   void DecreaseDateByOneCentury()
   {
       _Year -= 100;
   }

   static clsDate DecreaseDateByOneMillennium(clsDate Date)
    {
        Date._Year -= 1000;
        return Date;
    }
   void DecreaseDateByOneMillennium()
   {
       _Year -= 1000;
   }



   static clsDate IncreaseDateByOneWeek(clsDate Date)
   {
       for (short i = 0; i < 7; i++)
       {
           Date = IncreaseDateByOneDay(Date);
       }
       return Date;
   }
   void IncreaseDateByOneWeek()
   {
       for (short i = 0; i < 7; i++)
       {
           *this = IncreaseDateByOneDay(*this);
       }
      
   }

   static clsDate IncreaseDateByXWeek(clsDate Date, short Number)
   {
       for (short i = 0; i < Number; i++)
       {
           Date = IncreaseDateByOneWeek(Date);
       }
       return Date;
   }
   void IncreaseDateByXWeek(short Number)
   {
       for (short i = 0; i < Number; i++)
       {
           *this = IncreaseDateByOneWeek(*this);
       }
       
   }

   static clsDate IncreaseDateByOneMonth(clsDate Date)
   {
       if (Date._Month == 12)
       {
           Date._Month = 1;
           Date._Year++;
       }
       else
       {
           Date._Month++;
       }

       short NewMonthsDays = DaysInaMonth(Date._Month, Date._Year);

       if (Date._Day > NewMonthsDays)
           Date._Day = NewMonthsDays;


       return Date;
   }
   void IncreaseDateByOneMonth()
   {
       if (_Month == 12)
       {
          _Month = 1;
          _Year++;
       }
       else
       {
          _Month++;
       }

       short NewMonthsDays = DaysInaMonth(_Month, _Year);

       if (_Day > NewMonthsDays)
           _Day = NewMonthsDays;
   }

   static clsDate IncreaseDateByXMonth(clsDate Date, short Number)
   {
       for (short i = 0; i < Number; i++)
       {
           Date = IncreaseDateByOneMonth(Date);
       }
       return Date;
   }
   void IncreaseDateByXMonth( short Number)
   {
       for (short i = 0; i < Number; i++)
       {
           *this = IncreaseDateByOneMonth(*this);
       }
   }

   static clsDate IncreaseDateByOneYear(clsDate Date)
   {
       Date._Year++;

       short MaxDay = DaysInaMonth(Date._Month, Date._Year);
       
       if (Date._Day > MaxDay)
           Date._Day = MaxDay;

       return Date;
   }
   void IncreaseDateByOneYear()
   {
       _Year++;

       short MaxDay = DaysInaMonth(_Month, _Year);
       
       if (_Day > MaxDay)
           _Day = MaxDay;
   }

   static clsDate IncreaseDateByXYear(clsDate Date, short Number)
   {
       Date._Year += Number;

       // Or This way ...

       /*
       for (short i=0; i<=Number ; i++)
       {
         Date = IncreaseDateByOneYear(Date);
       }
       */
       return Date;
   }
   void IncreaseDateByXYear(short Number)
   {
       _Year += Number;

       // Or This way ...

       /*
       for (short i=0; i<=Number ; i++)
       {
         Date = IncreaseDateByOneYear(Date);
       }
       */
       
   }

   static clsDate IncreaseDateByOneDecade(clsDate Date)
   {
       Date._Year += 10;
       return Date;
   }
   void IncreaseDateByOneDecade()
   {
       _Year += 10;
   }

   static clsDate IncreaseDateByXDecade(clsDate Date, short Number)
   {
       Date._Year += Number * 10;
       return Date;

       //There is another way using for loop , But this better . 
   }
   void IncreaseDateByXDecade( short Number)
   {
       _Year += Number * 10;
     

       //There is another way using for loop , But this better . 
   }

   static clsDate IncreaseDateByOneCentury(clsDate Date)
   {
       Date._Year += 100;
       return Date;
   }
   void IncreaseDateByOneCentury()
   {
       _Year += 100;
   }

   static clsDate IncreaseDateByOneMillennium(clsDate Date)
   {
       Date._Year += 1000;
       return Date;
   }
   void IncreaseDateByOneMillennium()
   {
       _Year += 1000;
   }
   





	void Print()
	{
		printf("Date : %d/%d/%d ", _Day, _Month, _Year);
	}



};

