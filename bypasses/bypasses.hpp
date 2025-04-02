#pragma once
#include <Windows.h>
#include <iostream>
#include <string_view>
#include <cstdint>

extern std::uint32_t retcheck_device;

namespace bypasses
{
	void console_bypass(std::string_view title);

	template<typename deobfuscation>
	void __declspec(naked) __declspec(noinline) stub(deobfuscation...)
	{
		__asm
		{
			ret
		}
	}

	static void __declspec(naked) __declspec(noinline) get_reinstate_scrutinize(std::uintptr_t addy)
	{
		__asm
		{
			ret
		}
	}

	// IF THE CALLING CONVENTION IS A __cdecl MAKE IT __stdcall
	template<typename declaration, std::uint32_t func_addy>
	class reinstate_scrutinize
	{
	private:
		std::uint32_t resolved_address = 0;
	public:
		reinstate_scrutinize()
		{
			resolved_address = reinterpret_cast<std::uintptr_t>(GetModuleHandle(NULL)) + func_addy;
		}

		template <typename... vindication>
		__declspec(noinline) auto operator() (vindication... altercation)
		{
			static std::uintptr_t backup = 0; // no race condition, once per class
			static std::uintptr_t backup2 = 0;
			auto ret_value = 0;

			__asm
			{
				push esp
				push edi
				mov edi, finished
				pushfd
				pushad
				mov backup, esp
			}
			reinterpret_cast<declaration>(&stub<declaration>)(altercation...);
			reinterpret_cast<void(__stdcall*)(std::uintptr_t)>(get_reinstate_scrutinize)(resolved_address);
			__asm
			{
				pop eax
				push retcheck_device
				push eax
				ret
			finished:
				mov esp, backup
				mov ret_value, eax
				popad
				popfd
				pop edi
				pop esp
			}

			return ret_value;
		}
	};
}