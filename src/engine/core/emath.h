#pragma once
// Include third party library
#include <glm/glm.hpp>

// Include tara library
#include "config.h"

namespace Tara {
	class TARA_API TransformationComponent;
	class TARA_API CameraComponent;
	class TARA_API Mesh;

	struct TARA_API Plane
	{
	public:
		Plane() = default;
		Plane(const glm::vec3& p1, const glm::vec3& norm) : normal(glm::normalize(norm)), distance(glm::dot(normal, p1)) {}
		float GetSignedDistanceToPlan(const glm::vec3& point) const;

		// unit vector
		glm::vec3 normal = { 0.f, 1.f, 0.f };
		// Distance with origin
		float distance = 0.f;
	};

	struct TARA_API Frustum
	{
	public:
		Frustum() = default;
		Plane TopFace;
		Plane BottomFace;

		Plane RightFace;
		Plane LeftFace;

		Plane FarFace;
		Plane NearFace;

		static Frustum CreateFrustumFromCamera(CameraComponent& cam, float aspect, float fovY, float zNear, float zFar);
	};

	struct TARA_API BoundingVolume {
		virtual bool isOnFrustum(const Frustum& camFrustum, TransformationComponent* transform) const = 0;
		virtual bool isOnOrForwardPlan(const Plane& plan) const = 0;
		bool isOnFrustum(const Frustum& camFrustum) const;
	};

	struct TARA_API AABB : public BoundingVolume
	{
	public:
		AABB() = default;
		AABB(const glm::vec3& min, const glm::vec3& max) : BoundingVolume{}, center{ (max + min) * 0.5f }, extents{ max.x - center.x, max.y - center.y, max.z - center.z } {}
		AABB(const glm::vec3& inCenter, float iI, float iJ, float iK) : BoundingVolume{}, center{ inCenter }, extents{ iI, iJ, iK } {}

		bool isOnOrForwardPlan(const Plane& plan) const final;
		bool isOnFrustum(const Frustum& camFrustum, TransformationComponent* transform) const final;

		glm::vec3 center{ 0.f, 0.f, 0.f };
		glm::vec3 extents{ 0.f, 0.f, 0.f };
	};
}

