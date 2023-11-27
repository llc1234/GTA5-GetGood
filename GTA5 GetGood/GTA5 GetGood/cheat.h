#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
#include <TlHelp32.h>

#include "offsets.h"


bool God_Mode = false;

bool never_wanted = false;

bool set_Wanted_level = false;
float Wanted_level = 0;

bool set_Hour = false;
float Hour = 0;

bool set_run_speed = false;
float run_speed = 1;


HWND hwnd;
DWORD pid;
HANDLE handle;
uintptr_t GTA5_exe;

uintptr_t GetModuleBaseAddress(const char* modName) {
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
	if (hSnap != INVALID_HANDLE_VALUE) {
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry)) {
			do {
				if (!strcmp(modEntry.szModule, modName)) {
					CloseHandle(hSnap);
					return (uintptr_t)modEntry.modBaseAddr;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
}

void cheat_setup() {
	hwnd = FindWindowA(0, "Grand Theft Auto V");
	GetWindowThreadProcessId(hwnd, &pid);
	handle = OpenProcess(PROCESS_ALL_ACCESS, NULL, pid);

	std::cout << "hwnd: " << hwnd << std::endl;
	std::cout << "pid: " << pid << std::endl;
	std::cout << "handle: " << handle << std::endl;

	GTA5_exe = GetModuleBaseAddress("GTA5.exe");

	std::cout << "GTA5: " << GTA5_exe << std::endl;
}

uintptr_t Readlonglong(uintptr_t addr) {
	uintptr_t value;
	ReadProcessMemory(handle, (LPVOID)addr, &value, sizeof(value), 0);
	return value;
}

float ReadFloat(uintptr_t addr) {
	float value;
	ReadProcessMemory(handle, (LPVOID)addr, &value, sizeof(value), 0);
	return value;
}

void WriteFloat(uintptr_t addr, float value) {
	WriteProcessMemory(handle, (LPVOID)addr, &value, sizeof(value), 0);
}

int ReadInt(uintptr_t addr) {
	int value;
	ReadProcessMemory(handle, (LPVOID)addr, &value, sizeof(value), 0);
	return value;
}

void WriteInt(uintptr_t addr, int value) {
	WriteProcessMemory(handle, (LPVOID)addr, &value, sizeof(value), 0);
}

uintptr_t GetPointerAddr(uintptr_t addr, std::vector<uintptr_t> offsets) {
	uintptr_t t = Readlonglong(addr);

	for (int i = 0; i < offsets.size()-1; i++) {
		t = Readlonglong(t+offsets.at(i));
	}

	return t + offsets.at(offsets.size()-1);
}

void God_Mode_func() {
	uintptr_t addr = GetPointerAddr(GTA5_exe + God_Mode_base_Addr, God_Mode_Addr);
	WriteFloat(addr, 200.0);
}

void never_wanted_func(int level) {
	uintptr_t addr = GetPointerAddr(GTA5_exe + No_Police_base_Addr, No_Police_Addr);
	WriteInt(addr, level);
}

void set_hour_func(int h) {
	uintptr_t addr = GetPointerAddr(GTA5_exe + Hour_base_Addr, Hour_Addr);
	WriteInt(addr, h);
}

void run_speed_func() {
	uintptr_t addr = GetPointerAddr(GTA5_exe + Run_Speed_base_Addr, Run_Speed_Addr);
	WriteFloat(addr, run_speed);
}

void cheat_loop_1() {
	Sleep(2000);

	while (true) {
		if (God_Mode) {
			God_Mode_func();
		}

		if (never_wanted) {
			never_wanted_func(0);
		}

		if (set_Wanted_level) {
			never_wanted_func((int) Wanted_level);
		}

		if (set_Hour) {
			set_hour_func((int) Hour);
		}

		if (set_run_speed) {
			run_speed_func();
		}
	}
}