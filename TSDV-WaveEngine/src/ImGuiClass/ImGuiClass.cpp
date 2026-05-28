#include "ImGuiClass.h"

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <ImGui/imgui_impl_glfw.h>

#include "ServiceProvider/ServiceProvider.h"
#include <string>
#include <Renderer/Renderer.h>

namespace WaveEngine
{
	bool ImGuiClass::thirdPersonCamera = false;

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

		ImGui::Separator();

		ImGui::Checkbox("Third Person Camera: ", &thirdPersonCamera);

		ImGui::Separator();

		ImGui::DragFloat3("DirLight Dir", &Renderer::dirLight.direction.x);
		ImGui::DragFloat3("DirLight Ambient", &Renderer::dirLight.ambient.x);
		ImGui::DragFloat3("DirLight Diffuse", &Renderer::dirLight.diffuse.x);
		ImGui::DragFloat3("DirLight Specular", &Renderer::dirLight.specular.x);

		ImGui::Separator();

		for (int i = 0; i < Renderer::Amount_Per_Light; ++i)
		{
			string name = "FlashLight " + to_string(i) + ": ";

			ImGui::DragFloat3("Flash Pos", &Renderer::flashLights[i].position.x);
			ImGui::DragFloat3("Flash Dir", &Renderer::flashLights[i].direction.x);
			ImGui::DragFloat3("Flash Ambient", &Renderer::flashLights[i].ambient.x);
			ImGui::DragFloat3("Flash Diffuse", &Renderer::flashLights[i].diffuse.x);
			ImGui::DragFloat3("Flash Specular", &Renderer::flashLights[i].specular.x);
			ImGui::DragFloat("Flash const", &Renderer::flashLights[i].constant);
			ImGui::DragFloat("Flash linear", &Renderer::flashLights[i].linear);
			ImGui::DragFloat("Flash Quad", &Renderer::flashLights[i].quadratic);
			ImGui::DragFloat("Flash CutOff", &Renderer::flashLights[i].cutOff);
			ImGui::DragFloat("Flash OutterCutOff", &Renderer::flashLights[i].outerCutOff);
		}

		for (int i = 0; i < Renderer::Amount_Per_Light; ++i)
		{
			string name = "PointLight " + to_string(i) + ": ";

			ImGui::DragFloat3((name + " Pos").c_str(), &Renderer::pointLight[i].position.x);
			ImGui::DragFloat3((name + " Ambient").c_str(), &Renderer::pointLight[i].ambient.x);
			ImGui::DragFloat3((name + " Diffuse").c_str(), &Renderer::pointLight[i].diffuse.x);
			ImGui::DragFloat3((name + " Specular").c_str(), &Renderer::pointLight[i].specular.x);

			ImGui::DragFloat((name + " const").c_str(), &Renderer::pointLight[i].constant);
			ImGui::DragFloat((name + " linear").c_str(), &Renderer::pointLight[i].linear);
			ImGui::DragFloat((name + " Quad").c_str(), &Renderer::pointLight[i].quadratic);

			if (i < 3)
				ImGui::Separator();

		}

		ImGui::End();
	}

	void ImGuiClass::Draw()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}