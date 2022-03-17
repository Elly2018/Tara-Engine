#pragma once
#include "../core/config.h"
#include "../core/base.h"

namespace Tara {
	class TARA_API SceneObject;
	class TARA_API Scene;
	class TARA_API TransformationComponent;

	/*
		Summary:
			Components base class, include basic functionality that require to build a component.
	*/
	class TARA_API Component : public TaraObjectEventBase
	{
		friend class SceneObject;
	public:
		/*
			Summary:
				Create component instance
			Arugment:
				host -> the host of the component
		*/
		Component(SceneObject* host);
		virtual ~Component();

		/*
			Summary:
				Initialization, follows by constructor.
		*/
		virtual void Init() {}
		/*
			Summary:
				The first frame.
		*/
		virtual void Start() {}
		/*
			Summary:
				Called by each frame, mainly for update the logic.
		*/
		virtual void Update() {};
		/*
			Summary:
				Follows by destrctor.
		*/
		virtual void Destroy() {}
		/*
			Summary:
				Called when component become enable.
		*/
		virtual void Enable() {}
		/*
			Summary:
				Called when component become disable.
		*/
		virtual void Disable() {}

		/*
			Summary:
				Change component enable state.
		*/
		void SetEnable(const bool _enable);
		/*
			Summary:
				Check component is enable.
		*/
		bool GetEnable();
		/*
			Summary:
				Get host object of the component.
		*/
		SceneObject& Host();
		TransformationComponent& Transform();

	protected:
		SceneObject* m_host = nullptr;
		TransformationComponent* TransformComponent = nullptr;

	private:
		// Is component enable
		bool m_enable = true;
		// Is component initialization finish yet? (means finish call 'start()' method)
		bool m_init = false;
	};
};