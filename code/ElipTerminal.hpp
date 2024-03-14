#ifndef H__ELIP__TERMINAL_U__TOOLS__H
#define H__ELIP__TERMINAL_U__TOOLS__H
#include "ElipString.hpp"
#include "ElipVector.hpp"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "ElipFormat.hpp"
namespace Elip
{
    Elip::String Scan(Elip::String end)
    {
        Elip::String str;
        int car;
        while (!str.Contains(end.ToString()))
        {
            car = std::fgetc(stdin);
            std::string kkkk = std::string(1, static_cast<char>(car));

            str.InsertRight(kkkk);
        }
        return str;
    }
    Elip::String Scan(char end)
    {
        Elip::String str;
        int car;
        while (car != end)
        {
            car = std::fgetc(stdin);
            std::string kkkk = std::string(1, static_cast<char>(car));

            str.InsertRight(kkkk);
        }
        return str;
    }
    Elip::String ScanLine()
    {
        return Elip::Scan('\n');
    }

}
#endif