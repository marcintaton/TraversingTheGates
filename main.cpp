#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "src/engine/utility/Logging.h"
#include "src/setupManagers/GLsetup.h"
#include "src/setupManagers/GameObjectsSetup.h"
#include "src/systems/Renderer.h"

int main(void)
{
    Utility::Logging::setup_logger();
    //

    GL_setup();
    setupGameObjects();

    //
    Renderer r;

    //

    GL_cleanup();

    exit(EXIT_SUCCESS);
}