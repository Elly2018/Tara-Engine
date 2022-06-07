#pragma once
#include "../config.h"
#include "renderer_command.h"

namespace Tara {
	class TARA_API TransformationComponent;
	class TARA_API Mesh;
	class TARA_API Material;

	/*
		Summary:
			Collection renderer, It batch many mesh into single drawcall.
			Adding pair into the worker, the worker will figure out.
	*/
	class TARA_API BatchRenderer final {
	public:
		static BatchRenderer& Singleton();
		void AddRender(Mesh* mesh, Material* material, TransformationComponent* trans);
		void AddRender(Mesh* mesh, Material* material, glm::mat4 trans);
		/*
			Summary:
				Clean the render queue.
		*/
		void Clean();
		/*
			Summary:
				Render entire scenes.
		*/
		void DrawCall();
		/*
			Summary:
				Use specific material the render entire scenes.
		*/
		void DrawCall(Material* material, bool special = true);

	private:
		BatchRenderer() {
			m_renderCommands = std::unordered_map<RenderCommandKey, std::vector<glm::mat4>, RenderCommandKeyHash>();
			chunk = 200;
		}
		static BatchRenderer* m_Singleton;
		std::unordered_map<RenderCommandKey, std::vector<glm::mat4>, RenderCommandKeyHash> m_renderCommands;
		float_t chunk;
	};
}
