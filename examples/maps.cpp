#include "../code/Elip.hpp"
#include <iostream>

int main()
{
    Elip::Map<Elip::String, int> maps;
    maps.Set("hola", 30);
    // not maps["hola"] = 30;
    maps.Set("pepe", 9000000);

    Elip::Printf("{}\npepe: {}\n", maps.ToString(), maps.Get("pepe"));
}