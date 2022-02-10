#include "buildin/buildin.h"

namespace Tara {
	#pragma region Prefix
	std::string PREFIX_V = ""
		"#version 420\n"
		"layout(location = 0) in vec3 aPos;\n"
		"layout(location = 1) in vec3 aNormal;\n"
		"layout(location = 2) in vec2 aTex;\n"
		"out vec2 Tex;\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"";
	std::string PREFIX_F = ""
		"#version 420\n"
		"in vec2 Tex;\n"
		"out vec4 FragColor;\n";
#pragma endregion

	#pragma region Error
	std::string SHADER_ERROR_VERT = ""
		"void main()\n"
		"{\n"
		"	gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
		"	Tex = aTex;\n"
		"}\n";
	std::string SHADER_ERROR_FRAG = ""
		"void main()\n"
		"{\n"
		"FragColor = vec4(1.0, 0.0, 1.0, 1.0);\n"
		"}\n";
	#pragma endregion

	#pragma region Pure Color
	std::string SHADER_COLOR_VERT = ""
		"void main()\n"
		"{\n"
		"	gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
		"	Tex = aTex;\n"
		"}\n";
	std::string SHADER_COLOR_FRAG = ""
		"uniform vec3 color;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(color, 1.0);\n"
		"}\n";
	#pragma endregion

	std::string SHADER_GRADIENT_VERT = "";
	std::string SHADER_GRADIENT_FRAG = "";
	std::string SHADER_TEXTURE_VERT = "";
	std::string SHADER_TEXTURE_FRAG = "";
	std::string SHADER_LAMBERT_VERT = "";
	std::string SHADER_LAMBERT_FRAG = "";
	std::string SHADER_BLINN_VERT = "";
	std::string SHADER_BLINN_FRAG = "";
	std::string SHADER_GGX_VERT = "";
	std::string SHADER_GGX_FRAG = "";
	std::string SHADER_TOON_VERT = "";
	std::string SHADER_TOON_FRAG = "";
	std::string SHADER_DefaultPostprocess_VERT = "";
	std::string SHADER_DefaultPostprocess_FRAG = "";

	std::string BuildInShader::Error_V() {
		return SHADER_ERROR_VERT;
	}
	std::string BuildInShader::Error_F()
	{
		return SHADER_ERROR_FRAG;
	}
	std::string BuildInShader::Color_V()
	{
		return SHADER_COLOR_VERT;
	}
	std::string BuildInShader::Color_F()
	{
		return SHADER_COLOR_FRAG;
	}
	std::string BuildInShader::Gradient_V()
	{
		return std::string();
	}
	std::string BuildInShader::Gradient_F()
	{
		return std::string();
	}
	std::string BuildInShader::Texture_V()
	{
		return std::string();
	}
	std::string BuildInShader::Texture_F()
	{
		return std::string();
	}
	std::string BuildInShader::Lambert_V()
	{
		return std::string();
	}
	std::string BuildInShader::Lambert_F()
	{
		return std::string();
	}
	std::string BuildInShader::Blinn_V()
	{
		return std::string();
	}
	std::string BuildInShader::Blinn_F()
	{
		return std::string();
	}
	std::string BuildInShader::GGX_V()
	{
		return std::string();
	}
	std::string BuildInShader::GGX_F()
	{
		return std::string();
	}
	std::string BuildInShader::Toon_V()
	{
		return std::string();
	}
	std::string BuildInShader::Toon_F()
	{
		return std::string();
	}
	std::string BuildInShader::DefaultPostprocess_V()
	{
		return std::string();
	}
	std::string BuildInShader::DefaultPostprocess_F()
	{
		return std::string();
	}
}