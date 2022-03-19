#include "./tara.h"
// Include std library
#include <memory>

// Include third party library
#include <filesystem>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Include tara library
#include "core/config.h"
#include "core/asset.h"
#include "core/renderer/renderer.h"
#include "core/material/material.h"
#include "core/shader/shader.h"
#include "core/mesh/mesh.h"
#include "core/texture/texture.h"
#include "core/framebuffer/framebuffer.h"
#include "core/buildin/buildin_manager.h"
#include "system/allsystems.h"
#include "system/system.h"

namespace Tara {
	/*
		Summary:
			Clean all assets pool nullptr.
	*/
	void CleanGarbage()
	{
		Texture::GetAssetPool().CleanNull();
		Mesh::GetAssetPool().CleanNull();
		FrameBuffer::GetAssetPool().CleanNull();
	}

	bool Tara_Initialization()
	{
		Utility::Argument& arg = Utility::Argument::Singleton();
		Logger::LogToFile();
		std::filesystem::create_directory("temp");

		if (glfwInit() != GLFW_TRUE) {
			TARA_RUNTIME_ERROR("GLFW failed to initialize");
			return false;
		}

		TARA_DEBUG_LEVEL("Tara initialization start", 2);
		TARA_DEBUG("Debug filename: %s", DEBUG_FILENAME);
#ifdef TARA_WINDOW || TARA_LINUX
		ProfilerInit();
#endif

		SystemRegister& sr = SystemRegister::Singleton();
		sr.Register(new CameraSystem());
		sr.Register(new LightSystem());
		sr.Register(new MeshRendererSystem());

		TARA_DEBUG_LEVEL("Tara initialization end", 2);

		PackageManager& pm = PackageManager::Singleton();
		BuildinManager& bm = BuildinManager::Singleton();

		if (!arg.recordAllLog) Logger::LogToConsole();
		return true;
	}
	bool Tara_Shutdown()
	{
		CleanGarbage();
		TARA_DEBUG_LEVEL("Texture asset size: %zu", 1, Texture::GetAssetPool().Size());
		Texture::GetAssetPool().DeleteAll();
		TARA_DEBUG_LEVEL("Mesh asset size: %zu", 1, Mesh::GetAssetPool().Size());
		Material::GetAssetPool().DeleteAll();
		TARA_DEBUG_LEVEL("Material asset size: %zu", 1, Material::GetAssetPool().Size());
		Mesh::GetAssetPool().DeleteAll();
		TARA_DEBUG_LEVEL("Framebuffer asset size: %zu", 1, FrameBuffer::GetAssetPool().Size());
		FrameBuffer::GetAssetPool().DeleteAll();
		return true;
	}
}