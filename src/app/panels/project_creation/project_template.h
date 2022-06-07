#pragma once
#include "engine/core/config.h"

namespace Tara {
	class Texture2D;

	namespace UI {
		struct TARA_APP_API ProjectTemplateHeader {
			ProjectTemplateHeader() = default;
			ProjectTemplateHeader(std::string n,
				std::string d) : name(n), description(d) {}
			std::string name;
			std::string description;
		};

		struct TARA_APP_API ProjectTemplateImport {
			ProjectTemplateImport() = default;
			ProjectTemplateImport(std::string f,
				std::string t,
				bool r) : from(f), to(t), recursion(r) {}
			std::string from;
			std::string to;
			bool recursion = true;
		};

		/// <summary>
		/// <para> A struct contain project template description. </para>
		/// <para> Use for render project creation menu. </para>
		/// </summary>
		struct TARA_APP_API ProjectTemplate {
			ProjectTemplate() = default;
			ProjectTemplate(std::string n,
				std::string d,
				Texture2D* a,
				std::vector<ProjectTemplateImport> is) : name(n), readme(d), preview(a), imports(is) {}
			ProjectTemplate(std::string n,
				std::string d,
				std::vector<ProjectTemplateImport> is) : name(n), readme(d), preview(nullptr), imports(is) {}
			std::string name;
			std::string readme;
			Texture2D* preview;
			std::vector<ProjectTemplateImport> imports;
		};
	}
}
