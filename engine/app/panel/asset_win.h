#pragma once
#include <filesystem>
#include "../../editor/editor_container.h"
#include "../../editor/asset/filebase.h"

namespace Tara {
	namespace UI {
        enum class AssetWindowFilter {
            Texture,
            Material,
            Meshe,
            Tree
        };

        class AssetWindow : public ImGui_WindowBase {
        public:
            AssetWindow();
            void TopBar();
            void AssetLeftPanel();
            void AssetRightPanel();
            void Content() override;

        private:
            void Update();

            std::vector<FileSystem::FileBase*> currentLoad;
            bool m_First = true;
            AssetWindowFilter m_FilterMode = AssetWindowFilter::Tree;
            std::string m_SearchWord;
            std::filesystem::path m_CurrentDirectory = std::filesystem::path("Assets");
        };
	}
}