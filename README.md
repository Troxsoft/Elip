# A c++ 20 utils only headers
### Class
- Elip::String
- Elip::Vector
- Elip::Map
### Functions
- Str
- Split
- PrintVector
- ToVect
- ToVectStr
- Format -> wiht Color(Windows,Linux,MacOS)
- Printf ->with Format
- PrinfWithoutColor ->Prinf without color
- FormatfWithoutColor -> Format without color
- ChangeTerminalTitle -> (Windows,Linux,MacOS)
- ChangeTerminalCursorPosition -> (Windows,Linux,MacOS)
## How to include ?
```cpp
#include "Elip.hpp"
```
## Examples:
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
- Strings
```cpp
Elip::String myString("hello python hello");
myString.Replace("python", "amo");
myString.TrimLeft("hello");
Elip::Printf("{}",myString);
```
- More examples in examples folder
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
