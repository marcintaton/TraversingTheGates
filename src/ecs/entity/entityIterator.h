#pragma once

#include "IEntity.h"
#include <memory>
#include <vector>

template<class T>
struct EntityIterator {
    std::vector<EntityPtr> entities;
};