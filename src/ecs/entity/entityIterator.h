#pragma once

#include "IEntity.h"
#include <vector>

template<class T>
class EntityIterator
{
  public:
    std::vector<IEntity*> container;
};