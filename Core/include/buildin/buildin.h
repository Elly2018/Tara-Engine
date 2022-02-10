#pragma once
#include <config.h>
#include <string>


/*

	Manage the buildin resources.

*/

namespace Tara {
#ifndef TARA_NO_BUILDIN_3D
	class DllExport BuildInMesh {
	public:
		static std::string Cube();
		static std::string Sphere();
		static std::string Plane();
		static std::string Cone();
		static std::string Triangle();
		static std::string Quad();
	};
#else
	#ifndef TARA_NO_BUILDIN_2D
	// Even though if we remove 3D build-in reosurces.
	// We still keep quad mesh data, Because it's for 2D basic drawing needs
	class DllExport BuildInMesh {
	public:
		static std::string Quad();
	#endif // !TARA_NO_BUILDIN_2D
};
#endif // !TARA_NO_BUILDIN_3D

#ifndef TARA_NO_BUILDIN_2D
	class DllExport BuildInTexture {
	public:
		//static std::string Grid();
		//static std::string Default();
	};
#endif // !TARA_NO_BUILDIN_2D

#ifndef TARA_NO_BUILDIN_3D
	class DllExport BuildInShader {
	public:
		static std::string Error_V();
		static std::string Error_F();
		static std::string Color_V();
		static std::string Color_F();
		static std::string Gradient_V();
		static std::string Gradient_F();
		static std::string Texture_V();
		static std::string Texture_F();
		static std::string Lambert_V();
		static std::string Lambert_F();
		static std::string Blinn_V();
		static std::string Blinn_F();
		static std::string GGX_V();
		static std::string GGX_F();
		static std::string Toon_V();
		static std::string Toon_F();
		static std::string DefaultPostprocess_V();
		static std::string DefaultPostprocess_F();
	};
#else
	// If we don't import 3D build.
	// Remove all the shader that is only works in 3D space.
	class DllExport BuildInShader {
		static std::string Error_V();
		static std::string Error_F();
		static std::string Color_V();
		static std::string Color_F();
		static std::string Gradient_V();
		static std::string Gradient_F();
		static std::string Texture_V();
		static std::string Texture_F();
		static std::string DefaultPostprocess_V();
		static std::string DefaultPostprocess_F();
};
#endif // !TARA_NO_BUILDIN_2D
}