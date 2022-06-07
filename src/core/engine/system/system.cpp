#include "system.h"

namespace Tara {
	SystemRegister* SystemRegister::m_Singleton = new SystemRegister();

	SystemRegister::SystemRegister()
	{
		systems = std::list<SystemBase*>();
	}

	SystemRegister& SystemRegister::Singleton()
	{
		return *m_Singleton;
	}

	void SystemRegister::Register(SystemBase* system)
	{
		systems.push_back(system);
	}
	void SystemRegister::CleanNull()
	{
		for (auto i : systems) {
			i->CleanNull();
		}
	}
}