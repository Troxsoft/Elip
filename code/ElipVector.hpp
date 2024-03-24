#ifndef H__ELIP__VECTOR__TOOLS__H
#define H__ELIP__VECTOR__TOOLS__H
#include <iostream>
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
    /*
     */
    class Vector
    {
    private:
        std::vector<T> vector;

    public:
        Vector()
        {
        }
        Vector(std::vector<T> from)
        {
            this->vector = std::vector<T>(from);
        }

        void ReserveElements(std::size_t size)
        {

            this->vector.reserve(size);
        }
        // <template typename R> R Map()
        // {
        //     std::
        // }
        friend std::ostream &operator<<(std::ostream &out, Elip::Vector<T> const &obj)
        {
            unsigned int i = 0;
            std::cout << "{ ";
            while (i < obj.vector.size())
            {
                if (i + 1 >= obj.vector.size())
                {
                    std::cout << obj.vector[i];
                }
                else
                {
                    std::cout << obj.vector[i] << ",";
                }
                i++;
            }
            std::cout << " }";

            return out;
        };
        T &operator[](int index)
        {
            return this->vector[index];
        }

        T operator[](int index) const
        {
            return this->vector[index];
        }

        Elip::Vector<T> Copy()
        {
            Elip::Vector<T> copy;
            copy.vector = std::vector<T>(this->vector);
            return copy;
        }

        bool operator==(const std::vector<T> &mv)
        {
            if (this->vec == mv)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        bool operator==(const Elip::Vector<T> &obj)
        {
            if (this->vector == obj.vector)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        std::vector<T> *ToVector()
        {
            return &this->vector;
        }
        void PushFront(T element)
        {
            this->vector.insert(this->vector.begin(), 1, element);
        }
        void PushBack(T element)
        {
            this->vector.push_back(element);
        }
        T GetFirst()
        {
            return this->vector[0];
        }
        T GetLast()
        {
            return this->vector[this->GetLength() - 1];
        }
        void Set(unsigned int index, T element)
        {
            if (index > this->vector.size())
            {
                throw new Elip::IndexError("index > size of Elip::Vector");
            }
            this->vector[index] = element;
        }
        T Get(unsigned int index)
        {
            if (index > this->vector.size())
            {
                throw new Elip::IndexError("index > size of Elip::Vector");
            }
            return this->vector[index];
        }
        std::size_t GetLength()
        {
            return this->vector.size();
        }
        std::size_t GetSize()
        {
            return this->GetLength();
        }
        void Filter(std::function<bool(T, unsigned int)> callback)
        {
            Elip::Vector<T> newStr;
            for (size_t i = 0; i < this->GetLength(); i++)
            {
                bool func = callback(this->Get(i), i);
                if (func)
                {
                    newStr.PushBack(this->Get(i));
                }
            }
            this->vector = newStr.ToVector();
        }
        int SearchByCallback(std::function<bool(T)> callback)
        {
            for (std::size_t i = 0; i < this->GetSize(); i++)
            {
                if (callback(this->Get(i)))
                {
                    return i;
                }
            }
            return false;
        }
        void Delete(std::size_t index)
        {
            this->vector.erase(this->vector.begin() + index);
        }
        int Search(T element)
        {
            for (std::size_t i = 0; i < this->GetLength(); i++)
            {
                if (this->Get(i) == element)
                {
                    return i;
                }
            }
            return -1;
        }

        Elip::String ToString()
        {
            unsigned int i = 0;
            Elip::String str;
            str.ReserveMemory(sizeof(T) * this->GetSize() + sizeof("{") + sizeof("}"));
            str.InsertRight("{");
            while (i < this->GetSize())
            {
                if (i + 1 >= this->GetSize())
                {
                    str.InsertRight(Elip::FormatWithoutColor("{}", this->Get(i)).ToString());
                }
                else
                {
                    str.InsertRight(Elip::FormatWithoutColor("{},", this->Get(i)).ToString());
                }
                i++;
            }
            str.InsertRight("}");
            return str;
        }
        template <typename R>
        Elip::Vector<R> Map(std::function<R(T)> callback)
        {

            Elip::Vector<R> vec;
            for (std::size_t i = 0; i < this->GetSize(); i++)
            {
                vec.PushBack(callback(this->Get(i)));
            }
            return vec;
        }

        void Filter(std::function<unsigned int(T, unsigned int, Elip::Vector<T>)> callback)
        {
            Elip::Vector<T> newStr;

            for (size_t i = 0; i < this->GetLength(); i++)
            {
                unsigned int func = callback(this->Get(i), i, this->Copy());
                if (func == 0)
                {
                    newStr.PushBack(this->Get(i));
                }
                else
                {
                    i += func;
                }
            }
            this->vector = newStr.ToVector();
        }
    };
    Elip::String Join(Elip::Vector<Elip::String> vec, Elip::String sep)
    {
        Elip::String kk;
        for (std::size_t i = 0; i < vec.GetSize(); i++)
        {
            kk.InsertRight(vec[i].ToString());
            kk.InsertRight(sep.ToString());
        }
        return kk;
    }
} // namespace Elip

#endif