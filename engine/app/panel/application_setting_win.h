#pragma once
#include <filesystem>
#include "../../editor/editor_container.h"
#include "../../editor/asset/filebase.h"
#include "../../editor/editor_setting.h"

namespace Tara {
    namespace UI {

        class TARA_API AppSettingContent {
        public:
            virtual void DrawListFields() = 0;
        };

        class TARA_API AppSetting_App : public AppSettingContent {
        public:
            void DrawListFields() override;
        };

        class TARA_API AppSetting_Style : public AppSettingContent {
        public:
            AppSetting_Style();
            void DrawListFields() override;

        private:
            std::vector<std::pair<std::string, StyleColor*>> m_ThemeRegister;
        };

        class TARA_API AppSetting_Editor : public AppSettingContent {
        public:
            void DrawListFields() override;
        };

        class TARA_API AppSetting_Plugin : public AppSettingContent {
        public:
            void DrawListFields() override;
        };

        class TARA_API AppSettingWindow : public ImGui_WindowBase {
        public:
            AppSettingWindow();
            void LeftMenu();
            void RightContent();
            void Content() override;
            void SetSelect(int32_t index);

        private:
            void UpdateContent();
            AppSettingContent* m_CurrentContent = nullptr;
            int32_t m_Select = 0;
            bool m_First = true;
        };
    }
}