#pragma once
#include "../config.h"

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
}
