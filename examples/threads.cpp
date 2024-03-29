#include "../code/Elip.hpp"
#include <atomic>
std::atomic<int> counterFast(0);
int main()
{
    Elip::Thread::Run(Elip::ThreadPriority::LOW, []()
                      {
        for(int i=0;i<20000000000;i++){
            counterFast++;
        } });
    Elip::Thread::Run(Elip::ThreadPriority::VERY_LOW, []()
                      {
        for(int i=0;i<20000000000;i++){
            counterFast++;
        } });
    Elip::Thread::Run(Elip::ThreadPriority::VERY_HIGH, []()
                      {
        for(int i=0;i<20000000000;i++){
            counterFast++;
        } });
    Elip::Thread::Run(Elip::ThreadPriority::HIGH, []()
                      {
        for(int i=0;i<20000000000;i++){
            counterFast++;
        } });
    Elip::Thread::Run(Elip::ThreadPriority::NORMAL, []()
                      {
        for(int i=0;i<20000000000;i++){
            counterFast++;
        } });

    Elip::Thread::Sleep(10 * 1000);
    Elip::Printf("{}\n", counterFast.load());
}