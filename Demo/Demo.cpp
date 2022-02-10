/*
    User can add TARA_NO_IMGUI to preprocessor to tell compiler that imgui tool don't need to load
*/
#include <config.h>
#include <iostream>
#include <ewindow.h>
#include <engine.h>
#include <functional>

using namespace Tara;

struct PostProcessConfig {
public:
    MSAASamples m_sample = MSAASamples::None;
    bool m_updateSample = false;
};

EWindow* w;
EWindowConfig wc = EWindowConfig();
std::vector<Scene*> allScene = std::vector<Scene*>();
EObject* focusedObject = nullptr;
PostProcessConfig post = PostProcessConfig();

class DemoWindow;
class AssetWindow;
class FileExplorerWindow;
class SceneViewerWindow;
class PropertiesWindow;
class HierarchyWindow;
class HelperWindow;
class ConsoleWindow;

AssetWindow* asset;
FileExplorerWindow* fileExplorer;
SceneViewerWindow* sceneViewer;
PropertiesWindow* properties;
HierarchyWindow* hierarchy;
HelperWindow* helperTips;
ConsoleWindow* console;
UI::ImGui_DebugWindow* debug;
RenderState m_render = RenderState();

bool shouldUpdateScene = false;
bool shouldRenderScene = false;
bool shouldRecordRenderState = false;
bool showDebugState = false;
bool showGizmo = false;
CCamera* selectCameraObject = nullptr;

std::vector<LogMessage> messages = std::vector<LogMessage>();
bool updateMessages = true;
int rendermode = 0;

class AssetWindow : public UI::ImGui_WindowBase {
private:
    bool first = true;
    int leftViewSelect = -1;
public:
    AssetWindow() : UI::ImGui_WindowBase("Assets") {}
    void AssetLeftPanel() {
        if (UI::ImGui_CollapsingHeader("Assets")) {
            if (UI::ImGui_Selectable("Textures", leftViewSelect == 0)) leftViewSelect = 0;
            if (UI::ImGui_Selectable("Materials", leftViewSelect == 1)) leftViewSelect = 1;
            if (UI::ImGui_Selectable("Meshes", leftViewSelect == 2)) leftViewSelect = 2;
            if (UI::ImGui_Selectable("Shaders", leftViewSelect == 3)) leftViewSelect = 3;
        }
    }
    void AssetRightPanel() {
        if (leftViewSelect == 0) {
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
            UI::ImGui_TextureGridImageField("All", list);
        }
        else if (leftViewSelect == 1) {
            std::vector<Material*> list = std::vector<Material*>();
            AssetPool<Material>* pool = Material::GetAssetPool();
            size_t size = pool->Size();
            for (int i = 0; i < size; i++) {
                Material* mat = pool->Get(i);
                list.push_back(mat);
            }
            // Place texture grid field, default: column is auto, height is match parent.
            // And because we didn't input events, 
            // Default will show basic texture info when mouse is hovered.
            UI::ImGui_MaterialGridImageField("All", list);
        }
        else if (leftViewSelect == 2) {
            std::vector<Mesh*> list = std::vector<Mesh*>();
            AssetPool<Mesh>* pool = Mesh::GetAssetPool();
            size_t size = pool->Size();
            for (int i = 0; i < size; i++) {
                Mesh* mat = pool->Get(i);
                list.push_back(mat);
            }
            // Place texture grid field, default: column is auto, height is match parent.
            // And because we didn't input events, 
            // Default will show basic texture info when mouse is hovered.
            UI::ImGui_MeshGridImageField("All", list);
        }
        else if (leftViewSelect == 3) {
            std::vector<Shader*> list = std::vector<Shader*>();
            AssetPool<Shader>* pool = Shader::GetAssetPool();
            size_t size = pool->Size();
            for (int i = 0; i < size; i++) {
                Shader* mat = pool->Get(i);
                list.push_back(mat);
            }
            // Place texture grid field, default: column is auto, height is match parent.
            // And because we didn't input events, 
            // Default will show basic texture info when mouse is hovered.
            UI::ImGui_ShaderGridImageField("All", list);
        }
    }
    void Content() override {
        UI::ImGui_Column(2, true);
        if (first) {
            UI::ImGui_SetColumnWidth(0, 200);
            first = false;
        }
        UI::ImGui_BeginChild("Asset Left", 0, 0, true);
        AssetLeftPanel();
        UI::ImGui_EndChild();
        UI::ImGui_NextColumn();
        UI::ImGui_BeginChild("Asset Right", 0, 0, true);
        AssetRightPanel();
        UI::ImGui_EndChild();
    }
};
class FileExplorerWindow : public UI::ImGui_PopWindow {
public:
    FileExplorerWindow() : UI::ImGui_PopWindow("File Explorer") {}
};
class SceneViewerWindow : public UI::ImGui_SceneView {
public:
    SceneViewerWindow(const char* title) : UI::ImGui_SceneView(title, "Scene Viewer Frame") {
        UI::ImGui_WindiwFlags& m_flags = FrameFlags();
        m_flags.MenuBar = true;
        m_flags.AlwaysAutoResize = true;
    }
    void MenuBar() override {
        // This big chunk of menu setup code is control the render flow and post processing config
        if (UI::ImGui_BeginMenubar()) {
            if (UI::ImGui_BeginMenu("Display")) {
                if (UI::ImGui_MenuItem("Shaded", 0, rendermode == 0)) {
                    rendermode = 0;
                }
                if (UI::ImGui_MenuItem("Wireframe", 0, rendermode == 1)) {
                    rendermode = 1;
                }
                if (UI::ImGui_MenuItem("Shaded + Wireframe", 0, rendermode == 2)) {
                    rendermode = 2;
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
                if (UI::ImGui_BeginMenu("MSAA")) {
                    if (UI::ImGui_MenuItem("None", 0, post.m_sample == MSAASamples::None)) {
                        post.m_sample = MSAASamples::None;
                        post.m_updateSample = true;
                    }
                    if (UI::ImGui_MenuItem("2x", 0, post.m_sample == MSAASamples::_2x)) {
                        post.m_sample = MSAASamples::_2x;
                        post.m_updateSample = true;
                    }
                    if (UI::ImGui_MenuItem("4x", 0, post.m_sample == MSAASamples::_4x)) {
                        post.m_sample = MSAASamples::_4x;
                        post.m_updateSample = true;
                    }
                    if (UI::ImGui_MenuItem("8x", 0, post.m_sample == MSAASamples::_8x)) {
                        post.m_sample = MSAASamples::_8x;
                        post.m_updateSample = true;
                    }
                    if (UI::ImGui_MenuItem("16x", 0, post.m_sample == MSAASamples::_16x)) {
                        post.m_sample = MSAASamples::_16x;
                        post.m_updateSample = true;
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
            if (UI::ImGui_MenuItem("Gizmo", 0, showGizmo)) {
                showGizmo = !showGizmo;
            }
            UI::ImGui_EndMenubar();
        }
    }
    void PostRender() override {
        shouldUpdateScene = UI::ImGui_IsWindowFocued();
        glm::vec2 wpos = UI::ImGui_GetWindowPos();
        glm::vec2 wsize = UI::ImGui_GetWindowSize();
        DefaultContent();
        if (showDebugState) {
            near = m_camera->m_nearPlane;
            far = m_camera->m_farPlane;
            UI::ImGui_SetNextWindowPos(wpos.x + m_leftPadding + 20, wpos.y + m_topPadding + 50);
            UI::ImGui_BeginChild("Debug State", 180, 220, true);
            UI::ImGui_Text("FPS: %f", m_render.FPS);
            UI::ImGui_Text("CPU usage: %f", m_render.CPU_Usage);
            UI::ImGui_Text("GPU usage: %f", m_render.GPU_Usage);
            UI::ImGui_Text("Draw call: %i", m_render.DrawCall);
            UI::ImGui_Text("Vertices count: %i", m_render.Vertices);
            UI::ImGui_Text("Triangles count: %i", m_render.Triangle);
            UI::ImGui_DragFloat("Near", &near);
            UI::ImGui_DragFloat("Far", &far);
            UI::ImGui_Checkbox("Render State", &shouldRecordRenderState);
            UI::ImGui_EndChild();

            m_camera->m_nearPlane = near;
            m_camera->m_farPlane = far;
        }
        if (selectCameraObject) {
            UI::ImGui_SetNextWindowPos(wpos.x + wsize.x - 320, wpos.y + wsize.y - 260);
            UI::ImGui_BeginChild("Debug State", 300, 200, true);
            RenderCamera(selectCameraObject);
            UI::ImGui_EndChild();
        }
    }
    void SetCam(CCamera* c) {
        m_camera = c;
    }
    float near = 0;
    float far = 0;
};
class PropertiesWindow : public UI::ImGui_WindowBase {
public:
    UI::ImGui_WindiwFlags flags = UI::ImGui_WindiwFlags();
    PropertiesWindow() : UI::ImGui_WindowBase("Properties") {
        flags.AlwaysAutoResize = true;
    }
    void Content() override {
        UI::ImGui_BeginChild("Hierarchy Frame", 0, 0, true, flags);
        if (UI::ImGui_Checkbox("Debug", &EComponent::DebugMenu())) {
            TARA_DEBUG("Toggle Debug");
        }
        if (!focusedObject) {
            UI::ImGui_EndChild();
            return;
        }
        std::vector<EComponent*> comps = focusedObject->GetRelateComponents<EComponent>();
        int32_t count = 0;
        for (auto comp : comps) {
            count++;
            std::string id = typeid(*comp).name();
            Utility::String::RemoveString(id, "class ");
            Utility::String::RemoveString(id, "Tara::");
            if (UI::ImGui_CollapsingHeader(id.c_str())) {
                comp->GUI();
            }
        }
        UI::ImGui_EndChild();
    }
};
class HierarchyWindow : public UI::ImGui_WindowBase {
public:
    HierarchyWindow() : UI::ImGui_WindowBase("Hierarchy") {
        childWinFlags.MenuBar = true;
        childWinFlags.AlwaysAutoResize = true;
    }
    void Content() override {
        for (auto s : allScene) {
            if (!s) continue;
            size_t c = s->TopLayerCount();
            if (UI::ImGui_CollapsingHeader(s->Name())) {

                UI::ImGui_BeginChild((std::string(s->Name()) + "##").c_str(), 0, 0, false, childWinFlags);
                if (UI::ImGui_BeginMenubar()) {
                    if (UI::ImGui_BeginMenu("New")) {
                        if (UI::ImGui_MenuItem("Empty")) {
                            ObjectFactory::CreateEmpty();
                        }
                        if (UI::ImGui_MenuItem("Actor")) {
                            ObjectFactory::CreateActor();
                        }
                        if (UI::ImGui_MenuItem("Pawn")) {
                            ObjectFactory::CreatePawn();
                        }
                        if (UI::ImGui_BeginMenu("Camera")) {
                            if (UI::ImGui_MenuItem("Camera")) {
                                ObjectFactoryViewer::CreateCamera();
                            }
                            if (UI::ImGui_MenuItem("Free Camera")) {
                                ObjectFactoryViewer::CreateFreeCamera();
                            }
                            UI::ImGui_EndMenu();
                        }
                        UI::ImGui_EndMenu();
                    }
                    if (UI::ImGui_MenuItem("Edit")) {

                    }
                    if (UI::ImGui_MenuItem("Search")) {

                    }
                    UI::ImGui_EndMenubar();
                }
                UI::ImGui_Indent();
                for (size_t i = 0; i < c; i++) {
                    EObject* eo = s->GetChild(i);
                    focusedObject = UI::ImGui_EObjectHierarchy(eo, focusedObject);
                }
                if (focusedObject)
                    selectCameraObject = focusedObject->GetRelateComponent<CCamera>();
                UI::ImGui_UnIndent();
                UI::ImGui_EndChild();
            }
        }
    }
    char* search;
    UI::ImGui_WindiwFlags childWinFlags = UI::ImGui_WindiwFlags();
};
class HelperWindow : public UI::ImGui_WindowBase {
public:
    HelperWindow() : UI::ImGui_WindowBase("Helper") {}
    void Content() override {
        std::string text = "# H1 header\n ## H2 ssss\n H3 YoYo\n * Hello world\n* [link description](https://...)";
        UI::ImGui_Markdown(text);
    }
};
class ConsoleWindow : public UI::ImGui_WindowBase {
public:
    void Content() override {
        UI::ImGui_TableFlags tableflags = UI::ImGui_TableFlags();
        tableflags.BordersInnerV = true; tableflags.BordersOuterV = true;
        tableflags.BordersOuterV = true; tableflags.ReSizeble = true;
        tableflags.RowBG = true;
        // We can display different type of log
        if (UI::ImGui_Button("Clear")) {
            messages.clear();
        }
        if (UI::ImGui_BeginTabBar("ConsoleTab")) {
            if (UI::ImGui_BeginTabitems("All Logs")) {
                if (UI::ImGui_BeginTable("Application All Logs", 1, tableflags)) {
                    UI::ImGui_BeginChild("logs", 0, 0, false);
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
                    UI::ImGui_EndChild();
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
    ConsoleWindow() : UI::ImGui_WindowBase("Console") {}
private:
};
class ProfilerWindow : public UI::ImGui_WindowBase {
    ProfilerWindow() : UI::ImGui_WindowBase("Profiler") {}
};

class DemoWindow : public EWindow {
public:
    DemoWindow() : EWindow(1920, 1080, "Test", OpenGLVersion::Version4_5, wc) {
        TARA_DEBUG("Demo window start!");
        TARA_WARNING("Test Warning Message");
        TARA_ERROR("Test Error Message");
    };
    ~DemoWindow() {
        DeleteAllScene();
    };

    void Start() override {
        // Init the window
        EWindow::Start();
        // Init the Tara application,
        // This will import all the resources.
        Tara::Tara_Initialization();
        // Init scene
        Scene* m_scene = new Scene();
        // Add camera to look around
        EObject* camera = ObjectFactoryViewer::CreateCamera();
        camera->Name() = "Camera";
        CTransformation* cameratrans = camera->GetRelateComponent<CTransformation>();
        // Create cube object
        EObject* m_demo_object1 = ObjectFactory::CreatePawn();
        EObject* m_demo_object2 = ObjectFactory::CreatePawn();
        EObject* floor = ObjectFactory::CreatePawn();
        m_demo_object1->SetParent(m_demo_object2);

        m_demo_object1->Name() = "cube object";
        m_demo_object2->Name() = "sphere object";
        floor->Name() = "floor";
        CTransformation* trans1 = m_demo_object1->GetRelateComponent<CTransformation>();
        CTransformation* sphere = m_demo_object2->GetRelateComponent<CTransformation>();
        CMeshRenderer* meshr1 = m_demo_object1->GetRelateComponent<CMeshRenderer>();
        CMeshRenderer* meshr2 = m_demo_object2->GetRelateComponent<CMeshRenderer>();
        // Generate cube mesh
        Mesh* mesh1 = Mesh::GetCommon(CommomMesh::Cube);
        Mesh* mesh2 = Mesh::GetCommon(CommomMesh::Sphere);
        Mesh* mesh3 = Mesh::GetCommon(CommomMesh::Plane);
        // Generate texture
        Texture* m_texture = Texture::GetCommon(CommomTexture::Grid);
        Texture* m_texture2 = Texture::GetCommon(CommomTexture::Default);
        // Generate pure color shader
        Shader* texshader = Shader::GetCommon(CommonShader::Texture);
        Shader* baseshader = Shader::GetCommon(CommonShader::Texture);
        // Create material hold the shader
        Material* m_material1 = new Material(*texshader);
        m_material1->Name() = "color material 1";
        m_material1->SetTextureIndex("surface", 0);
        m_material1->SetTexture("surface", *m_texture);
        m_material1->SetVec3("color", vec3(1));

        Material* m_material2 = new Material(*baseshader);
        m_material2->Name() = "color material 2";
        m_material2->SetTextureIndex("surface", 0);
        m_material2->SetTexture("surface", *m_texture2);
        m_material2->SetVec3("color", vec3(1));

        // Apply to the cube object
        meshr1->SetMesh(mesh1);
        meshr1->SetMaterial(m_material1);
        meshr2->SetMesh(mesh2);
        meshr2->SetMaterial(m_material2);
        trans1->LocalPosition() = vec3(1, 2, 0);
        sphere->LocalPosition() = vec3(-1, 1, 0);
        cameratrans->LocalPosition() = vec3(0, 3, 5);
        for (int x = -10; x < 10; x++) {
            for (int z = -10; z < 10; z++) {
                EObject* floor_child = ObjectFactory::CreatePawn();
                std::string floor_name = "Floor ";
                floor_name += std::to_string(x);
                floor_name += ":";
                floor_name += std::to_string(z);
                floor_child->Name() = floor_name;
                CTransformation* plane = floor_child->GetRelateComponent<CTransformation>();
                CMeshRenderer* meshr_floor = floor_child->GetRelateComponent<CMeshRenderer>();
                meshr_floor->SetMesh(mesh3);
                meshr_floor->SetMaterial(m_material2);
                plane->LocalScale() = vec3(10, 1, 10);
                plane->LocalEualrAngle() = vec3(180, 0, 0);
                plane->LocalPosition() = vec3(x * 25, 0, z * 25);
                floor_child->SetParent(floor);
            }
        }

        // Upload scene
        m_scenes.push_back(m_scene);
        fileExplorer->SetVisible(false);
        helperTips->SetVisible(false);
        m_guiWindows.push_back(asset);
        m_guiWindows.push_back(fileExplorer);
        m_guiWindows.push_back(sceneViewer);
        m_guiWindows.push_back(properties);
        m_guiWindows.push_back(hierarchy);
        m_guiWindows.push_back(helperTips);
        m_guiWindows.push_back(console);
        m_guiWindows.push_back(debug);
    };
    void Update() override {
        EWindow::Update();
        if (post.m_updateSample) {
            Renderer::MainCamera().CameraFramebuffer().SetSamples(post.m_sample);
            post.m_updateSample = false;
        }
        m_renderCamera = std::vector<CCamera*>();
        if (selectCameraObject) {
            m_renderCamera.push_back(selectCameraObject);
        }
        shouldRenderScene = sceneViewer->Visible();
        updateScenes = shouldUpdateScene;
        renderScenes = shouldRenderScene;
        renderState = shouldRecordRenderState && sceneViewer->Visible();
        m_render = GetRenderState();
        switch (rendermode)
        {
        case 0: 
            wireframe = false;
            shaded = true;
            break;
        case 1:
            wireframe = true;
            shaded = false;
            break;
        case 2:
            wireframe = true;
            shaded = true;
            break;
        }
    }
    void DeleteAllScene() {
        for (auto s : m_scenes) {
            delete s;
        }
        m_scenes.clear();
        allScene = m_scenes;
    }
    void GUI() override {
        EWindow::GUI();
        UI::ImGui_DockspaceOverviewport();
        UI::ImGui_WindiwFlags wflags = UI::ImGui_WindiwFlags();
        wflags.MenuBar = true;
        if (UI::ImGui_BeginMainmenuBar()) {
            if (UI::ImGui_BeginMenu("File")) {
                if (UI::ImGui_BeginMenu("Load Scene")) {
                    if (UI::ImGui_MenuItem("Demo Scene")) {
                        DeleteAllScene();
                    }
                    if (UI::ImGui_MenuItem("Complex Model Test Scene")) {
                        DeleteAllScene();
                    }
                    if (UI::ImGui_MenuItem("Physics Test Scene")) {
                        DeleteAllScene();
                    }
                    if (UI::ImGui_MenuItem("Framebuffer Texture Test Scene")) {
                        DeleteAllScene();
                    }
                    UI::ImGui_EndMenu();
                }
                if (UI::ImGui_MenuItem("Exit")) {
                    Close();
                }
                UI::ImGui_EndMenu();
            }
            if (UI::ImGui_BeginMenu("Window")) {
                if (UI::ImGui_MenuItem("Asset", 0, asset->Visible())) {
                    asset->SetVisible(!asset->Visible());
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
                if (UI::ImGui_MenuItem("Debug Menu", 0, helperTips->Visible())) {
                    helperTips->SetVisible(!helperTips->Visible());
                }
                if (UI::ImGui_MenuItem("About")) {

                }
                UI::ImGui_EndMenu();
            }
            UI::ImGui_EndMainmenuBar();
        }
    }
    void Gizmo() override {
        //RendererDebug::DrawPlane(vec3(0, 10, 0), -Renderer::MainCamera().Host()->GetRelateComponent<CTransformation>()->GlobalPosition());
        //RendererDebug::DrawSphere(vec3(std::sin(EInput::Time()) * 10.f, 2, std::cos(EInput::Time()) * 10.f), 20);
        if (showGizmo) {
            // We can call the base for drawing all gizmo on the screen
            EWindow::Gizmo();
        }
    }
    void PostRender() override {
        // Default is render scene to window background
        // But we can disable that with override PostRender() function
        // The scene main camera is under EWindow memeber: m_camera
        sceneViewer->SetCam(&Renderer::MainCamera()); // Get main camera of the scene
        allScene = m_scenes;
        // Clean color depth buffer only
        CleanBuffer();
        // Render nothing
    }
};

int main()
{
    Logger::HideConsole();
    console = new ConsoleWindow();
    asset = new AssetWindow();
    fileExplorer = new FileExplorerWindow();
    sceneViewer = new SceneViewerWindow("Scene viewer");
    properties = new PropertiesWindow();
    hierarchy = new HierarchyWindow();
    helperTips = new HelperWindow();
    debug = new UI::ImGui_DebugWindow();
    // Register event
    // So everytime stdout is called, it can receive callback.
    Logger::RegisterLog(ConsoleWindow::AddMessage);
    wc.Vsync = false;
    w = new DemoWindow();
    w->Maximum();
    w->Start();
    w->Mainloop();
    delete w;
    return 0;
};