#include <memory>
#include <list>
#include "../engine/core/config.h"

namespace Tara {
	class TARA_API Extension;
	class GlobalPanels;

	/// <summary>
	/// The entry point for the application
	/// </summary>
	class TaraApplication final {
	public:
		TaraApplication();
		~TaraApplication();
		/// <summary>
		/// Engine initialization stage
		/// </summary>
		/// <returns></returns>
		bool Initialization();
		/// <summary>
		/// Apply engine extension <br />
		/// Some will require you will need to restart in order to load additional extension
		/// </summary>
		/// <param name="extension">Extension handle</param>
		/// <returns>Load successfully</returns>
		bool RegisterExtension(std::shared_ptr<Extension> extension);
		/// <summary>
		/// Start the engine
		/// </summary>
		void Run();

	private:
		// Register all editor windows here
		GlobalPanels& RegisterGlobalPanel();

		std::list<std::shared_ptr<Extension>> extensions;
	};
}