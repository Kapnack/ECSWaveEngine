#include "MaterialFactory.h"

#include <GL/glew.h>
#include <iostream>
#include <string>
#include <sstream>

#include "Material.h"
#include "FileReader/FileReader.h"

namespace WaveEngine
{
	MaterialFactory::MaterialFactory() : Service()
	{
		FileReader* fileReader = ServiceProvider::Instance().Get<FileReader>();

		string vertexShader = fileReader->ReadFile("Shaders/Shapes/basicVertexShader.shader");

		string fragmentShader = fileReader->ReadFile("Shaders/Shapes/basicFragmentShader.shader");

		CreateMaterial("basicShapeMaterial", vertexShader, fragmentShader);

		vertexShader = fileReader->ReadFile("Shaders/Sprites/basicVertexShader.shader");

		fragmentShader = fileReader->ReadFile("Shaders/Sprites/basicFragmentShader.shader");

		CreateMaterial("basicSpriteMaterial", vertexShader, fragmentShader);
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

		if (vs == 0 || fs == 0)
			return Material::NULL_MATERIAL;

		unsigned int programID = glCreateProgram();

		glAttachShader(programID, vs);
		glAttachShader(programID, fs);
		glLinkProgram(programID);
		glValidateProgram(programID);

		glDeleteShader(vs);
		glDeleteShader(fs);

		GLint success;
		glGetProgramiv(programID, GL_LINK_STATUS, &success);

		if (!success)
		{
			char infoLog[512];
			glGetProgramInfoLog(programID, 512, nullptr, infoLog);
			std::cout << "Program Link Error:\n" << infoLog << std::endl;

			glDeleteProgram(programID);
			return Material::NULL_MATERIAL;
		}

		++currentMaterialID;

		Material* newMaterial = new Material(currentMaterialID);

		GLint uniformCount = 0;
		glGetProgramiv(programID, GL_ACTIVE_UNIFORMS, &uniformCount);

		GLint maxNameLength = 0;
		glGetProgramiv(programID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLength);

		std::vector<GLchar> buffer(maxNameLength);

		for (GLint i = 0; i < uniformCount; i++)
		{
			GLsizei length;
			GLint size;
			GLenum type;

			glGetActiveUniform(programID,
				i,
				maxNameLength,
				&length,
				&size,
				&type,
				buffer.data());

			std::string uniformName(buffer.data(), length);
			GLint location = glGetUniformLocation(programID, uniformName.c_str());

			newMaterial->AddUniform(uniformName, type, location, size);

			std::cout << "Uniform: " << uniformName
				<< " | Location: " << location
				<< std::endl;
		}


		int i = 0;
		string selectedName = name.data();

		while (GetMaterialManager()->GetMaterial(selectedName))
		{
			++i;
			selectedName = string(name) + " (" + to_string(i) + ")";
		}

		newMaterial->SetName(selectedName);
		newMaterial->program = programID;
		GetMaterialManager()->SaveMaterial(currentMaterialID, newMaterial);

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

			return 0;
		}

		return id;
	}
}