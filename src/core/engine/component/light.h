#pragma once
// Import Tara engine library
#include "../core/config.h"
#include "../core/asset.h"
#include "component.h"

namespace Tara {
	class TARA_API SceneObject;
	class TARA_API ShadowFrameBuffer;

	/*
		Summary:
			Light types. it will effect shader drawing. (If shader support lights)
	*/
	enum class TARA_API LightType {
		Direction = 0,
		Point = 1,
		Spot = 2
	};


	/*
		Sumary:
			The struct data use in global uniform block.
	*/
	struct TARA_API Lighting final {
	public:
		friend class Material;
		friend class BatchRenderer;
		/*
			Summary:
				Direction: 0,
				Point: 1,
				Spot: 2.
		*/
		int32_t Type;
		/*
			Summary:
				Light in the world coordinate position.
		*/
		glm::vec3 GLobalPosition;
		/*
			Summary:
				Color of the light. w = intensity.
		*/
		glm::vec4 Color;
		/*
			Summary:
				A unit-vector shows light facing direction.
		*/
		glm::vec3 Direction;
		/*
			Summary:
				depth map of light.
		*/
		uint32_t Depth;

		glm::vec3 Pos;
		glm::mat4 Matrix;

	private:
		static std::vector<Lighting> ReceivedNearLightingData(glm::vec3 pos);
	};

	/*
		Summary:
			Light component. Mesh renderer will detect near lights to send light info uniform buffer.
	*/
	class TARA_API LightComponent : public Component {
	public:
		friend class Lighting;
		DEFAULT_HEADER_CTOR(LightComponent);
		virtual ~LightComponent();
		/*
			Summary:
				Generate light matrix
		*/
		glm::mat4 LightMatrix();
		void Use();
		void UnUse();
		glm::ivec2& ShadowMapSize();
		uint32_t DepthMap();

		// Light type, Default: direction.
		LightType m_type = LightType::Direction;
		// Light intensity.
		float_t m_intensity = 1.0f;
		// Light color.
		glm::vec3 m_color = glm::vec3(1, 1, 0.9f);
		// Range primary.
		float_t m_range1 = 2;
		// Range secondary.
		float_t m_range2 = 10;
		// Important has higher priority to render.
		bool m_important = false;

	private:
		TransformationComponent& trans = Transform();
		ShadowFrameBuffer* frame;
	};
}