#include <iostream>
#include <raylib.h>

#include <imgui.h>
#include <rlImGui.h>
#include <ImGuiThemes.h>


int main()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 450, "LLGD Tutorial");

	#pragma region imgui
	rlImGuiSetup(true);
	
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.FontGlobalScale = 2;

	setup_catppuccin_mocha_theme();
	#pragma endregion

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(DARKGRAY);
	#pragma region imgui
		rlImGuiBegin();

		//remove docking background and allow docking in our main viewport
		ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
		ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		ImGui::PopStyleColor(2);

	#pragma endregion

		DrawRectangle(75, 75, 100, 100, {0, 255, 0, 127});
		DrawRectangle(50, 50, 100, 100, {255, 0, 0, 127});

	#pragma region imgui widgets
		ImGui::Begin("test");

		ImGui::Text("hello");
		ImGui::Button("button");
		int t = 0;
		ImGui::TreeNode("test");

		ImGui::End();
	#pragma endregion

	#pragma region imgui
		rlImGuiEnd();
	#pragma endregion

		EndDrawing();
	}

#pragma region imgui
	rlImGuiShutdown();

#pragma endregion

	CloseWindow();

	return 0;
}