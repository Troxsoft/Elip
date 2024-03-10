#ifndef H__ELIP__EXCEPTIONS__TOOLS__H
#define H__ELIP__EXCEPTIONS__TOOLS__H
#include <iostream>
namespace Elip
{
  class ElipException : public std::exception
  {
  private:
    std::string message;
    std::string info_;

  public:
    ElipException(std::string msg, std::string info) : message(msg), info_(info)
    {
    }
    char *what()
    {
      return (char *)this->message.c_str();
    }
    std::string GetMessage()
    {
      return this->message;
    }
    std::string GetInfo()
    {
      return this->info_;
    }
  };
  class LenghtError : public Elip::ElipException
  {
  public:
    LenghtError(std::string info) : Elip::ElipException("The length is incorrect", info)
    {
    }
  };
  class IndexError : public Elip::ElipException
  {
  public:
    IndexError(std::string info) : Elip::ElipException("The length is incorrect", info)
    {
    }
  };
  class InvalidFormatError : public Elip::ElipException
  {
  public:
    InvalidFormatError(std::string info) : Elip::ElipException("The format is not invalid", info)
    {
    }
  };
  class MapKeyError : public Elip::ElipException
  {
  public:
    MapKeyError(std::string info) : Elip::ElipException("not exists the key", info)
    {
    }
  };
} // namespace Elip
#endif