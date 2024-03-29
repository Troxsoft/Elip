#ifndef H__ELIP__THREAD__TOOLS__H
#define H__ELIP__THREAD__TOOLS__H
// template <typename T>
#include <iostream>
#include <thread>
#include <functional>
#include "ElipExceptions.hpp"
#include <chrono>
#include "ElipMap.hpp"
#include "ElipTime.hpp"
#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

namespace Elip
{
    enum ThreadPriority
    {
        LOW,       // #### In `Posix`(Linux,etc..) = `7`,In `Windows` = `THREAD_PRIORITY_BELOW_NORMAL`
        VERY_LOW,  // #### In `Posix`(Linux,etc..) = `1`,In `Windows` = `THREAD_PRIORITY_LOWEST`
        NORMAL,    // #### In `Posix`(Linux,etc..) = `20`,In `Windows` = `THREAD_PRIORITY_NORMAL`
        HIGH,      // #### In `Posix`(Linux,etc..) = `25`,In `Windows` = `THREAD_PRIORITY_ABOVE_NORMAL`
        VERY_HIGH, // #### In `Posix`(Linux,etc..) = `40`,In `Windows` = `THREAD_PRIORITY_HIGHEST`
    };
    class Thread
    {
    private:
        std::thread th;
        Elip::ThreadPriority _priority;
        std::function<void(void)> callback;
        bool _terminate;

    public:
        Thread(std::function<void(void)> _callback) : _priority(Elip::ThreadPriority::NORMAL), th(_callback), _terminate(false), callback(_callback)
        {
        }
        Thread(Elip::ThreadPriority priority, std::function<void(void)> _callback) : _priority(priority), th(_callback), _terminate(false), callback(_callback)
        {
        }
        Thread(const Elip::Thread &other) : _priority(other._priority), th(other.callback), _terminate(other._terminate), callback(other.callback) {}
        void operator=(Elip::Thread th)
        {
            this->callback = th.callback;
            this->th = std::move(th.th);
            this->_priority = th._priority;
        }
        // void operator=(const Elip::Thread &th)
        // {
        //     this->callback = th.callback;
        //     this->th = std::move(th.th);
        // }
        bool operator==(const Elip::Thread &other)
        {
            if (other.th.get_id() == this->th.get_id() && this->_priority == other._priority)
            {
                return true;
            }
            return false;
        }
        // miliseconds
        static void Sleep(int duration)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(duration));
        }
        static std::thread::id ID()
        {
            return std::this_thread::get_id();
        }
        static void Run(std::function<void(void)> callback)
        {
            Elip::Thread th = Elip::Thread(callback);
            th.Exec();
        }
        static void RunAndLock(std::function<void(void)> callback)
        {
            Elip::Thread th = Elip::Thread(callback);
            th.ExecAndLock();
        }

        static void Run(Elip::ThreadPriority priority, std::function<void(void)> callback)
        {
            Elip::Thread th = Elip::Thread(priority, callback);
            th.Exec();
        }
        static void RunAndLock(Elip::ThreadPriority priority, std::function<void(void)> callback)
        {
            Elip::Thread th = Elip::Thread(priority, callback);
            th.ExecAndLock();
        }

        void Exec()
        {
            this->_terminate = false;
#ifdef _WIN32
            HANDLE handl = reinterpret_cast<HANDLE>(this->th.native_handle());
            switch (this->_priority)
            {
            case Elip::ThreadPriority::NORMAL:
                if (SetThreadPriority(handl, THREAD_PRIORITY_NORMAL) != 0)
                {
                    throw Elip::ThreadExecError();
                }
                break;
            case Elip::ThreadPriority::LOW:

                if (SetThreadPriority(handl, THREAD_PRIORITY_BELOW_NORMAL) != 0)
                {
                    throw Elip::ThreadExecError();
                }
                break;
            case Elip::ThreadPriority::HIGH:

                if (SetThreadPriority(handl, THREAD_PRIORITY_ABOVE_NORMAL) != 0)
                {
                    throw Elip::ThreadExecError();
                }
                break;
            case Elip::ThreadPriority::VERY_LOW:

                if (SetThreadPriority(handl, THREAD_PRIORITY_LOWEST) != 0)
                {

                    throw Elip::ThreadExecError();
                }
                break;
            case Elip::ThreadPriority::VERY_HIGH:

                if (SetThreadPriority(handl, THREAD_PRIORITY_HIGHEST) != 0)
                {

                    throw Elip::ThreadExecError();
                }
                break;
            default:
                throw Elip::ThreadExecError();
                break;
            }
// if(!SetThreadPriority(handl,THREAD_PRI))
#else
            pthread_t handl = this->_priority;
            sched_param params;
            if (this->_priority == Elip::ThreadPriority::NORMAL)
            {
                params.sched_priority = 20;
            }
            else if (this->_priority == Elip::ThreadPriority::HIGH)
            {
                params.sched_priority = 25;
            }
            else if (this->_priority == Elip::ThreadPriority::LOW)
            {
                params.sched_priority = 7;
            }
            else if (this->_priority == Elip::ThreadPriority::VERY_HIGH)
            {
                params.sched_priority = 40;
            }
            else if (this->_priority == Elip::ThreadPriority::VERY_LOW)
            {
                params.sched_priority = 1;
            }
            else
            {
                throw Elip::ThreadExecError();
            }
            if (pthread_setschedparam(handl, SCHED_OTHER, &params) != 0)
            {
                throw Elip::ThreadExecError();
            }
#endif
            this->th.detach();
        }
        bool IsTerminate()
        {
            return this->_terminate;
        }
        void ExecAndLock()
        {
            if (!this->th.joinable())
            {
                throw Elip::ThreadExecError();
            }
            this->_terminate = false;
            this->_terminate = false;
#ifdef _WIN32
            HANDLE handl = reinterpret_cast<HANDLE>(this->th.native_handle());
            switch (this->_priority)
            {
            case Elip::ThreadPriority::NORMAL:
                if (SetThreadPriority(handl, THREAD_PRIORITY_NORMAL) != 0)
                {
                    throw Elip::ThreadExecError();
                }
                break;
            case Elip::ThreadPriority::LOW:

                if (SetThreadPriority(handl, THREAD_PRIORITY_BELOW_NORMAL) != 0)
                {
                    throw Elip::ThreadExecError();
                }
                break;
            case Elip::ThreadPriority::HIGH:

                if (SetThreadPriority(handl, THREAD_PRIORITY_ABOVE_NORMAL) != 0)
                {
                    throw Elip::ThreadExecError();
                }
                break;
            case Elip::ThreadPriority::VERY_LOW:

                if (SetThreadPriority(handl, THREAD_PRIORITY_LOWEST) != 0)
                {
                    throw Elip::ThreadExecError();
                }
                break;
            case Elip::ThreadPriority::VERY_HIGH:

                if (SetThreadPriority(handl, THREAD_PRIORITY_HIGHEST) != 0)
                {
                    throw Elip::ThreadExecError();
                }
                break;
            default:
                // throw Elip::ThreadExecError();
                break;
            }
// if(!SetThreadPriority(handl,THREAD_PRI))
#else
            pthread_t handl = this->_priority;
            sched_param params;
            if (this->_priority == Elip::ThreadPriority::NORMAL)
            {
                params.sched_priority = 20;
            }
            else if (this->_priority == Elip::ThreadPriority::HIGH)
            {
                params.sched_priority = 25;
            }
            else if (this->_priority == Elip::ThreadPriority::LOW)
            {
                params.sched_priority = 7;
            }
            else if (this->_priority == Elip::ThreadPriority::VERY_HIGH)
            {
                params.sched_priority = 40;
            }
            else if (this->_priority == Elip::ThreadPriority::VERY_LOW)
            {
                params.sched_priority = 1;
            }
            else
            {
                throw Elip::ThreadExecError();
            }
            if (pthread_setschedparam(handl, SCHED_OTHER, &params) != 0)
            {
                throw Elip::ThreadExecError();
            }
#endif
            this->th.join();
        }
        // ~Thread(){
        //     delete th; // th is not pointer :(
        // }
    };
    // class ThreadManager
    // {
    // public:
    //     Elip::Map<Elip::String, Thread> Threads;
    //     ThreadManager()
    //     {
    //     }
    //     void Add(Elip::String key, Thread values)
    //     {
    //         this->Threads.Set(key, values);
    //     }
    //     void Exec(Elip::String key)
    //     {
    //         this->Threads.Get(key).Exec();
    //     }
    //     void ExecAndLock(Elip::String key)
    //     {
    //         this->Threads.Get(key).ExecAndLock();
    //     }
    //     void ExecAll()
    //     {
    //         auto values = this->Threads.GetValues();
    //         std::cout << values.GetLength() << "\n";
    //         for (int i = 0; i < values.GetLength(); i++)
    //         {
    //             values[i].Exec();
    //         }
    //     }
    //     void ExecAndLockAll()
    //     {
    //         auto values = this->Threads.GetValues();
    //         for (int i = 0; i < values.GetLength(); i++)
    //         {
    //             values[i].ExecAndLock();
    //         }
    //     }
    //     // void Wait(std::chrono::duration<double> duration)
    //     // {
    //     //     bool terminateAll = false;
    //     //     while (!terminateAll)
    //     //     {
    //     //         auto pp = this->Threads.GetValues();

    //     //         pp.Filter([](Elip::Thread thppp, unsigned int index)
    //     //                   {
    //     //             if(thppp.IsTerminate()){
    //     //                 return false;
    //     //             }
    //     //                 return true; });
    //     //         if (pp.GetSize() != 0)
    //     //         {
    //     //             Elip::Thread::Sleep(duration);
    //     //         }
    //     //         else

    //     //         {
    //     //             terminateAll = true;
    //     //         }
    //     //     }
    //     // }
    // };
} // namespace Elip

#endif