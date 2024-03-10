#include "../code/Elip.hpp"
#include <iostream>

int main()
{
    Elip::Vector<Elip::String> strs = Elip::ToVectStr({"1", "2", "3", "4", "5"});
    Elip::Vector<int> numbers = strs.Map<int>([](Elip::String str)
                                              { return str.ToInt(); });
    Elip::Printf("Strings: {}\nNumbers:{} \n", strs.ToString(), numbers.ToString());
}