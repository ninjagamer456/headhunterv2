#include <bypasses/bypasses.hpp>

namespace bypasses
{
	void console_bypass(std::string_view title)
	{
		DWORD backup = 0;
		FILE* f_ptr[3] = { 0 };

		VirtualProtect(&FreeConsole, 1, PAGE_EXECUTE_READWRITE, &backup);
		*reinterpret_cast<byte*>(&FreeConsole) = 0xC3;
		VirtualProtect(&FreeConsole, 1, backup, &backup);

		AllocConsole();

		freopen_s(&f_ptr[0], "CONOUT$", "w", stdout);
		freopen_s(&f_ptr[1], "CONIN$", "r", stdin);
		freopen_s(&f_ptr[2], "CONOUT$", "w", stderr);
	
		SetConsoleTitleA(title.data());
	}
}