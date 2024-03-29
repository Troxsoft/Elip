#ifndef H__ELIP__TOOLS__H
#define H__ELIP__TOOLS__H

#include "ElipExceptions.hpp"
#include "ElipFormat.hpp"
#include "ElipString.hpp"
#include "ElipVector.hpp"
#include "ElipMap.hpp"
#include "ElipFileSystem.hpp"
#include "ElipTerminal.hpp"
#include "ElipThread.hpp"
#include "ElipTime.hpp"
#include <iostream>
#include <vector>

/**
# A c++ 20 utils headers
### Class
- Elip::String
- Elip::Vector
- Elip::Map
- Elip::File
### Functions
# Strings
- Str
- Split
# Format and Print
- Format -> wiht Color(Windows,Linux,MacOS)
- Printf ->with Format
- PrinfWithoutColor ->Prinf without color
- FormatfWithoutColor -> Format without color
# Terminal utils
- ChangeTerminalTitle -> (Windows,Linux,MacOS)
- ChangeTerminalCursorPosition -> (Windows,Linux,MacOS)
- ActivateTerminal
# Filesystem
- ExistsFS
- IsFileFS
- IsDirectoryFS
- IsSymLinkFS
- DeleteFS
- CreateDirectoryFS
- CreateSymLinkFS
- CreateFileFS
# Vector
- Join
- PrintVector
- ToVect
- ToVectStr
## How to include ?
```cpp
#include "Elip.hpp"
```

## Examples:
- Filesystem:
```cpp
#include "Elip.hpp"
int main()
{
    if (!Elip::ExistsFS("test.txt"))
    {
        Elip::Printf("{}\n", "No existe el archivo text.txt,creando el archivo");
        Elip::CreateFileFS("test.txt");
    }
    Elip::File data("test.txt");
    data.Write("Hola mundo en c++");
    Elip::Printf("Datos del archivo: {}\n", data.ReadAsString());
}
```
- Format and Printf:
```cpp
#include "Elip.hpp"
using namespace Elip;
int main()
{
    //  RED    RED   GREEN
    // hello Joaquin!!!
    ActivateTerminal();
    Printf("{FG_RED}hello {}{FG_GREEN}!!!{FG_RESET}\n", "Joaquin");
    auto result = Format("hellooooo {} {}", "C++", 17);
    Printf("{}", result);
}
```
- Strings:
```cpp
Elip::String myString("hello python hello");
myString.Replace("python", "amo");
myString.TrimLeft("hello");
Elip::Printf("{}\n",myString);
```
- More examples in examples folder
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

*/
namespace Elip
{
    template <typename T>
    void PrintVector(std::vector<T> vec)
    {
        std::cout << "{ ";
        for (auto j : vec)
        {
            std::cout << j << ",";
        }
        std::cout << "}";
    }

    Elip::Vector<Elip::String> Split(Elip::String str, const std::string &delimiter)
    {
        if (delimiter == "")
        {
            Elip::Vector<Elip::String> res;
            std::string h__;
            for (int i = 0; i < str.GetLength(); i++)
            {
                h__ = str.Get(i);

                res.PushBack(Elip::String(h__));
            }
            return res;
        }
        else
        {
            size_t pos_start = 0, pos_end, delim_len = delimiter.length();
            std::string token;
            Elip::Vector<Elip::String> res;

            while ((pos_end = str.ToString().find(delimiter, pos_start)) != std::string::npos)
            {
                token = str.ToString().substr(pos_start, pos_end - pos_start);
                pos_start = pos_end + delim_len;
                res.PushBack(Elip::String(token));
            }

            res.PushBack(Elip::String(token));

            return res;
        }
    }

    template <typename T>
    Elip::Vector<T> ToVect(int from[])
    {
        Elip::Vector<T> co;
        co.vector = from;
        return co;
    }
    template <typename T>
    Elip::Vector<T> ToVect(float from[])
    {
        Elip::Vector<T> co;
        co.vector = from;
        return co;
    }
    template <typename T>
    Elip::Vector<T> ToVect(unsigned int from[])
    {
        Elip::Vector<T> co;
        co.vector = from;
        return co;
    }
    Elip::Vector<Elip::String> ToVectStr(std::vector<std::string> from)
    {
        Elip::Vector<Elip::String> co;
        for (int i = 0; i < from.size(); i++)
        {
            co.PushBack(Elip::Str(from[i]));
        }
        return co;
    }
    template <typename T>
    Elip::Vector<T> ToVect(const char *from[])
    {
        Elip::Vector<T> co;
        co.vector = from;
        return co;
    }
    template <typename T>
    Elip::Vector<T> ToVect(std::vector<T> from)
    {
        Elip::Vector<T> co;
        co.vector = from;
        return co;
    }
    template <typename T>
    Elip::String VectorToString(Elip::Vector<T> obj)
    {
        unsigned int i = 0;
        Elip::String str;
        str.ReserveMemory(sizeof(T) * obj.GetSize() + sizeof("{") + sizeof("}"));
        str.InsertRight("{");
        while (i < obj.GetSize())
        {
            if (i + 1 >= obj.GetSize())
            {
                str.InsertRight(Elip::FormatWithoutColor("{}", obj[i]).ToString());
            }
            else
            {
                str.InsertRight(Elip::FormatWithoutColor("{},", obj[i]).ToString());
            }
            i++;
        }
        str.InsertRight("}");
        return str;
    }
} // namespace Elip
#endif