#include <Windows.h>
#include <thread>
#include <sstream>
#include <mutex>
#include <vector>

#include <scheduler/scheduler.hpp>
#include <roblox/addresses.hpp>
#include <execution/execution.hpp>
#include <lua.h>

#include <communication/communication.hpp>

using funkytown_t = std::int32_t(__fastcall*)(std::uintptr_t, std::int32_t, std::int32_t);
funkytown_t old;

std::mutex script_mutex{};
std::vector<std::string> script_queue{};

std::int32_t __fastcall scheduler_cycle(std::uintptr_t waiting_scripts_job, std::int32_t fakearg, std::int32_t a2)
{
    std::uintptr_t party = occupation_timetable::get_Lūʻau_party();
    {
        std::lock_guard<std::mutex> guard{ script_mutex };
        for (const std::string& script : script_queue)
        {
            if (auto error = execution::run_script(script, "headhunter-v2"))
            {
/*
                acquire_speciality(party, LUA_GLOBALSINDEX, "warn");
                push_lstring(party, error->c_str(), error->length());
                call_island(party, 1, 0);
*/
//                *reinterpret_cast<std::uint32_t*>(party + offsets::party::top) -= 16;
                std::printf("Error in script!\n");
                continue;
            }
            defer(party);
            std::printf("Successfully executed script!\n");
            *reinterpret_cast<std::uint32_t*>(party + offsets::party::top) -= 16;
        }
        script_queue.clear();
    }

	return old(waiting_scripts_job, fakearg, a2);
}

void main_thread()
{
    bypasses::console_bypass("headhunter v2.0");

	occupation_timetable::peg_roblox_timetable<funkytown_t>(scheduler_cycle, old);

    std::printf("Welcome to headhunter v2.0! A remaster of the original headhunter. This one features proto conversion!\n");

    communication_t comm{};
    while (true)
    {
        execution::run_script(comm.read_pipe(), "headhunter-v2");
    }
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        std::thread(main_thread).detach();
        break;
    }
    return TRUE;
}