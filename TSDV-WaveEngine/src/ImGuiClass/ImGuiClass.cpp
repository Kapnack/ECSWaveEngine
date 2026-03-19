#include "ImGuiClass.h"

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <ImGui/imgui_impl_glfw.h>

#include "ServiceProvider/ServiceProvider.h"
#include <string>
#include <Renderer/Renderer.h>

namespace WaveEngine
{
	ImGuiClass::ImGuiClass()
	{
		Init();
	}

	ImGuiClass::~ImGuiClass()
	{
		Unload();
	}

	Window* ImGuiClass::GetWindow()
	{
		return ServiceProvider::Instance().Get<Window>();
	}

	Input* ImGuiClass::GetInput()
	{
		return ServiceProvider::Instance().Get<Input>();
	}

	void ImGuiClass::Init()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		ImGui_ImplGlfw_InitForOpenGL(GetWindow()->GetGLFWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 330");
		ImGui::StyleColorsDark();
	}

	void ImGuiClass::Unload()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiClass::Update()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("WaveEngine Debug Window");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		string text = "Batch Calls: " + to_string(ServiceProvider::Instance().Get<Renderer>()->GetBatchCalls()) + ".";
		ImGui::Text(text.c_str());
		text = "Draw Calls: " + to_string(ServiceProvider::Instance().Get<Renderer>()->GetDrawCalls()) + ".";
		ImGui::Text(text.c_str());

		ImGui::End();
	}

	void ImGuiClass::Draw()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}