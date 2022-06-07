#pragma once
// Include std library
#include <unordered_map>

// Include third party library
#include <glm/glm.hpp>

// Include tara library
#include "../config.h"
#include "../asset.h"
#include "../emath.h"
#include "renderer_batch.h"
#include "renderer_command.h"
#include "renderer_control.h"
#include "renderer_debug.h"
#include "renderer_state.h"

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
}