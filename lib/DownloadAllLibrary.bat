@echo off
git clone -b v5.2.2 https://github.com/assimp/assimp.git
git clone -b v3.6.0 https://github.com/libarchive/libarchive.git
git clone -b v2.9.1 https://github.com/pybind/pybind11.git
git clone -b 3.3.6 https://github.com/glfw/glfw.git
git clone https://github.com/rxi/uuid4.git
git clone -b 0.9.9.8 https://github.com/g-truc/glm.git
git clone -b v1.6 https://github.com/bombela/backward-cpp.git
git clone -b v3.10.5 https://github.com/nlohmann/json.git
git clone https://github.com/nothings/stb.git
git clone https://github.com/FFmpeg/FFmpeg.git
git clone -b openal-soft-1.21.0 https://github.com/kcat/openal-soft.git
git clone https://github.com/tkislan/base64.git

mkdir imgui
cd imgui
git clone -b docking https://github.com/ocornut/imgui.git
git clone https://github.com/BalazsJako/ImGuiColorTextEdit.git
git clone -b v0.9 https://github.com/thedmd/imgui-node-editor.git
git clone -b 1.83 https://github.com/CedricGuillemet/ImGuizmo.git
git clone https://github.com/juliettef/imgui_markdown.git
git clone https://github.com/patrickcjk/imgui-notify.git
cd ../
