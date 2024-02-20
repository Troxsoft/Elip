#include "../code/Elip.hpp"
#include <iostream>
#include <vector>
int main()
{
    Elip::Vector<Elip::String> myVector;

    myVector.PushBack(Elip::String("hola mundo"));
    myVector.PushBack(Elip::String("ana"));
    myVector.PushBack(Elip::String("lol"));
    std::cout << myVector << "\n";
    std::cout << "\n";
    std::cout << myVector.GetFirst() << "\n";
    myVector[2] = Elip::String("pendejo");
    std::cout << myVector.GetLast() << "\n";
    Elip::Vector<Elip::String> myH = Elip::ToVectStr({"hola", "mundo", "hola", "mundo"});
    std::cout << myH << "\n";
}