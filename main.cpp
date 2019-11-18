#include "src/GameLoop.h"
#include "src/setupManagers/GLsetup.h"
#include "src/setupManagers/StackModifier.h"

int main(void)
{
    Utility::Logging::setup_logger();

    Setup::resize_stack();
    Setup::GL_setup();

    //
    GameLoop gc;
    gc.initialize();
    gc.run_game_loop();
    //

    Setup::GL_cleanup();

    exit(EXIT_SUCCESS);
}