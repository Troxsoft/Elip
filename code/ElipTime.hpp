#ifndef H__ELIP__TIME_U__TOOLS__H
#define H__ELIP__TIME_U__TOOLS__H
#include <chrono>
namespace Elip
{
    std::chrono::duration<int> Sg(int sg)
    {
        return std::chrono::seconds(sg);
    }

    std::chrono::duration<int> Min(int min)
    {
        return std::chrono::minutes(min);
    }
    std::chrono::duration<double> Ms(int ms)
    {
        return std::chrono::milliseconds(ms);
    }

} // namespace Elip

#endif