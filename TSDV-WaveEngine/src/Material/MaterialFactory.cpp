#include "MaterialFactory.h"

#include <GL/glew.h>
#include <iostream>
#include <string>

#include "Material.h"

namespace WaveEngine
{
	MaterialFactory::MaterialFactory() : Service()
	{	
	}

	MaterialFactory::~MaterialFactory()
	{
	}

	MaterialManager* MaterialFactory::GetMaterialManager()
	{
		return ServiceProvider::Instance().Get<MaterialManager>();
	}

	unsigned int MaterialFactory::CreateMaterial(const string_view name, const string_view vertexShader, const string_view fragmentShader)
	{
		if (name == "" || vertexShader == "" || fragmentShader == "")
			return Material::NULL_MATERIAL;

		unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
		unsigned int fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

		if (vs == NULL || fs == NULL)
			return Material::NULL_MATERIAL;

		unsigned int gpuID = glCreateProgram();

		glAttachShader(gpuID, vs);
		glAttachShader(gpuID, fs);
		glLinkProgram(gpuID);
		glValidateProgram(gpuID);

		glDeleteShader(vs);
		glDeleteShader(fs);

		GLint success = 0;
		glGetProgramiv(gpuID, GL_LINK_STATUS, &success);

		if (!success)
		{
			char infoLog[512];
			glGetProgramInfoLog(gpuID, 512, nullptr, infoLog);
			std::cout << "Program Link Error:\n" << infoLog << std::endl;

			glDeleteProgram(gpuID);
			return Material::NULL_MATERIAL;
		}

		Material* newMaterial = new Material(++currentMaterialID);

		GLint uniformCount = 0;
		glGetProgramiv(gpuID, GL_ACTIVE_UNIFORMS, &uniformCount);

		GLint maxNameLength = 0;
		glGetProgramiv(gpuID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLength);

		GLchar* nameBuffer = new GLchar[maxNameLength];

		for (GLint i = 0; i < uniformCount; i++)
		{
			GLsizei length;
			GLint size;
			GLenum type;

			glGetActiveUniform(gpuID,
				i,
				maxNameLength,
				&length,
				&size,
				&type,
				nameBuffer);

			string uniformName = string(nameBuffer, length);
			GLint location = glGetUniformLocation(gpuID, uniformName.c_str());

			newMaterial->AddUniform(uniformName, type, location, size);

			cout << "Uniform: " << uniformName
				<< " | Location: " << location
				<< std::endl;
		}

		delete[] nameBuffer;

		int i = 0;
		string selectedName = name.data();

		while (GetMaterialManager()->GetMaterial(selectedName))
		{
			++i;
			selectedName = string(name) + " (" + to_string(i) + ")";
		}

		newMaterial->SetName(selectedName);
		newMaterial->gpuID = gpuID;
		GetMaterialManager()->SaveMaterial(newMaterial);

		return currentMaterialID;
	}

	unsigned int MaterialFactory::CompileShader(const string_view source, unsigned int type)
	{
		unsigned int id = glCreateShader(type);

		const char* src = source.data();

		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);
			cout << message << "\n\n";

			glDeleteShader(id);

			return NULL;
		}

		return id;
	}
}