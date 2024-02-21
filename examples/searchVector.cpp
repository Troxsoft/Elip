#include "../code/Elip.hpp"
#include <iostream>
int main()
{
    Elip::Vector<Elip::String> vec = Elip::ToVectStr({"hola", "pepe", "ano"});
    int h = vec.Search("pepe");
    auto h2 = vec.Copy();
    std::cout << h << "\n";
    h = h2.SearchByCallback([](Elip::String str) {
        if (str == "ano")
        {
            return true;
        }
        return false;
    });
    std::cout << h << "\n";
}