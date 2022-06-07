#pragma once
#include "../config.h"

namespace Tara {
	class TARA_API Mesh;
	class TARA_API Material;

	/*
		Summary:
			Command key is a way to sorting batch renderer objects.
	*/
	struct TARA_API RenderCommandKey {
	public:
		RenderCommandKey(Mesh* me, Material* mat, int32_t _x, int32_t _y, int32_t _z)
			: mesh(me), material(mat), x(_x), y(_y), z(_z) {}
		Mesh* mesh = nullptr;
		Material* material;
		int32_t x;
		int32_t y;
		int32_t z;

		constexpr bool operator==(const RenderCommandKey& other) const;
		constexpr bool operator!=(const RenderCommandKey& other) const;
	};

	struct TARA_API RenderCommandKeyHash {
		size_t operator()(const RenderCommandKey& k) const;
	};
}
