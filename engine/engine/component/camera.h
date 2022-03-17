#pragma once
// Import Tara engine library
#include "../core/config.h"
#include "component.h"

namespace Tara {
	struct TARA_API Frustum;
	class TARA_API DisplayFrameBuffer;
	class TARA_API SceneObject;

	/*
		Summary:
			Camera perspective types.
	*/
	enum class TARA_API CameraType {
		Perspective,
		Orthographic
	};
	/*
		Summary:
			Camera object.
			Scene will iterate through all camera to render.
	*/
	class TARA_API CameraComponent : public Component {
	public:
		DEFAULT_HEADER_CTOR(CameraComponent);
		virtual ~CameraComponent();
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
				Blit camera framebuffer.
		*/
		void Blit();
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
		bool Good();
		void Unbind();
		Frustum GetFrustum();
		DisplayFrameBuffer& CameraFramebuffer();
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
		float_t m_farPlane = 500;

	private:
		float_t GetAspectRatio();
		// Camera framebuffer
		DisplayFrameBuffer* frame;
	};
}