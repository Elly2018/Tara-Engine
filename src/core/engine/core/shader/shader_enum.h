#pragma once
#include "../config.h"

namespace Tara {
	/*
		Summary:
			Define current shader compiling stage.
			This compile stage will only use it when shader use spir-v compile mode.
	*/
	enum class TARA_API ShaderCompileStage {
		// Not compile right now.
		None,
		// Compiling.
		Compiling,
		// Successfully compile.
		Success,
		// Something went wrong.
		Failed,
	};


	/*
		Summary:
			Define shader compile mode.
	*/
	enum class TARA_API ShaderCompileMode {
		/*
			Summary:
				It will looking for 'glslc.exe' program file to run asynchronous compile function.
				Input shader code will create temp spir-v binary files in directory 'temp' with same name as shader resource name.
				After compile is done, it reads shader binary files to compile it. then delete the temp files afterward.
		*/
		SpirV,
		/*
			Summary:
				Use GLFW buildin shader compile. this will not trigger asynchronous compile.
		*/
		GLSL
	};


	/*
		Summary:
			Uniform type.
	*/
	enum class TARA_API ShaderUniformType {
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
	enum class TARA_API ShaderType {
		Vertex = 1,
		Tessellation = 2,
		Fragment = 4,
		Geometry = 8,
		Compute = 16,
		Commom = 32
	};
}