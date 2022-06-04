#include "special_file.h"
#include "../../engine/core/material/material.h"
#include "../../engine/core/texture/texture.h"
#include "../../engine/core/mesh/mesh.h"
#include "../editor_lowlevel.h"

namespace Tara {
	namespace FileSystem {
		bool MaterialFile::DrawGrid()
		{
			return false;
		}
		void MaterialFile::DrawProp()
		{
		}
		bool ShaderFile::DrawGrid()
		{
			return false;
		}
		void ShaderFile::DrawProp()
		{
		}
		bool MarkdownFile::DrawGrid()
		{
			return false;
		}
		void MarkdownFile::DrawProp()
		{
		}
		TextureFile::TextureFile(Texture2D* tex, std::filesystem::path path) : FileBase(path)
		{
			binder = tex;
		}
		bool TextureFile::DrawGrid()
		{
			using namespace UI;
			ImGui_TextureImageField(binder, 100);
			ImGui_NextColumn();
			return false;
		}
		void TextureFile::DrawProp()
		{
		}
		bool MeshFile::DrawGrid()
		{
			return false;
		}
		void MeshFile::DrawProp()
		{
		}
		bool PrefabFile::DrawGrid()
		{
			return false;
		}
		void PrefabFile::DrawProp()
		{
		}
		bool SceneFile::DrawGrid()
		{
			return false;
		}
		void SceneFile::DrawProp()
		{
		}
		bool WorldFile::DrawGrid()
		{
			return false;
		}
		void WorldFile::DrawProp()
		{
		}
		bool PostProcessingFile::DrawGrid()
		{
			return false;
		}
		void PostProcessingFile::DrawProp()
		{
		}
	}
}