#include "camera.h"
// Import Third party library
#include <glm/gtx/quaternion.hpp>

// Import Tara engine library
#include "../core/framebuffer/framebuffer.h"
#include "../core/scene_object/scene_object.h"
#include "../core/window/ewindow.h"
#include "../core/renderer/renderer.h"
#include "../core/emath.h"
#include "../system/system.h"
#include "transformation.h"

namespace Tara {
	DEFAULT_SRC_CTOR(CameraComponent) {
		SystemRegister& sys = SystemRegister::Singleton();
		frame = new DisplayFrameBuffer();
		sys.AppendComponent<CameraComponent>(this);
	}
	CameraComponent::~CameraComponent()
	{
		if(frame != nullptr) delete frame;
	}
	glm::mat4 CameraComponent::ViewMatrix()
	{
		TransformationComponent* trans = Host().GetRelateComponent<TransformationComponent>();
		if (trans == nullptr) return glm::mat4(1);
		glm::vec3 eu = trans->GlobalEualrAngle();
		glm::mat4 r = glm::mat4(1);
		r = glm::rotate(r, glm::radians(eu.x), glm::vec3(1, 0, 0));
		r = glm::rotate(r, glm::radians(eu.y), glm::vec3(0, 1, 0));
		r = glm::rotate(r, glm::radians(eu.z), glm::vec3(0, 0, 1));
		r = glm::translate(r, -trans->GlobalToLocalPoint(glm::vec3(0)));
		return r;
		//return glm::lookAt(trans->GlobalPosition(), trans->GlobalPosition() + trans->Forward(), glm::vec3(0, 1, 0));
	}
	glm::mat4 CameraComponent::ProjectionMatrix()
	{
		return glm::perspective(glm::radians(m_fov), GetAspectRatio(), m_nearPlane, m_farPlane);
	}

	void CameraComponent::Blit()
	{
		frame->Blit();
	}
	void CameraComponent::Use()
	{
		frame->Bind();
	}
	void CameraComponent::Unuse()
	{
		frame->Unbind();
	}
	void CameraComponent::Bind()
	{
		frame->BindTexture();
	}
	bool CameraComponent::Good()
	{
		return frame != nullptr;
	}
	void CameraComponent::Unbind()
	{
		frame->UnbindTexture();
	}
	Frustum CameraComponent::GetFrustum()
	{
		return Frustum::CreateFrustumFromCamera(*this, GetAspectRatio(), m_fov, m_nearPlane, m_farPlane);
	}
	DisplayFrameBuffer& CameraComponent::CameraFramebuffer()
	{
		return *frame;
	}
	uint32_t CameraComponent::TextureID()
	{
		return frame->TextureID();
	}
	float_t CameraComponent::GetAspectRatio()
	{
		if (m_fullscreen) {
			EWindow* w = CurrentWindow();
			glm::ivec2 size = w == nullptr ? glm::ivec2(1) : w->GetEWindowSize();
			return (float_t)size.x / (float_t)size.y;
		}
		else {
			return (float_t)m_width / (float_t)m_height;
		}
	}
}