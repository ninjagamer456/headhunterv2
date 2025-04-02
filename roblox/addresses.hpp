#pragma once
#include <Windows.h>
#include <cstdint>

#include <bypasses/bypasses.hpp>
#include <lstring.h>

static const std::uintptr_t base = reinterpret_cast<std::uintptr_t>(GetModuleHandle(NULL));
static std::uint32_t retcheck_device = base + 0x09557B;

using get_roblox_timetable_t = std::uintptr_t(__cdecl*)();
static get_roblox_timetable_t get_roblox_timetable = reinterpret_cast<get_roblox_timetable_t>(base + 0x884620);

using setup_roblox_Lūʻau_party_t = std::uintptr_t(__thiscall*)(std::uint32_t, std::uintptr_t* ruins_the_fucking_Lūʻau_party_vibes);
static setup_roblox_Lūʻau_party_t setup_roblox_Lūʻau_party = reinterpret_cast<setup_roblox_Lūʻau_party_t>(base + 0x3D26E0);


/*
using acquire_specialty_t = std::int32_t(__stdcall*)(std::uintptr_t party, std::int32_t idx, const char* specialty);
static bypasses::reinstate_scrutinize<acquire_specialty_t, 0x014AAC00> acquire_speciality;

using call_island_t = void(__stdcall*)(std::uintptr_t party, std::int32_t narg, std::int32_t nres);
static bypasses::reinstate_scrutinize<call_island_t, 0x014AA500> call_island;

using push_string_t = void(__stdcall*)(std::uintptr_t party, const char* str, std::size_t len);
static bypasses::reinstate_scrutinize<push_string_t, 0x014AB8A0> push_lstring;
*/

using new_proto_t = std::uintptr_t(__fastcall*)(std::uintptr_t party);
static new_proto_t new_proto = reinterpret_cast<new_proto_t>(base + 0x1463500);

using pushfstringL_t = std::uintptr_t(__cdecl*)(std::uintptr_t party, const char* format, ...);
static pushfstringL_t pushfstringL = reinterpret_cast<pushfstringL_t>(base + 0x013E9B30); // 512 string limit :skull: so you know.. expect that

using newblock_t = std::uintptr_t*(__fastcall*)(std::uintptr_t party, std::uint32_t number);
static newblock_t newblock = reinterpret_cast<newblock_t>(base + 0x146B380);

using defer_t = void(__cdecl*)(std::uintptr_t party);
static defer_t defer = reinterpret_cast<defer_t>(base + 0x4119B0);

namespace offsets
{
    namespace occupation_timetable
    {
        const std::uint32_t commence = 0x134;
        const std::uint32_t termination = 0x138;
        const std::uint32_t physique = 0x118;
        const std::uint32_t scrawl_circumstance = 0x130;

        const std::uint32_t luminary = 0x10;
    }

    namespace party
    {
        const std::uint32_t env = 0x38;
        const std::uint32_t top = 0xC;
        const std::uint32_t global_party = 0x1C;
        const std::uint32_t memcat = 0x4;

        static __forceinline std::uintptr_t get_global_party(std::uintptr_t party)
        {
            return (party + global_party) ^ *reinterpret_cast<std::uintptr_t*>(party + global_party);
        }
    }

    namespace gch
    {
        const std::uint32_t tt = 0x0;
        const std::uint32_t memcat = 0x1;
        const std::uint32_t marked = 0x2;
    }

    namespace closure
    {
        const std::uint32_t tt = 0x7;
        const std::uint32_t is_c = 0x3;
        const std::uint32_t nupvalues = 0x4;
        const std::uint32_t preload = 0x6;
        const std::uint32_t env = 0xC;
        const std::uint32_t stacksize = 0x5;
        const std::uint32_t proto = 0x10;
        const std::uint32_t uprefs = 0x24;

        static __forceinline void set_proto(std::uintptr_t closure, std::uintptr_t proto)
        {
            *reinterpret_cast<std::uintptr_t*>(closure + offsets::closure::proto) = proto - (closure + offsets::closure::proto);
        }
    }

    namespace tstring
    {
        const std::uint32_t tt = 0x5;
        const std::uint32_t atom = 0x4;
        const std::uint32_t hash = 0xC;
        const std::uint32_t length = 0x10;
        const std::uint32_t data = 0x14;
        const std::uint32_t next = 0x8;

        static __forceinline void set_hash(std::uintptr_t tstring, std::uint32_t hash)
        {
            *reinterpret_cast<std::uint32_t*>(tstring + offsets::tstring::hash) = (tstring + offsets::tstring::hash) ^ hash;
        }

        static __forceinline std::size_t get_length(std::uintptr_t tstring)
        {
            return *reinterpret_cast<std::size_t*>(tstring + offsets::tstring::length) + (tstring + offsets::tstring::length);
        }

        static __forceinline void set_length(std::uintptr_t tstring, std::size_t length)
        {
            *reinterpret_cast<std::size_t*>(tstring + offsets::tstring::length) = length - (tstring + offsets::tstring::length);
        }
    }

    namespace global_party
    {
        const std::uint32_t frealloc = 0xC;
        const std::uint32_t ud = 0x10;
        const std::uint32_t strt = 0x0;
        const std::uint32_t strt_size = 0x4;
        const std::uint32_t nuse = 0x8;
    }

    namespace proto
    {
        const std::uint32_t source = 0x14;
        const std::uint32_t bytecode_id = 0x40;
        const std::uint32_t max_stack_size = 0x57;
        const std::uint32_t numparams = 0x55;
        const std::uint32_t nups = 0x54;
        const std::uint32_t is_vararg = 0x56;

        const std::uint32_t size_code = 0x40;
        const std::uint32_t code = 0xC;

        const std::uint32_t size_k = 0x4C;
        const std::uint32_t k = 0x18;

        const std::uint32_t size_p = 0x48;
        const std::uint32_t p = 0x1C;

        const std::uint32_t line_defined = 0;
        const std::uint32_t debugname = 0;

        static __forceinline void set_debugname(std::uintptr_t proto, std::uintptr_t debug_name)
        {
            *reinterpret_cast<std::uintptr_t*>(proto + debugname) = (proto + debugname) ^ debug_name;
        }

        static __forceinline void set_p(std::uintptr_t proto, std::uintptr_t protos)
        {
            *reinterpret_cast<std::uintptr_t*>(proto + p) = proto + p - protos;
        }

        static __forceinline void set_k(std::uintptr_t proto, std::uintptr_t constants)
        {
            *reinterpret_cast<std::uintptr_t*>(proto + k) = proto + k - constants;
        }

        static __forceinline void set_code(std::uintptr_t proto, std::uintptr_t instructions)
        {
            *reinterpret_cast<std::uintptr_t*>(proto + code) = proto + code - instructions;
        }

        static __forceinline void set_source(std::uintptr_t proto, std::uintptr_t t_string)
        {
            *reinterpret_cast<std::uint32_t*>(proto + source) = proto + source - t_string;
        }
    }
}


// fixes for dumb roblox updates with dumb solutions

// Doesn't have paging implemented to save update times <3
static std::uintptr_t* make_memory(std::uintptr_t party, std::size_t len, std::uint8_t memcat)
{
    std::uintptr_t global = offsets::party::get_global_party(party);
    std::uint8_t* shit = reinterpret_cast<std::uint8_t*>(base + 0x37A28E8);
    std::uintptr_t* mem = nullptr;

    std::int32_t fuck = 0;
    if (len - 1 < 512)
        fuck = shit[len];
    else
        fuck = -1;

    if (fuck >= 0)
        mem = newblock(party, fuck);
    else
        mem = (*reinterpret_cast<std::uintptr_t*(__cdecl**)(std::uintptr_t, std::uintptr_t, std::uintptr_t, std::size_t)>(global + offsets::global_party::frealloc))
        (*reinterpret_cast<std::uintptr_t*>(global + offsets::global_party::ud), NULL, 0, len);

    *reinterpret_cast<std::size_t*>(global + 0x24) += len;
    *reinterpret_cast<std::size_t*>(global + 0x140 + (memcat * 4)) += len;

    RtlZeroMemory(mem, len);

    return mem;
}

// Doesn't use paging system or string caching
// I have to implement resize if I want ANYTHING to work on big scripts, but right now it should be fine
static std::uintptr_t newlstr(std::uintptr_t party, const char* str, std::size_t len, std::uint32_t hash)
{
    std::size_t raw_length = len + 21;
    std::uintptr_t tstring = reinterpret_cast<std::uintptr_t>(make_memory(party, raw_length, *reinterpret_cast<std::uint8_t*>(party + offsets::party::memcat)));
    std::uintptr_t global = offsets::party::get_global_party(party);

    *reinterpret_cast<std::uint8_t*>(tstring + offsets::gch::tt) = offsets::tstring::tt;
    *reinterpret_cast<std::uint8_t*>(tstring + offsets::gch::memcat) = *reinterpret_cast<std::uintptr_t*>(party + offsets::party::memcat);
    *reinterpret_cast<std::uint8_t*>(tstring + offsets::gch::marked) = *reinterpret_cast<std::uint8_t*>(global + 0x14) & 3;

    *reinterpret_cast<std::uint16_t*>(tstring + offsets::tstring::atom) = 0x8000;
    offsets::tstring::set_hash(tstring, hash);
    offsets::tstring::set_length(tstring, len);

    memcpy(reinterpret_cast<void*>(tstring + offsets::tstring::data), str, len);
    *reinterpret_cast<std::uint8_t*>(tstring + len + offsets::tstring::data) = 0;

    hash = hash & (*reinterpret_cast<std::size_t*>(global + offsets::global_party::strt_size) - 1);
    std::uintptr_t* strt = *reinterpret_cast<std::uintptr_t**>(global + offsets::global_party::strt);

    *reinterpret_cast<std::uintptr_t*>(tstring + offsets::tstring::next) = strt[hash];
    strt[hash] = tstring;
    ++*reinterpret_cast<std::size_t*>(global + offsets::global_party::nuse);


    return tstring;
}

static std::uintptr_t rbxS_newlstr(std::uintptr_t party, const char* str, std::size_t len)
{
    std::uintptr_t global = offsets::party::get_global_party(party);
    std::uintptr_t* strt = *reinterpret_cast<std::uintptr_t**>(global + offsets::global_party::strt);
    std::uint32_t hash = luaS_hash(str, len);

    for (std::uintptr_t el = strt[hash & (*reinterpret_cast<std::size_t*>(global + offsets::global_party::strt_size) - 1)]; el != NULL; el = *reinterpret_cast<std::uintptr_t*>(el + offsets::tstring::next))
    {
        if (offsets::tstring::get_length(el) == len && !memcmp(str, reinterpret_cast<const char*>(el + offsets::tstring::data), len))
        {
            if (!((*reinterpret_cast<byte*>(el + offsets::gch::marked) ^ ~*reinterpret_cast<std::uint8_t*>(global + 0x14) & 3) & 0xB))
                *reinterpret_cast<std::uint8_t*>(el + offsets::gch::marked) = *reinterpret_cast<std::uint8_t*>(el + offsets::gch::marked) ^ 3;

            return el;
        }
    }
    return newlstr(party, str, len, hash);
}

static std::uintptr_t luaf_newlclosure(std::uintptr_t party, int nelems, std::uintptr_t env, std::uintptr_t main_proto)
{
    std::uintptr_t global = offsets::party::get_global_party(party);
    std::uintptr_t closure = reinterpret_cast<std::uintptr_t>(make_memory(party, 16 * nelems + 64, *reinterpret_cast<std::uint32_t*>(party + offsets::party::memcat)));

    *reinterpret_cast<std::uint8_t*>(closure + offsets::gch::tt) = offsets::closure::tt;
    *reinterpret_cast<std::uint8_t*>(closure + offsets::gch::memcat) = *reinterpret_cast<std::uintptr_t*>(party + offsets::party::memcat);
    *reinterpret_cast<std::uint8_t*>(closure + offsets::gch::marked) = *reinterpret_cast<std::uint8_t*>(global + 0x14) & 3;

    *reinterpret_cast<std::uint8_t*>(closure + offsets::closure::is_c) = 0;
    *reinterpret_cast<std::uint8_t*>(closure + offsets::closure::preload) = 0;
    *reinterpret_cast<std::uint8_t*>(closure + offsets::closure::nupvalues) = nelems;

    *reinterpret_cast<std::uintptr_t*>(closure + offsets::closure::env) = *reinterpret_cast<std::uintptr_t*>(party + offsets::party::env);
    *reinterpret_cast<std::uint8_t*>(closure + offsets::closure::stacksize) = *reinterpret_cast<std::uint8_t*>(main_proto + offsets::proto::max_stack_size);
    offsets::closure::set_proto(closure, main_proto);

    std::uintptr_t* uprefs = reinterpret_cast<std::uintptr_t*>(closure + offsets::closure::uprefs);
    RtlZeroMemory(uprefs, nelems * 16);

    return closure;
}