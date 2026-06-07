#include "ImGuiClass.h"

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <ImGui/imgui_impl_glfw.h>

#include "ServiceProvider/ServiceProvider.h"
#include <string>
#include <Renderer/Renderer.h>
#include <ECS/WaveObject/WaveObjectRegistry.h>

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

	WaveObjectRegistry* ImGuiClass::GetWaveObjectRegistry()
	{
		return ServiceProvider::Instance().Get<WaveObjectRegistry>();
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
			text = "FlashLight " + to_string(i) + ": ";

			ImGui::DragFloat3((text + " Pos").c_str(), &Renderer::flashLights[i].position.x);
			ImGui::DragFloat3((text + " Dir").c_str(), &Renderer::flashLights[i].direction.x);
			ImGui::DragFloat3((text + " Ambient").c_str(), &Renderer::flashLights[i].ambient.x);
			ImGui::DragFloat3((text + " Diffuse").c_str(), &Renderer::flashLights[i].diffuse.x);
			ImGui::DragFloat3((text + " Specular").c_str(), &Renderer::flashLights[i].specular.x);
			ImGui::DragFloat((text + " const").c_str(), &Renderer::flashLights[i].constant);
			ImGui::DragFloat((text + " linear").c_str(), &Renderer::flashLights[i].linear);
			ImGui::DragFloat((text + " Quad").c_str(), &Renderer::flashLights[i].quadratic);
			ImGui::DragFloat((text + " CutOff").c_str(), &Renderer::flashLights[i].cutOff);
			ImGui::DragFloat((text + " OutterCutOff").c_str(), &Renderer::flashLights[i].outerCutOff);
			ImGui::Separator();
			ImGui::Separator();
		}

		for (int i = 0; i < Renderer::Amount_Per_Light; ++i)
		{
			text = "PointLight " + to_string(i) + ": ";

			ImGui::DragFloat3((text + " Pos").c_str(), &Renderer::pointLight[i].position.x);
			ImGui::DragFloat3((text + " Ambient").c_str(), &Renderer::pointLight[i].ambient.x);
			ImGui::DragFloat3((text + " Diffuse").c_str(), &Renderer::pointLight[i].diffuse.x);
			ImGui::DragFloat3((text + " Specular").c_str(), &Renderer::pointLight[i].specular.x);

			ImGui::DragFloat((text + " const").c_str(), &Renderer::pointLight[i].constant);
			ImGui::DragFloat((text + " linear").c_str(), &Renderer::pointLight[i].linear);
			ImGui::DragFloat((text + " Quad").c_str(), &Renderer::pointLight[i].quadratic);

			ImGui::Separator();
			ImGui::Separator();
		}

		map<unsigned int, WaveObject*> waveObjects = GetWaveObjectRegistry()->GetWaveObjects();

		for (map<unsigned int, WaveObject*>::iterator it = waveObjects.begin(); it != waveObjects.end(); ++it)
		{
			ImGui::Text(it->second->GetName().c_str());

			if (ImGui::DragFloat3((text + " Pos").c_str(), &newPos.x))
				it->second->GetTransform().SetPosition(newPos);

			if (ImGui::DragFloat3((text + " Rot").c_str(), &newRot.x))
				it->second->GetTransform().SetRotation(newRot);

			if (ImGui::DragFloat3((text + " Scale").c_str(), &newScale.x))
				it->second->GetTransform().SetRotation(newScale);

			ImGui::Separator();
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