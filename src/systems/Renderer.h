#pragma once

#include "../engine/GameEngine.h"

class Renderer : public ECS::System::System<Renderer>
{

  private:
    std::size_t custom_priority = 10;
    ECS::EntityId cached_camera_id;

    void do_on_update();
    void update_matrices();
    void render_objects();

  protected:
    virtual void update() override { do_on_update(); }

  public:
    Renderer();
};