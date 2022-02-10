#include "components/transformation.h"
#include <eobject.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#ifndef TARA_NO_IMGUI
	#include <gui/gui_lowlevel.h>
#endif
namespace Tara {
	void CTransformation::GUI()
	{
		#ifndef TARA_NO_IMGUI
		UI::ImGui_DragVec3("Position", &m_position, 0.1f);
		UI::ImGui_DragVec3("Eular Angle", &m_eularAngle, 0.1f);
		UI::ImGui_DragVec3("Scale", &m_scale, 0.1f);
		if (DebugMenu()) {
			glm::vec3 gp = GlobalPosition();
			glm::vec3 ge = GlobalEualrAngle();
			glm::vec3 gs = GlobalScale();
			UI::ImGui_LabelText("World Position", "%f, %f, %f", gp.x, gp.y, gp.z);
			UI::ImGui_LabelText("World EularAngle", "%f, %f, %f", ge.x, ge.y, ge.z);
			UI::ImGui_LabelText("World Scale", "%f, %f, %f", gs.x, gs.y, gs.z);
		}
		#endif
	}
	void CTransformation::Translate(float_t x, float_t y, float_t z, Space _s)
	{
		Translate(glm::vec3(x, y, z));
	}
	void CTransformation::Translate(glm::vec3 v, Space _s)
	{
		switch (_s)
		{
		case Tara::Space::World:
		{
			EObject* parent = m_host->Parent();
			if (!parent) {
				m_position += v;
			}
			else {
				CTransformation* cparent = parent->GetRelateComponent<CTransformation>();
				if (!cparent) {
					m_position += v;
				}
				else {
					glm::vec3 v3 = cparent->LocalToGlobal() * glm::vec4(v.x, v.y, v.z, 0);
					m_position += glm::normalize(v3) * glm::length(v3);
				}
			}
			break;
		}
		case Tara::Space::Local:
		{
			glm::vec3 v3 = glm::inverse(LocalToGlobal()) * glm::vec4(v.x, v.y, v.z, 0);
			m_position += v3;
			break;
		}
		}
	}
	void CTransformation::Rotate(float_t x, float_t y, float_t z, Space _s)
	{
		switch (_s)
		{
		case Tara::Space::World:
			const glm::vec3 v = glm::vec3(x, y, z);
			m_eularAngle += GlobalToLocalVector(v);
			break;
		case Tara::Space::Local:
			m_eularAngle += glm::vec3(x, y, z);
			break;
		}
	}
	void CTransformation::Rotate(float_t x, float_t y, Space _s)
	{
		Rotate(x, y, 0, _s);
	}
	void CTransformation::Rotate(glm::vec3 v, Space _s)
	{
		Rotate(v.x, v.y, v.z, _s);
	}
	glm::vec3& CTransformation::Forward()
	{
		glm::vec3 v = GlobalToLocalDirection(glm::vec3(0, 0, -1)); return v;
	}
	glm::vec3& CTransformation::Backward()
	{
		glm::vec3 v = GlobalToLocalDirection(glm::vec3(0, 0, 1)); return v;
	}
	glm::vec3& CTransformation::Left()
	{
		glm::vec3 v = GlobalToLocalDirection(glm::vec3(-1, 0, 0)); return v;
	}
	glm::vec3& CTransformation::Right()
	{
		glm::vec3 v = GlobalToLocalDirection(glm::vec3(1, 0, 0)); return v;
	}
	glm::vec3& CTransformation::Up()
	{
		glm::vec3 v = GlobalToLocalDirection(glm::vec3(0, 1, 0)); return v;
	}
	glm::vec3& CTransformation::Down()
	{
		glm::vec3 v = GlobalToLocalDirection(glm::vec3(0, -1, 0)); return v;
	}
	const glm::mat4 CTransformation::LocalMatrix()
	{
		glm::mat4 r = glm::mat4(1);
		r = glm::translate(r, -m_position);
		r = glm::rotate(r, glm::radians(m_eularAngle.x), glm::vec3(1, 0, 0));
		r = glm::rotate(r, glm::radians(m_eularAngle.y), glm::vec3(0, 1, 0));
		r = glm::rotate(r, glm::radians(m_eularAngle.z), glm::vec3(0, 0, 1));
		r = glm::scale(r, m_scale);
		return r;
	}
	const glm::mat4 CTransformation::LocalToGlobal()
	{
		EObject* parent = m_host->Parent();
		glm::mat4 r = LocalMatrix();
		if (parent) {
			CTransformation* trans = parent->GetRelateComponent<CTransformation>();
			if (trans) {
				r = trans->LocalToGlobal() * r;
			}
		}
		return r;
	}
	const glm::mat4 CTransformation::GlobalToLocal()
	{
		EObject* parent = m_host->Parent();
		glm::mat4 r = LocalMatrix();
		if (parent) {
			CTransformation* trans = parent->GetRelateComponent<CTransformation>();
			if (trans) {
				r = glm::inverse(trans->LocalToGlobal() * r);
			}
		}
		return r;
	}
	glm::vec3 CTransformation::LocalToGlobalPoint(const glm::vec3& v)
	{
		return LocalToGlobal() * glm::vec4(v.x, v.y, v.z, 1);
	}
	glm::vec3 CTransformation::LocalToGlobalVector(const glm::vec3& v)
	{
		return LocalToGlobal() * glm::vec4(v.x, v.y, v.z, 0);
	}
	glm::vec3 CTransformation::LocalToGlobalDirection(const glm::vec3& v)
	{
		// Mark, this might wrong ?
		return glm::normalize(GlobalRotation() * v);
	}
	glm::vec3 CTransformation::GlobalToLocalPoint(const glm::vec3& v)
	{
		return GlobalToLocal() * glm::vec4(v.x, v.y, v.z, 1);
	}
	glm::vec3 CTransformation::GlobalToLocalVector(const glm::vec3& v)
	{
		return GlobalToLocal() * glm::vec4(v.x, v.y, v.z, 0);
	}
	glm::vec3 CTransformation::GlobalToLocalDirection(const glm::vec3& v)
	{
		// Mark, this might wrong ?
		return glm::normalize(LocalRotation() * v);
	}
	glm::vec3 CTransformation::GlobalPosition()
	{
		return LocalToGlobalPoint(glm::vec3(0));
	}
	glm::quat CTransformation::GlobalRotation()
	{
		return glm::quat(glm::radians(GlobalEualrAngle()));
	}
	glm::vec3 CTransformation::GlobalEualrAngle()
	{
		EObject* parent = m_host->Parent();
		glm::vec3 r = m_eularAngle;
		if (parent) {
			CTransformation* trans = parent->GetRelateComponent<CTransformation>();
			if (trans) {
				return r += trans->GlobalEualrAngle();
			}
		}
		return r;
	}
	glm::vec3 CTransformation::GlobalScale()
	{
		return LocalToGlobalPoint(m_scale);
	}
	glm::vec3& CTransformation::LocalPosition()
	{
		return m_position;
	}
	glm::quat CTransformation::LocalRotation()
	{
		return glm::quat(glm::radians(m_eularAngle));
	}
	glm::vec3& CTransformation::LocalEualrAngle()
	{
		return m_eularAngle;
	}
	glm::vec3& CTransformation::LocalScale()
	{
		return m_scale;
	}
}