#pragma once

#include <unordered_map>
#include <string>
#include <GL/glew.h>

#include "WaveMath/Vector4/Vector4.h"
#include "WaveMath/Vector2/Vector2.h"
#include "WaveMath/Vector3/Vector3.h"
#include <glm/fwd.hpp>
#include "Color/Color.h"

namespace WaveEngine
{
	class MaterialManager;
	class MaterialFactory;
	class EntitiesImGui;
	class MaterialsImGui;

	using namespace std;

	struct Uniform
	{
		string name;
		GLenum type;
		GLint location;
		GLint size;
	};

	class Material final
	{
	private:

		string name;

		Color color = Color::White();

		unsigned int ID = 0;

		unsigned int gpuID = 0;

		float metalic = 0.0f;
		float roughness = 1.0f;

		vector<Uniform*> samplerUniforms;
		unordered_map<string, Uniform> uniforms;

		unordered_map<string, unsigned int> textures;

		Material(const unsigned int& ID);
		~Material();

		void SetName(const string& name);
		void AddUniform(const std::string& name, const GLenum& type, const GLint& location, const GLint& size);
		void Unload();

		friend class MaterialManager;
		friend class MaterialFactory;
		friend class EntitiesImGui;
		friend class MaterialsImGui;

	public:

		const static unsigned int NULL_MATERIAL;

		const string& GetName() const;

		const unsigned int& GetID() const;
		const unsigned int& GetGPUID() const;
		const Color& GetColor() const;
		const float& GetMetallic() const;
		const float& GetRoughness() const;

		void SetTexture(const std::string& uniformName, unsigned int textureGPUID);
		void AddAlbedoTexture(const unsigned int& textureGPUID);
		void AddNormalMap(const unsigned int& textureGPUID);
		void SetColor(const Color& color);
		void SetMetallic(const float& metallic);
		void SetRoughness(const float& roughtness);

		void SetVec2(const std::string& name, const Vector2& value);
		void SetVec2(const std::string& name, const float& x, const float& y);
		void SetVec3(const std::string& name, const Vector3& value);
		void SetVec3(const std::string& name, const float& x, const float& y, const float& z);
		void SetVec4(const std::string& name, const Vector4& value);
		void SetVec4(const std::string& name, const Color& value);
		void SetVec4(const std::string& name, const float& x, const float& y, const float& z, const float& w);
		void SetMat4(const std::string& name, const glm::mat4& value);
		void SetGLMVec4(const std::string& name, const glm::vec4& value);
		void SetGLMVec3(const std::string& name, const glm::vec3& value);
		void SetGLMVec2(const std::string& name, const glm::vec2& value);
		void SetFloat(const std::string& name, const float& value);
		void SetInt(const std::string& name, const int& value);
		void SetBool(const std::string& name, const bool& value);

		void Bind();
		void UnBind();
	};
}

