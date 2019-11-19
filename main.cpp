#include "src/GameLoop.h"
#include "src/setupManagers/GLsetup.h"
#include <stdlib.h>
#include <time.h>

int main(void)
{
    srand(time(NULL));
    Utility::Logging::setup_logger();

    Setup::GL_setup();

    //
    GameLoop gc;
    gc.initialize();
    gc.run_game_loop();
    //

    Setup::GL_cleanup();

    exit(EXIT_SUCCESS);
}