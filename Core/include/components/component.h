#pragma once
#include <config.h>

namespace Tara {
	class DllExport EObject;
	class DllExport EScene;
	class DllExport CTransformation;

	/*
		Summary:
			Components base class, include basic functionality that require to build a component.
	*/
	class DllExport EComponent
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

		#ifndef TARA_NO_IMGUI
	private:
		static bool m_debugMenu;
	public:
		static bool& DebugMenu();
		#endif

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

#ifndef TARA_NO_IMGUI
		/*
			Summary:
				GUI render method.
				Called by GUI func, not by EObject.
		*/
		virtual void GUI() {}
		/*
			Summary:
				For engine debug view use.
				Called by EObject during gizmo stage.
		*/
		virtual void Gizmo() {}
#endif

		/*
			Summary:
				Called by each frame, mainly for drawing.
		*/
		virtual void Render() {}
		/*
			Summary:
				Called by each frame, mainly for update the logic.
		*/
		virtual void Update() {}
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
		EObject* Host();
		CTransformation* Transform();

	protected:
		EObject* m_host = nullptr;
		CTransformation* TransformComponent = nullptr;

	private:
		// Is component enable
		bool m_enable = true;
		// Is component initialization finish yet? (means finish call 'start()' method)
		bool m_init = false;
	};
};