#ifndef H__ELIP__TOOLS__H
#define H__ELIP__TOOLS__H

#include "ElipExceptions.hpp"
#include "ElipFormat.hpp"
#include "ElipString.hpp"
#include "ElipVector.hpp"
#include <iostream>
#include <vector>
/**
## The `Elib library`.
#### What is?
- It is a `library` that contains `functions`, `classes`, `etc...` that makes
your life easier
### Tools:
- `Elip::String`
#### Example with `Elip::String`:
```
Elip::String myString("hello");
```
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
    Elip::String Str(unsigned int str)
    {
        return Elip::String(std::to_string(str));
    }
    Elip::String Str(float str)
    {
        return Elip::String(std::to_string(str));
    }
    Elip::String Str(int str)
    {
        return Elip::String(std::to_string(str));
    }
    Elip::String Str(const char *str)
    {
        return Elip::String(std::string(str));
    }
    Elip::String Str(std::string str)
    {
        return Elip::String(str);
    }
    Elip::String Str(char str[])
    {
        return Elip::String(std::string(str));
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