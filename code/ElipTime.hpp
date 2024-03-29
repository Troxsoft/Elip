#ifndef H__ELIP__TIME_U__TOOLS__H
#define H__ELIP__TIME_U__TOOLS__H
#include <chrono>
#include <iostream>
#include <ctime>
#include <time.h>
#include "ElipString.hpp"
namespace Elip
{
    class DateTime
    {
    private:
        Elip::String _amStyle = "AM";
        Elip::String _pmStyle = "PM";
        // date

        int _day;
        int _month;
        int _year;

        // time

        int _hours;
        int _minutes;
        int _seconds;

    public:
        // DateTime() : _day(0), _month(0), _year(0), _hours(0), _minutes(0), _seconds(0)
        // {
        // }
        DateTime(int year, int month, int day) : _year(year), _month(month), _day(day), _hours(0), _minutes(0), _seconds(0)
        {
        }
        DateTime(int year, int month, int day, int hours, int minutes, int seconds) : _year(year), _month(month), _day(day), _hours(hours), _minutes(minutes), _seconds(seconds)
        {
        }
        DateTime(const DateTime &data) : _day(data._day), _month(data._month), _year(data._year), _hours(data._hours), _minutes(data._minutes), _seconds(data._seconds)
        {
        }
        bool operator==(const DateTime &data)
        {
            return ((this->_day == data._day) && (this->_month == data._month) && (this->_year == data._year) && (this->_hours == data._hours) && (this->_minutes == data._minutes) && (this->_seconds == data._seconds));
        }
        static DateTime Now()
        {
            // Elip::DateTime data();
            auto hh = std::chrono::system_clock::now();
            auto kkk = std::chrono::system_clock::to_time_t(hh);
            auto pp = std::localtime(&kkk);
            return Elip::DateTime(pp->tm_year + 1900, pp->tm_mon + 1, pp->tm_mday, pp->tm_hour, pp->tm_min, pp->tm_sec);
        }
        int GetDay()
        {
            return this->_day;
        }
        int GetMonth()
        {
            return this->_month;
        }
        int GetYear()
        {
            return this->_year;
        }

        int GetHour()
        {
            return this->_hours;
        }
        void SetPMStyle(Elip::String pm)
        {
            this->_pmStyle = pm;
        }
        void SetAMStyle(Elip::String am)
        {
            this->_amStyle = am;
        }
        Elip::String GetAMStyle() { return this->_amStyle; }
        Elip::String GetPMStyle() { return this->_pmStyle; }
        int GetMinutes()
        {
            return this->_minutes;
        }
        int GetSeconds()
        {
            return this->_seconds;
        }
        void SetYear(int year)
        {
            this->_year = year;
        }
        void SetMonth(int month)
        {
            this->_month = month;
        }
        void SetDay(int day)
        {
            this->_day = day;
        }
        void SetHour(int hour)
        {
            this->_hours = hour;
        }
        void SetMinutes(int minutes)
        {
            this->_minutes = minutes;
        }
        void SetSeconds(int seconds)
        {
            this->_seconds = seconds;
        }

        /*
        {D} = day
        {M} = month
        {Y} = year

        {h} = hour 24
        {h12} = hour 12
        {m} = minutes
        {s} = seconds
        {$} = AM/PM
        */
        Elip::String Format(Elip::String style)
        {
            auto h900 = this->ConvertHour();
            style.ReplaceAll("{D}", Elip::Str(this->GetDay()).ToString());
            style.ReplaceAll("{M}", Elip::Str(this->_month).ToString());
            style.ReplaceAll("{Y}", Elip::Str(this->_year).ToString());
            style.ReplaceAll("{h}", Elip::Str(this->_hours).ToString());
            style.ReplaceAll("{m}", Elip::Str(this->_minutes).ToString());
            style.ReplaceAll("{s}", Elip::Str(this->_seconds).ToString());
            style.ReplaceAll("{$}", h900.second.ToString());
            style.ReplaceAll("{h12}", Elip::Str(h900.first).ToString());

            return style;
        }
        std::pair<int, Elip::String> ConvertHour()
        {
            int num;
            Elip::String sign;
            if (this->_hours == 0)
            {
                num = 12;
                sign = this->GetAMStyle();
            }
            else if (this->_hours == 1)
            {
                num = 1;
                sign = this->GetAMStyle();
            }
            else if (this->_hours == 2)
            {
                num = 2;
                sign = this->GetAMStyle();
            }
            else if (this->_hours == 3)
            {
                num = 3;
                sign = this->GetAMStyle();
            }
            else if (this->_hours == 4)
            {
                num = 4;
                sign = this->GetAMStyle();
            }
            else if (this->_hours == 5)
            {
                num = 5;
                sign = this->GetAMStyle();
            }
            else if (this->_hours == 6)
            {
                num = 6;
                sign = this->GetAMStyle();
            }
            else if (this->_hours == 7)
            {
                num = 7;
                sign = this->GetAMStyle();
            }
            else if (this->_hours == 8)
            {
                num = 8;
                sign = this->GetAMStyle();
            }
            else if (this->_hours == 9)
            {
                num = 9;
                sign = this->GetAMStyle();
            }
            else if (this->_hours == 10)
            {
                num = 10;
                sign = this->GetAMStyle();
            }
            else if (this->_hours == 11)
            {
                num = 11;
                sign = this->GetAMStyle();
            }
            else if (this->_hours == 12)
            {
                num = 12;
                sign = this->GetAMStyle();
            }
            else if (this->_hours == 13)
            {
                num = 1;
                sign = this->GetPMStyle();
            }
            else if (this->_hours == 14)
            {
                num = 2;
                sign = this->GetPMStyle();
            }
            else if (this->_hours == 15)
            {
                num = 3;
                sign = this->GetPMStyle();
            }
            else if (this->_hours == 16)
            {
                num = 4;
                sign = this->GetPMStyle();
            }
            else if (this->_hours == 17)
            {
                num = 5;
                sign = this->GetPMStyle();
            }
            else if (this->_hours == 18)
            {
                num = 6;
                sign = this->GetPMStyle();
            }
            else if (this->_hours == 19)
            {
                num = 7;
                sign = this->GetPMStyle();
            }
            else if (this->_hours == 20)
            {
                num = 8;
                sign = this->GetPMStyle();
            }
            else if (this->_hours == 21)
            {
                num = 9;
                sign = this->GetPMStyle();
            }
            else if (this->_hours == 22)
            {
                num = 10;
                sign = this->GetPMStyle();
            }
            else if (this->_hours == 23)
            {
                num = 11;
                sign = this->GetPMStyle();
            }
            return std::make_pair(num, sign);
        }
    };
    // class Duration
    //  std::chrono::duration<int> Sg(int sg)
    //  {
    //      return std::chrono::seconds(sg);
    //  }

    // std::chrono::duration<int> Min(int min)
    // {
    //     return std::chrono::minutes(min);
    // }
    // std::chrono::duration<double> Ms(int ms)
    // {
    //     return std::chrono::milliseconds(ms);
    // }

} // namespace Elip

#endif