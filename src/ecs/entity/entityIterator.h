#pragma once

#include "IEntity.h"
#include <memory>
#include <vector>

template<class T>
class EntityIterator
{
  public:
    std::vector<std::shared_ptr<IEntity>> container;
};