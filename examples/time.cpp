#include "../code/Elip.hpp"
#include <iostream>
int main()
{
    Elip::DateTime time = Elip::DateTime::Now();

    // time.SetYear(2011);
    // time.SetMonth(11);
    // time.SetDay(15);
    // time.SetHour(3);
    // time.SetMinutes(10);
    // time.SetSeconds(16);
    Elip::Printf("{}\n", time.Format("{h12}:{m} {$}"));
}