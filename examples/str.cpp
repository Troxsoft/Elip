#include <iostream>

#include "../code/Elip.hpp"
int main()
{
    Elip::String myString("hola mundo %//mi.;.-() python python y mas python hola");
    myString.Replace("python", "amo");
    if (myString.Contains("python"))
    {
        myString.ReplaceAll("python", "rust");
    }
    myString.TrimLeft("hola");
    std::string respuesta;
    std::cin >> respuesta;
    if (respuesta == "si")
    {
        myString.TrimRight("ho");
        myString.InsertLeft(" ano se putin ");
        myString.InsertRight("viva zelensky");
    }
    myString.Set(0, 'W');
    std::cout << myString << "\n";
    std::cout << myString.Search("ñ") << "\n";
    std::cout << myString.Count("rust") << "\n";

    Elip::String information("my name is ;pedro pascal ???");

    information.InsertRight(" No or ???");
    std::cout << information << "\n";

    information.Filter([](char value, unsigned int index) {
        if (value == 'p')
        {
            return false;
        }
        else
        {
            return true;
        }
    });

    information.Filter([](char value, unsigned int index, Elip::String str) {
        if (value == 'a' && str.Get(index + 1) == 's')
        {
            return 1;
        }
        else
        {
            return 0;
        }
    });
    if (information.EndsWith("????"))
    {
        std::cout << "si"
                  << "\n";
    }
    else
    {
        std::cout << "no"
                  << "\n";
    }
    if (information.StartsWith("my"))
    {
        std::cout << "si"
                  << "\n";
    }
    else
    {
        std::cout << "no"
                  << "\n";
    }

    std::cout << information << "\n";
    std::cout << information.SubString(0, 5) << "\n";
    information.ToUpperCase();
    std::cout << information << "\n";
    information.ToLowerCase();
    std::cout << information << "\n";
    Elip::PrintVector(information.SplitToVectorString(""));
    std::cout << "\n";
    std::cout << information << "\n";
    information = "amamamamamaama";
    std::cout << information << "\n";
    return 0;
}