#include "components/camera.h"
#include <ewindow.h>
#include <components/transformation.h>
#include <glm/gtx/quaternion.hpp>

namespace Tara {
	CCamera::~CCamera()
	{
		delete frame;
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
		EWindow* w = CurrentWindow();
		if (m_fullscreen && IsCurrentWindowIconify()) {
			EWindow* w = CurrentWindow();
			glm::ivec2 size = w == nullptr ? glm::ivec2(1) : w->GetEWindowSize();
			return glm::perspective(glm::radians(m_fov), (float_t)size.x / (float_t)size.y, m_nearPlane, m_farPlane);
		}
		else {
			return glm::perspective(glm::radians(m_fov), (float_t)m_width / (float_t)m_height, m_nearPlane, m_farPlane);
		}
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
	uint32_t CCamera::TextureID()
	{
		return frame->GetTextureID();
	}
}