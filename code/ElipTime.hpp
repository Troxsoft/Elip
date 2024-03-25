#ifndef H__ELIP__TIME_U__TOOLS__H
#define H__ELIP__TIME_U__TOOLS__H
#include <chrono>
#include <iostream>
#include <ctime>
#include <time.h>
namespace Elip
{
    class DateTime
    {

    public:
        DateTime(std::chrono::system_clock::time_point time)
        {
            this->_time = time;
        }
        DateTime(const Elip::DateTime &dateTime)
        {
            this->_time = dateTime._time;
        }
        bool operator==(const Elip::DateTime &dateTime)
        {
            return this->_time == dateTime._time;
        }
        void operator=(const Elip::DateTime &dateTime)
        {
            this->_time = dateTime._time;
        }

        DateTime(int year, int month, int day)
        {

            std::tm info = {};
            info.tm_year = year - 1900;
            info.tm_mday = day;
            info.tm_mon = month - 1;
            std::time_t heheu = std::mktime(&info);
            this->_time = std::chrono::system_clock::from_time_t(heheu);
        }
        std::time_t ToTimeT()
        {
            return std::chrono::system_clock::to_time_t(this->_time);
        }
        std::tm *ToTm()
        {
            std::time_t jjj = this->ToTimeT();
            return std::localtime(&jjj);
        }
        static DateTime Now()
        {
            std::chrono::system_clock::time_point tki = std::chrono::system_clock::now();
            return DateTime(tki);
        }

        // void SetYear()
        // {
        //     std::tm djd = {

        //     };
        // }
        // static DateTime Now(){

        // }
    private:
        std::chrono::system_clock::time_point _time;
    };
    std::chrono::duration<int> Sg(int sg)
    {
        return std::chrono::seconds(sg);
    }

    std::chrono::duration<int> Min(int min)
    {
        return std::chrono::minutes(min);
    }
    std::chrono::duration<double> Ms(int ms)
    {
        return std::chrono::milliseconds(ms);
    }

} // namespace Elip

#endif