#pragma once
// Include std library
#include <functional>

// Include tara library
#include "config.h"

namespace Tara {
	/*
		Summary:
			Tara engine event base.
	*/
	struct TARA_API TaraEventBase {
	public:
		virtual void Init() = 0;
		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void Destroy() = 0;
		virtual void Enable() = 0;
		virtual void Disable() = 0;
	};

	/*
		Summary:
			Tara engine object event base.
			Has delegate for each events.
	*/
	struct TARA_API TaraObjectEventBase : public TaraEventBase {
	public:
		TaraObjectEventBase();

	private:
		std::list<std::function<void()>> m_InitDelegate;
		std::list<std::function<void()>> m_StartDelegate;
		std::list<std::function<void()>> m_UpdateDelegate;
		std::list<std::function<void()>> m_DestroyDelegate;
		std::list<std::function<void()>> m_EnableDelegate;
		std::list<std::function<void()>> m_DisableDelegate;
	};
}