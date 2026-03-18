#pragma once

#include <iostream>
#include <unordered_map>
#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "TextureImporter/Texture.h"
#include "WaveMath/Vector4/Vector4.h"
#include "WaveMath/Vector2/Vector2.h"
#include "WaveMath/Vector3/Vector3.h"

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

		Vector4 color = Vector4(1, 1, 1, 1);

		unsigned int ID = 0;

		unsigned int program = 0;

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

		const string GetName() const;

		Vector4 GetColor() const;
		unsigned int GetID() const;
		unsigned int GetProgram() const;
		void SetTexture(const std::string& uniformName, unsigned int textureID);
		void SetColor(const Vector4& color);

		void SetVec2(const std::string& name, const Vector2& value);
		void SetVec3(const std::string& name, const Vector3& value);
		void SetVec4(const std::string& name, const Vector4& value);
		void SetMat4(const std::string& name, const glm::mat4& value);
		void SetGLMVec4(const std::string& name, const glm::vec4& value);
		void SetGLMVec3(const std::string& name, const glm::vec3& value);
		void SetGLMVec2(const std::string& name, const glm::vec2& value);
		void SetFloat(const std::string& name, const float& value);
		void SetInt(const std::string& name, const int& value);

		void Bind();
		void UnBind();
	};
}

