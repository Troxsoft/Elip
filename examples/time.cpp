#include "../code/Elip.hpp"
#include <iostream>
int main()
{
    Elip::DateTime time(2011, 11, 15);
    std::tm *tim = time.ToTm();

    Elip::Printf("Dia:{} Mes:{} Año:{}\n", tim->tm_mday, tim->tm_mon, tim->tm_year);
}