#pragma once
#include <iostream>
#include <Windows.h>
#include <thread>
#include <string>

#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Gui.h"
#include "cheat.h"


int tab = 0;
float window_pos[] = {100, 100};

void menu_setup(GLFWwindow* window) {
	ImGuiStyle& style = ImGui::GetStyle();
	// style.WindowRounding = 5.3f;
	// style.FrameRounding = 2.3f;
	style.ScrollbarRounding = 0;

	style.Colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 0.90f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	// style.Colors[ImGuiCol_WindowBg] = ImVec4(0.09f, 0.09f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.85f);
	// style.Colors[ImGuiCol_Border] = ImVec4(0.70f, 0.70f, 0.70f, 0.65f);
	// style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	// style.Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.01f, 1.00f);
	// style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.90f, 0.80f, 0.80f, 0.40f);
	// style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.90f, 0.65f, 0.65f, 0.45f);
	// style.Colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.83f);
	// style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.40f, 0.40f, 0.80f, 0.20f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.70f, 0.00f, 0.00f, 0.9f);
	// style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.01f, 0.01f, 0.02f, 0.80f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);

	std::thread(cheat_setup).detach();
	std::thread(cheat_loop_1).detach();

	Gui_setup();
}

void draw_tab1_Self() {
	if (Gui_back_Button("Back")) {
		tab = 0;
	}

	God_Mode = Gui_Checkbox("God Mode", God_Mode);
	never_wanted = Gui_Checkbox("Never Wanted", never_wanted);
	set_Wanted_level = Gui_Checkbox("Set Wanted Level", set_Wanted_level);
	Wanted_level = Gui_Slider_Float("Wanted level", Wanted_level, 238, 0.1);

	if (Wanted_level > 5) {
		Wanted_level = 5;
	} else if (Wanted_level < 0) {
		Wanted_level = 0;
	}

	set_run_speed = Gui_Checkbox("Set Speed", set_run_speed);
	run_speed = Gui_Slider_Float("Run Speed", run_speed, 238, 0.1);

	if (run_speed < 1) {
		run_speed = 1;
	} else if (run_speed > 10) {
		run_speed = 10;
	}
}

void draw_tab2_World() {
	if (Gui_back_Button("Back")) {
		tab = 0;
	}
	
	set_Hour = Gui_Checkbox("Set Hour", set_Hour);
	Hour = Gui_Slider_Float("Hour", Hour, 238, 0.1);

	if (Hour < 0) {
		Hour = 23;
	} else if (Hour > 23) {
		Hour = 0;
	}
}

void draw_tab3_Weapon() {
	if (Gui_back_Button("Back")) {
		tab = 0;
	}
}

void draw_tab4_Vehicle() {
	if (Gui_back_Button("Back")) {
		tab = 0;
	}
}

void draw_tab5_Teleport() {
	if (Gui_back_Button("Back")) {
		tab = 0;
	}
}

void draw_tab6_Misc() {
	if (Gui_back_Button("Back")) {
		tab = 0;
	}
}

void draw_tab7_Settings(GLFWwindow* window) {
	if (Gui_back_Button("Back")) {
		tab = 0;
	}

	window_pos[0] = Gui_Slider_Float("pos: x", window_pos[0], 220, 4);
	window_pos[1] = Gui_Slider_Float("pos: y", window_pos[1], 220, 4);

	glfwSetWindowPos(window, (int) window_pos[0], (int) window_pos[1]);
}

void draw_tab0() {
	if (Gui_Button("Self")) {
		tab = 1;
		restart_cursor_pos();
	}

	if (Gui_Button("World")) {
		tab = 2;
		restart_cursor_pos();
	}

	if (Gui_Button("Weapon")) {
		tab = 3;
		restart_cursor_pos();
	}
	
	if (Gui_Button("Vehicle")) {
		tab = 4;
		restart_cursor_pos();
	}
	
	if (Gui_Button("Teleport")) {
		tab = 5;
		restart_cursor_pos();
	}
	
	if (Gui_Button("Misc")) {
		tab = 6;
		restart_cursor_pos();
	}
	
	if (Gui_Button("Settings")) {
		tab = 7;
		restart_cursor_pos();
	}

	if (Gui_Button("Exit")) {
		exit(0);
	}
}


void menu_loop(GLFWwindow* window) {
	Gui_start();

	if (tab == 0) {
		draw_tab0();
	} else if (tab == 1) {
		draw_tab1_Self();
	} else if (tab == 2) {
		draw_tab2_World();
	} else if (tab == 3) {
		draw_tab3_Weapon();
	} else if (tab == 4) {
		draw_tab4_Vehicle();
	} else if (tab == 5) {
		draw_tab5_Teleport();
	} else if (tab == 6) {
		draw_tab6_Misc();
	} else if (tab == 7) {
		draw_tab7_Settings(window);
	}

	Gui_end();
}