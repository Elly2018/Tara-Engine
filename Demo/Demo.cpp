/*
    User can add TARA_NO_IMGUI to preprocessor to tell compiler that imgui tool don't need to load
*/
#include <config.h>
#include <iostream>
#include <ewindow.h>
#include <engine.h>

using namespace Tara;

Material* m_material1;
Material* m_material2;
Scene* m_scene;
Texture* m_texture;

CTransformation* cameratrans;
CTransformation* sphere;

vec3 cccolor = vec3(0.7f, 0.9f, 0.6f);
vec3 tccolor = vec3(1, 1, 1);
vec3 pos = vec3(0, 1, 1);

class MaterialAssetWindow;
class TextureAssetWindow;
class MeshAssetWindow;
class ShaderAssetWindow;
class FileExplorerWindow;
class SceneViewerWindow;
class PropertiesWindow;
class HierarchyWindow;
class HelperWindow;
class ConsoleWindow;
class DemoWindow;

UI::ImGui_DebugWindow* debug;
MaterialAssetWindow* materialAsset;
TextureAssetWindow* textureAsset;
MeshAssetWindow* meshAsset;
ShaderAssetWindow* shaderAsset;
FileExplorerWindow* fileExplorer;
SceneViewerWindow* sceneViewer;
PropertiesWindow* properties;
HierarchyWindow* hierarchy;
HelperWindow* helperTips;
ConsoleWindow* console;
EWindow* w;
CCamera* mainCamera;

EWindowConfig wc = EWindowConfig();
bool shouldUpdateScene = false;
bool shouldRenderScene = false;
bool showDebugState = false;

std::vector<LogMessage> messages = std::vector<LogMessage>();
bool updateMessages = true;

#ifndef TARA_NO_IMGUI
class MaterialAssetWindow : public UI::ImGui_WindowBase {
public:
    MaterialAssetWindow() : UI::ImGui_WindowBase("Material Assets") {}
};
class TextureAssetWindow : public UI::ImGui_WindowBase {
public:
    TextureAssetWindow() : UI::ImGui_WindowBase("Texture Assets") {}
    void Content() override {
        // Get all the texture from pool
        std::vector<Texture*> list = std::vector<Texture*>();
        AssetPool<Texture>* pool = Texture::GetAssetPool();
        size_t size = pool->Size();
        for (int i = 0; i < size; i++) {
            Texture* tex = pool->Get(i);
            list.push_back(tex);
        }
        // Place texture grid field, default: column is auto, height is match parent.
        // And because we didn't input events, 
        // Default will show basic texture info when mouse is hovered.
        UI::ImGui_TextureGridImageField("All Assets", list);
    }
};
class MeshAssetWindow : public UI::ImGui_WindowBase {
public:
    MeshAssetWindow() : UI::ImGui_WindowBase("Mesh Assets") {}
};
class ShaderAssetWindow : public UI::ImGui_WindowBase {
public:
    ShaderAssetWindow() : UI::ImGui_WindowBase("Shader Assets") {}
};
class FileExplorerWindow : public UI::ImGui_WindowBase {
public:
    FileExplorerWindow() : UI::ImGui_WindowBase("File Explorer") {}
};
class SceneViewerWindow : public UI::ImGui_WindowBase {
public:
    SceneViewerWindow() : UI::ImGui_WindowBase("Scene Viewer") {}
    void Content() override {
        UI::ImGui_WindiwFlags wflags = UI::ImGui_WindiwFlags();
        wflags.MenuBar = true;
        wflags.AlwaysAutoResize = true;
        UI::ImGui_BeginChild("Scene Viewer Frame", 0, 0, false, wflags);
        shouldUpdateScene = UI::ImGui_IsWindowFocued();
        // This big chunk of menu setup code is control the render flow and post processing config
        if (UI::ImGui_BeginMenubar()) {
            if (UI::ImGui_BeginMenu("Display")) {
                if (UI::ImGui_MenuItem("Shaded")) {

                }
                if (UI::ImGui_MenuItem("Wireframe")) {

                }
                if (UI::ImGui_MenuItem("Shaded + Wireframe")) {

                }
                UI::ImGui_Separator();
                if (UI::ImGui_MenuItem("Light")) {

                }
                if (UI::ImGui_MenuItem("Shadow")) {

                }
                if (UI::ImGui_MenuItem("Reflection")) {

                }
                UI::ImGui_EndMenu();
            }
            if (UI::ImGui_BeginMenu("Post Processing")) {
                if (UI::ImGui_MenuItem("Skybox")) {

                }
                if (UI::ImGui_MenuItem("Fog")) {

                }
                if (UI::ImGui_MenuItem("Motion Blur")) {

                }
                if (UI::ImGui_MenuItem("Flare")) {

                }
                UI::ImGui_Separator();
                if (UI::ImGui_BeginMenu("FXAA")) {
                    if (UI::ImGui_MenuItem("None")) {

                    }
                    if (UI::ImGui_MenuItem("2x")) {

                    }
                    if (UI::ImGui_MenuItem("4x")) {

                    }
                    if (UI::ImGui_MenuItem("8x")) {

                    }
                    if (UI::ImGui_MenuItem("16x")) {

                    }
                    UI::ImGui_EndMenu();
                }
                if (UI::ImGui_MenuItem("Ambient Occlusion")) {

                }
                if (UI::ImGui_MenuItem("Bloom")) {

                }
                if (UI::ImGui_MenuItem("Vignette")) {

                }
                UI::ImGui_EndMenu();
            }
            if (UI::ImGui_BeginMenu("Gizmo")) {
                if (UI::ImGui_MenuItem("Object Transformation Axis")) {

                }
                UI::ImGui_EndMenu();
            }
            if (UI::ImGui_BeginMenu("Aspect ratio")) {
                if (UI::ImGui_MenuItem("4:3")) {

                }
                if (UI::ImGui_MenuItem("16:9")) {

                }
                UI::ImGui_Separator();
                if (UI::ImGui_MenuItem("800x600")) {

                }
                if (UI::ImGui_MenuItem("1280x800")) {

                }
                if (UI::ImGui_MenuItem("1600x900")) {

                }
                if (UI::ImGui_MenuItem("1920x1080")) {

                }
                UI::ImGui_EndMenu();
            }
            if (UI::ImGui_MenuItem("Debug", 0, showDebugState)) {
                showDebugState = !showDebugState;
            }
            UI::ImGui_EndMenubar();
        }

        // GUI initialization is create earlier than scene
        // So the camera will be null at first
        // Put the guard here to prevent crash
        if (!mainCamera) {
            UI::ImGui_EndChild();
            return;
        }
        // Get the child window size and position
        vec2 wsize = UI::ImGui_GetWindowSize();
        vec2 wpos = UI::ImGui_GetWindowPos();
        /*
            Calculate height ratio first
        */
        // Total height will be child frame height - menubar height
        float_t frameHeight = wsize.y - 40;
        float_t heightRatio = frameHeight / mainCamera->m_height;
        vec2 mulSize = vec2(mainCamera->m_width, mainCamera->m_height) * heightRatio;
        // Now we have display texture that height is match with the child window size
        // But how about the width ?
        /*
            Calculate width ratio
            Then put the dummy as padding space
        */
        if (mulSize.x > wsize.x) {
            // The display width is bigger than child window width
            // We have to adjust display texture again
            // The same solution which we get the height match the child window size
            float_t widthRatio = wsize.x / mulSize.x;
            mulSize = mulSize * widthRatio;
            float_t heightDiff = frameHeight - mulSize.y;
            // Place padding top and bottom then we finish :D
            UI::ImGui_Dummy(0, heightDiff / 2.f);
            UI::ImGui_Image(mainCamera, mulSize.x, mulSize.y);
            UI::ImGui_Dummy(0, heightDiff / 2.f);
        }
        else {
            // The display width is smaller than child window width
            // Put the padding left then we finish :D
            UI::ImGui_Dummy((wsize.x - mulSize.x) / 2.f, 0);
            UI::ImGui_Sameline(0, 1);
            UI::ImGui_Image(mainCamera, mulSize.x, mulSize.y);
        }
        
        if (showDebugState) {
            UI::ImGui_SetNextWindowPos(wpos.x + 20, wpos.y + 40);
            UI::ImGui_BeginChild("Debug State", 100, 100, true);
            UI::ImGui_Text("YO");
            UI::ImGui_Text("YO");
            UI::ImGui_Text("YO");
            UI::ImGui_Text("YO");
            UI::ImGui_EndChild();
        }
        UI::ImGui_EndChild();
    }
};
class PropertiesWindow : public UI::ImGui_WindowBase {
public:
    PropertiesWindow() : UI::ImGui_WindowBase("Properties") {}
    void Content() override {
        UI::ImGui_Text("Is update: %i", shouldUpdateScene);
        UI::ImGui_Text("Is render: %i", shouldRenderScene);
    }
};
class HierarchyWindow : public UI::ImGui_WindowBase {
public:
    HierarchyWindow() : UI::ImGui_WindowBase("Hierarchy") {}
};
class HelperWindow : public UI::ImGui_WindowBase {
public:
    HelperWindow() : UI::ImGui_WindowBase("Helper") {}
};
class ConsoleWindow : public UI::ImGui_WindowBase {
public:
    void Content() override {
        UI::ImGui_TableFlags tableflags = UI::ImGui_TableFlags();
        tableflags.BordersInnerV = true; tableflags.BordersOuterV = true;
        tableflags.BordersOuterV = true; tableflags.ReSizeble = true;
        tableflags.RowBG = true;
        // We can display different type of log
        if (UI::ImGui_BeginTabBar("ConsoleTab")) {
            if (UI::ImGui_BeginTabitems("Application")) {
                if (UI::ImGui_BeginTable("Application Log", 1, tableflags)) {
                    for (auto m : messages) {
                        UI::ImGui_TextColor(m.color);
                        UI::ImGui_Text(m.message.c_str());
                        UI::ImGui_PopColor();
                        UI::ImGui_TableNextColumn();
                    }
                    // When updating, user's scroll bar will go to the bottom
                    if (updateMessages) {
                        UI::ImGui_SetScrollHereY(0.999f);
                        updateMessages = false;
                    }
                    UI::ImGui_EndTable();
                }
                UI::ImGui_EndTabitems();
            }
            UI::ImGui_EndTabBar();
        }
    }
    static void AddMessage(std::vector<LogMessage> n) {
        for (auto i : n) {
            // Add new coming message
            messages.push_back(i);
        }
        if (n.size() > 0) updateMessages = true;
    }
    ConsoleWindow() : UI::ImGui_WindowBase("Console") {
        // Register event
        // So everytime stdout is called, it can receive callback.
        Logger::RegisterLog(AddMessage);
    }
private:
};
#endif

class DemoWindow : public EWindow {
public:
    DemoWindow() : EWindow(1920, 1080, "Test", OpenGLVersion::Version4_5, wc) {
        TARA_DEBUG("Demo window start!");
        TARA_WARNING("Test Warning Message");
        TARA_ERROR("Test Error Message");
    };
    ~DemoWindow() {
        delete m_scene;
    };

    void Start() override {
        // Init the window
        EWindow::Start();
        // Init the Tara application,
        // This will import all the resources.
        Tara::Tara_Initialization();
        // Init scene
        m_scene = new Scene();
        // Add camera to look around
        EObject* camera = ObjectFactory::OFViewer::CreateFreeCamera();
        cameratrans = camera->GetRelateComponent<CTransformation>();
        // Create cube object
        EObject* m_demo_object1 = ObjectFactory::CreatePawn();
        EObject* m_demo_object2 = ObjectFactory::CreatePawn();
        m_demo_object1->SetName("cube object 1");
        m_demo_object2->SetName("cube object 2");
        CTransformation* trans1 = m_demo_object1->GetRelateComponent<CTransformation>();
        sphere = m_demo_object2->GetRelateComponent<CTransformation>();
        CMeshRenderer* meshr1 = m_demo_object1->GetRelateComponent<CMeshRenderer>();
        CMeshRenderer* meshr2 = m_demo_object2->GetRelateComponent<CMeshRenderer>();
        // Generate cube mesh
        Mesh* mesh1 = Mesh::GetCommon(CommomMesh::Cube);
        Mesh* mesh2 = Mesh::GetCommon(CommomMesh::Sphere);
        // Generate texture
        m_texture = Texture::GetCommon(CommomTexture::Default);
        // Generate pure color shader
        Shader* texshader = Shader::GetCommon(CommonShader::Texture);
        Shader* baseshader = Shader::GetCommon(CommonShader::Color);
        // Create material hold the shader
        m_material1 = new Material(texshader);
        m_material1->SetName("color material 1");
        m_material1->SetTextureIndex("surface", 0);
        m_material1->SetTexture("surface", m_texture);
        m_material1->SetVec3("color", tccolor);

        m_material2 = new Material(baseshader);
        m_material2->SetName("color material 2");
        m_material2->SetVec3("color", cccolor);

        // Apply to the cube object
        if (meshr1 != nullptr) {
            meshr1->SetMesh(mesh1);
            meshr1->SetMaterial(m_material1);
        }
        if (meshr2 != nullptr) {
            meshr2->SetMesh(mesh2);
            meshr2->SetMaterial(m_material2);
        }
        trans1->m_position = vec3(0, 0, 0);
        sphere->m_position = vec3(-1, 1, 0);

        // Upload scene
        m_scenes.push_back(m_scene);
#ifndef TARA_NO_IMGUI
        fileExplorer->SetVisible(false);
        shaderAsset->SetVisible(false);
        helperTips->SetVisible(false);
        m_guiWindows.push_back(materialAsset);
        m_guiWindows.push_back(textureAsset);
        m_guiWindows.push_back(meshAsset);
        m_guiWindows.push_back(shaderAsset);
        m_guiWindows.push_back(fileExplorer);
        m_guiWindows.push_back(sceneViewer);
        m_guiWindows.push_back(properties);
        m_guiWindows.push_back(hierarchy);
        m_guiWindows.push_back(helperTips);
        m_guiWindows.push_back(console);
        m_guiWindows.push_back(debug);
#endif
    };
    void Update() override {
        shouldRenderScene = sceneViewer->Visible();
        updateScenes = shouldUpdateScene;
        renderScenes = shouldRenderScene;
        if (EInput::IsKeyDown(keycode::K)) {
            TARA_DEBUG("YO");
        }
        EWindow::Update();
    }
    void GUI() override {
        EWindow::GUI();
        UI::ImGui_DockspaceOverviewport();
        bool import_scene = false;
        bool export_scene = false;
        UI::ImGui_WindiwFlags wflags = UI::ImGui_WindiwFlags();
        wflags.MenuBar = true;
        if (UI::ImGui_BeginMainmenuBar()) {
            if (UI::ImGui_BeginMenu("File")) {
                if (UI::ImGui_MenuItem("New Scene")) {

                }
                if (UI::ImGui_MenuItem("Import Scene")) {
                    import_scene = true;
                }
                if (UI::ImGui_MenuItem("Export Scene")) {
                    export_scene = true;
                }
                if (UI::ImGui_MenuItem("Exit")) {

                }
                UI::ImGui_EndMenu();
            }
            if (UI::ImGui_BeginMenu("Window")) {
                if (UI::ImGui_MenuItem("Material Asset", 0, materialAsset->Visible())) {
                    materialAsset->SetVisible(!materialAsset->Visible());
                }
                if (UI::ImGui_MenuItem("Texture Asset", 0, textureAsset->Visible())) {
                    textureAsset->SetVisible(!textureAsset->Visible());
                }
                if (UI::ImGui_MenuItem("Mesh Asset", 0, meshAsset->Visible())) {
                    meshAsset->SetVisible(!meshAsset->Visible());
                }
                if (UI::ImGui_MenuItem("Shader Asset", 0, shaderAsset->Visible())) {
                    shaderAsset->SetVisible(!shaderAsset->Visible());
                }
                if (UI::ImGui_MenuItem("Scene Viewer", 0, sceneViewer->Visible())) {
                    sceneViewer->SetVisible(!sceneViewer->Visible());
                }
                if (UI::ImGui_MenuItem("Properties", 0, properties->Visible())) {
                    properties->SetVisible(!properties->Visible());
                }
                if (UI::ImGui_MenuItem("Hierarchy", 0, hierarchy->Visible())) {
                    hierarchy->SetVisible(!hierarchy->Visible());
                }
                if (UI::ImGui_MenuItem("Console", 0, console->Visible())) {
                    console->SetVisible(!console->Visible());
                }
                if (UI::ImGui_MenuItem("Debug Menu", 0, debug->Visible())) {
                    debug->SetVisible(!debug->Visible());
                }
                UI::ImGui_EndMenu();
            }
            if (UI::ImGui_BeginMenu("Help")) {
                if (UI::ImGui_MenuItem("Github Page")) {

                }
                if (UI::ImGui_MenuItem("Helper Tips")) {

                }
                if (UI::ImGui_MenuItem("About")) {

                }
                UI::ImGui_EndMenu();
            }
            UI::ImGui_EndMainmenuBar();
        }

        UI::ImGui_WindiwFlags f = UI::ImGui_WindiwFlags();
        f.AlwaysAutoResize = true;
        f.NoMove = true;
        f.MenuBar = false;
        
        if (import_scene) {
            vec2 wsize = w->GetEWindowSize();
            UI::ImGui_SetNextWindowPos(wsize.x / 2.f, wsize.y / 2.f, UI::ImGui_ConditionFlags(), 0.5f, 0.5f);
            UI::ImGui_OpenPopup("Import Scene");
        }
        if (UI::ImGui_BeginPopupModal("Import Scene", 0, f)) {
            UI::ImGui_Text("YOOO %s %s ", "What's up", "my dude !!");
            UI::ImGui_Separator();
            UI::ImGui_TextUnformatted("YOOO");
            UI::ImGui_Separator();
            UI::ImGui_TextUnformatted("YOOO");
            UI::ImGui_Separator();
            UI::ImGui_TextUnformatted("YOOO");
            if (UI::ImGui_Button("Close")) {
                UI::ImGui_ClosePopup();
            }
            UI::ImGui_EndPopup();
        }

        if (export_scene) {
            vec2 wsize = w->GetEWindowSize();
            UI::ImGui_SetNextWindowPos(wsize.x / 2.f, wsize.y / 2.f, UI::ImGui_ConditionFlags(), 0.5f, 0.5f);
            UI::ImGui_OpenPopup("Export Scene");
        }
        if (UI::ImGui_BeginPopupModal("Export Scene", 0, f)) {
            UI::ImGui_Text("YOOO %s %s ", "What's up", "my dude !!");
            UI::ImGui_Separator();
            UI::ImGui_TextUnformatted("YOOO");
            UI::ImGui_Separator();
            UI::ImGui_TextUnformatted("YOOO");
            UI::ImGui_Separator();
            UI::ImGui_TextUnformatted("YOOO");
            if (UI::ImGui_Button("Close")) {
                UI::ImGui_ClosePopup();
            }
            UI::ImGui_EndPopup();
        }
    }
    void PostRender() override {
        // Default is render scene to window background
        // But we can disable that with override PostRender() function
        // The scene main camera is under EWindow memeber: m_camera
        mainCamera = m_camera; // Get main camera of the scene

        // Clean color depth buffer only
        CleanBuffer();
        // Render nothing
    }
};

int main()
{
    Logger::HideConsole();
    console = new ConsoleWindow();
    materialAsset = new MaterialAssetWindow();
    textureAsset = new TextureAssetWindow();
    meshAsset = new MeshAssetWindow();
    shaderAsset = new ShaderAssetWindow();
    fileExplorer = new FileExplorerWindow();
    sceneViewer = new SceneViewerWindow();
    properties = new PropertiesWindow();
    hierarchy = new HierarchyWindow();
    helperTips = new HelperWindow();
    debug = new UI::ImGui_DebugWindow();
    w = new DemoWindow();
    w->Maximum();
    w->Start();
    w->Mainloop();
    delete w;
    return 0;
};