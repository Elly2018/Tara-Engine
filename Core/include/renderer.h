#pragma once
#include <config.h>
#include <material.h>
#include <framebuffer.h>
#include <glm/glm.hpp>
#include <emath.h>

namespace Tara {
	class DllExport EObject;
	/*
		Summary:
			Each mainloop render result.
	*/
	struct DllExport RenderState {
	public:
		double_t FPS;
		double_t CPU_Usage;
		double_t GPU_Usage;
		double_t RAM_Usage;
		size_t DrawCall;
		size_t Vertices;
		size_t Triangle;
	};

	/*
		Summary:
			Renderer utilities.
	*/
	class DllExport Renderer
	{
	public:
		/*
			Summary:
				Current use framebuffer.
		*/
		static FrameBuffer* primarydisplay;
		/*
			Summary:
				Current use view matrix.
		*/
		static glm::mat4 view;
		/*
			Summary:
				Current use projection matrix.
		*/
		static glm::mat4 projection;
		static bool wireframeMode;
		static bool shadedMode;
		static bool m_renderRecord;
		static Material* pureColor;
		static RenderState m_RenderState;

		static Frustum& CameraFrustum();
		static CCamera& MainCamera();
		static CTransformation& MainCameraBody();
		static void GenerateSceneCamera();

	private:
		static Frustum m_cameraFrustum;
		static CCamera* m_camera;
		static EObject* m_cameraObject;
		static CTransformation* m_cameraTrans;
	};

	/*
		Render the debug view on screen.
		All the function call should during the Gizmo stage.
	*/
	class DllExport RendererDebug {
	public:
		static float_t& Alpha();
		static glm::vec3& Colro();
		static void DrawLine(const glm::vec3 pos1, const glm::vec3 pos2);
		static void DrawSphere(const glm::vec3 pos, const float_t radius = 1);
		static void DrawCube(const glm::vec3 pos, const glm::vec3 scale = glm::vec3(1));
		static void DrawPlane(const glm::vec3 pos, const glm::vec3 normal, const glm::vec2 size = glm::vec2(1));
	private:
		static glm::vec3 color;
		static float_t alpha;
	};

	/*
		Generate gizmo that can use for control object.
		All the function call should during the Gizmo stage.
	*/
	class DllExport RendererControl {

	};
}