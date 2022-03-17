#pragma once
// Include std library
#include <map>
#include <functional>
#include <future>
#include <thread>
#include <chrono>
#include <vector>

// Include third party library
#include <glm/glm.hpp>

// Include tara library
#include "../config.h"
#include "../asset.h"

/*

	Shader holds the program and functions which can get the shader information.
	Material class can base on that to create the properties and fields.
	It'll easier to manipulate shader data for material

*/

namespace Tara {
	/*
		Structures and classes
	*/
	class TARA_API Material;

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


	/*

		Summary:
			Shader handle the processes of creating program, compile shaders, loading shader files.
			You can use the complete compiled shader by calling "use()".
	*/
	class TARA_API Shader : public AssetBase
	{
	public:
		friend class Material;
		friend class BuildinManager;
		/*
			Summary:
				Create shader instance.
				This will generate shader program.
		*/
		Shader();
	protected:
		Shader(bool buildin);
	public:
		/*
			Summary:
				Destroy shader instance.
				This will delete shader program, and delete all exist shader buffers.
		*/
		~Shader();
		/*
			Summary:
				Shader update event.
				When shader compile finish this event will get call.
			Detail:
				When shader is compile done or recompile.
				The material who binding with this shader instance will get a update callback.
				It makes material update the exist properties.
		*/
		void RegisterUpdateEvent(Material* sender, std::function<void()> callback);
		/*
			Summary:
				Unregister shader update event.
				When shader compile finish this event will get call.
		*/
		void UnRegisterUpdateEvent(Material* sender);
		/*
			Summary:
				Use the shader program.
			Return:
				Return false if program is not compile yet.
		*/
		bool Use();
		/*
			Summary:
				Binding an empty pointer (fallback to default opengl shader).
		*/
		void Unuse();
		/*
			Summary:
				Compile the shader code to spri-v binary files asynchronously.
				Then read the shader binary from temp directory and build the shader program.
				You can check compile state by calling 'CompileState()'.
		*/
		void Compile();
		/*
			Summary:
				Compile the shader GLSL code and build the shader program.
		*/
		void CompileGLSL();
		/*
			Summary:
				Is shader program current exist or not.
				Is it safe to use this shader.
		*/
		bool Good();
		/*
			Summary:
				Check current compiling state.
		*/
		ShaderCompileStage CompileState();
		/*
			Summary:
				Delete shader code and buffers.
		*/
		void DeleteShader();
		/*
			Summary:
				Delete stored shader buffers.
		*/
		void DeleteShaderBuffer();
		/*
			Summary:
				Delete stored shader code.
		*/
		void DeleteShaderData();
		/*
			Summary:
				Load the shader code file from drive.
			Arugment:
				type: Shader type.
				filename: File path.
				useGLSL: 
					True: Load file text and store into 'shader_code'.
					False: Compile to spir-v binary file and read it into 'shader_binary'.
		*/
		virtual void SetShaderFromFile(ShaderType type, const char* filename, bool useGLSL = true);
		/*
			Summary:
				Load the shader code file from drive.
		*/
		virtual void SetShaderFromCode(ShaderType type, const char* code);
		/*
			Summary:
				Load the shader binary file from drive
		*/
		virtual void SetShaderFromBinary(ShaderType type, void* binary);
		/*
			Summary:
				Get the uniform location by name.
		*/
		int32_t GetUniformLocation(const char* name);
		/*
			Summary:
				Get the uniform block index by name.
		*/
		int32_t GetUniformBlockIndex(const char* name);
		/*
			Summary:
				Output shader location.
		*/
		void PrintUniform();
		/*
			Summary:
				Get all uniform info.
		*/
		ShaderUniformInformation Uniforms();

	protected:
		/*
			Summary:
				Compile start. this will check the compile mode.
				Spir-v: Asynchronously compile mode.
				GLSL: Compile use glfw build-in function.
		*/
		void CompileStart();
		/*
			Summary:
				Compile single spir-v shader.
				Grab memory from 'shader_binary' and build the shader buffer.
		*/
		void CompileShader(ShaderType type);
		/*
			Summary:
				Compile single GLSL shader.
				Grab source code from 'shader_code' and build the shader buffer.
			Notice: 
				This will assume 'shader_code' are all GLSL.
		*/
		void CompileShaderGLSL(ShaderType type);

	private:
		/*
			Summary:
				Main spir-v compile function.
		*/
		bool ThreadCompile();
		/*
			Summary:
				Main GLSL compile function.
		*/
		bool ThreadCompileGLSL();
		// Is the shader program exist, good to use.
		bool m_good = false;
		// Is shader currently waiting for update,
		bool m_dirty = false;
		// Register update function.
		std::map<Material*, std::function<void()>> m_updateEvent = std::map<Material*, std::function<void()>>();
		// Shader output message.
		std::string m_message = "";
		// Current compile mode.
		ShaderCompileMode m_mode = ShaderCompileMode::SpirV;
		// Shader compile processing.
		std::future<bool> m_compileAsync;
		// Shader program.
		int32_t program = -1;
		/*
			Shader store information
		*/
		// Shader buffer program.
		std::map<ShaderType, int32_t> shader_program = std::map<ShaderType, int32_t>();
		// Shader source code.
		std::map<ShaderType, std::string> shader_code = std::map<ShaderType, std::string>();
		// Shader templ file name.
		std::map<ShaderType, std::string> shader_temp_name = std::map<ShaderType, std::string>();
		// Shader binary data.
		std::map<ShaderType, void*> shader_binary = std::map<ShaderType, void*>();
		// Each shader compile stage.
		std::map<ShaderType, ShaderCompileStage> shader_stage = std::map<ShaderType, ShaderCompileStage>();
		// Uniform information.
		// Material will require this pieces of information to create properties.
		// This information will update when compile is finish.
		ShaderUniformInformation uniformData = ShaderUniformInformation();
	};


	/*
		Summary:
			The shader code that is commomly use.
			For other shader script to include.
	*/
	class TARA_API ShaderLibrary {
	public:
		static ShaderLibrary& Singleton();

		bool SupportExtension();
		bool AddLibrary(const char* name, const char* path);
		bool AddLibraryFromMemory(const char* name, std::string data);
		bool RemoveLibrary(const char* name);
		bool NameExist(const char* name);
	private:
		ShaderLibrary();
		static ShaderLibrary* m_Singleton;

		std::vector<std::string> registerName = std::vector<std::string>();
	};

	inline TARA_API ShaderLibrary* ShaderLibrary::m_Singleton = new ShaderLibrary;
}