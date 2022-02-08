#pragma once
#include <config.h>
#include <components/component.h>

namespace Tara {
	/*
		Summary:
			Light types. it will effect shader drawing. (If shader support lights)
	*/
	enum class DllExport LightType {
		Direction,
		Point,
		Spot
	};
	/*
		Summary:
			Light component. Mesh renderer will detect near lights to send light info uniform buffer.
	*/
	class DllExport CLight : public EComponent {
	public:
		DEFAULT_CTOR_IMPLE(CLight);

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
	};
}