#ifndef H__ELIP__FILESYSTEM__H
#define H__ELIP__FILESYSTEM__H
#include <fstream>
#include <iostream>
#include "ElipString.hpp"
#include "ElipExceptions.hpp"
#include "ElipVector.hpp"
#include <filesystem>
namespace Elip
{
    class File
    {
    private:
        std::fstream file;
        Elip::String path;

    public:
        File(Elip::String path) : file(path.ToString(), std::ios::in | std::ios::out), path(path)
        {
            // this->file.open(path.ToString());
            if (this->file.fail() || !this->file.is_open())
            {
                throw Elip::FileError("Fail in the load file");
            }
        }
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
        Elip::Vector<Elip::String> ReadAsVector(Elip::String sep)
        {
            Elip::String str(this->ReadAsString());
            Elip::Vector<Elip::String> lines(str.SplitToVector(sep.ToString()));
            return lines;
        }
        Elip::Vector<Elip::String> ReadAsVector()
        {
            return this->ReadAsVector("\n");
        }
        void Write(Elip::String data)
        {
            this->file.clear();
            this->file << data.ToString();
        }
        void WriteAsVector(Elip::Vector<Elip::String> data, Elip::String sep)
        {
            this->file.clear();
            this->Write(Elip::Join(data, sep));
        }
        void WriteAsVector(Elip::Vector<Elip::String> data)
        {
            this->WriteAsVector(data, "\n");
        }
        Elip::String GetPath()
        {
            return this->path;
        }
        ~File()
        {
            this->file.close();
        }
    };

    bool ExistsFS(Elip::String path)
    {
        return std::filesystem::exists(path.ToString());
    }
    bool IsFileFS(Elip::String path)
    {
        if (ExistsFS(path) == false)
        {
            return false;
        }
        return std::filesystem::is_regular_file(path.ToString());
    }
    bool IsDirectoryFS(Elip::String path)
    {
        if (ExistsFS(path) == false)
        {
            return false;
        }
        return std::filesystem::is_directory(path.ToString());
    }
    bool IsSymLinkFS(Elip::String path)
    {
        if (ExistsFS(path) == false)
        {
            return false;
        }
        return std::filesystem::is_symlink(path.ToString());
    }
    void DeleteFS(Elip::String path)
    {
        if (ExistsFS(path) == false)
        {
            return;
        }
        std::filesystem::remove_all(path.ToString());
    }
    void CreateDirectoryFS(Elip::String path)
    {
        if (ExistsFS(path))
        {
            return;
        }
        std::filesystem::create_directory(path.ToString());
    }
    void CreateSymLinkFS(Elip::String path, Elip::String to)
    {
        if (ExistsFS(path))
        {
            return;
        }
        std::filesystem::create_symlink(to.ToString(), path.ToString());
    }
    void CreateFileFS(Elip::String path)
    {
        if (ExistsFS(path))
        {
            return;
        }
        std::ofstream{path.ToString()};
    }

} // namespace Elip

#endif