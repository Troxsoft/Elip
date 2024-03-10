#ifndef H__ELIP__STRING__TOOLS__H
#define H__ELIP__STRING__TOOLS__H
#include "ElipExceptions.hpp"

#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <locale>
#include <vector>
namespace Elip
{
    /*
    ## The `Elip::String` class
    ### Contains `methods` for `handling` `strings`
    */
    class String
    {
    private:
        std::string str;

    public:
        String(const std::string &string) : str(string)
        {
        }
        String(const char string[]) : str(string)
        {
        }
        String() : str("")
        {
        }
        std::size_t GetLength()
        {
            return this->str.length();
        }
        void Replace(const std::string &toSearch, const std::string &toReplace)
        {
            this->str = this->str.replace(this->str.find(toSearch), toSearch.size(), toReplace);
        }
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
        bool operator==(const std::string &str)
        {
            if (this->str == str)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
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

        bool Contains(const std::string &toSearch)
        {
            if (this->str.find(toSearch) != std::string::npos)
            {
                return true;
            }
            return false;
        }
        std::string ToString() noexcept
        {
            return this->str;
        }

        void TrimLeft(const std::string &toTrim)
        {
            this->str.erase(str.find_last_not_of(toTrim) + 1);
        }
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
        int ToInt()
        {
            return std::stoi(this->ToString());
        }
        float ToFloat()
        {
            return std::stof(this->ToString());
        }
        double ToDouble()
        {
            return std::stod(this->ToString());
        }
        long double ToLongDouble()
        {
            return std::stold(this->ToString());
        }

        void TrimRight(const std::string &toTrim)
        {
            this->str.erase(0, str.find_first_not_of(toTrim));
        }
        void Set(const std::string &newStr)
        {
            this->str = newStr;
        }
        void Set(unsigned int index, char newChar)
        {
            if (index > this->GetLength())
            {
                throw new Elip::IndexError("index > string size");
            }
            this->str[index] = newChar;
        }
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