#pragma once
#include <config.h>
#include <framebuffer.h>
#include <components/component.h>

namespace Tara {
	/*
		Summary:
			Camera perspective types.
	*/
	enum class DllExport CameraType {
		Perspective,
		Orthographic
	};
	/*
		Summary:
			Camera object.
			Scene will iterate through all camera to render.
	*/
	class DllExport CCamera : public EComponent {
	public:
		DEFAULT_CTOR_IMPLE(CCamera);
		~CCamera();
		/*
			Summary:
				Get camera view matrix.
		*/
		glm::mat4 ViewMatrix();
		/*
			Summary:
				Get camera projection matrix.
		*/
		glm::mat4 ProjectionMatrix();
		/*
			Summary:
				Binding camera framebuffer.
		*/
		void Use();
		/*
			Summary:
				Unbinding camera framebuffer.
		*/
		void Unuse();
		/*
			Summary:
				Binding camera framebuffer texture.
		*/
		void Bind();
		/*
			Summary:
				Unbinding camera framebuffer texture.
		*/
		void Unbind();
		uint32_t TextureID();

		// Camera types, default: perspective
		CameraType m_type = CameraType::Perspective;
		bool m_fullscreen = false;
		// Field of view
		float_t m_fov = 60;
		// Orthographic camera view size
		float_t m_size = 5;
		// Screen width
		float_t m_width = 1920;
		// Screen height
		float_t m_height = 1080;
		// Near plane
		float_t m_nearPlane = 0.01f;
		// Far plane
		float_t m_farPlane = 1000;

	private:
		// Camera framebuffer
		FrameBuffer* frame = new FrameBuffer();
	};
}