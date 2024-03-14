#ifndef H__ELIP__STRING__TOOLS__H
#define H__ELIP__STRING__TOOLS__H
#include "ElipExceptions.hpp"

#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <locale>
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
    /*
    ## A utils class for string
    #### Tools:
    - `Manipulate` `strings`
    - Utils `functions` for `strings`
    ### Example:
```cpp
// Create String
Elip::String str("hello");
// Replace hello wih hi
str.Replace("hello","hi");
str.Conatains("hi"); // return true
str.Contains("hello"); // return false
```*/
    class String
    {
    private:
        std::string str;

    public:
        /*
        ### Make a string with: `std::string`
        */
        String(const std::string &string) : str(string)
        {
        }
        /*
    ### Make a string with: `const char[]`
    */
        String(const char string[]) : str(string)
        {
        }
        /*
        ### Make a empty string as ""
        */
        String() : str("")
        {
        }
        /*
        ## Get length for string
        ##### Wrapper for
```cpp
std::string.length();
```
        */
        std::size_t GetLength()
        {
            return this->str.length();
        }
        /*
        ### Replace a search with other string
        ###
        */
        void Replace(const std::string &toSearch, const std::string &toReplace)
        {
            this->str = this->str.replace(this->str.find(toSearch), toSearch.size(), toReplace);
        }
        /*
        ### Replace all searchs with other string
        ###
        */
        void ReplaceAll(const std::string &toSearch, const std::string &toReplace)
        {
            for (int i = 0; this->Contains(toSearch); i++)
            {
                this->Replace(toSearch, toReplace);
            }
        }
        friend std::ostream &operator<<(std::ostream &out, const Elip::String &obj);
        void operator=(std::string str)
        {
            this->str = str;
        }
        // bool operator==(const std::string &str)
        // {
        //     if (this->str == str)
        //     {
        //         return true;
        //     }
        //     else
        //     {
        //         return false;
        //     }
        // }
        bool operator==(const Elip::String &str)
        {
            if (this->str == str.str)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        /*
        ## Check if string contains other string
        */
        bool Contains(const std::string &toSearch)
        {
            if (this->str.find(toSearch) != std::string::npos)
            {
                return true;
            }
            return false;
        }
        /*
        ### Convert Elip::String to std::string
        */
        std::string ToString() noexcept
        {
            return this->str;
        }
        /*
        ### Remove a string at the end
        */
        void TrimLeft(const std::string &toTrim)
        {
            this->str.erase(str.find_last_not_of(toTrim) + 1);
        }
        /*
        ### This function is used to determine the number of occurrences of a specified substring within a given string.
        */
        int Count(const std::string &str)
        {
            int count = 0;
            size_t pos = 0;
            while ((pos = this->str.find(str, pos)) != std::string::npos)
            {
                // Incrementar el contador y avanzar la posición de inicio de la búsqueda
                ++count;
                pos += str.length();
            }
            return count;
        }
        /*
        ### Try convert this `string` as `int`
        */
        int ToInt()
        {
            return std::stoi(this->ToString());
        }
        /*
       ### Try convert this `string` as `float`
       */
        float ToFloat()
        {
            return std::stof(this->ToString());
        }
        /*
       ### Try convert this `string` as `double`
       */
        double ToDouble()
        {
            return std::stod(this->ToString());
        }
        /*
       ### Try convert this `string` as `long double`
       */
        long double ToLongDouble()
        {
            return std::stold(this->ToString());
        }
        /*
        ### Remove a string at the start
        */
        void TrimRight(const std::string &toTrim)
        {
            this->str.erase(0, str.find_first_not_of(toTrim));
        }
        /*
        ## Equivalent to `==`
        */
        void Set(const std::string &newStr)
        {
            this->str = newStr;
        }
        /*
      ## Set char into string
      */
        void Set(unsigned int index, char newChar)
        {
            if (index > this->GetLength())
            {
                throw new Elip::IndexError("index > string size");
            }
            this->str[index] = newChar;
        }
        /*
        ## Get char with index
        */
        char Get(unsigned int index)
        {
            if (index > this->GetLength())
            {
                throw new Elip::IndexError("index > string size");
            }
            return this->str[index];
        }
        void InsertLeft(const std::string &toInsert)
        {
            this->str.insert(0, toInsert);
        }
        void ReserveMemory(std::size_t size)
        {
            this->str.reserve(size);
        }
        void InsertRight(const std::string &toInsert)
        {
            this->str.insert(this->GetLength(), toInsert);
        }
        bool StartsWith(const std::string &isStartWith)
        {
            if (isStartWith.length() > this->GetLength())
            {
                return false;
            }
            if (this->str.substr(0, isStartWith.length()) == isStartWith)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        Elip::String SubString(unsigned int start, unsigned int end)
        {
            if (start > this->GetLength())
            {
                throw new Elip::LenghtError("The start > string size");
            }
            if (end > this->GetLength())
            {
                throw new Elip::LenghtError("The end > string size");
            }
            if (start > end)
            {
                throw new Elip::LenghtError("Start > End");
            }
            return Elip::String(this->str.substr(start, end));
        }
        bool EndsWith(const std::string &isEndsWith)
        {
            if (this->GetLength() - isEndsWith.length() < 0)
            {
                return false;
            }

            if (this->str.substr(this->GetLength() - isEndsWith.length(), isEndsWith.length()) == isEndsWith)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        std::size_t GetSize()
        {
            return this->GetLength();
        }
        /*

      If it returns true, the number is saved, otherwise it is not saved.
        */
        void Filter(std::function<bool(char, unsigned int)> callback)
        {

            std::string newStr;
            for (size_t i = 0; i < this->GetLength(); i++)
            {
                bool func = callback(this->Get(i), i);
                if (func)
                {
                    newStr.push_back(this->Get(i));
                }
            }
            this->Set(newStr);
        }
        Elip::String Copy()
        {
            return Elip::String(this->str);
        }
        void Filter(std::function<unsigned int(char, unsigned int, Elip::String)> callback)
        {
            std::string newStr;
            std::string copyStr = this->str;

            for (size_t i = 0; i < this->GetLength(); i++)
            {
                unsigned int func = callback(this->Get(i), i, this->Copy());
                if (func == 0)
                {
                    newStr.push_back(this->Get(i));
                }
                else
                {
                    i += func;
                }
            }
            this->Set(newStr);
        }

        int Search(const std::string &toSearch)
        {
            int f = this->str.find(toSearch);
            if (f == std::string::npos)
            {
                f = -1;
            }
            return f;
        }
        void ToUpperCase()
        {
            std::transform(this->str.begin(), this->str.end(), this->str.begin(), ::toupper);
        }
        void ToLowerCase()
        {
            std::transform(this->str.begin(), this->str.end(), this->str.begin(), ::tolower);
        }
        std::vector<Elip::String> SplitToVector(const std::string &delimiter)
        {
            std::vector<std::string> split = this->SplitToVectorString(delimiter);
            std::vector<Elip::String> splitStr;
            for (std::size_t i = 0; i < split.size(); i++)
            {
                splitStr.push_back(Elip::String(split[i]));
            }
            return splitStr;
        }
        std::vector<std::string> SplitToVectorString(const std::string &delimiter)
        {
            if (delimiter == "")
            {
                std::vector<std::string> res;
                std::string h__;
                for (int i = 0; i < this->str.length(); i++)
                {
                    h__ = this->str[i];
                    res.push_back(h__);
                }
                return res;
            }
            else
            {
                size_t pos_start = 0, pos_end, delim_len = delimiter.length();
                std::string token;
                std::vector<std::string> res;

                while ((pos_end = this->str.find(delimiter, pos_start)) != std::string::npos)
                {
                    token = this->str.substr(pos_start, pos_end - pos_start);
                    pos_start = pos_end + delim_len;
                    res.push_back(token);
                }

                res.push_back(this->str.substr(pos_start));
                return res;
            }
        }
        //~String();
    };
    std::ostream &operator<<(std::ostream &out, const Elip::String &obj)
    {
        out << obj.str;
        return out;
    }
} // namespace Elip

#endif