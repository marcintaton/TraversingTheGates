#pragma once

#include <GL/glew.h>
#include <unordered_map>

#include "../engine/GameEngine.h"

enum class TextureType {
    GROUND,
    PLAYER,
    H_DOOR_OPEN,
    H_DOOR_CLOSED,
    V_DOOR_OPEN,
    V_DOOR_CLOSED,
    WALL
};

class TextureManager : public ECS::System::IndependentSystem<TextureManager>
{
  private:
    std::unordered_map<TextureType, GLuint> textures;

    GLuint load_texture(const char* file_path);
    void load_game_textures();

  public:
    TextureManager();

    GLuint get_texture(TextureType of_type);
};
