#include "transformation.h"

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Tara {
	TransformationComponent::~TransformationComponent()
	{
	}
	void TransformationComponent::Translate(float_t x, float_t y, float_t z, Space _s)
	{
		Translate(glm::vec3(x, y, z));
	}
	void TransformationComponent::Translate(glm::vec3 v, Space _s)
	{
		switch (_s)
		{
		case Tara::Space::World:
		{
			SceneObject* parent = m_host->Parent();
			if (!parent) {
				m_position += v;
			}
			else {
				TransformationComponent* cparent = parent->GetRelateComponent<TransformationComponent>();
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
	void TransformationComponent::Rotate(float_t x, float_t y, float_t z, Space _s)
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
	void TransformationComponent::Rotate(float_t x, float_t y, Space _s)
	{
		Rotate(x, y, 0, _s);
	}
	void TransformationComponent::Rotate(glm::vec3 v, Space _s)
	{
		Rotate(v.x, v.y, v.z, _s);
	}
	glm::vec3& TransformationComponent::Forward()
	{
		glm::vec3 v = GlobalToLocalDirection(glm::vec3(0, 0, -1)); return v;
	}
	glm::vec3& TransformationComponent::Backward()
	{
		glm::vec3 v = GlobalToLocalDirection(glm::vec3(0, 0, 1)); return v;
	}
	glm::vec3& TransformationComponent::Left()
	{
		glm::vec3 v = GlobalToLocalDirection(glm::vec3(-1, 0, 0)); return v;
	}
	glm::vec3& TransformationComponent::Right()
	{
		glm::vec3 v = GlobalToLocalDirection(glm::vec3(1, 0, 0)); return v;
	}
	glm::vec3& TransformationComponent::Up()
	{
		glm::vec3 v = GlobalToLocalDirection(glm::vec3(0, 1, 0)); return v;
	}
	glm::vec3& TransformationComponent::Down()
	{
		glm::vec3 v = GlobalToLocalDirection(glm::vec3(0, -1, 0)); return v;
	}
	const glm::mat4 TransformationComponent::LocalMatrix()
	{
		glm::mat4 r = glm::mat4(1);
		r = glm::translate(r, -m_position);
		r = glm::rotate(r, glm::radians(m_eularAngle.x), glm::vec3(1, 0, 0));
		r = glm::rotate(r, glm::radians(m_eularAngle.y), glm::vec3(0, 1, 0));
		r = glm::rotate(r, glm::radians(m_eularAngle.z), glm::vec3(0, 0, 1));
		r = glm::scale(r, m_scale);
		return r;
	}
	const glm::mat4 TransformationComponent::LocalToGlobal()
	{
		SceneObject* parent = Host().Parent();
		glm::mat4 r = LocalMatrix();
		if (parent) {
			TransformationComponent* trans = parent->GetRelateComponent<TransformationComponent>();
			if (trans) {
				r = trans->LocalToGlobal() * r;
			}
		}
		return r;
	}
	const glm::mat4 TransformationComponent::GlobalToLocal()
	{
		SceneObject* parent = m_host->Parent();
		glm::mat4 r = LocalMatrix();
		if (parent) {
			TransformationComponent* trans = parent->GetRelateComponent<TransformationComponent>();
			if (trans) {
				r = glm::inverse(trans->LocalToGlobal() * r);
			}
		}
		return r;
	}
	glm::vec3 TransformationComponent::LocalToGlobalPoint(const glm::vec3& v)
	{
		return LocalToGlobal() * glm::vec4(v.x, v.y, v.z, 1);
	}
	glm::vec3 TransformationComponent::LocalToGlobalVector(const glm::vec3& v)
	{
		return LocalToGlobal() * glm::vec4(v.x, v.y, v.z, 0);
	}
	glm::vec3 TransformationComponent::LocalToGlobalDirection(const glm::vec3& v)
	{
		// Mark, this might wrong ?
		return glm::normalize(GlobalRotation() * v);
	}
	glm::vec3 TransformationComponent::GlobalToLocalPoint(const glm::vec3& v)
	{
		return GlobalToLocal() * glm::vec4(v.x, v.y, v.z, 1);
	}
	glm::vec3 TransformationComponent::GlobalToLocalVector(const glm::vec3& v)
	{
		return GlobalToLocal() * glm::vec4(v.x, v.y, v.z, 0);
	}
	glm::vec3 TransformationComponent::GlobalToLocalDirection(const glm::vec3& v)
	{
		// Mark, this might wrong ?
		return glm::normalize(LocalRotation() * v);
	}
	glm::vec3 TransformationComponent::GlobalPosition()
	{
		return LocalToGlobalPoint(glm::vec3(0));
	}
	glm::quat TransformationComponent::GlobalRotation()
	{
		return glm::quat(glm::radians(GlobalEualrAngle()));
	}
	glm::vec3 TransformationComponent::GlobalEualrAngle()
	{
		SceneObject* parent = m_host->Parent();
		glm::vec3 r = m_eularAngle;
		if (parent) {
			TransformationComponent* trans = parent->GetRelateComponent<TransformationComponent>();
			if (trans) {
				return r += trans->GlobalEualrAngle();
			}
		}
		return r;
	}
	glm::vec3 TransformationComponent::GlobalScale()
	{
		return LocalToGlobalPoint(m_scale);
	}
	glm::vec3& TransformationComponent::LocalPosition()
	{
		return m_position;
	}
	glm::quat TransformationComponent::LocalRotation()
	{
		return glm::quat(glm::radians(m_eularAngle));
	}
	glm::vec3& TransformationComponent::LocalEualrAngle()
	{
		return m_eularAngle;
	}
	glm::vec3& TransformationComponent::LocalScale()
	{
		return m_scale;
	}
}