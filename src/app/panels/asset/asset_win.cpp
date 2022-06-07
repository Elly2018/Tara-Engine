#include "asset_win.h"
#include <filesystem>
#include <direct.h>
#include <stdio.h>
#include "engine/core/asset.h"
#include "engine/core/texture/texture.h"
#include "engine/core/shader/shader.h"
#include "engine/core/material/material.h"
#include "engine/core/mesh/mesh.h"
#include "editor/editor_lowlevel.h"
#include "editor/project/project.h"

namespace Tara {
	namespace UI {

        void AssetsExistChecker() {
            if (!std::filesystem::exists("Assets")) {
                std::filesystem::create_directory("Assets");
            }
        }

        bool AssetTree(std::string dir, std::filesystem::path& current) {
            if (!std::filesystem::exists(dir)) return false;
            bool isUpdate = false;
            for (auto& p : std::filesystem::directory_iterator(dir)) {
                if (p.is_directory()) {
                    std::string id = p.path().string();
                    std::string title = p.path().filename().string();
                    bool p_select = current == p.path();

                    bool p_hasChildren = false;
                    for (auto& i : std::filesystem::directory_iterator(id)) {
                        if (i.is_directory()) {
                            p_hasChildren = true;
                            break;
                        }
                    }

                    bool open = ImGui_CustomTreeNode(("AssetWin##" + id).c_str(), title.c_str(), &p_select, p_hasChildren);

                    // Before enter recursion, it should check update first,
                    // Otherwise it will override the state when recursion hit the end.
                    if (p_select) {
                        if (current.string() != id) {
                            isUpdate = true;
                            current = std::filesystem::path(id);
                        }
                    }

                    // Enter recursion 
                    if (open) {
                        ImGui_Indent(15);
                        bool b = AssetTree(id, current);
                        ImGui_UnIndent(15);
                    }
                }
            }
            return isUpdate;
        }

        AssetWindow::AssetWindow() : ImGui_WindowBase("Assets") {}

        void AssetWindow::TopBar()
        {
            ImGui_TextField("search pattern", &m_SearchWord);
        }

        void AssetWindow::AssetLeftPanel() {
            if (ImGui_CollapsingHeader("Category")) {
                if (ImGui_Selectable("Textures", m_FilterMode == AssetWindowFilter::Texture)) {
                    m_FilterMode = AssetWindowFilter::Texture;
                    Update();
                }
                if (ImGui_Selectable("Materials", m_FilterMode == AssetWindowFilter::Material)) {
                    m_FilterMode = AssetWindowFilter::Material;
                    Update();
                }
                if (ImGui_Selectable("Meshes", m_FilterMode == AssetWindowFilter::Meshe)) {
                    m_FilterMode = AssetWindowFilter::Meshe;
                    Update();
                }
            }

            if (ImGui_CollapsingHeader("Assets Database")) {
                AssetsExistChecker();
                if (AssetTree("Assets", m_CurrentDirectory)) {
                    m_FilterMode = AssetWindowFilter::Tree;
                    Update();
                }
            }
        }
        void AssetWindow::AssetRightPanel() {
            ImGui_BeginGrid();
            for (auto& i : currentLoad) {
                i->DrawGrid();
            }
            ImGui_EndGrid();
        }
        void AssetWindow::Content() {
            TaraProject& project = TaraProject::Singleton();

            int state = -1;
            // Show cate
            if (project.RequireProject() && project.HaveProject()) state = 0;
            // Need project setup
            else if (project.RequireProject() && !project.HaveProject()) state = 1;
            // Asset disable
            else state = 2;

            switch (state) {
            case 0:
            {
                ImGui_Column(2, true);
                if (m_First) {
                    ImGui_SetColumnWidth(0, 200);
                    m_First = false;
                }
                ImGui_BeginChild("Asset Left", 0, 0, true);
                AssetLeftPanel();
                ImGui_EndChild();
                ImGui_NextColumn();
                ImGui_BeginChild("Asset Right", 0, 0, true);
                TopBar();
                AssetRightPanel();
                ImGui_EndChild();
                ImGui_Column(1, false);
                break;
            }
            case 1:
            {
                ImGui_CenterText("Requre project setup.");
                break;
            }
            case 2:
            {
                ImGui_CenterText("Project is disabled right now.");
                break;
            }
            }
        }
        void AssetWindow::Update()
        {
            using namespace FileSystem;
            for (auto i : currentLoad) {
                delete i;
            }
            switch (m_FilterMode)
            {
            case AssetWindowFilter::Texture:
            {
                FileDataBase& fdb = FileDataBase::Singleton();
                currentLoad = fdb.GetFiles("Assets", true, FileType::Texture);
                m_CurrentDirectory = "Assets";
                break;
            }
            case AssetWindowFilter::Material:
            {
                FileDataBase& fdb = FileDataBase::Singleton();
                currentLoad = fdb.GetFiles("Assets", true, FileType::Material);
                m_CurrentDirectory = "Assets";
                break;
            }
            case AssetWindowFilter::Meshe:
            {
                FileDataBase& fdb = FileDataBase::Singleton();
                currentLoad = fdb.GetFiles("Assets", true, FileType::Mesh);
                m_CurrentDirectory = "Assets";
                break;
            }
            case AssetWindowFilter::Tree:
            {
                FileDataBase& fdb = FileDataBase::Singleton();
                currentLoad = fdb.GetFiles(m_CurrentDirectory.string().c_str(), false);
                break;
            }
            }
        }
	}
}