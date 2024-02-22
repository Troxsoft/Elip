#include "../code/Elip.hpp"
using namespace Elip;
int main()
{
    //  RED    RED   GREEN
    // hello Joaquin!!!
    // Printf("{FG_RED}hello {}{FG_GREEN}!!!{FG_RESET}\n", "Joaquin");
    // auto result = Format("hellooooo {} {}", "C++", 17);
    // Printf("{}", result);
    Vector<int> h;
    h.ReserveElements(100);
    for (int i = 0; i < 100; i++)
    {
        h.PushBack(i);
    }
    String hola("mundo");
    hola.InsertLeft("hola ");
    hola.InsertRight(" en python");
    Printf("{BG_GREEN}{FG_RED}{}{RESET_COLOR}\nTexto: {}\n", VectorToString(h), hola);
}