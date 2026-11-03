#pragma once

#include <vector>
#include <string>
#include <GL/glew.h>
#include <glm/fwd.hpp>
#include <unordered_map>

#include "Export.h"
#include "Color/Color.h"
#include "ECS/WObject/WObject.h"
#include "MaterialBehaviourConcept.h"
#include "WaveMath/Vector4/Vector4.h"
#include "WaveMath/Vector2/Vector2.h"
#include "WaveMath/Vector3/Vector3.h"
#include "WaveMath/Matrix4x4/Matrix4x4.h"

namespace WaveEngine
{
	class EntitiesImGui;
	class MaterialsImGui;
	class MaterialManager;
	class MaterialFactory;
	class WaveMaterialBehaviour;

	using namespace std;

	struct Uniform
	{
		string name;
		GLenum type;
		GLint location;
		GLint size;
	};

	class WAVEEXPORT Material final : public WObject
	{
	private:

		string name;

		Color color = Color::White();

		unsigned int gpuID = 0;

		float metalic = 0.0f;
		float roughness = 1.0f;

		vector<Uniform*> samplerUniforms;
		unordered_map<string, Uniform> uniforms;

		unordered_map<string, unsigned int> textures;

		Material();
		~Material();

		void SetName(const string& name);
		void AddUniform(const std::string& name, const GLenum& type, const GLint& location, const GLint& size);

		friend class EntitiesImGui;
		friend class MaterialsImGui;
		friend class MaterialManager;
		friend class MaterialFactory;

	public:

		static Material* Create(const char* name, const char* vertexShader, const char* fragmentShader);
		static Material* Load(const char* name, const char* vertexShader, const char* fragmentShader);

		WaveMaterialBehaviour* GetBehaviour() const;
		bool TryGetBehaviour(WaveMaterialBehaviour*& waveMaterialBehaviour) const;

		const string& GetName() const;

		unsigned int GetGPUID() const;
		Color GetColor() const;
		float GetMetallic() const;
		float GetRoughness() const;

		void SetTexture(const std::string& uniformName, unsigned int textureGPUID);
		void AddAlbedoTexture(const unsigned int& textureGPUID);
		void AddNormalMap(const unsigned int& textureGPUID);
		void SetColor(Color color);
		void SetMetallic(float metallic);
		void SetRoughness(float roughtness);

		void SetVec2(const std::string& name, Vector2 value);
		void SetVec2(const std::string& name, float x, float y);
		void SetVec3(const std::string& name, Vector3 value);
		void SetVec3(const std::string& name, float x, float y, float z);
		void SetVec4(const std::string& name, const Vector4& value);
		void SetVec4(const std::string& name, Color value);
		void SetVec4(const std::string& name, float x, float y, float z, float w);
		void SetMat4(const std::string& name, const Matrix4x4& value);
		void SetMat4(const std::string& name, const glm::mat4& value);
		void SetGLMVec4(const std::string& name, const glm::vec4& value);
		void SetGLMVec3(const std::string& name, const glm::vec3& value);
		void SetGLMVec2(const std::string& name, const glm::vec2& value);
		void SetFloat(const std::string& name, float value);
		void SetInt(const std::string& name, const int& value);
		void SetBool(const std::string& name, const bool& value);

		template<MaterialBehaviourConcept T>
		void SetBehaviour();

		void Bind();
		void UnBind();
	};
}

#include "Material.tpp"