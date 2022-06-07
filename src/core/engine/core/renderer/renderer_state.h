#pragma once
#include "../config.h"

namespace Tara {
	/*
		Summary:
			Each mainloop render result.
	*/
	struct TARA_API RenderState {
	public:
		double_t FPS;
		double_t CPU_Usage;
		double_t GPU_Usage;
		double_t RAM_Usage;
		size_t DrawCall;
		size_t Vertices;
		size_t Triangle;
	};
}