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
namespace Elip
{

template <typename... Args> std::vector<std::any> __ArgsToVector__(Args &&...args)
{
    // Expansión de paquetes para inicializar el vector
    return {std::forward<Args>(args)...};
}
#ifdef _WIN32
void ActivateColor()
{
    HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD consoleMode;
    GetConsoleMode(handleOut, &consoleMode);
    consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    consoleMode |= DISABLE_NEWLINE_AUTO_RETURN;
    SetConsoleMode(handleOut, consoleMode);
}

#else
void ActivateColor()
{
}
#endif
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

    return cop;
}
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
template <typename... Args> Elip::String Format(std::string format, Args... args)
{
    Elip::String f = Elip::Format(Elip::String(format), __ArgsToVector__(args...));
    return f;
}
void Printf(Elip::String format, std::vector<std::any> args)
{
    Elip::String f = Elip::Format(format, args);
    printf("%s", f.ToString().c_str());
}

void Printf(std::string format, std::vector<std::any> args)
{
    Elip::String f = Elip::Format(Elip::String(format), args);

    fputs(f.ToString().c_str(), stdout);
}
template <typename... Args> void Printf(std::string format, Args... args)
{
    Elip::String f = Elip::Format(Elip::String(format), __ArgsToVector__(args...));

    fputs(f.ToString().c_str(), stdout);
}
} // namespace Elip

#endif