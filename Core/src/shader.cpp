#include "Shader.h"
#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <utility.h>
#include <buildin/buildin.h>

// Use shader file to test buildin shader
#define USE_SHADER_FILE

namespace Tara {
	#ifdef USE_SHADER_FILE
	#define FILE_ERROR_V ".\\Resources\\Error.vert"
	#define FILE_ERROR_F ".\\Resources\\Error.frag"
	#define FILE_PURE_COLOR_V ".\\Resources\\PureColor.vert"
	#define FILE_PURE_COLOR_F ".\\Resources\\PureColor.frag"
	#define FILE_GRADIENT_V ".\\Resources\\Gradient.vert"
	#define FILE_GRADIENT_F ".\\Resources\\Gradient.frag"
	#define FILE_TEXTURE_V ".\\Resources\\Texture.vert"
	#define FILE_TEXTURE_F ".\\Resources\\Texture.frag"
	#define FILE_LAMBERT_V ".\\Resources\\Lambert.vert"
	#define FILE_LAMBERT_F ".\\Resources\\Lambert.frag"
	#define FILE_BLINN_V ".\\Resources\\Blinn.vert"
	#define FILE_BLINN_F ".\\Resources\\Blinn.frag"
	#define FILE_GGX_V ".\\Resources\\GGX.vert"
	#define FILE_GGX_F ".\\Resources\\GGX.frag"
	#define FILE_TOON_V ".\\Resources\\Toon.vert"
	#define FILE_TOON_F ".\\Resources\\Toon.frag"
	#define FILE_DEFAULT_POSTPROCESS_V ".\\Resources\\DefaultPostProcess.vert"
	#define FILE_DEFAULT_POSTPROCESS_F ".\\Resources\\DefaultPostProcess.frag"
	#endif // USE_SHADER_FILE

	#pragma region BuildIn Getter
	Shader* GetFromBuildIn(std::string v, std::string f) {
		Shader* buffer = new Shader();
#ifdef USE_SHADER_FILE
		buffer->SetVertexFromFile(v.c_str());
		buffer->SetFragmentFromFile(f.c_str());
#else
		buffer->SetVertexFromCode(v.c_str());
		buffer->SetFragmentFromCode(f.c_str());
#endif
		bool success = buffer->Compile();
		if (success) buffer->DeleteShader();
		return buffer;
	}
	Shader* GetErrorShader()
	{
#ifdef USE_SHADER_FILE
		return GetFromBuildIn(FILE_ERROR_V, FILE_ERROR_F);	
#else
		return GetFromBuildIn(BuildInShader::Error_V(), BuildInShader::Error_F());
#endif
	}
	Shader* GetColorShader()
	{
#ifdef USE_SHADER_FILE
		return GetFromBuildIn(FILE_PURE_COLOR_V, FILE_PURE_COLOR_F);
#else
		return GetFromBuildIn(BuildInShader::Color_V(), BuildInShader::Color_F());
#endif
	}
	Shader* GetGradientShader()
	{
#ifdef USE_SHADER_FILE
		return GetFromBuildIn(FILE_GRADIENT_V, FILE_GRADIENT_F);
#else
		return GetFromBuildIn(BuildInShader::Gradient_V(), BuildInShader::Gradient_F());
#endif
	}
	Shader* GetTextureShader()
	{
#ifdef USE_SHADER_FILE
		return GetFromBuildIn(FILE_TEXTURE_V, FILE_TEXTURE_F);
#else
		return GetFromBuildIn(BuildInShader::Texture_V(), BuildInShader::Texture_F());
#endif
	}
	Shader* GetDefaultPostprocessShader()
	{
#ifdef USE_SHADER_FILE
		return GetFromBuildIn(FILE_DEFAULT_POSTPROCESS_V, FILE_DEFAULT_POSTPROCESS_F);
#else
		return GetFromBuildIn(BuildInShader::DefaultPostprocess_V(), BuildInShader::DefaultPostprocess_F());
#endif
	}
	#ifndef TARA_NO_BUILDIN_3D
	// 3D shader generate todo function
	Shader* GetLambert() {
#ifdef USE_SHADER_FILE
		return GetFromBuildIn(FILE_LAMBERT_V, FILE_LAMBERT_F);
#else
		return GetFromBuildIn(BuildInShader::Lambert_V(), BuildInShader::Lambert_F());
#endif
	}
	Shader* GetBlinn() {
#ifdef USE_SHADER_FILE
		return GetFromBuildIn(FILE_BLINN_V, FILE_BLINN_F);
#else
		return GetFromBuildIn(BuildInShader::Blinn_V(), BuildInShader::Blinn_F());
#endif
	}
	Shader* GetGGX() {
#ifdef USE_SHADER_FILE
		return GetFromBuildIn(FILE_GGX_V, FILE_GGX_F);
#else
		return GetFromBuildIn(BuildInShader::GGX_V(), BuildInShader::GGX_F());
#endif
	}
	Shader* GetToon() {
#ifdef USE_SHADER_FILE
		return GetFromBuildIn(FILE_TOON_V, FILE_TOON_F);
#else
		return GetFromBuildIn(BuildInShader::Toon_V(), BuildInShader::Toon_F());
#endif
	}
	#endif
	#pragma endregion

	#pragma region Const Static Declaration
	std::map<ShaderType, std::string> Shadertype_string = {
		{ShaderType::Vertex, "VERTEX"},
		{ShaderType::Tessellation, "TESSELLATION"},
		{ShaderType::Fragment, "FRAGMENT"},
		{ShaderType::Geometry, "GEOMETRY"},
		{ShaderType::Compute, "COMPUTE"}
	};
	std::map<ShaderUniformType, uint32_t> uniformMap = {
		{ShaderUniformType::Float, GL_FLOAT},
		{ShaderUniformType::Double, GL_DOUBLE},
		{ShaderUniformType::Int, GL_INT},
		{ShaderUniformType::Int, GL_UNSIGNED_INT},
		{ShaderUniformType::Bool, GL_BOOL},

		{ShaderUniformType::Vec2, GL_FLOAT_VEC2},
		{ShaderUniformType::Vec3, GL_FLOAT_VEC3},
		{ShaderUniformType::Vec4, GL_FLOAT_VEC3},
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
	const std::map<CommonShader, std::pair<std::string, std::function<Shader* ()>>> shader_commonMap = {
		{CommonShader::Error, {"Error Shader", GetErrorShader}},
		{CommonShader::Color, {"Color Shader", GetColorShader}},
		{CommonShader::Gradient, {"Gradient Shader", GetGradientShader}},
		{CommonShader::Texture, {"Texture Shader", GetTextureShader}},
	#ifndef TARA_NO_BUILDIN_3D
		{CommonShader::Lambert, {"Lambert Shader", GetLambert}},
		{CommonShader::Blinn, {"Blinn Shader", GetBlinn}},
		{CommonShader::GGX, {"GGX Shader", GetGGX}},
		{CommonShader::Toon, {"Toon Shader", GetToon}},
	#endif
		{CommonShader::DefaultPostprocess, {"Default Postprocess", GetDefaultPostprocessShader}},
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
#ifndef TARA_NO_BUILDIN_3D
		TARA_DEBUG_LEVEL("Buildin resources shader create: Lambert", 1);
		Shader::GetCommon(CommonShader::Lambert);
		TARA_DEBUG_LEVEL("Buildin resources shader create: Blinn", 1);
		Shader::GetCommon(CommonShader::Blinn);
		TARA_DEBUG_LEVEL("Buildin resources shader create: GGX", 1);
		Shader::GetCommon(CommonShader::GGX);
		TARA_DEBUG_LEVEL("Buildin resources shader create: Toon", 1);
		Shader::GetCommon(CommonShader::Toon);
#endif
		TARA_DEBUG_LEVEL("Buildin resources shader create: Postprocess", 1);
		Shader::GetCommon(CommonShader::DefaultPostprocess);
	}

	Shader::Shader()
	{
		TARA_DEBUG_LEVEL("Shader created!", 1);
		program = glCreateProgram();
		TARA_DEBUG_LEVEL("\tShader pool add!", 1);
		GetAssetPool()->Add(*this);
	}
	Shader::~Shader()
	{
		TARA_DEBUG_LEVEL("Shader destroy! %s", 1, Name().c_str());
		glDeleteProgram(program);
		TARA_DEBUG_LEVEL("\tShader buffer destroy! %s", 1, Name().c_str());
		DeleteShader();
	}
	Shader* Shader::GetCommon(CommonShader type)
	{
		if (!shader_commonMap.count(type)) {
			TARA_WARNING_LEVEL("Commom shader does not register:", 3);
			return nullptr;
		}
		auto cgs = shader_commonMap.at(type);
		Shader* s = GetAssetPool()->FindByName(cgs.first.c_str(), true);
		if (s == nullptr) {
			s = cgs.second();
			s->Name() = cgs.first;
			s->BuildIn() = true;
		}
		else {
			return s;
		}
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
			TARA_ERROR_LEVEL("ERROR::Shader::PROGRAM::LINKING_FAILED:%s\n%s", 4, Name().c_str(), infoLog);
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
		vertex_code = Utility::File::LoadFromFile(filename).c_str();
	}
	void Shader::SetVertexFromCode(const char* code)
	{
		vertex_code = strdup(code);
	}
	void Shader::SetTessellationFromFile(const char* filename)
	{
		tessellation_code = Utility::File::LoadFromFile(filename).c_str();
	}
	void Shader::SetTessellationFromCode(const char* code)
	{
		tessellation_code = strdup(code);
	}
	void Shader::SetFragmentFromFile(const char* filename)
	{
		fragment_code = Utility::File::LoadFromFile(filename).c_str();
	}
	void Shader::SetFragmentFromCode(const char* code)
	{
		fragment_code = strdup(code);
	}
	void Shader::SetGeometryFromFile(const char* filename)
	{
		geometry_code = Utility::File::LoadFromFile(filename).c_str();
	}
	void Shader::SetGeometryFromCode(const char* code)
	{
		geometry_code = strdup(code);
	}
	void Shader::SetComputeFromFile(const char* filename)
	{
		compute_code = Utility::File::LoadFromFile(filename).c_str();
	}
	void Shader::SetComputeFromCode(const char* code)
	{
		compute_code = strdup(code);
	}

	int32_t Shader::GetUniformLocation(const char* name)
	{
		return glGetUniformLocation(program, name);
	}
	void Shader::PrintUniform()
	{
		std::vector<ShaderUniform> info = Uniforms();
		TARA_DEBUG("Print shader uniform: %s", Name().c_str());
		for (auto m : info) {
			TARA_DEBUG("\tUniform name: %s", m.Name.c_str());
			TARA_DEBUG("\t\tUniform name: %i", m.Length);
			TARA_DEBUG("\t\tsize: %i", m.Size);
			TARA_DEBUG("\t\ttype: %s", uniformString.at(m.Type));
			TARA_DEBUG("\t\tlocation: %i", m.Location);
		}
	}
	std::vector<ShaderUniform> Shader::Uniforms()
	{
		int32_t count;
		std::vector<ShaderUniform> result = std::vector<ShaderUniform>();
		glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &count);
		for (int32_t i = 0; i < count; i++)
		{
			char bufSize[64];
			int32_t length = 0;
			int32_t	size = 0;
			uint32_t type = 0;
			glGetActiveUniform(program, i, sizeof(bufSize), &length, &size, &type, bufSize);

			ShaderUniform buffer = ShaderUniform();
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
			buffer.Location = glGetUniformLocation(program, buffer.Name.c_str());
			buffer.Length = length;
			buffer.Size = size;
			result.push_back(buffer);
		}
		return result;
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
};