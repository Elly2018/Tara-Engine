#pragma once
#include "../config.h"

namespace Tara {
	/*
		Summary:
			Shader uniform content.
			Specifie uniform detail information.
	*/
	struct TARA_API ShaderUniformContent {
	public:
		// Uniform fullname.
		std::string Name;
		// Uniform type name.
		std::string TypeName;
		// Variable name, without block name prefix.
		std::string VariableName;
		// Uniform type.
		ShaderUniformType Type;
		// Index of uniform
		int32_t Index;
		// Location or offset position.
		int32_t Location;
		// The size of this uniform.
		size_t Size;
	};


	/*
		Summary:
			Shader uniform block information.
			Content the detail about the shader uniform block.
	*/
	struct TARA_API ShaderUniformBlockInformation {
	public:
		// Uniform block name
		std::string BlockName;
		// Uniform block total size
		size_t Size;
		// Uniform index, ignore this if you're using global uniform block.
		int32_t Index;
		// Content of uniform block
		std::vector<ShaderUniformContent> Content;
	};


	/*
		Summary:
			Shader uniform information.
			The full pack of uniform information about the shader.
	*/
	struct TARA_API ShaderUniformInformation {
	public:
		// Uniform block info
		std::vector<ShaderUniformBlockInformation> BlockData;
		// Uniform info
		std::vector<ShaderUniformContent> Data;
	};
}