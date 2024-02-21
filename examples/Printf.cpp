#include "../code/Elip.hpp"
using namespace Elip;
int main()
{
    //  RED    RED   GREEN
    // hello Joaquin!!!
    Printf("{FG_RED}hello {}{FG_GREEN}!!!{FG_RESET}\n", "Joaquin");
    auto result = Format("hellooooo {} {}", "C++", 17);
    Printf("{}", result);
}