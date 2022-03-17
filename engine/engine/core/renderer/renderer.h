#pragma once
// Include std library
#include <unordered_map>

// Include third party library
#include <glm/glm.hpp>

// Include tara library
#include "../config.h"
#include "../asset.h"
#include "../emath.h"

namespace Tara {
	class TARA_API Mesh;
	class TARA_API Material;
	class TARA_API SceneObject;
	class TARA_API LightComponent;
	class TARA_API CameraComponent;
	class TARA_API SceneObject;
	class TARA_API FrameBuffer;
	class TARA_API TransformationComponent;
	struct TARA_API Frustum;

	enum class TARA_API DrawingMode {
		Shaded,
		Wireframe,
		Reflection,
		Depth
	};

	/*
		Summary:
			Each mainloop render result.
	*/
	struct TARA_API RenderState {
	public:
		double_t FPS;
		double_t CPU_Usage;
		double_t GPU_Usage;
		double_t RAM_Usage;
		size_t DrawCall;
		size_t Vertices;
		size_t Triangle;
	};

	struct TARA_API RenderCommandKey {
	public:
		RenderCommandKey(Mesh* me, Material* mat, int32_t _x, int32_t _y, int32_t _z)
			: mesh(me), material(mat), x(_x), y(_y), z(_z) {}
		Mesh* mesh = nullptr;
		Material* material;
		int32_t x;
		int32_t y;
		int32_t z;

		constexpr bool operator==(const RenderCommandKey& other) const;
		constexpr bool operator!=(const RenderCommandKey& other) const;
	};

	struct TARA_API RenderCommandKeyHash {
		size_t operator()(const RenderCommandKey& k) const;
	};

	/*
	* 
		Summary:
			Renderer utilities.
	*/
	class TARA_API Renderer
	{
	public:
		static Renderer& Singleton();
		/*
			Summary:
				Current use framebuffer.
		*/
		FrameBuffer* primarydisplay = nullptr;
		/*
			Summary:
				Current use view matrix.
		*/
		glm::mat4 view = glm::mat4(1);
		/*
			Summary:
				Current use projection matrix.
		*/
		glm::mat4 projection = glm::mat4(1);

		DrawingMode drawingMode = DrawingMode::Shaded;
		bool wireframeMode = false;
		bool shadedMode = false;
		bool m_renderRecord = true;
		RenderState m_RenderState = RenderState();

		/*
			Summary:
				This method will only use when it's ingame mode.
				When it's editor mode, the default camera will take over.
		*/
		void RegisterMainCamera(SceneObject* so);
		/*
			Summary:
				This will generate a camera that is detached to scene.
				It's purely for editor use camera.
		*/
		void GenerateSceneCamera();
		Frustum& CameraFrustum();
		CameraComponent& MainCamera();
		TransformationComponent& MainCameraBody();

	private:
		static Renderer* m_Singleton;
		Frustum m_cameraFrustum = Frustum();
		CameraComponent* m_camera = nullptr;
		SceneObject* m_cameraObject = nullptr;
		TransformationComponent* m_cameraTrans = nullptr;
	};


	class TARA_API BatchRenderer {
	public:
		static BatchRenderer& Singleton();
		void AddRender(Mesh* mesh, Material* material, TransformationComponent* trans);
		void AddRender(Mesh* mesh, Material* material, glm::mat4 trans);
		/*
			Summary:
				Clean the render queue.
		*/
		void Clean();
		/*
			Summary:
				Render entire scenes.
		*/
		void DrawCall();
		/*
			Summary:
				Use specific material the render entire scenes.
		*/
		void DrawCall(Material* material, bool special = true);

	private:
		static BatchRenderer* m_Singleton;
		std::unordered_map<RenderCommandKey, std::vector<glm::mat4>, RenderCommandKeyHash> m_renderCommands = std::unordered_map<RenderCommandKey, std::vector<glm::mat4>, RenderCommandKeyHash>();
	};

	/*
		Render the debug view on screen.
		All the function call should during the Gizmo stage.
	*/
	class TARA_API RendererDebug {
	public:
		static RendererDebug& Singleton();
		float_t& Alpha();
		glm::vec3& Colro();
		void DrawLine(const glm::vec3 pos1, const glm::vec3 pos2);

	private:
		static RendererDebug* m_Singleton;
		glm::vec3 color = glm::vec3(1);
		float_t alpha = 1;
	};


	/*
		Generate gizmo that can use for control object.
		All the function call should during the Gizmo stage.
	*/
	class TARA_API RendererControl {

	};


	class TARA_API RendererTransformationUniformBlock {
	public:
		static void Initialization();
		static void Shutdown();
		static void SetModel(glm::mat4 v);
		static void SetView(glm::mat4 v);
		static void SetProejction(glm::mat4 v);
		static uint32_t GetUniformBlockID();
	private:
		static uint32_t ubo;
	};

	class TARA_API RendererLightingUniformBlock {
	public:
		static void Initialization(int32_t supportLightCount);
		static void Shutdown();
		static void SetLight(int32_t index, LightComponent* light);
		static uint32_t GetUniformBlockID();
	private:
		static uint32_t ubo;
		static int32_t lightCount;
	};

	inline TARA_API Renderer* Renderer::m_Singleton = new Renderer();
	inline TARA_API BatchRenderer* BatchRenderer::m_Singleton = new BatchRenderer();
	inline TARA_API RendererDebug* RendererDebug::m_Singleton = new RendererDebug();
}