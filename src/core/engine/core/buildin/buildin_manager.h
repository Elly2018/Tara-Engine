#pragma once
#include "../config.h"
#include "../utility.h"

namespace Tara {
	class TARA_API Mesh;
	class TARA_API Texture2D;
	class TARA_API Shader;
	enum class TARA_API ShaderType;


	/// <summary>
	/// Handle buildin resources.
	/// </summary>
	class TARA_API BuildinManager : public Utility::Zip {
	public:
		BuildinManager(const char* filepath);
		virtual ~BuildinManager();

		std::pair<void*, size_t> GetPrimitiveFontMemory(std::string path);
		Shader* PackagingShader(std::string name);
		std::string GetShaderString(std::string name, ShaderType type);

		Mesh* GetPrimitiveMesh(std::string name);
		Texture2D* GetPrimitiveTexture(std::string name);
		Texture2D* GetPrimitiveIcon(std::string name);

		void ReadManifest();

		nlohmann::json Manifest;
	};

}