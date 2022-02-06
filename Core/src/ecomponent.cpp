#include "ecomponent.h"
#include <eobject.h>
#include <einput.h>
#include <renderer.h>
#include <ewindow.h>

namespace Tara {
	#pragma region EComponent
	EComponent::EComponent(EObject* _host)
	{
		m_host = _host;
		Init();
	}
	EComponent::~EComponent()
	{
		for (EComponent* i : components) {
			delete i;
		}
	}

	void EComponent::Init() {}
	void EComponent::Start() {}
	void EComponent::Render() {}
	void EComponent::Update() {}
	void EComponent::Destroy() {}
	void EComponent::Enable() {}
	void EComponent::Disable() {}

	void EComponent::SetEnable(bool _enable)
	{
		m_enable = _enable;
		if (_enable) Enable();
		else Disable();
	}
	bool EComponent::GetEnable()
	{
		return m_enable;
	}
	EObject* EComponent::Host()
	{
		return m_host;
	}
	#pragma endregion

	#pragma region CTransformation
	void CTransformation::Translate(float_t x, float_t y, float_t z, Space _s)
	{
		Translate(glm::vec3(x, y, z));
	}
	void CTransformation::Translate(glm::vec3 v, Space _s)
	{
		m_position += v;
	}
	void CTransformation::Rotate(glm::vec3 v, Space _s)
	{
		m_rotation = glm::quat(glm::eulerAngles(m_rotation) + glm::radians(v));
	}
	glm::mat4 CTransformation::ModelMatrix()
	{
		EObject* parent = m_host->Parent();
		glm::mat4 r = glm::mat4(1);
		r = glm::translate(r, m_position);
		r = r * glm::toMat4(m_rotation);
		r = glm::scale(r, m_scale);
		if (parent != nullptr) {
			CTransformation* trans = parent->GetRelateComponent<CTransformation>();
			r = r * trans->ModelMatrix();
		}
		return r;
	}
	#pragma endregion

	#pragma region CMeshRenderer
	void CMeshRenderer::SetMesh(Mesh* _Mesh) {
		m_mesh = _Mesh;
	}
	Mesh* CMeshRenderer::GetMesh() {
		return m_mesh;
	}
	void CMeshRenderer::SetMaterial(Material* _mat) {
		m_mat = _mat;
	}
	Material* CMeshRenderer::GetMaterial() {
		return m_mat;
	}
	void CMeshRenderer::Draw() {
		if (m_mat != nullptr && m_mesh != nullptr) {
			m_mat->Use();
			m_mat->UniformMat4("model", m_trans->ModelMatrix());
			m_mat->UniformMat4("view", renderer::view);
			m_mat->UniformMat4("projection", renderer::projection);
			m_mesh->Draw();
		}
	}
	void CMeshRenderer::Start()
	{
		m_trans = m_host->GetRelateComponent<CTransformation>();
	}
	void CMeshRenderer::Render()
	{
		Draw();
	}
	#pragma endregion

	#pragma region CCamera
	CCamera::~CCamera()
	{
		delete frame;
	}
	glm::mat4 CCamera::ViewMatrix()
	{
		CTransformation* trans = m_host->GetRelateComponent<CTransformation>();
		EObject* parent = m_host->Parent();
		if (trans == nullptr) return glm::mat4(1);

		return glm::lookAt(trans->m_position, trans->m_position + glm::normalize(trans->m_rotation * glm::vec3(0, 0, -1)), glm::vec3(0, 1, 0));
		glm::mat4 r = glm::mat4(1);
		r = glm::translate(r, -trans->m_position);
		r = r * glm::toMat4(trans->m_rotation);
		if (parent != nullptr) {
			CTransformation* trans = parent->GetRelateComponent<CTransformation>();
			r = r * trans->ModelMatrix();
		}
		return glm::transpose(r);
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
	#pragma endregion

	#pragma region CFreeCamera
	void CFreeCamera::Start()
	{
		trans = m_host->GetRelateComponent<CTransformation>();
		trans->m_position = glm::vec3(0, 0, 5);
	}
	void CFreeCamera::Update()
	{
		glm::vec2 delta = EInput::GetMouseDelta();
		if (EInput::IsMouseButton(button_action::Button2))
			trans->Rotate(glm::vec3(-delta.y * 0.2f, delta.x * 0.2f, 0));
		glm::vec3 movedir = glm::vec3(0);
		if (EInput::IsKey(keycode::W)) movedir += glm::vec3(0, 0, -1);
		if (EInput::IsKey(keycode::S)) movedir += glm::vec3(0, 0, 1);
		if (EInput::IsKey(keycode::A)) movedir += glm::vec3(-1, 0, 0);
		if (EInput::IsKey(keycode::D)) movedir += glm::vec3(1, 0, 0);
		if (EInput::IsKey(keycode::LEFT_SHIFT)) movedir += glm::vec3(0, -1, 0);
		if (EInput::IsKey(keycode::SPACE)) movedir += glm::vec3(0, 1, 0);
		trans->Translate(movedir);
	}
	#pragma endregion

	#pragma region CColiision
	void CColiision::OnCollisionEnter(CollisionData data)
	{
	}
	void CColiision::OnCollisionLeave(CollisionData data)
	{
	}
	void CColiision::OnCollisionStay(CollisionData data)
	{
	}
	void CColiision::OnTriggerEnter(CollisionData data)
	{
	}
	void CColiision::OnTriggerLeave(CollisionData data)
	{
	}
	void CColiision::OnTriggerStay(CollisionData data)
	{
	}
	#pragma endregion

	#pragma region CCharacterControl
	void CCharacterControl::Start()
	{
		m_trans = m_host->GetRelateComponent<CTransformation>();
	}
	void CCharacterControl::Update()
	{
		glm::vec3 movedir = glm::vec3(0);
		if (EInput::IsKey(keycode::W)) movedir += glm::vec3(0, 0, m_movingSpeed);
		if (EInput::IsKey(keycode::S)) movedir += glm::vec3(0, 0, -m_movingSpeed);
		if (EInput::IsKey(keycode::A)) movedir += glm::vec3(-m_movingSpeed, 0, 0);
		if (EInput::IsKey(keycode::D)) movedir += glm::vec3(m_movingSpeed, 0, 0);
		Move(movedir, Space::Local);
		if (EInput::IsKeyDown(keycode::SPACE)) Jump();
		Look(EInput::GetMouseDelta());
	}
	void CCharacterControl::Move(glm::vec3 dir, Space _space)
	{
		//EVIE_DEBUG("moving: %f %f %f", dir.x, dir.y, dir.z);
	}
	void CCharacterControl::Look(glm::vec2 dir)
	{
	}
	void CCharacterControl::Jump()
	{
	}
	#pragma endregion
}