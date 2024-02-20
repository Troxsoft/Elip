# A c++ 11 utils only headers
### Class
- Elip::String
- Elip::Vector
### Functions
- Str
- Split
- PrintVector
- ToVect
- ToVectStr
## How to include ?
```cpp
#include "Elip.hpp"
```
## Examples:
- Elip::String:
```cpp
Elip::String myString("Hello dev");
myString.Replace("dev", "you name");
std::cout << myString<<"\n";
```
- Elip::Vector:
```cpp
Elip::Vector<Elip::String> myVector;

myVector.PushBack(Elip::String("hola mundo"));
myVector.PushBack(Elip::String("ana"));
myVector.PushBack(Elip::String("lol"));
std::cout << myVector << "\n";
std::cout << "\n";
std::cout << myVector.GetFirst() << "\n";
myVector[2] = Elip::String("f en el chat");
std::cout << myVector.GetLast() << "\n";
```
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
