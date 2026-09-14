#include <iostream>
#include <raylib.h>

#include <imgui.h>
#include <rlImGui.h>
#include <ImGuiThemes.h>

#include <gameMain.h>

int main(void)
{

#if PRODUCTION_BUILD == 1
	SetTraceLogLevel(LOG_NONE);
#endif

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 450, "LLGD Tutorial");
	SetExitKey(KEY_F8);
	SetTargetFPS(240);

	#pragma region imgui
	rlImGuiSetup(true);
	
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.FontGlobalScale = 2;

	setup_catppuccin_mocha_theme();
	#pragma endregion

	if (!initGame())
	{
		return 0;
	}

	while (!WindowShouldClose())
	{
		BeginDrawing();

	#pragma region imgui
		rlImGuiBegin();

		//remove docking background and allow docking in our main viewport
		ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
		ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		ImGui::PopStyleColor(2);

	#pragma endregion

		if (!updateGame())
		{
			CloseWindow();
		}

	#pragma region imgui
		rlImGuiEnd();
	#pragma endregion

		EndDrawing();
	}

	closeGame();

#pragma region imgui
	rlImGuiShutdown();

#pragma endregion


	return 0;
}