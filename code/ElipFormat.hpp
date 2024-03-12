#ifndef H__ELIP__FORMAT__TOOLS__H
#define H__ELIP__FORMAT__TOOLS__H
#include "ElipExceptions.hpp"
#include "ElipString.hpp"
#include <any>
#include <iostream>
#include <stdio.h>
#include <vector>
#ifdef _WIN32
#include <windows.h>

#endif
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
    ## Set a terminal title
    */
    // void ChangeTerminalTitle(const std::string &title)
    // {
    //     Elip::String str("\033]0;KI\007");
    //     str.Replace("KI", title);
    //     fputs(str.ToString().c_str(), stdout);
    // }
    /*
    ## Set a terminal title
    ### Multiplataform ??
    - Yes -> (Terminal based on `POSIX` and Windows with `winapi`)
    */
    void ChangeTerminalTitle(Elip::String title)
    {
#ifdef _WIN32
        SetConsoleTitle(title.ToString().c_str());
#else
        Elip::String str("\033]0;KI\007");

        str.Replace("KI", title.ToString());
        fputs(str.ToString().c_str(), stdout);
#endif
    }
    /*
    ### Set `cursor` of terminal
    ## Example:
```cpp
Elip::ChangeTerminalCursorPosition(2,2);
```
    */
    void ChangeTerminalCursorPosition(unsigned int x, unsigned int y)
    {
        Elip::String str("\033[y;xH");
        str.Replace("y", std::to_string(y));

        str.Replace("x", std::to_string(x));
        fputs(str.ToString().c_str(), stdout);
    }
    // # `Internal` function
    template <typename... Args>
    std::vector<std::any> __ArgsToVector__(Args &&...args)
    {
        // Expansión de paquetes para inicializar el vector
        return {std::forward<Args>(args)...};
    }
#ifdef _WIN32
    /*
    ## In windows activate POSIS emulate
    */
    void ActivateTerminal()
    {
        HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD consoleMode;
        GetConsoleMode(handleOut, &consoleMode);
        consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        consoleMode |= DISABLE_NEWLINE_AUTO_RETURN;
        SetConsoleMode(handleOut, consoleMode);
    }

#else
    /*
    ## In windows activate POSIS emulate
    ## In Linux it doesn't do anything
    */
    void ActivateTerminal()
    {
    }
#endif
    /*
    # `INTERNAL` function
    # convert a string with code colors in the POSIS colors
    ### Example:
    - {FG_RED} -> `\033[31m`
    - {FG_RESET} -> `\033[0m`
    */
    Elip::String __ConvertColor__(Elip::String str)
    {
        Elip::String cop;
        cop = str.Copy();
        cop.ReplaceAll("{FG_RESET}", "\033[0m");
        cop.ReplaceAll("{FG_RED}", "\033[31m");
        cop.ReplaceAll("{FG_GREEN}", "\033[32m");
        cop.ReplaceAll("{FG_YELLOW}", "\033[33m");
        cop.ReplaceAll("{FG_BLUE}", "\033[34m");
        cop.ReplaceAll("{FG_PURPLE}", "\033[35m");
        cop.ReplaceAll("{FG_BLACK}", "\033[30m");
        cop.ReplaceAll("{FG_WHITE}", "\033[37m");
        cop.ReplaceAll("{FG_CYAN}", "\033[36m");
        cop.ReplaceAll("{BG_BLACK}", "\033[40m");
        cop.ReplaceAll("{BG_RED}", "\033[41m");
        cop.ReplaceAll("{BG_GREEN}", "\033[42m");
        cop.ReplaceAll("{BG_YELLOW}", "\033[43m");
        cop.ReplaceAll("{BG_BLUE}", "\033[44m");
        cop.ReplaceAll("{BG_PURPLE}", "\033[45m");
        cop.ReplaceAll("{BG_CYAN}", "\033[46m");
        cop.ReplaceAll("{BG_WHITE}", "\033[47m");
        cop.ReplaceAll("{BG_RESET}", "\033[49m");
        cop.ReplaceAll("{RESET_COLOR}", "\033[49m\033[0m");
        /*
        Fondo cian: \033[46m
        Fondo blanco: \033[47m
        Restaurar fondo predeterminado: \033[49m
        */

        return cop;
    }
    /*
    ## Format function inpirated on format! in Rust
    #### This Format is very limited ,not support formatting types ,etc...
    # ✔ Valid Types:
    - `Elip::String`
    - `std::string`
    - `int`
    - `float`
*/
    Elip::String Format(Elip::String format, std::vector<std::any> args)
    {
        format = __ConvertColor__(format);
        Elip::String result(format);

        for (int i = 0; i < args.size(); i++)
        {
            if (args[i].has_value())
            {
                if (int *p = std::any_cast<int>(&args[i]))
                {
                    result.Replace("{}", std::to_string(*p));
                }
                else if (float *p = std::any_cast<float>(&args[i]))
                {
                    result.Replace("{}", std::to_string(*p));
                }
                else if (std::string *p = std::any_cast<std::string>(&args[i]))
                {
                    result.Replace("{}", *p);
                }

                else if (char *p = std::any_cast<char>(&args[i]))
                {
                    result.Replace("{}", std::to_string(*p));
                }
                else if (auto p = std::any_cast<const char *>(&args[i]))
                {
                    result.Replace("{}", std::string(*p));
                }
                else if (Elip::String *p = std::any_cast<Elip::String>(&args[i]))
                {
                    result.Replace("{}", p->ToString());
                }

                else if (args[i].type() == typeid(const char *))
                {
                    result.Replace("{}", std::any_cast<const char>(&args[i]));
                }
                else
                {
                    throw new Elip::InvalidFormatError("The type of format is invalid >:(");
                }
            }
        }
        return result;
    }
    /*
## Format function inpirated on format! in Rust
#### This Format is very limited ,not support formatting types ,etc...
# ✔ Valid Types:
- `Elip::String`
- `std::string`
- `int`
- `float`
*/
    template <typename... Args>
    Elip::String Format(std::string format, Args... args)
    {
        Elip::String f = Elip::Format(Elip::String(format), __ArgsToVector__(args...));
        return f;
    }
    /*
    ## Format function inpirated on format! in Rust (without color)
    #### This Format is very limited ,not support formatting types ,etc...
    # ✔ Valid Types:
    - `Elip::String`
    - `std::string`
    - `int`
    - `float`
*/
    Elip::String FormatWithoutColor(Elip::String format, std::vector<std::any> args)
    {

        Elip::String result(format);
        for (int i = 0; i < args.size(); i++)
        {
            if (args[i].has_value())
            {
                if (int *p = std::any_cast<int>(&args[i]))
                {
                    result.Replace("{}", std::to_string(*p));
                }
                else if (float *p = std::any_cast<float>(&args[i]))
                {
                    result.Replace("{}", std::to_string(*p));
                }
                else if (std::string *p = std::any_cast<std::string>(&args[i]))
                {
                    result.Replace("{}", *p);
                }

                else if (char *p = std::any_cast<char>(&args[i]))
                {
                    result.Replace("{}", std::to_string(*p));
                }
                else if (auto p = std::any_cast<const char *>(&args[i]))
                {
                    result.Replace("{}", std::string(*p));
                }
                else if (Elip::String *p = std::any_cast<Elip::String>(&args[i]))
                {
                    result.Replace("{}", p->ToString());
                }

                else if (args[i].type() == typeid(const char *))
                {
                    result.Replace("{}", std::any_cast<const char>(&args[i]));
                }
                else
                {
                    throw new Elip::InvalidFormatError("The type of format is invalid >:(");
                }
            }
        }
        return result;
    }
    /*
    ## Format function inpirated on format! in Rust(without color)
    #### This Format is very limited ,not support formatting types ,etc...
    # ✔ Valid Types:
    - `Elip::String`
    - `std::string`
    - `int`
    - `float`
*/
    template <typename... Args>
    Elip::String FormatWithoutColor(std::string format, Args... args)
    {
        Elip::String f = Elip::Format(Elip::String(format), __ArgsToVector__(args...));
        return f;
    }
    /*
    ## Prinf: print with format
    # Example:
```cpp
Elip::Printf("{} {} {}","mexico","is","cool");
```
    */
    void Printf(std::string format, std::vector<std::any> args)
    {
        Elip::String f = Elip::Format(Elip::String(format), args);

        fputs(f.ToString().c_str(), stdout);
    }
    /*
    ## Prinf: print with format
    # Example:
```cpp
Elip::Printf("{} {} {}","mexico","is","cool");
```
    */
    template <typename... Args>
    void Printf(std::string format, Args... args)
    {
        Elip::String f = Elip::Format(Elip::String(format), __ArgsToVector__(args...));

        fputs(f.ToString().c_str(), stdout);
    }
    /*
    ## Prinf: print with format(without color)
    # Example:
```cpp
Elip::Printf("{} {} {}","mexico","is","cool");
```
    */
    void PrintfWithoutColor(std::string format, std::vector<std::any> args)
    {
        Elip::String f = Elip::FormatWithoutColor(Elip::String(format), args);

        fputs(f.ToString().c_str(), stdout);
    }
    /*
## Prinf: print with format(without color)
# Example:
```cpp
Elip::Printf("{} {} {}","mexico","is","cool");
```
*/
    template <typename... Args>
    void PrintfWithoutColor(std::string format, Args... args)
    {
        Elip::String f = Elip::FormatWithoutColor(Elip::String(format), __ArgsToVector__(args...));

        fputs(f.ToString().c_str(), stdout);
    }
} // namespace Elip

#endif