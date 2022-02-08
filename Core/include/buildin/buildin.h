#pragma once
#include <config.h>
#include <string>

#ifndef TARA_NO_BUILDIN
namespace Tara {
	class DllExport BuildInMesh {
	public:
		static std::string Cube();
		static std::string Sphere();
		static std::string Plane();
		static std::string Cone();
		static std::string Triangle();
		static std::string Quad();
	};
	class DllExport BuildInTexture {
	public:
		static std::string Grid();
		static std::string Default();
	};
	class DllExport BuildInShader {

	};
}
#endif // !TARA_NO_BUILDIN