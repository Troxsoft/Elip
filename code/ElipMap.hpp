#ifndef H__ELIP__MAP__H
#define H__ELIP__MAP__H
#include <map>
#include "ElipVector.hpp"
#include "ElipString.hpp"
#include "ElipExceptions.hpp"
#include "ElipFormat.hpp"
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
    template <typename K, typename V>

    class Map
    {
    private:
        Elip::Vector<K> _keys;
        Elip::Vector<V> _values;

    public:
        Map()
        {
        }

        bool Exists(K key)
        {
            if (this->_keys.Search(key) == -1)
            {
                return false;
            }
            return true;
        }
        void Delete(K key)
        {
            if (this->_keys.Search(key) == -1)
            {
                throw Elip::MapKeyError("The key not exist");
            }
            else
            {
                auto index = this->_keys.Search(key);
                this->_keys.Delete(index);
                this->_values.Delete(index);
            }
        }
        void Set(K key, V value)
        {
            if (this->_keys.Search(key) == -1)
            {
                this->_keys.PushBack(key);
                this->_values.PushBack(value);
            }
            else
            {
                auto index = this->_keys.Search(key);

                this->_values.Set(index, value);
            }
        }
        V Get(K key)
        {
            if (this->_keys.Search(key) == -1)
            {
                throw Elip::MapKeyError("The key not exist");
            }
            else
            {
                return this->_values.Get(this->_keys.Search(key));
            }
        }

        std::size_t GetSize()
        {
            return this->_keys.GetSize();
        }
        std::size_t GetLength()
        {
            return this->GetSize();
        }
        Elip::String ToString()
        {
            Elip::Vector<K> keys = this->GetKeys();
            Elip::Vector<V> values = this->GetValues();
            Elip::String str;
            str.ReserveMemory(sizeof(V) + sizeof(K) * keys.GetSize() + sizeof("{") + sizeof("}") + (sizeof(":") * keys.GetSize() - 1));
            str.InsertRight("{");
            for (std::size_t i = 0; i < keys.GetSize(); i++)
            {
                if (i + 1 < keys.GetSize())
                {
                    str.InsertRight(Elip::FormatWithoutColor("{}:{},", keys[i], values[i]).ToString());
                }
                else
                {
                    str.InsertRight(Elip::FormatWithoutColor("{}:{}", keys[i], values[i]).ToString());
                }
            }
            str.InsertRight("}");
            return str;
        }
        Elip::Vector<K> GetKeys()
        {
            return this->_keys.Copy();
        }
        Elip::Vector<V> GetValues()
        {
            return this->_values.Copy();
        }
        void operator=(Elip::Map<K, V> other)
        {
            this->_keys = other._keys;
            this->_values = other._values;
        }
        bool operator==(const Elip::Map<K, V> &other)
        {
            if (this->_keys == other._keys && this->_values == other._values)
            {
                return true;
            }
            return false;
        }
        std::map<K, V> ToMap()
        {
            std::map<K, V> mapp;
            for (std::size_t i = 0; i < this->GetSize(); i++)
            {
                mapp[this->_keys[i]] = this->_values[i];
            }
            return mapp;
        }
    };
}; // namespace Elip

#endif