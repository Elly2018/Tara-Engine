#include <memory>
#include <list>
#include "../engine/core/config.h"

namespace Tara {
	class TARA_API Extension;

	class TaraApplication final {
	public:
		TaraApplication();
		static TaraApplication& Singleton();

		bool Initialization();
		bool RegisterExtension(Extension* extension);
		void Run();

	private:
		static TaraApplication* m_app;

		std::list<Extension*> extensions;
	};
}