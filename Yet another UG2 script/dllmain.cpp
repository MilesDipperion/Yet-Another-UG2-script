// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Windows.h>
#include "injector/injector.hpp"
#include <iostream>

int ScreenX = GetSystemMetrics(SM_CXSCREEN);	//Get screen width from desktop resolution
int ScreenY = GetSystemMetrics(SM_CYSCREEN);	//Get screen height from desktop resolution

void main()
{
	//Set screen width according to desktop resolution
	injector::WriteMemory(0x5BF62F, ScreenX, true);
	injector::WriteMemory(0x5BF646, ScreenX, true);
	injector::WriteMemory(0x5BF65D, ScreenX, true);
	injector::WriteMemory(0x5BF674, ScreenX, true);
	injector::WriteMemory(0x5BF68B, ScreenX, true);
	injector::WriteMemory(0x5BF6A2, ScreenX, true);

	//Set screen height according to desktop resolution
	injector::WriteMemory(0x5BF635, ScreenY, true);
	injector::WriteMemory(0x5BF64C, ScreenY, true);
	injector::WriteMemory(0x5BF663, ScreenY, true);
	injector::WriteMemory(0x5BF67A, ScreenY, true);
	injector::WriteMemory(0x5BF691, ScreenY, true);
	injector::WriteMemory(0x5BF6A8, ScreenY, true);

	//Windowed mode (Not included until I move the window)
	//injector::WriteMemory<unsigned char>(0x87098C, 1, true); 

	//Disable pausing by xan1242 (doesn't work the way I wanted)
	//injector::MakeJMP(0x5BF210, 0x5BF21B, true);

	//Auto-setting affinity to a single core (fixes crashes)
	HANDLE process = GetCurrentProcess();
	DWORD_PTR processAffinityMask = 1;

	BOOL success = SetProcessAffinityMask(process, processAffinityMask);
	SetPriorityClass(GetCurrentProcess(), THREAD_PRIORITY_TIME_CRITICAL);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		main();
    }
    return TRUE;
}

