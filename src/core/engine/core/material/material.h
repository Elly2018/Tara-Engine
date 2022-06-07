#pragma once
// Include std library
#include <map>

// Include third party library
#include <glm/glm.hpp>

// Include tara library
#include "../config.h"
#include "../asset.h"
#include "../shader/shader.h"

/*

	Material mainly handles the drawing shader properties.
	It grabs structure information from shader and create workers to handle each uniform block.

*/

/*
	Summary:
		A macro that helper to create uniform function declaration.
*/
#pragma region Macro Declaration
#define MATERIAL_UNIFORM_BLOCK_SETTER(name, type)\
	void Set##name (const char* varName, type v, const int32_t index = 0);\

#define MATERIAL_UNIFORM_BLOCK_GETTER(name, type)\
	const type Get##name (const char* varName, const int32_t index = 0);\

#define MATERIAL_FUNCTION_SETTER(name, type)\
	void Set##name (const char* fullname, type v, const int32_t index = 0);\
	void Set##name (const char* blockname, const char* varName, type v, int index = 0);\

#define MATERIAL_FUNCTION_GETTER(name, type)\
	const type Get##name (const char* fullname, const int32_t index = 0);\
	const type Get##name (const char* blockname, const char* varName, const int index = 0);\

#pragma endregion

namespace Tara {
	/*
		Structures and classes
	*/
	class TARA_API Texture2D;
	class TARA_API TextureCube;

	enum class TARA_API ShaderUniformType;

	/*
		Summary:
			Use blend mode.
	*/
	enum class TARA_API MaterialBlendMode {
		Zero,
		One,
		Src_Color,
		One_Minus_Src_Color,
		Dst_Color,
		One_Minus_Dst_Color,
		Src_Alpha,
		One_Minus_Src_Alpha,
		Dst_Alpha,
		One_Minus_Dst_Alpha,
		Const_Color,
		One_Minus_Const_Color,
		Const_Alpha,
		One_Minus_Const_Alpha,
	};


	/*
		Summary:
			Material category.
	*/
	enum class TARA_API MaterialDomain {
		Surface,
		PostProcessing
	};


	/*
		Summary:
			Use shaded, It will effect the uniform block it's binding
	*/
	enum class TARA_API MaterialShadedMode {
		Unlit,
		Lit,
	};


	enum class TARA_API CommomMaterialType {
		Error,
		Color,
		Normal,
		Reflection,
		DirectionalShadow,
		PointShadow
	};

	enum class TARA_API STD140UnifromBlock {
		Model,
		Utility,
		LightData,
		LightMatrix
	};


	/*
		Summary:
			Uniform block worker.
	*/
	class TARA_API MaterialUniformBlock {
	public:
		friend class Material;
		/*
			Summary:
				Create an empty uniform block buffer.
				You can update this by calling 'Update(ShaderUniformBlockInformation)'.
		*/
		MaterialUniformBlock();
		/*
			Summary:
				Create uniform block buffer worker.
		*/
		MaterialUniformBlock(ShaderUniformBlockInformation& blockInformation);
		~MaterialUniformBlock();
		/*
			Summary:
				Update the structure of this uniform block.
				Previous data keep it, during the restructure. (If the name and type and size is the same though)
		*/
		void Update(ShaderUniformBlockInformation updateInfo);
		/*
			Summary:
				Clean the binding memory.
		*/
		void SetToDefault();
		/*
			Summary:
				Raw set data function
		*/
		void SetData(const char* varName, void* v, const int index);

		/*
			Summary:
				Build-in value setter and getter function.
				If these type does not match your require, you can use 'SetData' raw function to send to data.
				Be cateful the layout though.
		*/
		#pragma region Setter Getter
		MATERIAL_UNIFORM_BLOCK_SETTER(Bool, bool);
		MATERIAL_UNIFORM_BLOCK_SETTER(Int, int32_t);
		MATERIAL_UNIFORM_BLOCK_SETTER(Float, float_t);
		MATERIAL_UNIFORM_BLOCK_SETTER(Vec2, glm::vec2);
		MATERIAL_UNIFORM_BLOCK_SETTER(Vec3, glm::vec3);
		MATERIAL_UNIFORM_BLOCK_SETTER(Vec4, glm::vec4);
		MATERIAL_UNIFORM_BLOCK_SETTER(Mat3, glm::mat3);
		MATERIAL_UNIFORM_BLOCK_SETTER(Mat4, glm::mat4);

		MATERIAL_UNIFORM_BLOCK_GETTER(Bool, bool);
		MATERIAL_UNIFORM_BLOCK_GETTER(Int, int32_t);
		MATERIAL_UNIFORM_BLOCK_GETTER(Float, float_t);
		MATERIAL_UNIFORM_BLOCK_GETTER(Vec2, glm::vec2);
		MATERIAL_UNIFORM_BLOCK_GETTER(Vec3, glm::vec3);
		MATERIAL_UNIFORM_BLOCK_GETTER(Vec4, glm::vec4);
		MATERIAL_UNIFORM_BLOCK_GETTER(Mat3, glm::mat3);
		MATERIAL_UNIFORM_BLOCK_GETTER(Mat4, glm::mat4);
		#pragma endregion

		/*
			Summary:
				Get uniform block ID.
		*/
		uint32_t BlockID();
		/*
			Summary:
				Get uniform block index.
				This only useful when it's specified user define shader properties.
		*/
		uint32_t Index();
		/*
			Summary:
				Get uniform block total size.
		*/
		size_t Size();

	private:
		// Variable name, [info]
		std::map<std::string, std::vector<ShaderUniformContent>> m_data = std::map<std::string, std::vector<ShaderUniformContent>>();
		// Block information
		ShaderUniformBlockInformation m_blockInformation = ShaderUniformBlockInformation();
		// Block ID
		uint32_t m_blockID = -1;
	};


	struct TARA_API MaterialConfig {
	public:
		MaterialDomain Domain = MaterialDomain::Surface;
		bool UseBlend = true;
		MaterialBlendMode BlendSrc = MaterialBlendMode::One;
		MaterialBlendMode BlendDst = MaterialBlendMode::Zero;
		MaterialBlendMode BlendAlphaSrc = MaterialBlendMode::One;
		MaterialBlendMode BlendAlphaDst = MaterialBlendMode::Zero;
		MaterialShadedMode Shaded = MaterialShadedMode::Unlit;
		bool TwoSide = false;
		int32_t RenderQueue = 3000;
	};

	/*
		Summary:
			The container for shader, store uniform data.
			When 'use()' is call, it will send all the uniform buffer.
	*/
	class TARA_API Material final : public AssetBase {
	public:
		friend class Renderer;
		friend class BatchRenderer;
		friend class RendererDebug;
		friend class EWindow;
		friend class MeshRendererComponent;
		friend class Shader;
		Material(Shader& _shader);
	protected:
		Material(bool buildin, Shader& _shader);
	public:
		~Material();

		/*
			Summary:
				Get asset pool
		*/
		static AssetPool<Material>& GetAssetPool();
		
		/*
			Summary:
				Generate global buffer.
		*/
		static void MaterialInitialization();
		/*
			Summary:
				Create a copy of this material.
		*/
		Material& Clone();
		/*
			Summary:
				Use the shader program.
				And sending all the uniform buffer.
		*/
		void Use();
		/*
			Summary:
				Unuse the shader program.
		*/
		void Unuse();
		/*
			Summary:
				Get material binding shader.
		*/
		Shader& GetShader();
		MaterialConfig& Config();
		/*
			Summary:
				Apply the shader setting.
				Restructure the uniform block worker, and binding the entry point for each uniform blocks.
				Depends on the material setting 'm_useBuildinBufferIndex' will count how many build-in block has use.
				The final m_useBuildinBufferIndex value will become the initial value for user define uniform blocks entry point.
		*/
		void Apply();

		#ifndef TARA_NO_IMGUI
		/*
			Summary:
				Draw all the material properties on GUI.
		*/
		void GUI();
		#endif // !TARA_NO_IMGUI

		/*
			Summary:
				Set texture uniform by name.
		*/
		void SetTexture2D(const char* name, Texture2D* v);
		void SetTexture2D(const char* name, uint32_t v);

		void SetTextureCube(const char* name, TextureCube* v);
		void SetTextureCube(const char* name, uint32_t v);
		void RemoveTexture(const char* name);
		/*
			Summary:
				Get texture instance by name.
		*/
		uint32_t GetTexture(const char* name);

		/*
			Summary:
				Build-in material setter and getter.
				If this is not enough you can use 'SetData', 'GetData' raw function.
		*/
		#pragma region Material Setter Getter
		MATERIAL_FUNCTION_SETTER(Bool, bool);
		MATERIAL_FUNCTION_SETTER(Int, int32_t);
		MATERIAL_FUNCTION_SETTER(Float, float_t);
		MATERIAL_FUNCTION_SETTER(Vec2, glm::vec2);
		MATERIAL_FUNCTION_SETTER(Vec3, glm::vec3);
		MATERIAL_FUNCTION_SETTER(Vec4, glm::vec4);
		MATERIAL_FUNCTION_SETTER(Mat3, glm::mat3);
		MATERIAL_FUNCTION_SETTER(Mat4, glm::mat4);

		
		MATERIAL_FUNCTION_GETTER(Bool, bool);
		MATERIAL_FUNCTION_GETTER(Int, int32_t);
		MATERIAL_FUNCTION_GETTER(Float, float_t);
		MATERIAL_FUNCTION_GETTER(Vec2, glm::vec2);
		MATERIAL_FUNCTION_GETTER(Vec3, glm::vec3);
		MATERIAL_FUNCTION_GETTER(Vec4, glm::vec4);
		MATERIAL_FUNCTION_GETTER(Mat3, glm::mat3);
		MATERIAL_FUNCTION_GETTER(Mat4, glm::mat4);
		#pragma endregion

	private:
		/*
			Summary:
				Send texture buffer by name.
		*/
		void UniformTexture2D(const char* name, Texture2D& v, int32_t binding);
		/*
			Summary:
				Send texture buffer by name.
		*/
		void UniformTexture2D(const char* name, const uint32_t v, int32_t binding);
		/*
			Summary:
				Send texture buffer by name.
		*/
		void UniformTextureCube(const char* name, TextureCube& v, int32_t binding);
		/*
			Summary:
				Send texture buffer by name.
		*/
		void UniformTextureCube(const char* name, const uint32_t v, int32_t binding);
		/*
			Summary:
				Print the uniform information in console
		*/
		void PrintUniformLocations();
		/*
			Summary:
				Clean all uniform data.
		*/
		void CleanUniform();
		/*
			Summary:
				This will recreate the uniform buffer.
				Previous data with same data will keep it.
		*/
		void ShaderUpdateCallback();
		/*
			Summary:
				Split string by character '.'
				If character not exist it will just return the full string.
		*/
		std::pair<std::string, std::string> GetUniformNameDetail(const char* fullname);

		/*
			Summary:
				This shows the how many global uniform block index we have use.
				User define uniform block index will start at this value.
		*/
		const uint32_t m_useBuildinBufferIndex = 5;
		MaterialConfig m_configbuffer = MaterialConfig();
		MaterialConfig m_config = MaterialConfig();
		std::map<std::string, std::pair<ShaderUniformType, uint32_t>> m_TextureBind = std::map<std::string, std::pair<ShaderUniformType, uint32_t>>();
		std::map<std::string, MaterialUniformBlock*> m_blocks = std::map<std::string, MaterialUniformBlock*>();
		// Binding shader.
		Shader* m_shader;
		static std::pair<int32_t, Texture2D*> lastUseTexture;
		static AssetPool<Material>* m_materialPool;
		// Global uniform block.
		static std::map<std::string, MaterialUniformBlock*> m_globalBlocks;
	};

	TARA_API std::map<CommomMaterialType, Material*>& CommomMaterial();
	TARA_API void RegisterCommom(CommomMaterialType type, Shader* shader);
}