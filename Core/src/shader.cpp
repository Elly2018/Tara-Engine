#include "Shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <utility.h>

namespace Tara {
	#pragma region Const Static Declaration
	const const char* PureColor_Vert = ".\\Resources\\PureColor.vert";
	const const char* PureColor_Frag = ".\\Resources\\PureColor.frag";
	const const char* Gradient_Vert = ".\\Resources\\Gradient.vert";
	const const char* Gradient_Frag = ".\\Resources\\Gradient.frag";
	const const char* TextureSurface_Vert = ".\\Resources\\TextureSurface.vert";
	const const char* TextureSurface_Frag = ".\\Resources\\TextureSurface.frag";
	const const char* DefaultPostProcess_Vert = ".\\Resources\\DefaultPostProcess.vert";
	const const char* DefaultPostProcess_Frag = ".\\Resources\\DefaultPostProcess.frag";
	std::map<ShaderType, std::string> Shadertype_string = {
		{ShaderType::Vertex, "VERTEX"},
		{ShaderType::Tessellation, "TESSELLATION"},
		{ShaderType::Fragment, "FRAGMENT"},
		{ShaderType::Geometry, "GEOMETRY"},
		{ShaderType::Compute, "COMPUTE"}
	};
	AssetPool<Shader>* Shader::m_shaderPool = new AssetPool<Shader>();
	#pragma endregion

	void CreateDefaultShaders()
	{
		TARA_DEBUG_LEVEL("Buildin resources shader create: Color", 1);
		Shader::GetCommon(CommonShader::Color);
		TARA_DEBUG_LEVEL("Buildin resources shader create: Gradient", 1);
		Shader::GetCommon(CommonShader::Gradient);
		TARA_DEBUG_LEVEL("Buildin resources shader create: Texture", 1);
		Shader::GetCommon(CommonShader::Texture);
		TARA_DEBUG_LEVEL("Buildin resources shader create: Postprocess", 1);
		Shader::GetCommon(CommonShader::DefaultPostprocess);
	}

	Shader::Shader()
	{
		TARA_DEBUG_LEVEL("Shader created!", 1);
		program = glCreateProgram();
		TARA_DEBUG_LEVEL("\tShader pool add!", 1);
		m_shaderPool->Add(this);
	}
	Shader::~Shader()
	{
		TARA_DEBUG_LEVEL("Shader destroy! %s", 1, Name());
		glDeleteProgram(program);
		TARA_DEBUG_LEVEL("\tShader buffer destroy! %s", 1, Name());
		DeleteShader();
		TARA_DEBUG_LEVEL("\tShader pool remove! %s", 1, Name());
	}
	Shader* Shader::GetCommon(CommonShader type)
	{
		switch (type) {
		case CommonShader::Color:
		{
			Shader* s = m_shaderPool->Find("Color Shader", true);
			if (s == nullptr) return GetColorShader();
			else return s;
		}
		case CommonShader::Gradient:
		{
			Shader* s = m_shaderPool->Find("Gradient Shader", true);
			if (s == nullptr) return GetGradientShader();
			else return s;
		}
		case CommonShader::Texture:
		{
			Shader* s = m_shaderPool->Find("Texture Shader", true);
			if (s == nullptr) return GetTextureShader();
			else return s;
		}
		case CommonShader::DefaultPostprocess:
		{
			Shader* s = m_shaderPool->Find("Default Postprocess", true);
			if (s == nullptr) return GetDefaultPostprocessShader();
			else return s;
		}
		}
		return nullptr;
	}
	Shader* Shader::GetColorShader()
	{
		Shader* buffer = new Shader();
		buffer->m_buildIn = true;
		buffer->m_name = "Color Shader";
		buffer->SetVertexFromFile(PureColor_Vert);
		buffer->SetFragmentFromFile(PureColor_Frag);
		bool success = buffer->Compile();
		if (success) buffer->DeleteShader();
		return buffer;
	}
	Shader* Shader::GetGradientShader()
	{
		Shader* buffer = new Shader();
		buffer->m_buildIn = true;
		buffer->m_name = "Gradient Shader";
		buffer->SetVertexFromFile(Gradient_Vert);
		buffer->SetFragmentFromFile(Gradient_Frag);
		bool success = buffer->Compile();
		if (success) buffer->DeleteShader();
		return buffer;
	}
	Shader* Shader::GetTextureShader()
	{
		Shader* buffer = new Shader();
		buffer->m_buildIn = true;
		buffer->m_name = "Texture Shader";
		buffer->SetVertexFromFile(TextureSurface_Vert);
		buffer->SetFragmentFromFile(TextureSurface_Frag);
		bool success = buffer->Compile();
		if (success) buffer->DeleteShader();
		return buffer;
	}
	Shader* Shader::GetDefaultPostprocessShader()
	{
		Shader* buffer = new Shader();
		buffer->m_buildIn = true;
		buffer->m_name = "Default Postprocess";
		buffer->SetVertexFromFile(DefaultPostProcess_Vert);
		buffer->SetFragmentFromFile(DefaultPostProcess_Frag);
		bool success = buffer->Compile();
		if (success) buffer->DeleteShader();
		return buffer;
	}
	AssetPool<Shader>* Shader::GetAssetPool()
	{
		return m_shaderPool;
	}

	void Shader::Use()
	{
		glUseProgram(program);
	}
	void Shader::Unuse()
	{
		glUseProgram(0);
	}
	bool Shader::Compile()
	{
		int success;
		char infoLog[512];

		if (!vertex_code.empty()) CompileShader(ShaderType::Vertex);
		if (!tessellation_code.empty()) CompileShader(ShaderType::Tessellation);
		if (!fragment_code.empty()) CompileShader(ShaderType::Fragment);
		if (!geometry_code.empty()) CompileShader(ShaderType::Geometry);
		if (!compute_code.empty()) CompileShader(ShaderType::Compute);

		if (!vertex_code.empty()) glAttachShader(program, vertex);
		if (!tessellation_code.empty()) glAttachShader(program, tessellation);
		if (!fragment_code.empty()) glAttachShader(program, fragment);
		if (!geometry_code.empty()) glAttachShader(program, geometry);
		if (!compute_code.empty()) glAttachShader(program, compute);
		glLinkProgram(program);
		// print linking errors if any
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(program, 512, NULL, infoLog);
			TARA_ERROR_LEVEL("ERROR::Shader::PROGRAM::LINKING_FAILED:%s\n%s", 4, Name(), infoLog);
		}
		return success;
	}
	void Shader::DeleteShader()
	{
		DeleteShaderBuffer();
		DeleteShaderString();
	}
	void Shader::DeleteShaderBuffer()
	{
		if (vertex != -1) { glDeleteShader(vertex); vertex = -1; };
		if (tessellation != -1) { glDeleteShader(tessellation); tessellation = -1; };
		if (fragment != -1) { glDeleteShader(fragment); fragment = -1; };
		if (geometry != -1) { glDeleteShader(geometry); geometry = -1; };
		if (compute != -1) { glDeleteShader(compute); compute = -1; };
	}
	void Shader::DeleteShaderString()
	{
		vertex_code.clear();
		tessellation_code.clear();
		fragment_code.clear();
		geometry_code.clear();
		compute_code.clear();
	}
	void Shader::SetVertexFromFile(const char* filename)
	{
		vertex_code = LoadFromFile(filename).c_str();
	}
	void Shader::SetVertexFromCode(const char* code)
	{
		vertex_code = strdup(code);
	}
	void Shader::SetTessellationFromFile(const char* filename)
	{
		tessellation_code = LoadFromFile(filename).c_str();
	}
	void Shader::SetTessellationFromCode(const char* code)
	{
		tessellation_code = strdup(code);
	}
	void Shader::SetFragmentFromFile(const char* filename)
	{
		fragment_code = LoadFromFile(filename).c_str();
	}
	void Shader::SetFragmentFromCode(const char* code)
	{
		fragment_code = strdup(code);
	}
	void Shader::SetGeometryFromFile(const char* filename)
	{
		geometry_code = LoadFromFile(filename).c_str();
	}
	void Shader::SetGeometryFromCode(const char* code)
	{
		geometry_code = strdup(code);
	}
	void Shader::SetComputeFromFile(const char* filename)
	{
		compute_code = LoadFromFile(filename).c_str();
	}
	void Shader::SetComputeFromCode(const char* code)
	{
		compute_code = strdup(code);
	}

	int Shader::GetUniformLocation(const char* name)
	{
		return glGetUniformLocation(program, name);
	}
	void Shader::PrintUniform()
	{
	
	}
	void Shader::CompileShader(ShaderType type)
	{
		TARA_DEBUG();
		TARA_DEBUG("Compile Shader... %s %s", m_name.c_str(), Shadertype_string.at(type).c_str());
		int success;
		char infoLog[512];

		int target = -1;
		TARA_DEBUG_LEVEL("#########################################################", 1);
		TARA_DEBUG_LEVEL("#\t\t\t%s %s\t\t\t#", 1, Shadertype_string.at(type).c_str(), "start");
		TARA_DEBUG_LEVEL("#########################################################", 1);
		TARA_DEBUG_LEVEL("", 1);
		switch (type)
		{
		case ShaderType::Vertex:
		{
			vertex = glCreateShader(GL_VERTEX_SHADER);
			target = vertex;
			const char* c_str = vertex_code.c_str();
			glShaderSource(vertex, 1, &c_str, NULL);
			TARA_DEBUG_LEVEL("%s", 1, vertex_code.c_str());
			break;
		}
		case ShaderType::Tessellation:
		{
			tessellation = glCreateShader(GL_TESS_CONTROL_SHADER);
			target = tessellation;
			const char* c_str = tessellation_code.c_str();
			glShaderSource(tessellation, 1, &c_str, NULL);
			TARA_DEBUG_LEVEL("%s", 1, tessellation_code.c_str());
			break;
		}
		case ShaderType::Fragment:
		{
			fragment = glCreateShader(GL_FRAGMENT_SHADER);
			target = fragment;
			const char* c_str = fragment_code.c_str();
			glShaderSource(fragment, 1, &c_str, NULL);
			TARA_DEBUG_LEVEL("%s", 1, fragment_code.c_str());
			break;
		}
		case ShaderType::Geometry:
		{
			geometry = glCreateShader(GL_GEOMETRY_SHADER);
			target = geometry;
			const char* c_str = geometry_code.c_str();
			glShaderSource(geometry, 1, &c_str, NULL);
			TARA_DEBUG_LEVEL("%s", 1, geometry_code.c_str());
			break;
		}
		case ShaderType::Compute:
		{
			compute = glCreateShader(GL_COMPUTE_SHADER);
			target = compute;
			const char* c_str = compute_code.c_str();
			glShaderSource(compute, 1, &c_str, NULL);
			TARA_DEBUG_LEVEL("%s", 1, compute_code.c_str());
			break;
		}}
		TARA_DEBUG_LEVEL("", 1);
		TARA_DEBUG_LEVEL("#########################################################", 1);
		TARA_DEBUG_LEVEL("#\t\t\t%s %s\t\t\t#", 1, Shadertype_string.at(type).c_str(), "end");
		TARA_DEBUG_LEVEL("#########################################################", 1);
	
		glCompileShader(target);
		// print compile errors if any
		glGetShaderiv(target, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(target, 512, NULL, infoLog);
			TARA_DEBUG_LEVEL("ERROR::Shader::%s::COMPILATION_FAILED\n%s", 4, Shadertype_string.at(type).c_str(), infoLog);
		};
	}
	std::string Shader::LoadFromFile(const char* filename)
	{
		return Utility::File::LoadFromFile(filename);
	}
};