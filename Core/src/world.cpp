#include "world.h"

namespace Tara {
    World* current = nullptr;

    World::World()
    {
        if (current == nullptr) current = this;
    }

    World::~World()
    {
    }

    World* current_world()
    {
        return current;
    }

    void set_activeworld(World* target)
    {
        current = target;
    }
}