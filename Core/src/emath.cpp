#include "emath.h"
#include <eobject.h>
#include <components/camera.h>
#include <components/transformation.h>

namespace Tara {
	float Plane::GetSignedDistanceToPlan(const glm::vec3& point) const
	{
		return glm::dot(normal, point) - distance;
	}
	Frustum Frustum::CreateFrustumFromCamera(CCamera& cam, float aspect, float fovY, float zNear, float zFar)
	{
		Frustum frustum;
		EObject* camobject = cam.Host();
		CTransformation& camTrans = *camobject->GetRelateComponent<CTransformation>();
		const float halfVSide = zFar * tanf(fovY * .5f);
		const float halfHSide = halfVSide * aspect;
		const glm::vec3 globalPos = camTrans.GlobalPosition();
		const glm::vec3 camForward = camTrans.Forward();
		const glm::vec3 camUp = camTrans.Up();
		const glm::vec3 camRight = camTrans.Right();
		const glm::vec3 frontMultFar = zFar * camForward;

		frustum.NearFace = { globalPos + zNear * camForward, camForward };
		frustum.FarFace = { globalPos + frontMultFar, -camForward };
		frustum.RightFace = { globalPos, glm::cross(camUp, frontMultFar + camRight * halfHSide) };
		frustum.LeftFace = { globalPos, glm::cross(frontMultFar - camRight * halfHSide, camUp) };
		frustum.TopFace = { globalPos, glm::cross(camRight, frontMultFar - camUp * halfVSide) };
		frustum.BottomFace = { globalPos, glm::cross(frontMultFar + camUp * halfVSide, camRight) };

		return frustum;
	}
	bool BoundingVolume::isOnFrustum(const Frustum& camFrustum) const
	{
		return (isOnOrForwardPlan(camFrustum.LeftFace) &&
			isOnOrForwardPlan(camFrustum.RightFace) &&
			isOnOrForwardPlan(camFrustum.TopFace) &&
			isOnOrForwardPlan(camFrustum.BottomFace) &&
			isOnOrForwardPlan(camFrustum.NearFace) &&
			isOnOrForwardPlan(camFrustum.FarFace));
	}
	bool AABB::isOnOrForwardPlan(const Plane& plan) const
	{
		// Compute the projection interval radius of b onto L(t) = b.c + t * p.n
		const float r = extents.x * std::abs(plan.normal.x) + extents.y * std::abs(plan.normal.y) +
			extents.z * std::abs(plan.normal.z);

		return -r <= plan.GetSignedDistanceToPlan(center);
	}
	bool AABB::isOnFrustum(const Frustum& camFrustum, CTransformation& transform) const
	{
		//Get global scale thanks to our transform
		const glm::vec3 globalCenter = transform.LocalToGlobalPoint(center);

		// Scaled orientation
		const glm::vec3 right = transform.Right() * extents.x;
		const glm::vec3 up = transform.Up() * extents.y;
		const glm::vec3 forward = transform.Forward() * extents.z;

		const float newIi = std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, right)) +
			std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, up)) +
			std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, forward));

		const float newIj = std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, right)) +
			std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, up)) +
			std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, forward));

		const float newIk = std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, right)) +
			std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, up)) +
			std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, forward));

		const AABB globalAABB(globalCenter, newIi, newIj, newIk);

		return (globalAABB.isOnOrForwardPlan(camFrustum.LeftFace) &&
			globalAABB.isOnOrForwardPlan(camFrustum.RightFace) &&
			globalAABB.isOnOrForwardPlan(camFrustum.TopFace) &&
			globalAABB.isOnOrForwardPlan(camFrustum.BottomFace) &&
			globalAABB.isOnOrForwardPlan(camFrustum.NearFace) &&
			globalAABB.isOnOrForwardPlan(camFrustum.FarFace));
	}
}