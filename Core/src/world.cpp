#include "world.h"

Tara::world* current = nullptr;

Tara::world::world()
{
    if (current == nullptr) current = this;
}

Tara::world::~world()
{
}

Tara::world* Tara::current_world()
{
    return current;
}

void Tara::set_activeworld(world* target)
{
    current = target;
}
