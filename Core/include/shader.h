#pragma once
#include <map>
#include <vector>
#include <config.h>
#include <asset.h>
#include <glm/glm.hpp>

namespace Tara {
	/*

		Structs, classes declaration

	*/
	class DllExport Shader;

	/// <summary>
	/// Shader types
	/// </summary>
	DllExport enum class ShaderType {
		Vertex,
		Tessellation,
		Fragment,
		Geometry,
		Compute
	};
	/// <summary>
	/// Common shader type (Build-in)
	/// </summary>
	DllExport enum class CommonShader {
		Color,
		Gradient,
		Texture,
		DefaultPostprocess
	};

	/*
		Summary:
			Generate default shaders.
	*/
	DllExport void CreateDefaultShaders();

	/*
		Summary:
			Shader handle the processes of creating program, compile shaders, loading shader files.
			You can use the complete compiled shader by calling "use()".
	*/
	class Shader : public AssetBase
	{
	public:
		friend class Material;
		Shader();
		~Shader();
		/*
			Summary:
				Generate common use shader.
		*/
		static Shader* GetCommon(CommonShader type);
		/*
			Summary:
				Generate pure color shader (Build-In).
		*/
		static Shader* GetColorShader();
		/*
			Summary:
				Generate gradient shader (Build-In).
		*/
		static Shader* GetGradientShader();
		/*
			Summary:
				Generate gradient shader (Build-In).
		*/
		static Shader* GetTextureShader();
		/*
			Summary:
				Generate default post process shader (Build-In).
		*/
		static Shader* GetDefaultPostprocessShader();
		/*
			Summary:
				Get asset pool
		*/
		static AssetPool<Shader>* GetAssetPool();

		/*
			Summary:
				Use the shader program.
		*/
		void Use();
		/*
			Summary:
				Binding an empty pointer (fallback to default opengl shader).
		*/
		void Unuse();
		/// <returns>Success</returns>
		/*
			Summary:
				Compile the shader code and build the shader program.
		*/
		bool Compile();
		void DeleteShader();
		void DeleteShaderBuffer();
		void DeleteShaderString();

		virtual void SetVertexFromFile(const char* filename);
		virtual void SetVertexFromCode(const char* code);
		virtual void SetTessellationFromFile(const char* filename);
		virtual void SetTessellationFromCode(const char* code);
		virtual void SetFragmentFromFile(const char* filename);
		virtual void SetFragmentFromCode(const char* code);
		virtual void SetGeometryFromFile(const char* filename);
		virtual void SetGeometryFromCode(const char* code);
		virtual void SetComputeFromFile(const char* filename);
		virtual void SetComputeFromCode(const char* code);

		int GetUniformLocation(const char* name);
		void PrintUniform();

	protected:
		void CompileShader(ShaderType type);
		std::string LoadFromFile(const char* filename);

		int program = -1;
		int vertex = -1;
		int tessellation = -1;
		int fragment = -1;
		int geometry = -1;
		int compute = -1;

		std::string vertex_code = std::string();
		std::string tessellation_code = std::string();
		std::string fragment_code = std::string();
		std::string geometry_code = std::string();
		std::string compute_code = std::string();

	private:
		static AssetPool<Shader>* m_shaderPool;
	};
}