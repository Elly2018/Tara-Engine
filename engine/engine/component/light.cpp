#include "light.h"
// Import std library
#include <algorithm>
// Import Third party library
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
// Import Tara engine library
#include "transformation.h"
#include "../core/scene_object/scene_object.h"
#include "../core/framebuffer/framebuffer.h"
#include "../core/input.h"
#include "../system/system.h"
#include "../system/light_system.h"

namespace Tara {
	typedef std::pair<LightComponent*, TransformationComponent*> lightpair;
	glm::vec3 CompareLightPosition = glm::vec3(0);

	bool LightSort(lightpair a, lightpair b) {
		return glm::distance(a.second->GlobalPosition(), CompareLightPosition) < glm::distance(b.second->GlobalPosition(), CompareLightPosition);
	}
	Lighting PackData(lightpair a) {
		Lighting data = Lighting();
		data.GLobalPosition = a.second->GlobalPosition();
		data.Direction = a.second->LocalToGlobalVector(glm::vec3(0, 0, 1));
		data.Color = glm::vec4(a.first->m_color, a.first->m_intensity);
		data.Type = (int32_t)a.first->m_type;
		data.Depth = a.first->DepthMap();
		data.Pos = a.first->Transform().GlobalPosition();
		data.Matrix = a.first->LightMatrix();
		return data;
	}

	std::vector<Lighting> Lighting::ReceivedNearLightingData(glm::vec3 pos)
	{
		SystemRegister& sr = SystemRegister::Singleton();
		CompareLightPosition = pos;
		std::vector<Lighting> buffer = std::vector<Lighting>();

		std::vector<lightpair> important = std::vector<lightpair>();
		std::vector<lightpair> unimportant = std::vector<lightpair>();
		
		LightSystem& lightSystem = *dynamic_cast<LightSystem*>(sr.GetSystem<LightComponent>());

		for (auto i : lightSystem) {
			if (!i) continue;

			TransformationComponent* trans = i->Host().GetRelateComponent<TransformationComponent>();
			if (!trans) continue;

			if (i->m_important) important.push_back({ i , trans });
			else unimportant.push_back({ i , trans });
		}
		

		// Sort it by the distance between light and input position
		std::sort(important.begin(), important.end(), LightSort);
		std::sort(unimportant.begin(), unimportant.end(), LightSort);

		for (auto i : important) {
			buffer.push_back(PackData(i));
			if (buffer.size() >= 4) return buffer;
		}

		for (auto i : unimportant) {
			buffer.push_back(PackData(i));
			if (buffer.size() >= 4) return buffer;
		}

		return buffer;
	}

	DEFAULT_SRC_CTOR(LightComponent)
	{
		SystemRegister& sys = SystemRegister::Singleton();
		sys.AppendComponent<LightComponent>(this);
		frame = new ShadowFrameBuffer();
	}
	LightComponent::~LightComponent()
	{
		SystemRegister& sys = SystemRegister::Singleton();
		sys.RemoveComponent<LightComponent>(this);
		delete frame;
	}
	glm::mat4 LightComponent::LightMatrix()
	{
		glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);
		glm::mat4 lightView = glm::lookAt(trans.GlobalPosition(), trans.Forward(), glm::vec3(0.0, 1.0, 0.0));
		return lightProjection * lightView;
	}
	void LightComponent::Use()
	{
		frame->Bind();
	}
	void LightComponent::UnUse()
	{
		frame->Unbind();
	}
	glm::ivec2& LightComponent::ShadowMapSize()
	{
		return frame->Size();
	}
	uint32_t LightComponent::DepthMap()
	{
		return frame->TextureID();
	}
}