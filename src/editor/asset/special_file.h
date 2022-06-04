#pragma once
#include "filebase.h"

namespace Tara {
	class TARA_API Material;
	class TARA_API Texture2D;
	class TARA_API Mesh;

	namespace FileSystem {
		class TARA_EDITOR_API SpecialFile : public FileBase {
		public:
			
		};

		class TARA_EDITOR_API MaterialFile final : public FileBase {
		public:
			bool DrawGrid() override;
			void DrawProp() override;
			AssetBase* BindingFile() override { return (AssetBase*)binder; }
		private:
			Material* binder;
		};

		class TARA_EDITOR_API ShaderFile final : public FileBase {
		public:
			bool DrawGrid() override;
			void DrawProp() override;
		};

		class TARA_EDITOR_API MarkdownFile final : public FileBase {
		public:
			bool DrawGrid() override;
			void DrawProp() override;
		private:
			std::string data;
		};

		class TARA_EDITOR_API TextureFile final : public FileBase {
		public:
			TextureFile(Texture2D* tex, std::filesystem::path path);
			AssetBase* BindingFile() override { return (AssetBase*)binder; }
			bool DrawGrid() override;
			void DrawProp() override;
		private:
			Texture2D* binder;
		};

		class TARA_EDITOR_API MeshFile final : public FileBase {
		public:
			AssetBase* BindingFile() override { return (AssetBase*)binder; }
			bool DrawGrid() override;
			void DrawProp() override;
		private:
			Mesh* binder;
		};

		class TARA_EDITOR_API PrefabFile final : public FileBase {
		public:
			bool DrawGrid() override;
			void DrawProp() override;
		};

		class TARA_EDITOR_API SceneFile final : public FileBase {
		public:
			bool DrawGrid() override;
			void DrawProp() override;
		};

		class TARA_EDITOR_API WorldFile final : public FileBase{
		public:
			bool DrawGrid() override;
			void DrawProp() override;
		};

		class TARA_EDITOR_API PostProcessingFile final : public FileBase{
		public:
			bool DrawGrid() override;
			void DrawProp() override;
		};
	}
}
