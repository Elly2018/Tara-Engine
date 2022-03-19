#include "shader.h"

// Include std library
#include <stdio.h>
#include <stdlib.h>
#include <filesystem>
#include <string>
#include <regex>

// Include third party library
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

// Include tara library
#include "../utility.h"

using namespace std::chrono_literals;

namespace Tara {
	ShaderLibrary* ShaderLibrary::m_Singleton = nullptr;
#pragma region Const Static Declaration
	std::map<ShaderType, std::string> Shadertype_string = {
		{ShaderType::Vertex, "VERTEX"},
		{ShaderType::Tessellation, "TESSELLATION"},
		{ShaderType::Fragment, "FRAGMENT"},
		{ShaderType::Geometry, "GEOMETRY"},
		{ShaderType::Compute, "COMPUTE"}
	};
	std::map<ShaderType, int32_t> shadertype_target{
		{ShaderType::Vertex, GL_VERTEX_SHADER},
		{ShaderType::Tessellation, GL_TESS_CONTROL_SHADER},
		{ShaderType::Fragment, GL_FRAGMENT_SHADER},
		{ShaderType::Geometry, GL_GEOMETRY_SHADER},
		{ShaderType::Compute, GL_COMPUTE_SHADER}
	};
	std::map<ShaderUniformType, uint32_t> uniformMap = {
		{ShaderUniformType::Float, GL_FLOAT},
		{ShaderUniformType::Double, GL_DOUBLE},
		{ShaderUniformType::Int, GL_INT},
		{ShaderUniformType::Int, GL_UNSIGNED_INT},
		{ShaderUniformType::Bool, GL_BOOL},

		{ShaderUniformType::Vec2, GL_FLOAT_VEC2},
		{ShaderUniformType::Vec3, GL_FLOAT_VEC3},
		{ShaderUniformType::Vec4, GL_FLOAT_VEC4},
		{ShaderUniformType::BVec2, GL_BOOL_VEC2},
		{ShaderUniformType::BVec3, GL_BOOL_VEC3},
		{ShaderUniformType::BVec4, GL_BOOL_VEC4},
		{ShaderUniformType::DVec2, GL_DOUBLE_VEC2},
		{ShaderUniformType::DVec3, GL_DOUBLE_VEC3},
		{ShaderUniformType::DVec4, GL_DOUBLE_VEC4},
		{ShaderUniformType::IVec2, GL_INT_VEC2},
		{ShaderUniformType::IVec3, GL_INT_VEC3},
		{ShaderUniformType::IVec4, GL_INT_VEC4},
		{ShaderUniformType::UVec2, GL_UNSIGNED_INT_VEC2},
		{ShaderUniformType::UVec3, GL_UNSIGNED_INT_VEC3},
		{ShaderUniformType::UVec4, GL_UNSIGNED_INT_VEC4},

		{ShaderUniformType::Mat2, GL_FLOAT_MAT2},
		{ShaderUniformType::Mat3, GL_FLOAT_MAT3},
		{ShaderUniformType::Mat4, GL_FLOAT_MAT4},
		{ShaderUniformType::Mat2x3, GL_FLOAT_MAT2x3},
		{ShaderUniformType::Mat2x4, GL_FLOAT_MAT2x4},
		{ShaderUniformType::Mat3x2, GL_FLOAT_MAT3x2},
		{ShaderUniformType::Mat3x4, GL_FLOAT_MAT3x4},
		{ShaderUniformType::Mat4x2, GL_FLOAT_MAT4x2},
		{ShaderUniformType::Mat4x3, GL_FLOAT_MAT4x3},
		{ShaderUniformType::DMat2, GL_DOUBLE_MAT2},
		{ShaderUniformType::DMat3, GL_DOUBLE_MAT3},
		{ShaderUniformType::DMat4, GL_DOUBLE_MAT4},
		{ShaderUniformType::DMat2x3, GL_DOUBLE_MAT2x3},
		{ShaderUniformType::DMat2x4, GL_DOUBLE_MAT2x4},
		{ShaderUniformType::DMat3x2, GL_DOUBLE_MAT3x2},
		{ShaderUniformType::DMat3x4, GL_DOUBLE_MAT3x4},
		{ShaderUniformType::DMat4x2, GL_DOUBLE_MAT4x2},
		{ShaderUniformType::DMat4x3, GL_DOUBLE_MAT4x3},

		{ShaderUniformType::Texture1D, GL_SAMPLER_1D},
		{ShaderUniformType::Texture2D, GL_SAMPLER_2D},
		{ShaderUniformType::Texture3D, GL_SAMPLER_3D},
		{ShaderUniformType::TextureCube, GL_SAMPLER_CUBE},
		{ShaderUniformType::Texture1DShadow, GL_SAMPLER_1D_SHADOW},
		{ShaderUniformType::Texture2DShadow, GL_SAMPLER_2D_SHADOW},
		{ShaderUniformType::Texture1DArray, GL_SAMPLER_1D_ARRAY},
		{ShaderUniformType::Texture2DArray, GL_SAMPLER_2D_ARRAY},
		{ShaderUniformType::Texture2DRect, GL_SAMPLER_2D_RECT},
		{ShaderUniformType::Texture2DRectShadow, GL_SAMPLER_2D_RECT_SHADOW},
		{ShaderUniformType::Texture2DMultisample, GL_SAMPLER_2D_MULTISAMPLE},
		{ShaderUniformType::Texture2DMultisampleArray, GL_SAMPLER_2D_MULTISAMPLE_ARRAY},
		{ShaderUniformType::Texture1DShadowArray, GL_SAMPLER_1D_ARRAY_SHADOW},
		{ShaderUniformType::Texture2DShadowArray, GL_SAMPLER_2D_ARRAY_SHADOW},
		{ShaderUniformType::ITexture1D, GL_INT_SAMPLER_1D},
		{ShaderUniformType::ITexture2D, GL_INT_SAMPLER_2D},
		{ShaderUniformType::ITexture3D, GL_INT_SAMPLER_3D},
		{ShaderUniformType::ITextureCube, GL_INT_SAMPLER_CUBE},
		{ShaderUniformType::ITexture1DArray, GL_INT_SAMPLER_1D_ARRAY},
		{ShaderUniformType::ITexture2DArray, GL_INT_SAMPLER_2D_ARRAY},
		{ShaderUniformType::ITexture2DRect, GL_INT_SAMPLER_2D_RECT},
		{ShaderUniformType::ITexture2DMultisample, GL_INT_SAMPLER_2D_MULTISAMPLE},
		{ShaderUniformType::ITexture2DMultisampleArray, GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY},
		{ShaderUniformType::UTexture1D, GL_UNSIGNED_INT_SAMPLER_1D},
		{ShaderUniformType::UTexture2D, GL_UNSIGNED_INT_SAMPLER_2D},
		{ShaderUniformType::UTexture3D, GL_UNSIGNED_INT_SAMPLER_3D},
		{ShaderUniformType::UTextureCube, GL_UNSIGNED_INT_SAMPLER_CUBE},
		{ShaderUniformType::UTexture1DArray, GL_UNSIGNED_INT_SAMPLER_1D_ARRAY},
		{ShaderUniformType::UTexture2DArray, GL_UNSIGNED_INT_SAMPLER_2D_ARRAY},
		{ShaderUniformType::UTexture2DRect, GL_UNSIGNED_INT_SAMPLER_2D_RECT},
		{ShaderUniformType::UTexture2DMultisample, GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE},
		{ShaderUniformType::UTexture2DMultisampleArray, GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY},
	};
	std::map<ShaderUniformType, const char*> uniformString = {
		{ShaderUniformType::Float, "float"},
		{ShaderUniformType::Double, "double"},
		{ShaderUniformType::Int, "int"},
		{ShaderUniformType::UInt, "unsigned int"},
		{ShaderUniformType::Bool, "bool"},

		{ShaderUniformType::Vec2, "vec2"},
		{ShaderUniformType::Vec3, "vec3"},
		{ShaderUniformType::Vec4, "vec4"},
		{ShaderUniformType::BVec2, "bvec2"},
		{ShaderUniformType::BVec3, "bvec3"},
		{ShaderUniformType::BVec4, "bvec4"},
		{ShaderUniformType::DVec2, "dvec2"},
		{ShaderUniformType::DVec3, "dvec3"},
		{ShaderUniformType::DVec4, "dvec4"},
		{ShaderUniformType::IVec2, "ivec2"},
		{ShaderUniformType::IVec3, "ivec3"},
		{ShaderUniformType::IVec4, "ivec4"},
		{ShaderUniformType::UVec2, "uvec2"},
		{ShaderUniformType::UVec3, "uvec3"},
		{ShaderUniformType::UVec4, "uvec4"},

		{ShaderUniformType::Mat2, "mat2"},
		{ShaderUniformType::Mat3, "mat3"},
		{ShaderUniformType::Mat4, "mat4"},
		{ShaderUniformType::Mat2x3, "mat2x3"},
		{ShaderUniformType::Mat2x4, "mat2x4"},
		{ShaderUniformType::Mat3x2, "mat3x2"},
		{ShaderUniformType::Mat3x4, "mat3x4"},
		{ShaderUniformType::Mat4x2, "mat4x2"},
		{ShaderUniformType::Mat4x3, "mat4x3"},
		{ShaderUniformType::DMat2, "mat2"},
		{ShaderUniformType::DMat3, "dmat3"},
		{ShaderUniformType::DMat4, "dmat4"},
		{ShaderUniformType::DMat2x3, "dmat2x3"},
		{ShaderUniformType::DMat2x4, "dmat2x4"},
		{ShaderUniformType::DMat3x2, "dmat3x2"},
		{ShaderUniformType::DMat3x4, "dmat3x4"},
		{ShaderUniformType::DMat4x2, "dmat4x2"},
		{ShaderUniformType::DMat4x3, "dmat4x3"},

		{ShaderUniformType::Texture1D, "sampler1D"},
		{ShaderUniformType::Texture2D, "sampler2D"},
		{ShaderUniformType::Texture3D, "sampler3D"},
		{ShaderUniformType::TextureCube, "samplerCube"},
		{ShaderUniformType::Texture1DShadow, "sampler1DShadow"},
		{ShaderUniformType::Texture2DShadow, "sampler2DShadow"},
		{ShaderUniformType::Texture1DArray, "sampler1DArray"},
		{ShaderUniformType::Texture2DArray, "sampler2DArray"},
		{ShaderUniformType::Texture2DRect, "sampler2DRect"},
		{ShaderUniformType::Texture2DRectShadow, "sampler2DRectShadow"},
		{ShaderUniformType::Texture2DMultisample, "sampler2DMS"},
		{ShaderUniformType::Texture2DMultisampleArray, "sampler2DMSArray"},
		{ShaderUniformType::Texture1DShadowArray, "sampler1DArrayShadow"},
		{ShaderUniformType::Texture2DShadowArray, "sampler2DArrayShadow"},
		{ShaderUniformType::ITexture1D, "isampler1D"},
		{ShaderUniformType::ITexture2D, "isampler2D"},
		{ShaderUniformType::ITexture3D, "isampler3D"},
		{ShaderUniformType::ITextureCube, "isamplerCube"},
		{ShaderUniformType::ITexture1DArray, "isampler1DArray"},
		{ShaderUniformType::ITexture2DArray, "isampler2DArray"},
		{ShaderUniformType::ITexture2DRect, "isampler2DRect"},
		{ShaderUniformType::ITexture2DMultisample, "isampler2DMS"},
		{ShaderUniformType::ITexture2DMultisampleArray, "isampler2DMSArray"},
		{ShaderUniformType::UTexture1D, "usampler1D"},
		{ShaderUniformType::UTexture2D, "usampler2D"},
		{ShaderUniformType::UTexture3D, "usampler3D"},
		{ShaderUniformType::UTextureCube, "usamplerCube"},
		{ShaderUniformType::UTexture1DArray, "usampler1DArray"},
		{ShaderUniformType::UTexture2DArray, "usampler2DArray"},
		{ShaderUniformType::UTexture2DRect, "usampler2DRect"},
		{ShaderUniformType::UTexture2DMultisample, "usampler2DMS"},
		{ShaderUniformType::UTexture2DMultisampleArray, "usampler2DMSArray"},
	};
	std::map<ShaderUniformType, size_t> uniformSize = {
		{ShaderUniformType::Float, sizeof(float_t)},
		{ShaderUniformType::Double, sizeof(double_t)},
		{ShaderUniformType::Int, sizeof(int32_t)},
		{ShaderUniformType::UInt, sizeof(uint32_t)},
		{ShaderUniformType::Bool, sizeof(int32_t)},

		{ShaderUniformType::Vec2, sizeof(glm::vec2)},
		{ShaderUniformType::Vec3, sizeof(glm::vec3)},
		{ShaderUniformType::Vec4, sizeof(glm::vec4)},
		{ShaderUniformType::BVec2, sizeof(glm::ivec2)},
		{ShaderUniformType::BVec3, sizeof(glm::ivec3)},
		{ShaderUniformType::BVec4, sizeof(glm::ivec4)},
		{ShaderUniformType::DVec2, sizeof(glm::dvec2)},
		{ShaderUniformType::DVec3, sizeof(glm::dvec3)},
		{ShaderUniformType::DVec4, sizeof(glm::dvec4)},
		{ShaderUniformType::IVec2, sizeof(glm::ivec2)},
		{ShaderUniformType::IVec3, sizeof(glm::ivec3)},
		{ShaderUniformType::IVec4, sizeof(glm::ivec4)},
		{ShaderUniformType::UVec2, sizeof(glm::uvec2)},
		{ShaderUniformType::UVec3, sizeof(glm::uvec3)},
		{ShaderUniformType::UVec4, sizeof(glm::uvec4)},

		{ShaderUniformType::Mat2, sizeof(glm::mat2)},
		{ShaderUniformType::Mat3, sizeof(glm::mat3)},
		{ShaderUniformType::Mat4, sizeof(glm::mat4)},
		{ShaderUniformType::Mat2x3, sizeof(glm::mat2x3)},
		{ShaderUniformType::Mat2x4, sizeof(glm::mat2x4)},
		{ShaderUniformType::Mat3x2, sizeof(glm::mat3x2)},
		{ShaderUniformType::Mat3x4, sizeof(glm::mat3x4)},
		{ShaderUniformType::Mat4x2, sizeof(glm::mat4x2)},
		{ShaderUniformType::Mat4x3, sizeof(glm::mat4x3)},
		{ShaderUniformType::DMat2, sizeof(glm::dmat2)},
		{ShaderUniformType::DMat3, sizeof(glm::dmat3)},
		{ShaderUniformType::DMat4, sizeof(glm::dmat4)},
		{ShaderUniformType::DMat2x3, sizeof(glm::dmat2x3)},
		{ShaderUniformType::DMat2x4, sizeof(glm::dmat2x4)},
		{ShaderUniformType::DMat3x2, sizeof(glm::dmat3x2)},
		{ShaderUniformType::DMat3x4, sizeof(glm::dmat3x4)},
		{ShaderUniformType::DMat4x2, sizeof(glm::dmat4x2)},
		{ShaderUniformType::DMat4x3, sizeof(glm::dmat4x3)},
	};
#pragma endregion

#pragma region Shader
	Shader::Shader()
	{
		TARA_DEBUG_LEVEL("Shader created!", 1);
		program = glCreateProgram();
		TARA_DEBUG_LEVEL("\tShader pool add!", 1);
		m_compileAsync = std::async(std::launch::deferred, [this] {
			switch (m_mode) {
			case ShaderCompileMode::SpirV:
				return ThreadCompile();
			case ShaderCompileMode::GLSL:
				return ThreadCompileGLSL();
			default:
				return ThreadCompileGLSL();
			}
		});
	}
	Shader::Shader(bool buildin) : Shader()
	{
		m_buildIn = buildin;
	}
	Shader::~Shader()
	{
		TARA_DEBUG_LEVEL("Shader destroy! %s", 1, Name.c_str());
		glDeleteProgram(program);
		TARA_DEBUG_LEVEL("\tShader buffer destroy! %s", 1, Name.c_str());
		DeleteShader();
	}
	void Shader::RegisterUpdateEvent(Material* sender, std::function<void()> callback) {
		callback();
		if (m_updateEvent.count(sender)) {
			m_updateEvent[sender] = callback;
		}
	}
	void Shader::UnRegisterUpdateEvent(Material* sender) {
		m_updateEvent.erase(sender);
	}
	bool Shader::Use()
	{
		if (!m_good) {
			TARA_WARNING_LEVEL("Trying to use not compile shader: %s", 2, Name.c_str());
			return false;
		}
		glUseProgram(program);
		return true;
	}
	void Shader::Unuse()
	{
		glUseProgram(0);
	}
	void Shader::Compile()
	{
		m_mode = ShaderCompileMode::SpirV;
		CompileStart();
	}
	void Shader::CompileGLSL()
	{
		m_mode = ShaderCompileMode::GLSL;
		CompileStart();
	}
	bool Shader::Good() {
		return m_good;
	}
	ShaderCompileStage Shader::CompileState() {
		int succ = 0;
		int cing = 0;
		for (auto i : shader_stage) {
			switch (i.second)
			{
			// One of them failed means failed
			case ShaderCompileStage::Failed:
				return ShaderCompileStage::Failed;
			case ShaderCompileStage::Success:
				succ++;
				break;
			case ShaderCompileStage::Compiling:
				cing++;
				break;
			}
		}
		if (cing == 0 && succ == 0) return ShaderCompileStage::None;
		else if (cing == 0 && succ > 0) return ShaderCompileStage::Success;
		else if (cing > 0) return ShaderCompileStage::Compiling;
		else return ShaderCompileStage::None;
	}
	void Shader::DeleteShader()
	{
		DeleteShaderBuffer();
		DeleteShaderData();
	}
	void Shader::DeleteShaderBuffer()
	{
		auto func = [this](ShaderType type) -> void {
			if (shader_program.count(type)) {
				glDeleteShader(shader_program.at(type));
				auto it = shader_program.find(type);
				shader_program.erase(it);
			}
		};
		func(ShaderType::Vertex);
		func(ShaderType::Fragment);
		func(ShaderType::Geometry);
		func(ShaderType::Tessellation);
		func(ShaderType::Compute);
	}
	void Shader::DeleteShaderData()
	{
		for (int i = 0; i < 5; i++) {
			if (shader_code.count((ShaderType)i)) {
				auto it1 = shader_code.find((ShaderType)i);
				shader_code.erase(it1);
			}
			if (shader_binary.count((ShaderType)i)) {
				auto it1 = shader_binary.find((ShaderType)i);
				shader_binary.erase(it1);
			}
			if (shader_stage.count((ShaderType)i)) {
				auto it1 = shader_stage.find((ShaderType)i);
				shader_stage.erase(it1);
			}
		}
	}

	void Shader::SetShaderFromFile(ShaderType type, const char* filename, bool useGLSL)
	{
		TARA_DEBUG_LEVEL("Import shader %s file: %s", 2, Shadertype_string.at(type).c_str(), filename);
		if (!std::filesystem::exists(filename)) {
			TARA_ERROR_LEVEL("File does not exist: %s", 4, filename);
			return;
		}
		shader_code[type] = Utility::File::LoadFromFile(filename).c_str();
		shader_stage[type] = ShaderCompileStage::None;
		if (useGLSL) return;

		std::filesystem::path p(filename);
		TARA_DEBUG("%s file name: %s", Shadertype_string.at(type).c_str(), p.filename().string().c_str());
		std::string command = "glslc -c ";
		std::string tempname = p.filename().string() + ".glsl";
		command += filename;
		command += " -o .\\temp\\";
		command += tempname;
		shader_temp_name[type] = tempname;
		TARA_DEBUG("%s compile command: %s", Shadertype_string.at(type).c_str(), command.c_str());
		int success = system(command.c_str());
		TARA_DEBUG("%s compile result: %i", Shadertype_string.at(type).c_str(), success);
	}
	void Shader::SetShaderFromCode(ShaderType type, const char* code)
	{
		TARA_DEBUG_LEVEL("Import shader %s code, size: %i", 2, Shadertype_string.at(type).c_str(), sizeof(code));
		shader_code[type] = code;
		shader_stage[type] = ShaderCompileStage::None;
	}
	void Shader::SetShaderFromBinary(ShaderType type, void* binary)
	{
		TARA_DEBUG_LEVEL("Import shader %s binary, size: %i", 2, Shadertype_string.at(type).c_str(), sizeof(binary));
		shader_binary[type] = binary;
		shader_stage[type] = ShaderCompileStage::None;
	}

	int32_t Shader::GetUniformLocation(const char* name)
	{
		return glGetUniformLocation(program, name);
	}
	int32_t Shader::GetUniformBlockIndex(const char* name)
	{
		return glGetUniformBlockIndex(program, name);
	}
	void Shader::PrintUniform()
	{
		ShaderUniformInformation info = Uniforms();
		TARA_DEBUG("Print shader uniform: %s", Name.c_str());
		TARA_DEBUG("\tUniform:");
		for (auto m : info.Data) {
			TARA_DEBUG("\t\tUniform name: %s", m.Name.c_str());
			TARA_DEBUG("\t\ttype: %s", uniformString.at(m.Type));
			TARA_DEBUG("\t\tVaraible name: %s", m.VariableName.c_str());
			TARA_DEBUG("\t\tsize: %zu", m.Size);
			TARA_DEBUG("\t\tlocation: %i", m.Location);
		}
		TARA_DEBUG("\tUniform block:");
		for (auto m : info.BlockData) {
			TARA_DEBUG("\t\tUniform block name: %s", m.BlockName.c_str());
			TARA_DEBUG("\t\tUniform block size: %zu", m.Size);
			TARA_DEBUG("\t\tUniform block index: %zu", m.Index);
			for (auto mc : m.Content) {
				TARA_DEBUG("\t\t\tUniform name: %s", mc.Name.c_str());
				TARA_DEBUG("\t\t\ttype: %s", uniformString.at(mc.Type));
				TARA_DEBUG("\t\t\tVaraible name: %s", mc.VariableName.c_str());
				TARA_DEBUG("\t\t\tsize: %zu", mc.Size);
				TARA_DEBUG("\t\t\tlocation: %i", mc.Location);
			}
		}
	}
	ShaderUniformInformation Shader::Uniforms()
	{
		if (!m_dirty || !m_good) return uniformData;
		TARA_DEBUG_LEVEL("Form uniform data: %s", 1, Name.c_str());
		int32_t count;
		ShaderUniformInformation result = ShaderUniformInformation();
		result.BlockData = std::vector<ShaderUniformBlockInformation>();
		result.Data = std::vector<ShaderUniformContent>();
		// Get uniform count first.
		glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &count);
		// Indexing the uniform.
		for (int32_t i = 0; i < count; i++)
		{
			// Prepare data
			bool isUniformBlock;
			char bufSize[64];
			int32_t length = 0;
			int32_t	size = 0;
			uint32_t type = 0;
			glGetActiveUniform(program, i, sizeof(bufSize), &length, &size, &type, bufSize);
			uint32_t index[1];
			const char* bufName[] = { bufSize };
			glGetUniformIndices(program, 1, bufName, index);
			ShaderUniformContent buffer = ShaderUniformContent();
			bool find = false;
			for (auto m : uniformMap) {
				if (m.second == type) {
					buffer.Type = m.first;
					find = true;
					break;
				}
			}
			if (!find) {
				TARA_WARNING_LEVEL("Tara does not support this uniform type: %i", 2, type);
				continue;
			}
			buffer.Name = bufSize;
			buffer.TypeName = uniformString.at(buffer.Type);
			buffer.Location = glGetUniformLocation(program, buffer.Name.c_str());
			buffer.Size = uniformSize.count(buffer.Type) ? uniformSize.at(buffer.Type) : 0;
			buffer.Index = index[0];

			size_t pos = buffer.Name.find('.');
			isUniformBlock = pos != std::string::npos;

			if (isUniformBlock) {
				std::string blockName = buffer.Name.substr(0, pos);
				bool pushToRoot = true;
				ShaderUniformBlockInformation* blockdata = nullptr;
				for (int32_t j = 0; j < result.BlockData.size(); j++) {
					if (result.BlockData[j].BlockName == blockName) {
						blockdata = &result.BlockData[j];
						pushToRoot = false;
						break;
					}
				}
				if (!blockdata) {
					blockdata = new ShaderUniformBlockInformation();
					blockdata->BlockName = blockName;
					blockdata->Index = glGetUniformBlockIndex(program, blockdata->BlockName.c_str());
				}

				uint32_t ix = glGetProgramResourceIndex(program, GL_UNIFORM, buffer.Name.c_str());
				uint32_t props[] = { GL_ARRAY_STRIDE, GL_OFFSET };
				GLint values[2] = {};
				glGetProgramResourceiv(program, GL_UNIFORM, ix, 2, props, 2, NULL, values);
				
				int32_t arrayIndex = -1;
				const char* search_regex = "\\[[0-9]\\]";

				std::smatch m;
				std::regex_search(buffer.Name, m, std::regex(search_regex));
				if (m.str().size() > 0) {
					std::string match = m.str();
					match.pop_back();
					match.erase(0, 1);
					//TARA_DEBUG("%s: %s", buffer.Name.c_str(), match.c_str());
					arrayIndex = std::stoi(match);
				}

				buffer.Location = values[1] + (arrayIndex * values[0]);
				buffer.VariableName = isUniformBlock ? buffer.Name.substr(pos + 1, buffer.Name.length()).c_str() : buffer.Name.c_str();

				blockdata->Content.push_back(buffer);
				blockdata->Size += std::fmax(buffer.Size, 16);

				if(pushToRoot)
					result.BlockData.push_back(*blockdata);
			}
			else {
				buffer.VariableName = isUniformBlock ? buffer.Name.substr(pos, buffer.Name.length()).c_str() : buffer.Name.c_str();
				result.Data.push_back(buffer);
			}
		}
		uniformData = result;
		return result;
	}

	void Shader::CompileStart() {
		auto status = m_compileAsync.wait_for(0ms);
		if (status == std::future_status::ready) {
			// Done
			for (auto i : shader_stage) {
				i.second = ShaderCompileStage::Compiling;
			}
			m_compileAsync.get();
			m_message = "Compiling...";
		}
		else {
			// Not done yet
			m_compileAsync.wait();
			m_message = "Previous compile process not finish yet!";
		}
	}
	void Shader::CompileShader(ShaderType type) {
		// hmmmm
	}
	void Shader::CompileShaderGLSL(ShaderType type)
	{
		TARA_DEBUG("");
		TARA_DEBUG("Compile Shader... %s %s", Name.c_str(), Shadertype_string.at(type).c_str());
		int success;
		char infoLog[512];

		if (shader_program.count(type)) {
			glDeleteShader(shader_program[type]);
			shader_program[type] = -1;
		}
		int target = -1;
		TARA_DEBUG_LEVEL("#########################################################", 1);
		TARA_DEBUG_LEVEL("#\t\t\t%s %s\t\t\t#", 1, Shadertype_string.at(type).c_str(), "start");
		TARA_DEBUG_LEVEL("#########################################################", 1);
		TARA_DEBUG_LEVEL("", 1);

		target = glCreateShader(shadertype_target.at(type));
		const char* c_str = shader_code.at(type).c_str();
		glShaderSource(target, 1, &c_str, NULL);
		TARA_DEBUG_LEVEL("%s", 1, shader_code.at(type).c_str());
		TARA_DEBUG_LEVEL("", 1);
		TARA_DEBUG_LEVEL("#########################################################", 1);
		TARA_DEBUG_LEVEL("#\t\t\t%s %s\t\t\t#", 1, Shadertype_string.at(type).c_str(), "end");
		TARA_DEBUG_LEVEL("#########################################################", 1);
		shader_program[type] = target;

		static const char* const searchPath = "/";
		glCompileShaderIncludeARB(target, 1, &searchPath, nullptr);
		glCompileShader(target);
		// print compile errors if any
		glGetShaderiv(target, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(target, 512, NULL, infoLog);
			TARA_DEBUG_LEVEL("ERROR::Shader::%s::COMPILATION_FAILED\n%s", 4, Shadertype_string.at(type).c_str(), infoLog);
			glDeleteShader(shader_program[type]);
			shader_program[type] = -1;
			shader_stage[type] = ShaderCompileStage::Failed;
			return;
		};
		shader_stage[type] = ShaderCompileStage::Success;
	}

	bool Shader::ThreadCompile() {
		// ....
		return false;
	}
	bool Shader::ThreadCompileGLSL() {
		int success;
		char infoLog[512];

		if (shader_code.count(ShaderType::Vertex)) CompileShaderGLSL(ShaderType::Vertex);
		if (shader_code.count(ShaderType::Tessellation)) CompileShaderGLSL(ShaderType::Tessellation);
		if (shader_code.count(ShaderType::Fragment)) CompileShaderGLSL(ShaderType::Fragment);
		if (shader_code.count(ShaderType::Geometry)) CompileShaderGLSL(ShaderType::Geometry);
		if (shader_code.count(ShaderType::Compute)) CompileShaderGLSL(ShaderType::Compute);

		if (shader_program.count(ShaderType::Vertex)) glAttachShader(program, shader_program.at(ShaderType::Vertex));
		if (shader_program.count(ShaderType::Tessellation)) glAttachShader(program, shader_program.at(ShaderType::Tessellation));
		if (shader_program.count(ShaderType::Fragment)) glAttachShader(program, shader_program.at(ShaderType::Fragment));
		if (shader_program.count(ShaderType::Geometry)) glAttachShader(program, shader_program.at(ShaderType::Geometry));
		if (shader_program.count(ShaderType::Compute)) glAttachShader(program, shader_program.at(ShaderType::Compute));

		glLinkProgram(program);
		// print linking errors if any
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(program, 512, NULL, infoLog);
			m_message = "shader compile failed !";
			TARA_ERROR_LEVEL("ERROR::Shader::PROGRAM::LINKING_FAILED:%s\n%s", 4, Name.c_str(), infoLog);
			return success;
		}
		m_good = success;
		m_message = "successfully compiled !";
		for (auto cb : m_updateEvent) if (cb.first) cb.second();
		m_dirty = true;
		uniformData = Uniforms();
		m_dirty = false;
		PrintUniform();
		return success;
	}
#pragma endregion
	ShaderLibrary& ShaderLibrary::Singleton()
	{
		if (!m_Singleton) m_Singleton = new ShaderLibrary();
		return *m_Singleton;
	}
	bool ShaderLibrary::SupportExtension()
	{
		return glfwExtensionSupported("GL_ARB_shading_language_include");
	}
	bool ShaderLibrary::AddLibrary(const char* name, const char* path)
	{
		if (!std::filesystem::exists(path)) {
			TARA_WARNING_LEVEL("Cannot find shader library: %s, %s", 4, name, path);
			return false;
		}
		std::string code = Utility::File::LoadFromFile(path);
		AddLibraryFromMemory(name, code);
	}
	bool ShaderLibrary::AddLibraryFromMemory(const char* name, std::string code)
	{
		std::string n = "/" + std::string(name);
		glNamedStringARB(GL_SHADER_INCLUDE_ARB, n.size(), n.c_str(), code.size(), code.c_str());
		if (!NameExist(n.c_str())) {
			registerName.push_back(n.c_str());
			TARA_DEBUG_LEVEL("Add new shader library: %s \n%s", 2, name, code.c_str());
		}
		else {
			TARA_DEBUG_LEVEL("Replace shader library: %s", 2, name);
		}
		return true;
	}
	bool ShaderLibrary::RemoveLibrary(const char* name)
	{
		std::string n = "/" + std::string(name);
		glNamedStringARB(GL_SHADER_INCLUDE_ARB, n.size(), n.c_str(), NULL, NULL);
		TARA_DEBUG_LEVEL("Remove shader library: %s", 2, name);
		registerName.erase(std::remove(registerName.begin(), registerName.end(), n), registerName.end());
		return true;
	}
	bool ShaderLibrary::NameExist(const char* name)
	{
		std::string n = "/" + std::string(name);
		return std::find(registerName.begin(), registerName.end(), n) != registerName.end();
	}
	ShaderLibrary::ShaderLibrary() {

	}
};