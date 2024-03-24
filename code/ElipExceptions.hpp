#ifndef H__ELIP__EXCEPTIONS__TOOLS__H
#define H__ELIP__EXCEPTIONS__TOOLS__H
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
	/**
	 *
	 * ### The `Base` class for Elip exeptions
	 * ## Exeptions group:
	 * -  `LenghtError`
	 * - `IndexError`
	 * - `InvalidFormatError`
	 * - `MapKeyError`
	 * - `FileError`
	 */
	class ElipException : public std::exception
	{
	private:
		std::string message;
		std::string info_;

	public:
		ElipException(std::string msg, std::string info) : message(msg), info_(info)
		{
		}
		/**
		 * ## Get a message of error
		 */
		char *what()
		{
			return (char *)this->message.c_str();
		}
		/**
		 * ## Get a `message` of error
		 */
		std::string GetMessage()
		{
			return this->message;
		}
		/**
		 * ## Get a `information` of error
		 */
		std::string GetInfo()
		{
			return this->info_;
		}
	};
	/**
	 * ## Caused by trying because something that was wrong size was used
	 * #### `Alert`: Typographic error:LenghtError->LengthError :(
	 */
	class LenghtError : public Elip::ElipException
	{
	public:
		LenghtError(std::string info) : Elip::ElipException("The length is incorrect", info)
		{
		}
	};
	/**
	 * ## Caused by trying to access the wrong index in a `vector` or `string`
	 * # Classes that cause this exception:
	 * - `Elip::String`
	 * - `Elip::Vector`
	 */
	class IndexError : public Elip::ElipException
	{
	public:
		IndexError(std::string info) : Elip::ElipException("The length is incorrect", info)
		{
		}
	};
	/**
	 * ## Caused by trying to format a type not supported by `Elip::Format`
	 * # Functions causing this exception:
	 * - `Elip::Format`
	 * - `Elip::FormatWithoutColor`
	 * - `Elip::Printf`
	 * - `Elip::PrinfWithoutColor`
	 */
	class InvalidFormatError : public Elip::ElipException
	{
	public:
		InvalidFormatError(std::string info) : Elip::ElipException("The format is not invalid", info)
		{
		}
	};
	/**
	 * ## Caused by attempting to access an unset key in the `Elip::Map`
	 * ## Classes that cause it:
	 * - `Elip::Map`
	 */
	class MapKeyError : public Elip::ElipException
	{
	public:
		MapKeyError(std::string info) : Elip::ElipException("not exists the key", info)
		{
		}
	};
	/**
	 * ## Caused by `any error` in the `file`
	 * # What causes it?
	 * - `File handling functions`
	 * - `Elip::File`
	 * - `And more`
	 */
	class FileError : public Elip::ElipException
	{
	public:
		FileError(std::string info) : Elip::ElipException("Error in the file.", info)
		{
		}
	};
	class ThreadError : public Elip::ElipException
	{
	public:
		ThreadError(std::string info) : Elip::ElipException("Error in thread.", info)
		{
		}
	};
	class ThreadExecError : public Elip::ThreadError
	{
	public:
		ThreadExecError() : Elip::ThreadError("Error in the try running thread")
		{
		}
	};

} // namespace Elip
#endif