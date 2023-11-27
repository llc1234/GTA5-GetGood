#pragma once
#include <Windows.h>
#include <vector>



uintptr_t God_Mode_base_Addr = 0x025E54E8;
std::vector<uintptr_t> God_Mode_Addr = {0x200, 0x280};

uintptr_t No_Police_base_Addr = 0x025E54E8;
std::vector<uintptr_t> No_Police_Addr = {0x628};

uintptr_t getpos_base_Addr = 0x0292A220;
std::vector<uintptr_t> getpos_Addr = {0x1A0};

uintptr_t Nightvision_base_Addr = 0x02520F18;
std::vector<uintptr_t> Nightvision_Addr = {0x0, 0x1A8, 0x208};

uintptr_t Hour_base_Addr = 0x01D63540;
std::vector<uintptr_t> Hour_Addr = {0xE0 , 0x28, 0x8C0};

uintptr_t Pistol_Ammo_base_Addr = 0x02C08E98;
std::vector<uintptr_t> Pistol_Ammo_Addr = {0x640};

uintptr_t Run_Speed_base_Addr = 0x025E54E8;
std::vector<uintptr_t> Run_Speed_Addr = {0xA90};

uintptr_t base_Addr = 0x0;
std::vector<uintptr_t> Addr = {};