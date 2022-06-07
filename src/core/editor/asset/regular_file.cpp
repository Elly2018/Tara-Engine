#include "regular_file.h"
#include "../editor_lowlevel.h"
#include "../../engine/core/buildin/buildin_manager.h"

namespace Tara{
	namespace FileSystem {
		RegularFile::~RegularFile()
		{

		}
		bool RegularFile::DrawGrid()
		{
			using namespace UI;
			BuildinManager* bm = PackageManager::Singleton().buildin;
			Texture2D* icon = bm->GetPrimitiveIcon("arrow.png");
			ImGui_TextureImageField(icon, 100);
			ImGui_NextColumn();
			return false;
		}
		void RegularFile::DrawProp()
		{
			UI::ImGui_Text("Test Prop Draw");
		}
	}
}
