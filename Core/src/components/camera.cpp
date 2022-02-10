#include "components/camera.h"
#include <ewindow.h>
#include <components/transformation.h>
#include <glm/gtx/quaternion.hpp>
#include <renderer.h>
#ifndef TARA_NO_IMGUI
	#include <gui/gui_lowlevel.h>
#endif

namespace Tara {
	CCamera::~CCamera()
	{
		delete frame;
	}
	void CCamera::GUI()
	{
#ifndef TARA_NO_IMGUI
		CCamera& maincamera = Renderer::MainCamera();
		
		UI::ImGui_BeginDisabled(true);
		if (UI::ImGui_Button("Set As Main")) {
			
		}
		UI::ImGui_EndDisabled();
#endif
	}
	glm::mat4 CCamera::ViewMatrix()
	{
		CTransformation* trans = m_host->GetRelateComponent<CTransformation>();
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
	glm::mat4 CCamera::ProjectionMatrix()
	{
		return glm::perspective(glm::radians(m_fov), GetAspectRatio(), m_nearPlane, m_farPlane);
	}

	void CCamera::Blit()
	{
		frame->Blit();
	}
	void CCamera::Use()
	{
		frame->Bind();
	}
	void CCamera::Unuse()
	{
		frame->Unbind();
	}
	void CCamera::Bind()
	{
		frame->BindTexture();
	}
	void CCamera::Unbind()
	{
		frame->UnbindTexture();
	}
	Frustum CCamera::GetFrustum()
	{
		return Frustum::CreateFrustumFromCamera(*this, GetAspectRatio(), m_fov, m_nearPlane, m_farPlane);
	}
	FrameBuffer& CCamera::CameraFramebuffer()
	{
		return *frame;
	}
	uint32_t CCamera::TextureID()
	{
		return frame->TextureID();
	}
	float_t CCamera::GetAspectRatio()
	{
		if (m_fullscreen && IsCurrentWindowIconify()) {
			EWindow* w = CurrentWindow();
			glm::ivec2 size = w == nullptr ? glm::ivec2(1) : w->GetEWindowSize();
			return (float_t)size.x / (float_t)size.y;
		}
		else {
			return (float_t)m_width / (float_t)m_height;
		}
	}
}