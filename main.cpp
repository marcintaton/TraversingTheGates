#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "src/engine/GameEngine.h"
#include "src/engine/utility/Logging.h"
#include "src/setupManagers/ECSObjectsSetup.h"
#include "src/setupManagers/GLsetup.h"
#include "src/time/Timer.h"

void update() {}

int main(void)
{
    Utility::Logging::setup_logger();
    Timer timer;
    //

    auto window = GL_setup();
    setup_game_objects();
    setup_systems();

    //

    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //

        //

        glfwSwapBuffers(window);
        glfwPollEvents();

        // update deltatime
        timer.update_timer();
    }

    //

    GL_cleanup();

    exit(EXIT_SUCCESS);
}