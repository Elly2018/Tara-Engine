#include "scene_viewer_win.h"
#include <glm/glm.hpp>
#include "editor/editor_lowlevel.h"
#include "engine/component/camera.h"
#include "engine/core/renderer/renderer.h"
#include "engine/core/framebuffer/framebuffer.h"
#include "appcore/global_states.h"

namespace Tara {
	namespace UI {
        SceneViewerWindow::SceneViewerWindow() : SceneViewerWindow("Scene") {}
        SceneViewerWindow::SceneViewerWindow(const char* title) : ImGui_SceneView(title, "Scene Viewer Frame") {
            ImGui_WindiwFlags& m_flags = FrameFlags();
            m_flags.MenuBar = true;
            m_flags.AlwaysAutoResize = true;
        }
        void SceneViewerWindow::MenuBar() {
            Global::GlobalStatePackage& psg = Global::GlobalStatePackage::Singleton();
            int32_t rendermode = psg.state_int.GetState("RenderMode");
            int32_t msaa = psg.state_int.GetState("MSAA");
            bool gizmo = psg.state_bool.GetState("Gizmo");
            bool post_update = psg.state_bool.GetState("Post_Update");

            Renderer& renderer = Renderer::Singleton();
            // This big chunk of menu setup code is control the render flow and pg.post processing config
            if (ImGui_BeginMenubar()) {
                if (ImGui_BeginMenu("Display")) {
                    if (ImGui_MenuItem("Shaded", 0, rendermode == 0)) {
                        rendermode = 0;
                    }
                    if (ImGui_MenuItem("Wireframe", 0, rendermode == 1)) {
                        rendermode = 1;
                    }
                    if (ImGui_MenuItem("Shaded + Wireframe", 0, rendermode == 2)) {
                        rendermode = 2;
                    }
                    ImGui_Separator();
                    if (ImGui_MenuItem("Light")) {

                    }
                    if (ImGui_MenuItem("Shadow")) {

                    }
                    if (ImGui_MenuItem("Reflection")) {

                    }
                    ImGui_EndMenu();
                }
                if (ImGui_BeginMenu("Post Processing")) {
                    if (ImGui_MenuItem("Skybox")) {

                    }
                    if (ImGui_MenuItem("Fog")) {

                    }
                    if (ImGui_MenuItem("Motion Blur")) {

                    }
                    if (ImGui_MenuItem("Flare")) {

                    }
                    ImGui_Separator();
                    if (ImGui_BeginMenu("MSAA")) {
                        if (ImGui_MenuItem("None", 0, (MSAASamples)msaa == MSAASamples::None)) {
                            msaa = (int32_t)MSAASamples::None;
                            post_update = true;
                        }
                        if (ImGui_MenuItem("2x", 0, (MSAASamples)msaa == MSAASamples::_2x)) {
                            msaa = (int32_t)MSAASamples::_2x;
                            post_update = true;
                        }
                        if (ImGui_MenuItem("4x", 0, (MSAASamples)msaa == MSAASamples::_4x)) {
                            msaa = (int32_t)MSAASamples::_4x;
                            post_update = true;
                        }
                        if (ImGui_MenuItem("8x", 0, (MSAASamples)msaa == MSAASamples::_8x)) {
                            msaa = (int32_t)MSAASamples::_8x;
                            post_update = true;
                        }
                        if (ImGui_MenuItem("16x", 0, (MSAASamples)msaa == MSAASamples::_16x)) {
                            msaa = (int32_t)MSAASamples::_16x;
                            post_update = true;
                        }
                        ImGui_EndMenu();
                    }
                    if (ImGui_MenuItem("Ambient Occlusion")) {

                    }
                    if (ImGui_MenuItem("Bloom")) {

                    }
                    if (ImGui_MenuItem("Vignette")) {

                    }
                    ImGui_EndMenu();
                }
                if (ImGui_BeginMenu("Gizmo")) {
                    if (ImGui_MenuItem("Object Transformation Axis")) {

                    }
                    ImGui_EndMenu();
                }
                if (ImGui_BeginMenu("Aspect ratio")) {
                    if (ImGui_MenuItem("4:3")) {

                    }
                    if (ImGui_MenuItem("16:9")) {

                    }
                    ImGui_Separator();
                    if (ImGui_MenuItem("800x600")) {

                    }
                    if (ImGui_MenuItem("1280x800")) {

                    }
                    if (ImGui_MenuItem("1600x900")) {

                    }
                    if (ImGui_MenuItem("1920x1080")) {

                    }
                    ImGui_EndMenu();
                }
                if (ImGui_MenuItem("Debug", 0, debugWin)) {
                    debugWin = !debugWin;
                }
                if (ImGui_MenuItem("Gizmo", 0, gizmo)) {
                    gizmo = !gizmo;
                }
                ImGui_EndMenubar();
            }

            if (post_update) {
                renderer.MainCamera().CameraFramebuffer().SetSamples((MSAASamples)msaa);
                post_update = false;
            }
            psg.state_int.SetState("RenderMode", rendermode);
            psg.state_int.SetState("MSAA", msaa);
            psg.state_bool.SetState("Gizmo", gizmo);
            psg.state_bool.SetState("Post_Update", post_update);
        }
        void SceneViewerWindow::PostRender() {
            Global::GlobalStatePackage& psg = Global::GlobalStatePackage::Singleton();

            psg.state_bool.SetState("Should_Update_Scene", ImGui_IsWindowFocued());
            RenderState renderstate = psg.state_renderState.GetState("Current", RenderState());
            bool record_renderstate = psg.state_bool.GetState("Should_Record_Render_State", true);
            CameraComponent* selectCamera = psg.state_camera.GetState("SelectCamera");
            glm::vec2 wpos = ImGui_GetWindowPos();
            glm::vec2 wsize = ImGui_GetWindowSize();
            DefaultContent();

            if (debugWin) {
                near = m_camera->m_nearPlane;
                far = m_camera->m_farPlane;
                ImGui_SetNextWindowPos(wpos.x + m_leftPadding + 20, wpos.y + 50);
                ImGui_BeginChild("Debug State", 180, 220, true);
                ImGui_Text("FPS: %f", renderstate.FPS);
                ImGui_Text("CPU usage: %f", renderstate.CPU_Usage);
                ImGui_Text("GPU usage: %f", renderstate.GPU_Usage);
                ImGui_Text("Draw call: %i", renderstate.DrawCall);
                ImGui_Text("Vertices count: %i", renderstate.Vertices);
                ImGui_Text("Triangles count: %i", renderstate.Triangle);
                ImGui_DragFloat("Near", &near);
                ImGui_DragFloat("Far", &far);
                ImGui_Checkbox("Render State", &record_renderstate);
                ImGui_EndChild();

                m_camera->m_nearPlane = near;
                m_camera->m_farPlane = far;
            }
            if (selectCamera) {
                ImGui_SetNextWindowPos(wpos.x + wsize.x - 320, wpos.y + wsize.y - 260);
                ImGui_BeginChild("Camera Select Viewer", 300, 200, true);
                RenderCamera(selectCamera);
                ImGui_EndChild();
            }

            psg.state_renderState.SetState("Current", renderstate);
            psg.state_bool.SetState("Should_Record_Render_State", record_renderstate);
            psg.state_camera.SetState("SelectCamera", selectCamera);
        }
        void SceneViewerWindow::SetCam(CameraComponent* c) {
            m_camera = c;
        }
        bool SceneViewerWindow::HaveCam()
        {
            return m_camera != nullptr;
        }
	}
}