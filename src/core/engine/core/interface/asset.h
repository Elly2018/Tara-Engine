#pragma once
// Import std library
#include <map>
#include <filesystem>

// Import Tara engine library
#include "../config.h"

namespace Tara {
	class TARA_API Mesh;
	class TARA_API Texture2D;
	struct TARA_API ZipContent;


	/// <summary>
	/// Package resources query interface
	/// </summary>
	class TARA_API IPackage {
	public:
		/// <summary>
		/// Check file path is exist.
		/// </summary>
		/// <param name="filename">path</param>
		virtual bool FileExist(std::string filename) = 0;
		/// <summary>
		/// Check dir path is exist.
		/// </summary>
		/// <param name="dir">path</param>
		virtual bool DirectroyExist(std::string dir) = 0;
		
		virtual std::vector<std::string> GetDirectories(std::string dir) = 0;
		
		virtual std::vector<std::string> GetFiles(std::string dir) = 0;
		/// <summary>
		/// Get converted character array from target file path.
		/// </summary>
		/// <param name="filename">File path</param>
		/// <returns>Convert result</returns>
		virtual std::vector<char> GetFileData_Char(std::string filename) = 0;
		/// <summary>
		/// Get converted unsigned character array from target file path.
		/// </summary>
		/// <param name="filename">File path</param>
		/// <returns>Convert result</returns>
		virtual std::vector<uint8_t> GetFileData_UChar(std::string filename) = 0;
		/// <summary>
		/// Get converted string from target file path.
		/// </summary>
		/// <param name="filename">File path</param>
		/// <returns>Convert result</returns>
		virtual std::string GetFileData_String(std::string filename) = 0;
		/// <summary>
		/// Get memory pointer from target file path.
		/// </summary>
		/// <param name="filename">File path</param>
		/// <returns>Memory pointer</returns>
		virtual void* GetFileData_Void(std::string filename) = 0;
		/// <summary>
		/// Get memory size from target file path.
		/// </summary>
		/// <param name="filename">File path</param>
		/// <returns>Size of the file</returns>
		virtual size_t GetFileData_Size(std::string filename) = 0;
		/// <summary>
		/// Get the mesh data from package.
		/// </summary>
		/// <param name="path">path</param>
		/// <returns>Null if not found</returns>
		virtual Mesh* GetMesh(std::string path) = 0;
		/// <summary>
		/// Get the texture data from package.
		/// </summary>
		/// <param name="path">path</param>
		/// <returns>Null if not found</returns>
		virtual Texture2D* GetTexture(std::string path) = 0;
		virtual bool CheckDataIsLoaded(std::string filename) = 0;
		virtual void LoadData(std::string filename) = 0;
	};
}