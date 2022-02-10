#pragma once
#include <map>
#include <vector>
#include <config.h>
#include <asset.h>
#include <glm/glm.hpp>

namespace Tara {
	/*
		Summary:
			Uniform type.
	*/
	enum class DllExport ShaderUniformType {
		Float,
		Double,
		Int,
		UInt,
		Bool,

		Vec2,
		Vec3,
		Vec4,
		BVec2,
		BVec3,
		BVec4,
		DVec2,
		DVec3,
		DVec4,
		IVec2,
		IVec3,
		IVec4,
		UVec2,
		UVec3,
		UVec4,

		Mat2,
		Mat3,
		Mat4,
		Mat2x3,
		Mat2x4,
		Mat3x2,
		Mat3x4,
		Mat4x2,
		Mat4x3,
		DMat2,
		DMat3,
		DMat4,
		DMat2x3,
		DMat2x4,
		DMat3x2,
		DMat3x4,
		DMat4x2,
		DMat4x3,

		Texture1D,
		Texture2D,
		Texture3D,
		TextureCube,
		Texture1DShadow,
		Texture2DShadow,
		Texture1DArray,
		Texture2DArray,
		Texture2DRect,
		Texture2DRectShadow,
		Texture2DMultisample,
		Texture2DMultisampleArray,
		Texture1DShadowArray,
		Texture2DShadowArray,
		ITexture1D,
		ITexture2D,
		ITexture3D,
		ITextureCube,
		ITexture1DArray,
		ITexture2DArray,
		ITexture2DRect,
		ITexture2DMultisample,
		ITexture2DMultisampleArray,
		UTexture1D,
		UTexture2D,
		UTexture3D,
		UTextureCube,
		UTexture1DArray,
		UTexture2DArray,
		UTexture2DRect,
		UTexture2DMultisample,
		UTexture2DMultisampleArray,
	};


	/*
		Summary:
			Shader types.
	*/
	enum class DllExport ShaderType {
		Vertex,
		Tessellation,
		Fragment,
		Geometry,
		Compute
	};
	

	/*
		Summary:
			Buildin shader type.
	*/
	enum class DllExport CommonShader {
		Error,
		Color,
		Gradient,
		Texture,
#ifndef TARA_NO_BUILDIN_3D
		Lambert,
		Blinn,
		GGX,
		Toon,
#endif
		DefaultPostprocess
	};


	/*
		Summary:
			Generate default shaders.
	*/
	DllExport void CreateDefaultShaders();


	/*
		Summary:
			A container store uniform information.
	*/
	struct DllExport ShaderUniform {
	public:
		std::string Name;
		int32_t Location;
		int32_t Size;
		int32_t Length;
		ShaderUniformType Type;
	};


	/*

		Summary:
			Shader handle the processes of creating program, compile shaders, loading shader files.
			You can use the complete compiled shader by calling "use()".
	*/
	class DllExport Shader : public AssetBase
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
		/*
			Summary:
				Compile the shader code and build the shader program.
		*/
		bool Compile();
		/*
			Summary:
				Delete shader code string and buffer.
		*/
		void DeleteShader();
		/*
			Summary:
				Delete stored shader buffer.
		*/
		void DeleteShaderBuffer();
		/*
			Summary:
				Delete stored shader code string.
		*/
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

		/*
			Summary:
				Delete stored shader code string.
		*/
		int32_t GetUniformLocation(const char* name);
		/*
			Summary:
				Output shader location.
		*/
		void PrintUniform();
		/*
			Summary:
				Get all uniform info.
		*/
		std::vector<ShaderUniform> Uniforms();

	protected:
		void CompileShader(ShaderType type);

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