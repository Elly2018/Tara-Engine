#pragma once
#include "filebase.h"

namespace Tara {
	namespace FileSystem {
		class TARA_API RegularFile final : public FileBase {
		public:
			RegularFile() : FileBase() {}
			RegularFile(std::filesystem::path p) : FileBase(p) {}
			~RegularFile();

			AssetBase* BindingFile() override { return nullptr; }
			bool DrawGrid() override;
			void DrawProp() override;
		};
	}
}
