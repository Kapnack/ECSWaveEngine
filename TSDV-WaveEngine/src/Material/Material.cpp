#include "Material.h"

#include <GL/glew.h>

#define GLM_FORCE_ALIGNED_GENTYPES
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Color/Color.h"

using namespace std;

namespace WaveEngine
{
	const unsigned int Material::NULL_MATERIAL = 0;

	Material::Material(const unsigned int& ID)
	{
		this->ID = ID;
	}

	Material::~Material()
	{
		Unload();
	}

	const string& Material::GetName() const
	{
		return name;
	}

	const Color& Material::GetColor() const
	{
		return color;
	}

	const unsigned int& Material::GetID() const
	{
		return ID;
	}

	const unsigned int& Material::GetGPUID() const
	{
		return gpuID;
	}

	void Material::SetTexture(const std::string& uniformName, unsigned int textureID)
	{
		textures[uniformName] = textureID;
	}

	void Material::AddAlbedoTexture(const unsigned int& textureGPUID)
	{
		const string albedoParamName = "uAlbedo";

		SetTexture(albedoParamName, textureGPUID);
	}

	void Material::AddNormalMap(const unsigned int& textureGPUID)
	{
		const string albedoParamName = "uNormal";

		SetTexture(albedoParamName, textureGPUID);
	}

	void Material::SetName(const string& name)
	{
		this->name = name;
	}

	void Material::AddUniform(const std::string& name, const GLenum& type, const GLint& location, const GLint& size)
	{
		if (location == -1)
			return;

		uniforms[name] = { name, type, location, size };

		if (type == GL_SAMPLER_2D)
			samplerUniforms.push_back(&uniforms[name]);
	}

	void Material::SetColor(const Color& color)
	{
		this->color = color;
	}

	void Material::SetVec2(const std::string& name, const Vector2& value)
	{
		SetVec2(name, value.x, value.y);
	}

	void Material::SetVec2(const std::string& name, const float& x, const float& y)
	{
		SetGLMVec2(name, glm::vec2(x, y));
	}

	void Material::SetVec3(const std::string& name, const Vector3& value)
	{
		SetGLMVec3(name, glm::vec3(value.x, value.y, value.z));
	}

	void Material::SetVec3(const std::string& name, const float& x, const float& y, const float& z)
	{
		SetGLMVec3(name, glm::vec3(x, y, z));
	}

	void Material::SetVec4(const std::string& name, const Vector4& value)
	{
		SetGLMVec4(name, glm::vec4(value.x, value.y, value.z, value.w));
	}

	void Material::SetVec4(const std::string& name, const Color& value)
	{
		SetGLMVec4(name, glm::vec4(value.r, value.g, value.b, value.a));
	}

	void Material::SetVec4(const std::string& name, const float& x, const float& y, const float& z, const float& w)
	{
		SetGLMVec4(name, glm::vec4(x, y, z, w));
	}

	void Material::SetMat4(const std::string& name, const glm::mat4& value)
	{
		unordered_map<string, Uniform>::iterator it = uniforms.find(name);
		if (it == uniforms.end())
			return;

		glUniformMatrix4fv(it->second.location, it->second.size, GL_FALSE, glm::value_ptr(value));
	}

	void Material::SetGLMVec4(const std::string& name, const glm::vec4& value)
	{
		unordered_map<string, Uniform>::iterator it = uniforms.find(name);
		if (it == uniforms.end())
			return;

		glUniform4f(it->second.location, value.x, value.y, value.z, value.w);
	}

	void Material::SetGLMVec3(const std::string& name, const glm::vec3& value)
	{
		unordered_map<string, Uniform>::iterator it = uniforms.find(name);
		if (it == uniforms.end())
			return;

		glUniform3fv(it->second.location, it->second.size, glm::value_ptr(value));
	}

	void Material::SetGLMVec2(const std::string& name, const glm::vec2& value)
	{
		unordered_map<string, Uniform>::iterator it = uniforms.find(name);
		if (it == uniforms.end())
			return;

		glUniform2fv(it->second.location, it->second.size, glm::value_ptr(value));
	}

	void Material::SetFloat(const std::string& name, const float& value)
	{
		unordered_map<string, Uniform>::iterator it = uniforms.find(name);
		if (it == uniforms.end())
			return;

		glUniform1fv(it->second.location, it->second.size, &value);
	}

	void Material::SetInt(const std::string& name, const int& value)
	{
		unordered_map<string, Uniform>::iterator it = uniforms.find(name);
		if (it == uniforms.end())
			return;

		glUniform1i(it->second.location, value);
	}

	void Material::SetBool(const std::string& name, const bool& value)
	{
		unordered_map<string, Uniform>::iterator it = uniforms.find(name);
		if (it == uniforms.end())
			return;

		glUniform1i(it->second.location, value);
	}

	void Material::Bind()
	{
		glUseProgram(gpuID);

		unsigned int textureSlot = 0;
		for (Uniform* u : samplerUniforms)
		{
			unordered_map<string, unsigned int>::iterator it = textures.find(u->name);
			if (it == textures.end())
				continue;

			glActiveTexture(GL_TEXTURE0 + textureSlot);
			glBindTexture(GL_TEXTURE_2D, it->second);
			glUniform1i(u->location, textureSlot++);
			SetBool("has" + u->name, textures.size());
		}

		SetVec4("uColor", color);
	}

	void Material::UnBind()
	{
		glUseProgram(NULL);
	}

	void Material::Unload()
	{
		glDeleteProgram(gpuID);
	}
}