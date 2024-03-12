#ifndef H__ELIP__FILESYSTEM__H
#define H__ELIP__FILESYSTEM__H
#include <fstream>
#include <iostream>
#include "ElipString.hpp"
#include "ElipExceptions.hpp"
#include "ElipVector.hpp"
#include <filesystem>
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
## Class that handles files
### Example:
```cpp
// Open the file
Elip::File myfile("nasaData.txt");
// Write in the file: nasaData.txt
myfile.Write("Information number:300303,...");
// Print text of file
Elip::Printf("Data of file: {}\n",myfile.ReadAsString());
```
     */
    class File
    {
    private:
        // ## Internal `file`
        std::fstream file;
        // ## `Path` of file
        Elip::String path;

    public:
        /*
## Make a file with path
## Example:
```cpp
// Create file with path of:"thisIsMyFile.txt":
Elip::File myFile("thisIsMyFile.txt");
```
        */
        File(Elip::String path) : file(path.ToString(), std::ios::in | std::ios::out), path(path)
        {
            // this->file.open(path.ToString());
            if (this->file.fail() || !this->file.is_open())
            {
                throw Elip::FileError("Fail in the load file");
            }
        }
        /*
## Read the file as Elip::String
## Example:
```cpp
//Test.txt -> hello from ...
file.ReadAsString(); // return a Elip::String with text: "hello from ..."
```
#### Return a `Elip::String`

        */
        Elip::String ReadAsString()
        {
            this->file.seekg(0);
            Elip::String str;
            std::string line;
            while (std::getline(this->file, line))
            {

                str.InsertRight(line);
                str.InsertRight("\n");
            }
            this->file.seekg(0);
            return str;
        }
        /*
## Read the file as Elip::Vector<Elip::String>
## Example:
```cpp
//Test.txt -> "1 2 3 4"
file.ReadAsVector(" "); // return a Elip::Vector<Elip::String>:{"1","2","3","4"}
```
#### Return a `Elip::Vector<Elip::String>`

        */
        Elip::Vector<Elip::String> ReadAsVector(Elip::String sep)
        {
            Elip::String str(this->ReadAsString());
            Elip::Vector<Elip::String> lines(str.SplitToVector(sep.ToString()));
            return lines;
        }
        /*
## Read the file as `Elip::Vector<Elip::String> `
### `ReadAsVector();` is a alias for `ReadAsVector("\n");`
## Example:
```cpp
//Test.txt ->
//hello
//from
//mexico , spain or ...
file.ReadAsVector(); // return a Elip::Vector<Elip::String>:{"hello","from","mexico , spain or ... "}
```
#### Return a `Elip::Vector<Elip::String>`

        */
        Elip::Vector<Elip::String> ReadAsVector()
        {
            return this->ReadAsVector("\n");
        }
        /*
        ## Write text`(as Elip::String)` in the file
        ### This function clear all data of this file and write the new data
        ## Example:
```cpp
// File-> "Hello from:"
file.Write("Pepe");
//file content: "Pepe"
```
        */
        void Write(Elip::String data)
        {
            this->file.clear();
            this->file << data.ToString();
        }
        /*
        ## Write text`(as Elip::Vector<Elip::String>)` in the file
        ### This function clear all data of this file and write the new data
        ## Example:
```cpp
// File-> "Hello from: \n mexivo"
file.WriteAsVector(Elip::Vector<Elip::String>({"hello","juan"}," "));
//file content: "hello juan"
```
        */
        void WriteAsVector(Elip::Vector<Elip::String> data, Elip::String sep)
        {
            this->file.clear();
            this->Write(Elip::Join(data, sep));
        }
        void WriteAsVector(Elip::Vector<Elip::String> data)
        {
            this->WriteAsVector(data, "\n");
        }
        /*
        ## Get file path
        ### Example:
```cpp
Elip::File file("db/users.txt");
file.GetPath(); // "db/users.txt"
```
        */
        Elip::String GetPath()
        {
            return this->path;
        }
        /*
        # `Close` the file
        ## Wrapper of `fstream.close();`
        */
        void Close()
        {
            file.close();
        }
        /*
        ## Close `automatically` the file.
        - file.Close()
        */
        ~File()
        {
            this->file.close();
        }
    };
    /*
    ## Check if `exist` the file,directory,symlink in the filesystem
    */
    bool ExistsFS(Elip::String path)
    {
        return std::filesystem::exists(path.ToString());
    }
    /*
    ## Check if is file or no
    */
    bool IsFileFS(Elip::String path)
    {
        if (ExistsFS(path) == false)
        {
            return false;
        }
        return std::filesystem::is_regular_file(path.ToString());
    }
    /*
    ## Check if is directory or no
    */
    bool IsDirectoryFS(Elip::String path)
    {
        if (ExistsFS(path) == false)
        {
            return false;
        }
        return std::filesystem::is_directory(path.ToString());
    }
    /*
    ## Check if is Symlink or no
    */
    bool IsSymLinkFS(Elip::String path)
    {
        if (ExistsFS(path) == false)
        {
            return false;
        }
        return std::filesystem::is_symlink(path.ToString());
    }
    /*
## `Delete` a file,symLink,directory,etc from the filesystem
    */
    void DeleteFS(Elip::String path)
    {
        if (ExistsFS(path) == false)
        {
            return;
        }
        std::filesystem::remove_all(path.ToString());
    }
    /*
    ## Create a `directory` in the filesystem
    ### Example:
```cpp
Elip::CreateDirectoryFS("tmp");
```
    */
    void CreateDirectoryFS(Elip::String path)
    {
        if (ExistsFS(path))
        {
            return;
        }
        std::filesystem::create_directory(path.ToString());
    }
    /*
    ## Create a `SymLink` in the filesystem
    ### Example:
```cpp
Elip::CreateSymLinkFS("app","path/to/executable/application/app.exe");
```
    */
    void CreateSymLinkFS(Elip::String path, Elip::String to)
    {
        if (ExistsFS(path))
        {
            return;
        }
        std::filesystem::create_symlink(to.ToString(), path.ToString());
    }
    /*
    ## Create a `file` in the filesystem
    ### Example:
```cpp
Elip::CreateFileFS("log.txt");
```
    */
    void CreateFileFS(Elip::String path)
    {
        if (ExistsFS(path))
        {
            return;
        }
        std::ofstream{path.ToString()};
    }
    /*
    ## Wrapper of
```cpp
Elip::File file(path);
file.Write(data);
file.Close();
```
    */
    void WriteFileFS(Elip::String path, Elip::String data)
    {
        Elip::File file(path);
        file.Write(data);
        file.Close();
    }
    /*
    ## Wrapper of
```cpp
Elip::File file(path);
file.WriteAsVector(data);
file.Close();
```
    */
    void WriteFileFS(Elip::String path, Elip::Vector<Elip::String> data)
    {
        Elip::File file(path);
        file.WriteAsVector(data);
        file.Close();
    }
    /*
    ## Wrapper of
```cpp
Elip::File file(path);
file.WriteAsVector(data, sep);
file.Close();
```
    */
    void WriteFileFS(Elip::String path, Elip::Vector<Elip::String> data, Elip::String sep)
    {
        Elip::File file(path);
        file.WriteAsVector(data, sep);
        file.Close();
    }
    /*
    ## Wrapper of
```cpp
Elip::File file(path);
Elip::String str = file.ReadAsString();
file.Close();
```
    */
    Elip::String ReadFileFS(Elip::String path)
    {
        Elip::File file(path);
        Elip::String str = file.ReadAsString();
        file.Close();
        return str;
    }
    /*
    ## Wrapper of
```cpp
Elip::File file(path);
file.ReadAsVector();
file.Close();
```
    */
    Elip::Vector<Elip::String> ReadFileAsVectorFS(Elip::String path)
    {
        Elip::File file(path);
        Elip::Vector<Elip::String> str = file.ReadAsVector();
        file.Close();
        return str;
    }
    /*
    ## Wrapper of
```cpp
Elip::File file(path);
file.ReadAsVector(sep);
file.Close();
```
    */
    Elip::Vector<Elip::String> ReadFileAsVectorFS(Elip::String path, Elip::String sep)
    {
        Elip::File file(path);
        Elip::Vector<Elip::String> str = file.ReadAsVector(sep);
        file.Close();
        return str;
    }
} // namespace Elip

#endif