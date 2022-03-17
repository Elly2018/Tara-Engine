#include "world.h"

namespace Tara {
    World* current = nullptr;

    PhysicsSetting::PhysicsSetting() {
        gravity = glm::vec3(0, 9.81f, 0);
    }

    PhysicsSetting::~PhysicsSetting() {

    }

    LightSetting::LightSetting() {
        ambientLight = glm::vec4(0.1f, 0.1f, 0.1f, 0.1f);
    }

    LightSetting::~LightSetting() {

    }

    World* World::Instance()
    {
        if (current == nullptr) {
            current = new World();
        }
        return current;
    }

    void World::SetDefault()
    {
        delete m_physicsSetting;
        delete m_lightSetting;
        m_physicsSetting = new PhysicsSetting();
        m_lightSetting = new LightSetting();
    }

    World::World()
    {
        if (current == nullptr) current = this;
    }

    World::~World()
    {
        delete m_physicsSetting;
        delete m_lightSetting;
    }
}