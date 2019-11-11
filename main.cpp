// #include <GL/glew.h>
// #include <GLFW/glfw3.h>
// #include <SOIL/SOIL.h>

// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>

#include "src/engine/GameEngine.h"
#include "src/time/Timer.h"

#include "src/setupManagers/GLsetup.h"

#include "src/GameLoop.h"
#include "src/global/GlobalGLData.h"
#include "src/systems/TextureManager.h"
#include "tests/MainTest.h"

int main(void)
{
    Utility::Logging::setup_logger();
    //
    //
    GameLoop gc;

    Setup::GL_setup(); // windw do globals
    //

    gc.initialize();
    //
    gc.run_game_loop();
    //

    Setup::GL_cleanup();

    exit(EXIT_SUCCESS);
}