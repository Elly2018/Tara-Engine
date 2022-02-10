#pragma once
#include <config.h>
#include <components/component.h>

/*

	Transformation component handles the important feature in coordinate system.
	Each component only store the local position, eular angles, scales.

*/
namespace Tara {
	/*
		Summary:
			Space will effect transformation calculation.
			World: According world coordination.
			Local: Inherit parent transformation.
	*/
	enum class DllExport Space {
		World,
		Local
	};
	/*
		Summary:
			Store the transformation data for the eobject.
			Most of component will require transform to works, there are few does not need transform to works.
			Such as post process component, or system logic control component.
	*/
	class DllExport CTransformation : public EComponent {
	public:
		DEFAULT_CTOR_IMPLE(CTransformation);

		void GUI() override;
		/*
		
			Some easy use function to use.

		*/
		#pragma region Features
		/*
			Summary:
				Translate by input vector3 data.
			Arugment:
				x, y, z -> Moving vector3.
				_s -> Space info, detail please check space enum summary.
		*/
		void Translate(float_t x, float_t y, float_t z, Space _s = Space::Local);
		/*
			Summary:
				Translate by input vector3 data.
			Arugment:
				v -> Moving vector3.
				_s -> Space info, detail please check space enum summary.
		*/
		void Translate(glm::vec3 v, Space _s = Space::Local);
		/*
			Summary:
				Rotate by input eular angle vector3 data.
			Arugment:
				x, y, z -> Rotate vector3.
				_s -> Space info, detail please check space enum summary.
		*/
		void Rotate(float_t x, float_t y, float_t z, Space _s = Space::Local);
		void Rotate(float_t x, float_t y, Space _s = Space::Local);
		/*
			Summary:
				Rotate by input eular angle vector3 data.
			Arugment:
				v -> Rotate vector3.
				_s -> Space info, detail please check space enum summary.
		*/
		void Rotate(glm::vec3 v, Space _s = Space::Local);
		/*
			Summary:
				Get the global vector of [0, 0, 1]
		*/
		glm::vec3& Forward();
		/*
			Summary:
				Get the global vector of [0, 0, -1]
		*/
		glm::vec3& Backward();
		/*
			Summary:
				Get the global vector of [-1, 0, 0]
		*/
		glm::vec3& Left();
		/*
			Summary:
				Get the global vector of [1, 0, 0]
		*/
		glm::vec3& Right();
		/*
			Summary:
				Get the global vector of [0, 1, 0]
		*/
		glm::vec3& Up();
		/*
			Summary:
				Get the global vector of [0, -1, 0]
		*/
		glm::vec3& Down();
		#pragma endregion


		/*
		
			Coordinate system conversion and calculation functions.

		*/
		#pragma region Transformation Calculation
		/*
			Summary:
				Get the local space matrix.
		*/
		const glm::mat4 LocalMatrix();
		/*
			Summary:
				Get the model matrix.
		*/
		const glm::mat4 LocalToGlobal();
		/*
			Summary:
				Inverse of model matrix.
		*/
		const glm::mat4 GlobalToLocal();
		/*
			Summary:
				Convert local position to global position.
		*/
		glm::vec3 LocalToGlobalPoint(const glm::vec3& v);
		/*
			Summary:
				Convert local vector to global vector.
		*/
		glm::vec3 LocalToGlobalVector(const glm::vec3& v);
		/*
			Summary:
				Convert local direction to global direction.
		*/
		glm::vec3 LocalToGlobalDirection(const glm::vec3& v);
		/*
			Summary:
				Convert global position to local position.
		*/
		glm::vec3 GlobalToLocalPoint(const glm::vec3& v);
		/*
			Summary:
				Convert global vector to local vector.
		*/
		glm::vec3 GlobalToLocalVector(const glm::vec3& v);
		/*
			Summary:
				Convert global direction to local direction.
		*/
		glm::vec3 GlobalToLocalDirection(const glm::vec3& v);
		/*
			Summary:
				Get global position.
		*/
		glm::vec3 GlobalPosition();
		/*
			Summary:
				Get global orientation.
		*/
		glm::quat GlobalRotation();
		/*
			Summary:
				Get global eular angles.
		*/
		glm::vec3 GlobalEualrAngle();
		/*
			Summary:
				Get global scale.
		*/
		glm::vec3 GlobalScale();
		/*
			Summary:
				Access local position.
		*/
		glm::vec3& LocalPosition();
		/*
			Summary:
				Get calculated local orientation.
		*/
		glm::quat LocalRotation();
		/*
			Summary:
				Access local eular angles.
		*/
		glm::vec3& LocalEualrAngle();
		/*
			Summary:
				Access local scale.
		*/
		glm::vec3& LocalScale();
		#pragma endregion

	private:
		glm::vec3 m_position = glm::vec3(0);
		glm::vec3 m_eularAngle = glm::vec3(0);
		glm::vec3 m_scale = glm::vec3(1);
	};
}