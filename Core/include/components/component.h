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
		static bool m_debugMenu;
		static void SetDebugMenu(bool v);
		static bool GetDebugMenu();
		#endif

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
				GUI render method
		*/
		virtual void GUI();
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
		CTransformation* TransformComponent();

	private:
		// Is component enable
		bool m_enable = true;
		// Is component initialization finish yet? (means finish call 'start()' method)
		bool m_init = false;
	};
};