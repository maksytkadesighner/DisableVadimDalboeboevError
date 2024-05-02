#include <Windows.h>

void WriteMemory(unsigned adr, unsigned value, int bytes)
{
    LPVOID address = (LPVOID)(adr);

    DWORD oldProtect;
    VirtualProtect(address, 5, PAGE_EXECUTE_READWRITE, &oldProtect);

    memset(address, value, bytes);

    VirtualProtect(address, 5, oldProtect, &oldProtect);
}

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,
    DWORD fdwReason,
    LPVOID lpvReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        uintptr_t vadim = reinterpret_cast<uintptr_t>(GetModuleHandleA("d3d9.asi"));
        WriteMemory(vadim + 0x98F0, 0x90, 5);
    }
}