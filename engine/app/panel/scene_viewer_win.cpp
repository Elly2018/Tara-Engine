#include "scene_viewer_win.h"
#include <glm/glm.hpp>
#include "../../editor/editor_lowlevel.h"
#include "../../engine/component/camera.h"
#include "global_state.h"

namespace Tara {
	namespace UI {
        SceneViewerWindow::SceneViewerWindow(const char* title) : ImGui_SceneView(title, "Scene Viewer Frame") {
            ImGui_WindiwFlags& m_flags = FrameFlags();
            m_flags.MenuBar = true;
            m_flags.AlwaysAutoResize = true;
        }
        void SceneViewerWindow::MenuBar() {
            PanelGlobalState& pg = PanelGlobalState::Singleton();
            Renderer& renderer = Renderer::Singleton();
            // This big chunk of menu setup code is control the render flow and pg.post processing config
            if (ImGui_BeginMenubar()) {
                if (ImGui_BeginMenu("Display")) {
                    if (ImGui_MenuItem("Shaded", 0, pg.rendermode == 0)) {
                        pg.rendermode = 0;
                    }
                    if (ImGui_MenuItem("Wireframe", 0, pg.rendermode == 1)) {
                        pg.rendermode = 1;
                    }
                    if (ImGui_MenuItem("Shaded + Wireframe", 0, pg.rendermode == 2)) {
                        pg.rendermode = 2;
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
                        if (ImGui_MenuItem("None", 0, pg.post.m_sample == MSAASamples::None)) {
                            pg.post.m_sample = MSAASamples::None;
                            pg.post.m_update = true;
                        }
                        if (ImGui_MenuItem("2x", 0, pg.post.m_sample == MSAASamples::_2x)) {
                            pg.post.m_sample = MSAASamples::_2x;
                            pg.post.m_update = true;
                        }
                        if (ImGui_MenuItem("4x", 0, pg.post.m_sample == MSAASamples::_4x)) {
                            pg.post.m_sample = MSAASamples::_4x;
                            pg.post.m_update = true;
                        }
                        if (ImGui_MenuItem("8x", 0, pg.post.m_sample == MSAASamples::_8x)) {
                            pg.post.m_sample = MSAASamples::_8x;
                            pg.post.m_update = true;
                        }
                        if (ImGui_MenuItem("16x", 0, pg.post.m_sample == MSAASamples::_16x)) {
                            pg.post.m_sample = MSAASamples::_16x;
                            pg.post.m_update = true;
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
                if (ImGui_MenuItem("Gizmo", 0, pg.showGizmo)) {
                    pg.showGizmo = !pg.showGizmo;
                }
                ImGui_EndMenubar();
            }

            if (pg.post.m_update) {
                renderer.MainCamera().CameraFramebuffer().SetSamples(pg.post.m_sample);
                pg.post.m_update = false;
            }
        }
        void SceneViewerWindow::PostRender() {
            PanelGlobalState& pg = PanelGlobalState::Singleton();
            pg.shouldUpdateScene = ImGui_IsWindowFocued();
            glm::vec2 wpos = ImGui_GetWindowPos();
            glm::vec2 wsize = ImGui_GetWindowSize();
            DefaultContent();
            if (debugWin) {
                near = m_camera->m_nearPlane;
                far = m_camera->m_farPlane;
                ImGui_SetNextWindowPos(wpos.x + m_leftPadding + 20, wpos.y + 50);
                ImGui_BeginChild("Debug State", 180, 220, true);
                ImGui_Text("FPS: %f", pg.m_render.FPS);
                ImGui_Text("CPU usage: %f", pg.m_render.CPU_Usage);
                ImGui_Text("GPU usage: %f", pg.m_render.GPU_Usage);
                ImGui_Text("Draw call: %i", pg.m_render.DrawCall);
                ImGui_Text("Vertices count: %i", pg.m_render.Vertices);
                ImGui_Text("Triangles count: %i", pg.m_render.Triangle);
                ImGui_DragFloat("Near", &near);
                ImGui_DragFloat("Far", &far);
                ImGui_Checkbox("Render State", &pg.shouldRecordRenderState);
                ImGui_EndChild();

                m_camera->m_nearPlane = near;
                m_camera->m_farPlane = far;
            }
            if (pg.selectCameraObject) {
                ImGui_SetNextWindowPos(wpos.x + wsize.x - 320, wpos.y + wsize.y - 260);
                ImGui_BeginChild("Camera Select Viewer", 300, 200, true);
                RenderCamera(pg.selectCameraObject);
                ImGui_EndChild();
            }
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