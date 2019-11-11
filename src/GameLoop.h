#pragma once

#include "engine/GameEngine.h"
#include "time/Timer.h"

class GameLoop
{
  private:
    Timer timer;
    ECS::System::SystemUpdateInvoker system_update_invoker;

  public:
    void initialize();
    void run_game_loop();
};
