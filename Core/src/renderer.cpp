#include "renderer.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <mesh.h>
#include <material.h>
#include <scene.h>
#include <components/free_camera.h>

// Include third party library
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Tara {
#pragma region Static Members
	FrameBuffer* Renderer::primarydisplay = nullptr;
	glm::mat4 Renderer::view = glm::mat4(1);
	glm::mat4 Renderer::projection = glm::mat4(1);
	bool Renderer::wireframeMode = false;
	bool Renderer::shadedMode = false;
	bool Renderer::m_renderRecord = true;
	Material* Renderer::pureColor = nullptr;
	RenderState Renderer::m_RenderState = RenderState();

	Frustum Renderer::m_cameraFrustum = Frustum();
	CCamera* Renderer::m_camera = nullptr;
	EObject* Renderer::m_cameraObject = nullptr;
	CTransformation* Renderer::m_cameraTrans = nullptr;

	glm::vec3 RendererDebug::color = glm::vec3(1);
	float_t RendererDebug::alpha = 1;
#pragma endregion

	Frustum& Renderer::CameraFrustum()
	{
		return m_cameraFrustum;
	}
	CCamera& Renderer::MainCamera()
	{
		if (!m_camera) GenerateSceneCamera();
		return *m_camera;
	}
	CTransformation& Renderer::MainCameraBody()
	{
		if (!m_cameraTrans) GenerateSceneCamera();
		return *m_cameraTrans;
	}
	void Renderer::GenerateSceneCamera()
	{
		if (m_camera) delete m_cameraObject;
		m_cameraObject = new EObject();
		m_cameraObject->m_hostScene->RemoveObject(m_cameraObject);
		m_cameraObject->m_hostScene = nullptr;
		m_cameraTrans = m_cameraObject->AddComponent<CTransformation>();
		m_camera = m_cameraObject->AddComponent<CFreeCamera>();
		m_cameraObject->Start();
	}

	float_t& RendererDebug::Alpha()
	{
		return alpha;
	}

	glm::vec3& RendererDebug::Colro()
	{
		return color;
	}

	void RendererDebug::DrawLine(const glm::vec3 pos1, const glm::vec3 pos2)
	{
		Mesh& line = *new Mesh();
		std::vector<glm::vec3> var = {
			pos1, (pos2 + pos1) / 1.999f, pos2
		};
		std::vector<uint32_t> ind = {
			0, 1, 2
		};
		line.SetVertices(var);
		line.SetIndices(ind);
		line.Update();
		
		Renderer::pureColor->Use();
		Renderer::pureColor->UniformVec3("color", color);
		Renderer::pureColor->UniformNumber("alpha", alpha);
		Renderer::pureColor->UniformMat4("model", glm::mat4(1));
		Renderer::pureColor->UniformMat4("view", Renderer::view);
		Renderer::pureColor->UniformMat4("projection", Renderer::projection);
		glFrontFace(GL_CW);
		line.Draw();
		glFrontFace(GL_CCW);
		line.Draw();
		Mesh::GetAssetPool()->Remove(line, true);
	}
	void RendererDebug::DrawSphere(const glm::vec3 pos, const float_t radius)
	{
		Mesh& sphere = Mesh::GetCommon(CommomMesh::Sphere)->Clone();
		glm::mat4 r = glm::mat4(1);
		r = glm::translate(r, -pos);
		r = glm::scale(r, glm::vec3(radius));
		Renderer::pureColor->Use();
		Renderer::pureColor->UniformVec3("color", color);
		Renderer::pureColor->UniformNumber("alpha", alpha);
		Renderer::pureColor->UniformMat4("model", r);
		Renderer::pureColor->UniformMat4("view", Renderer::view);
		Renderer::pureColor->UniformMat4("projection", Renderer::projection);
		glFrontFace(GL_CW);
		sphere.Draw();
		glFrontFace(GL_CCW);
		sphere.Draw();
		Mesh::GetAssetPool()->Remove(sphere, true);
	}
	void RendererDebug::DrawCube(const glm::vec3 pos, const glm::vec3 scale)
	{
		Mesh& cube = Mesh::GetCommon(CommomMesh::Cube)->Clone();
		glm::mat4 r = glm::mat4(1);
		r = glm::translate(r, -pos);
		r = glm::scale(r, scale);
		Renderer::pureColor->Use();
		Renderer::pureColor->UniformVec3("color", color);
		Renderer::pureColor->UniformNumber("alpha", alpha);
		Renderer::pureColor->UniformMat4("model", r);
		Renderer::pureColor->UniformMat4("view", Renderer::view);
		Renderer::pureColor->UniformMat4("projection", Renderer::projection);
		glFrontFace(GL_CW);
		cube.Draw();
		glFrontFace(GL_CCW);
		cube.Draw();
		Mesh::GetAssetPool()->Remove(cube, true);
	}
	void RendererDebug::DrawPlane(const glm::vec3 pos, const glm::vec3 normal, const glm::vec2 size)
	{
		Mesh plane = Mesh::GetCommon(CommomMesh::Plane)->Clone();
		glm::mat4 r = glm::mat4(1);
		r = glm::translate(r, -pos);
		r *= glm::toMat4(glm::quatLookAtRH(glm::normalize(normal), glm::vec3(0, 1, 0)));
		r = glm::scale(r, glm::vec3(size.x, 1, size.y));
		Renderer::pureColor->Use();
		Renderer::pureColor->UniformVec3("color", color);
		Renderer::pureColor->UniformNumber("alpha", alpha);
		Renderer::pureColor->UniformMat4("model", r);
		Renderer::pureColor->UniformMat4("view", Renderer::view);
		Renderer::pureColor->UniformMat4("projection", Renderer::projection);
		glFrontFace(GL_CW);
		plane.Draw();
		glFrontFace(GL_CCW);
		plane.Draw();
		Mesh::GetAssetPool()->Remove(plane, true);
	}
}