#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


int Cursor_y = 7;
int tab_to_all = 0;
int Cursor_tab_counter = 0;

int pos_x = 10;
int pos_y = 25;

int window_size[] = {270, 350};

bool press_up = false;
bool press_down = false;
bool press_left = false;
bool press_right = false;


void Gui_setup() {

}


void KeyEvent() {
	if (!press_up && GetKeyState('I') & 0x8000) {
		press_up = true;
		Cursor_y -= 23;
		Cursor_tab_counter--;

		if (Cursor_y <= 7) {
			Cursor_y = 7;
			Cursor_tab_counter = 0;
		}
	}

	if (!(GetKeyState('I') & 0x8000)) {
		press_up = false;
	}

	if (!press_down && GetKeyState('K') & 0x8000) {
		press_down = true;
		Cursor_y += 23;
		Cursor_tab_counter++;
	}

	if (!(GetKeyState('K') & 0x8000)) {
		press_down = false;
	}

	if (!press_left && GetKeyState('J') & 0x8000) {
		press_left = true;
	}

	if (!(GetKeyState('J') & 0x8000)) {
		press_left = false;
	}

	if (!press_right && GetKeyState('L') & 0x8000) {
		press_right = true;
	}

	if (!(GetKeyState('L') & 0x8000)) {
		press_right = false;
	}
}


void DrawMenu() {
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(window_size[0], window_size[1]));
	ImGui::Begin("GTA5 GetGood", 0, ImGuiWindowFlags_NoResize);
}


void DrawMenuCursor() {
	ImGui::SetCursorPos(ImVec2(0, 25));
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	ImVec2 p = ImGui::GetCursorScreenPos();
	draw_list->AddLine(ImVec2(p.x-5, p.y+Cursor_y), ImVec2(p.x+300.0f, p.y+Cursor_y), IM_COL32(150, 0, 0, 255), 20.0f);
}


void DrawButtonRect(int px, int py, bool t) {
	ImGui::SetCursorPos(ImVec2(0, 25));
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	ImVec2 p = ImGui::GetCursorScreenPos();

	p.x += px;
	p.y += py-23;

	if (t) {
		draw_list->AddRectFilled(ImVec2(p.x, p.y), ImVec2(p.x+10, p.y+10), IM_COL32(255, 255, 255, 255), 3.0f);
	} else {
		draw_list->AddRect(ImVec2(p.x, p.y), ImVec2(p.x+10, p.y+10), IM_COL32(255, 255, 255, 255), 10.0f);
	}
}


void DrawButtonTrangle(int px, int py) {
	ImGui::SetCursorPos(ImVec2(0, 25));
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	ImVec2 p = ImGui::GetCursorScreenPos();

	p.x += px;
	p.y += py-23;

	draw_list->AddLine(ImVec2(p.x, p.y), ImVec2(p.x+6, p.y+6), IM_COL32(255, 255, 255, 255), 1.0f);
	draw_list->AddLine(ImVec2(p.x+6, p.y+5), ImVec2(p.x, p.y+11), IM_COL32(255, 255, 255, 255), 1.0f);
}


void DrawButtonTrangleBack(int px, int py) {
	ImGui::SetCursorPos(ImVec2(0, 25));
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	ImVec2 p = ImGui::GetCursorScreenPos();

	p.x += px;
	p.y += py-23;

	draw_list->AddLine(ImVec2(p.x, p.y), ImVec2(p.x-6, p.y+6), IM_COL32(255, 255, 255, 255), 1.0f);
	draw_list->AddLine(ImVec2(p.x-6, p.y+6), ImVec2(p.x, p.y+12), IM_COL32(255, 255, 255, 255), 1.0f);
}


float Gui_Slider_Float(const char* text, float value, int dis, float in) {
	std::string s = std::to_string((int) value);

	ImGui::SetCursorPos(ImVec2(pos_x, pos_y));

	ImGui::Text(text);

	ImGui::SetCursorPos(ImVec2(pos_x+dis, pos_y));
	ImGui::Text(s.c_str());

	pos_y += 23;

	if (press_right) {
		if (tab_to_all == Cursor_tab_counter) {
			value += in;
		}
	}

	if (press_left) {
		if (tab_to_all == Cursor_tab_counter) {
			value -= in;
		}
	}

	tab_to_all += 1;

	return value;
}


bool Gui_Checkbox(const char* text, bool check_t) {
	ImGui::SetCursorPos(ImVec2(pos_x, pos_y));
	ImGui::Text(text);

	DrawButtonRect(pos_x+window_size[0]-33, pos_y, check_t);
	
	pos_y += 23;
	
	bool r = check_t;

	if (press_right) {
		if (tab_to_all == Cursor_tab_counter) {
			r = true;
		}
	}

	if (press_left) {
		if (tab_to_all == Cursor_tab_counter) {
			r = false;
		}
	}

	tab_to_all += 1;

	return r;
}


bool Gui_Button(const char* text) {
	ImGui::SetCursorPos(ImVec2(pos_x, pos_y));
	ImGui::Text(text);

	DrawButtonTrangle(pos_x+window_size[0]-30, pos_y);

	pos_y += 23;

	bool r = false;

	if (press_right) {
		if (tab_to_all == Cursor_tab_counter) {
			r = true;
		}
	}

	tab_to_all += 1;

	return r;
}


bool Gui_back_Button(const char* text) {
	ImGui::SetCursorPos(ImVec2(pos_x, pos_y));
	ImGui::Text(text);

	DrawButtonTrangleBack(pos_x+window_size[0]-25, pos_y);

	pos_y += 23;

	bool r = false;

	if (press_left) {
		if (tab_to_all == Cursor_tab_counter) {
			r = true;
		}
	}

	tab_to_all += 1;

	return r;
}


void restart_cursor_pos() {
	Cursor_tab_counter = 0;
	Cursor_y = 7;
}


void Endmenu() {
	tab_to_all = 0;
	pos_y = 25;
	ImGui::End();
}


void Gui_start() {
	KeyEvent();
	DrawMenu();
	DrawMenuCursor();
}


void Gui_end() {
	Endmenu();
}