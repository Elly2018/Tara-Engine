#pragma once
#include <vector>

#include <config.h>
#include <mesh.h>
#include <material.h>
#include <framebuffer.h>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Tara {
	/*

		Structs, classes declaration

	*/
	struct DllExport CollisionData;
	class DllExport EObject;
	class DllExport Mesh;
	class DllExport Material;
	class DllExport EComponent;

	class DllExport CTransformation;
	class DllExport CMeshRenderer;
	class DllExport CCamera;
	class DllExport CFreeCamera;
	class DllExport CLight;
	class DllExport CPhysics;
	class DllExport CColiision;
	class DllExport CCharacterControl;

	#pragma region Enum Types
	/*
		Summary:
			Camera perspective types.
	*/
	enum class DllExport CameraType {
		Perspective,
		Orthographic
	};
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
			Physics constraint will lock the specific axis of rotation or position.
	*/
	enum class DllExport PhysicsConstraint {
		Position_x = 1,
		Position_y = 2,
		Position_z = 4,
		Rotation_x = 8,
		Rotation_y = 16,
		Rotation_z = 32,
	};
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
	#pragma endregion

	#pragma region Structures
	/*
		Summary:
			The pack of information contains all the collision event data.
	*/
	struct CollisionData {
	public:
		EObject* target;
		glm::vec3 point;
	};
	#pragma endregion


	/*
		Summary:
			Components base class, include basic functionality that require to build a component.
	*/
	class EComponent
	{
		friend class EObject;
	public:
		/*
			Summary:
				Create component instance
			Arugment:
				host -> the host of the component
		*/
		EComponent(EObject* host);
		~EComponent();

		/*
			Summary:
				Initialization, follows by constructor.
		*/
		virtual void Init();
		/*
			Summary:
				The first frame.
		*/
		virtual void Start();
		/*
			Summary:
				Called by each frame, mainly for drawing.
		*/
		virtual void Render();
		/*
			Summary:
				Called by each frame, mainly for update the logic.
		*/
		virtual void Update();
		/*
			Summary:
				Follows by destrctor.
		*/
		virtual void Destroy();
		/*
			Summary:
				Called when component become enable.
		*/
		virtual void Enable();
		/*
			Summary:
				Called when component become disable.
		*/
		virtual void Disable();

		/*
			Summary:
				Change component enable state.
		*/
		void SetEnable(bool _enable);
		/*
			Summary:
				Check component is enable.
		*/
		bool GetEnable();
		/*
			Summary:
				Get host object of the component.
		*/
		EObject* Host();

	protected:
		EObject* m_host = nullptr;

	private:
		std::vector<EComponent*> components = std::vector<EComponent*>();
		// Is component enable
		bool m_enable = true;
		// Is component initialization finish yet? (means finish call 'start()' method)
		bool m_init = false;
	};
	#pragma region Component Subclasses
	/*
		Summary:
			Store the transformation data for the eobject.
			Most of component will require transform to works, there are few does not need transform to works.
			Such as post process component, or system logic control component.
	*/
	class CTransformation : public EComponent {
	public:
		DEFAULT_CTOR_IMPLE(CTransformation);
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
				Get the eobject model matrix.
		*/
		glm::mat4 ModelMatrix();

		glm::vec3 m_position = glm::vec3(0);
		glm::quat m_rotation = glm::quat();
		glm::vec3 m_scale = glm::vec3(1);
	};
	/*
		Summary:
			Rendering mesh with material.
	*/
	class CMeshRenderer : public EComponent {
	public:
		DEFAULT_CTOR_IMPLE(CMeshRenderer);
		/*
			Summary:
				Assign mesh pointer.
		*/
		void SetMesh(Mesh* _mesh);
		/*
			Summary:
				Get mesh.
		*/
		Mesh* GetMesh();
		/*
			Summary:
				Assign material pointer.
		*/
		void SetMaterial(Material* _mat);
		/*
			Summary:
				Get material.
		*/
		Material* GetMaterial();
		/*
			Summary:
				Drawing mesh onto screen.
				It won't render if mesh or material equal null pointer.
		*/
		void Draw();
		void Start() override;
		void Render() override;
	private:
		// Assign mesh.
		Mesh* m_mesh = nullptr;
		// Assign material.
		Material* m_mat = nullptr;
		// Component host transformation.
		CTransformation* m_trans = nullptr;
	};
	/*
		Summary:
			Camera object.
			Scene will iterate through all camera to render.
	*/
	class CCamera : public EComponent {
	public:
		DEFAULT_CTOR_IMPLE(CCamera);
		~CCamera();
		/*
			Summary:
				Get camera view matrix.
		*/
		glm::mat4 ViewMatrix();
		/*
			Summary:
				Get camera projection matrix.
		*/
		glm::mat4 ProjectionMatrix();
		/*
			Summary:
				Binding camera framebuffer.
		*/
		void Use();
		/*
			Summary:
				Unbinding camera framebuffer.
		*/
		void Unuse();
		/*
			Summary:
				Binding camera framebuffer texture.
		*/
		void Bind();
		/*
			Summary:
				Unbinding camera framebuffer texture.
		*/
		void Unbind();
		uint32_t TextureID();

		// Camera types, default: perspective
		CameraType m_type = CameraType::Perspective;
		bool m_fullscreen = false;
		// Field of view
		float_t m_fov = 60;
		// Orthographic camera view size
		float_t m_size = 5;
		// Screen width
		float_t m_width = 1920;
		// Screen height
		float_t m_height = 1080;
		// Near plane
		float_t m_nearPlane = 0.01f;
		// Far plane
		float_t m_farPlane = 1000;

	private:
		// Camera framebuffer
		FrameBuffer* frame = new FrameBuffer();
	};
	/*
		Summary:
			Free moving camera. 
			The very basic scene viewer camera.
	*/
	class CFreeCamera : public CCamera {
	public:
		DEFAULT_CTOR_INHERIT_IMPLE(CFreeCamera, CCamera);
		void Start() override;
		void Update() override;
	private:
		CTransformation* trans;
	};
	/*
		Summary:
			Light component. Mesh renderer will detect near lights to send light info uniform buffer.
	*/
	class CLight : public EComponent {
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
	/*
		Summary:
			Physics component will decide that if object should apply force.
			The global physics parameters is in world class. in case user want to change it.
	*/
	class CPhysics : public EComponent {
	public:
		DEFAULT_CTOR_IMPLE(CPhysics);
		// Apply global force
		bool apply_physics = true;
		// Contsraint flags
		int32_t constraint = 0;
	};
	/*
		Collision detection base class
	*/
	class CColiision : public EComponent {
	public:
		DEFAULT_CTOR_IMPLE(CColiision);
		/*
			Summary:
				Called when physics object enter the area.
		*/
		virtual void OnCollisionEnter(CollisionData data);
		/*
			Summary:
				Called when physics object leave the area.
		*/
		virtual void OnCollisionLeave(CollisionData data);
		/*
			Summary:
				Called when physics object in the area.
		*/
		virtual void OnCollisionStay(CollisionData data);
		/*
			Summary:
				Called when trigger object enter the area.
		*/
		virtual void OnTriggerEnter(CollisionData data);
		/*
			Summary:
				Called when trigger object leave the area.
		*/
		virtual void OnTriggerLeave(CollisionData data);
		/*
			Summary:
				Called when trigger object in the area.
		*/
		virtual void OnTriggerStay(CollisionData data);

		// Is collision trigger type.
		bool m_trigger = false;
	};
	/*
		Summary:
			Character controller base class.
			With basic movement functionality.
	*/
	class CCharacterControl : public EComponent {
	public:
		DEFAULT_CTOR_IMPLE(CCharacterControl);
		void Start() override;
		void Update() override;
		void Move(glm::vec3 dir, Space _space = Space::Local);
		void Look(glm::vec2 dir);
		void Jump();

		float_t m_mouseSensitivity = 1;
		float_t m_movingSpeed = 0.5f;
		float_t m_jumpForce = 2;

	private:
		EObject* m_cameraObject = nullptr;
		CTransformation* m_trans = nullptr;
	};
#pragma endregion
}