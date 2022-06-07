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
#include "shader_enum.h"
#include "shader_struct.h"

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
}