#include "engine/core/window/ewindow.h"

namespace Tara {
	class AppWindow final : public EWindow {
	public:
		AppWindow();
		virtual ~AppWindow();

	protected:
		void Start() override;
		void Update() override;
		void Render() override;
		void PostRender() override;

		void GUI();
		void DeleteAllScene();
	};
}