#include "../code/Elip.hpp"
#include <iostream>
using namespace Elip;
int main()
{
    ActivateTerminal();
    ChangeTerminalTitle("tu eres un dev");
    ChangeTerminalCursorPosition(20, 20);
    Printf("{}\n", "hello dev");
}