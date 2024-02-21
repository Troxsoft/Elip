#include "../code/Elip.hpp"
#include <iostream>
using namespace Elip;
int main()
{
    ActivateColor();
    for (int i = 0; i < 100; i++)
    {
        Printf("{FG_GREEN}Number:{}{FG_RESET}\n", i);
    }
    auto j = Format("hola {}", "mundo");
    Printf("{FG_RED}{}{FG_RESET}\n", j);
}