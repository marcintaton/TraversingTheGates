#pragma once

#include "material.h"
#include "mesh.h"
#include "transform.h"

class GameObject
{
  private:
  public:
    Transform transform;
    Material material;
    Mesh mesh;

  public:
    GameObject(/* args */);
    GameObject(Transform transform, Material material, Mesh mesh);
    ~GameObject();

    void render();
};