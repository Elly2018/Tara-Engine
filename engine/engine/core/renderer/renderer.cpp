#include "renderer.h"
// Include std library
#include <vector>

// Include third party library
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Include tara library
#include "../emath.h"
#include "../utility.h"
#include "../scene/scene.h"
#include "../scene_object/scene_object.h"
#include "../mesh/mesh.h"
#include "../material/material.h"
#include "../shader/shader.h"
#include "../world/world.h"
#include "../../component/component.h"
#include "../../component/transformation.h"
#include "../../component/light.h"
#include "../../component/free_camera.h"

namespace Tara {

	constexpr bool RenderCommandKey::operator==(const RenderCommandKey& other) const
	{
		return mesh == other.mesh &&
			material == other.material &&
			x == other.x &&
			y == other.y &&
			z == other.z;
	}

	constexpr bool RenderCommandKey::operator!=(const RenderCommandKey& other) const
	{
		return mesh != other.mesh ||
			material != other.material ||
			x != other.x ||
			y != other.y ||
			z != other.z;
	}
	size_t RenderCommandKeyHash::operator()(const RenderCommandKey& k) const
	{
		return ((std::hash<int32_t>()(k.x)
			^ (std::hash<int32_t>()(k.y) << 1)) >> 1)
			^ (std::hash<int32_t>()(k.z) << 1) + ((int32_t)k.mesh) * ((int32_t)k.material);
	}
	Renderer& Renderer::Singleton()
	{
		return *m_Singleton;
	}
	void Renderer::RegisterMainCamera(SceneObject* so)
	{
		CameraComponent* cc = so->GetRelateComponent<CameraComponent>();
		TransformationComponent* tc = so->GetRelateComponent<TransformationComponent>();
		if (!cc || !tc) return;
		m_cameraObject = so;
		m_cameraTrans = tc;
		m_camera = cc;
	}
	void Renderer::GenerateSceneCamera()
	{
		if (m_camera) delete m_cameraObject;
		m_cameraObject = new SceneObject();
		m_cameraObject->m_hostScene->RemoveObject(m_cameraObject);
		m_cameraObject->m_hostScene = nullptr;
		m_cameraTrans = m_cameraObject->AddComponent<TransformationComponent>();
		m_camera = m_cameraObject->AddComponent<FreeCameraComponent>();
		m_cameraTrans->LocalPosition() = glm::vec3(0, 2, 3);
		m_cameraTrans->LocalEualrAngle() = glm::vec3(-20, 0, 0);
		m_cameraObject->Start();
	}

	Frustum& Renderer::CameraFrustum()
	{
		return m_cameraFrustum;
	}
	CameraComponent& Renderer::MainCamera()
	{
		if (!m_camera) GenerateSceneCamera();
		return *m_camera;
	}
	TransformationComponent& Renderer::MainCameraBody()
	{
		if (!m_cameraTrans) GenerateSceneCamera();
		return *m_cameraTrans;
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
		
		Material::CommomMaterial.at(CommomMaterialType::Color)->Use();
		glFrontFace(GL_CW);
		line.Draw();
		glFrontFace(GL_CCW);
		line.Draw();
		Mesh::GetAssetPool().Remove(&line, true);
	}
	BatchRenderer& BatchRenderer::Singleton()
	{
		return *m_Singleton;
	}
	void BatchRenderer::AddRender(Mesh* mesh, Material* material, TransformationComponent* trans)
	{
		AddRender(mesh, material, trans->LocalToGlobal());
	}
	void BatchRenderer::AddRender(Mesh* mesh, Material* material, glm::mat4 trans)
	{
		glm::vec3 pos = trans * glm::vec4(0.0, 0.0, 0.0, 1.0);
		glm::ivec3 place = glm::ivec3(roundf(pos.x / 200), roundf(pos.y / 200), roundf(pos.z / 200));
		RenderCommandKey key = RenderCommandKey(mesh, material, place.x, place.y, place.z);
		if (m_renderCommands.count(key)) {
			m_renderCommands[key].push_back(trans);
		}
		else {
			std::vector<glm::mat4> buffer = std::vector<glm::mat4>();
			buffer.push_back(trans);
			m_renderCommands[key] = buffer;
		}
	}
	void BatchRenderer::Clean()
	{
		m_renderCommands = std::unordered_map<RenderCommandKey, std::vector<glm::mat4>, RenderCommandKeyHash>();
	}
	void BatchRenderer::DrawCall()
	{
		DrawCall(nullptr, false);
	}
	void BatchRenderer::DrawCall(Material* material, bool special)
	{
		if (m_renderCommands.size() == 0) return;
		Renderer& renderer = Renderer::Singleton();

		MaterialUniformBlock* lightblock = Material::m_globalBlocks.at("LightingData");
		MaterialUniformBlock* lightmatblock = Material::m_globalBlocks.at("LightMatrix");
		glm::vec3 eye = renderer.MainCameraBody().GlobalPosition();
		World* w = World::Instance();
		lightblock->SetVec4("ambient", w->m_lightSetting->ambientLight);
		lightblock->SetVec3("eye", eye);

		for (auto pair : m_renderCommands) {
			int count = 0;
			int drawCall = 0;
			RenderCommandKey element = pair.first;
			Material* useMat = material == nullptr ? element.material : material;
			useMat->Use();

			MaterialConfig& matConfig = useMat->Config();
			if (matConfig.Shaded == MaterialShadedMode::Lit && renderer.drawingMode == DrawingMode::Shaded) {
				if (!lightblock || !lightmatblock) continue;

				useMat->RemoveTexture("shadows_0");
				useMat->RemoveTexture("shadows_1");
				useMat->RemoveTexture("shadows_2");
				useMat->RemoveTexture("shadows_3");

				std::vector<Lighting> lights = Lighting::ReceivedNearLightingData(glm::vec3(element.x, element.y, element.z));
				
				int32_t i = 0;
				for (; i < lights.size(); i++) {
					Lighting& g = lights[i];
					//lightblock->SetData("light", &g, i);
					lightblock->SetInt(Utility::String::FormatString("light[%i].lightType", i).c_str(), g.Type);
					lightblock->SetVec3(Utility::String::FormatString("light[%i].position", i).c_str(), g.GLobalPosition);
					lightblock->SetVec4(Utility::String::FormatString("light[%i].color", i).c_str(), g.Color);
					lightblock->SetVec3(Utility::String::FormatString("light[%i].direction", i).c_str(), g.Direction);
					std::string shadowMapName = "shadows_";
					shadowMapName += std::to_string(i);
					useMat->UniformTexture2D(shadowMapName.c_str(), g.Depth, i);

					lightmatblock->SetVec3(Utility::String::FormatString("lightMat[%i].lightPos", i).c_str(), g.Pos);
					lightmatblock->SetMat4(Utility::String::FormatString("lightMat[%i].lightSpaceMatrix", i).c_str(), g.Matrix);
				}
				for (; i < 4; i++) {
					lightblock->SetInt(Utility::String::FormatString("light[%i].lightType", i).c_str(), -1);
					lightblock->SetVec3(Utility::String::FormatString("light[%i].position", i).c_str(), glm::vec3(0));
					lightblock->SetVec4(Utility::String::FormatString("light[%i].color", i).c_str(), glm::vec4(0));
					lightblock->SetVec3(Utility::String::FormatString("light[%i].direction", i).c_str(), glm::vec3(0));
					std::string shadowMapName = "shadows_";
					shadowMapName += std::to_string(i);
					useMat->UniformTexture2D(shadowMapName.c_str(), -1, i);
				}
			}

			useMat->Use();
			if (matConfig.TwoSide) {
				glFrontFace(GL_CW);
				element.mesh->BatchDraw(pair.second);
				drawCall++;
				count += pair.second.size();
				glFrontFace(GL_CCW);
			}
			element.mesh->BatchDraw(pair.second);
			drawCall++;
			count += pair.second.size();
			useMat->Unuse();

			if (!renderer.m_renderRecord || special) continue;
			else {
				renderer.m_RenderState.DrawCall += static_cast<size_t>(drawCall);
				renderer.m_RenderState.Vertices += element.mesh->VerticesCount() * static_cast<size_t>(count);
				renderer.m_RenderState.Triangle += element.mesh->TriangleCount() * static_cast<size_t>(count);
			}
		}
	}
}