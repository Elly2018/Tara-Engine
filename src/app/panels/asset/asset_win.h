#pragma once
#include <filesystem>
#include "engine/core/config.h"
#include "editor/editor_container.h"
#include "editor/asset/filebase.h"

namespace Tara {
	namespace UI {
        enum class TARA_APP_API AssetWindowFilter {
            Texture,
            Material,
            Meshe,
            Tree
        };

        class TARA_APP_API AssetWindow : public ImGui_WindowBase {
        public:
            AssetWindow();
            /// <summary>
            /// Top search/path bar.
            /// </summary>
            void TopBar();
            /// <summary>
            /// Category section.
            /// </summary>
            void AssetLeftPanel();
            /// <summary>
            /// Asset contents.
            /// </summary>
            void AssetRightPanel();
            void Content() override;

        private:
            /// <summary>
            /// When state has changed.
            /// </summary>
            void Update();

            std::vector<FileSystem::FileBase*> currentLoad;
            bool m_First = true;
            AssetWindowFilter m_FilterMode = AssetWindowFilter::Tree;
            std::string m_SearchWord;
            std::filesystem::path m_CurrentDirectory = std::filesystem::path("Assets");
        };
	}
}