#include "TextureManager.h"

#include <SOIL/SOIL.h>

TextureManager::TextureManager()
{
    load_game_textures();
}

void TextureManager::load_game_textures()
{

    textures[TextureType::GROUND] = load_texture("assets/textures/ground.png");
    textures[TextureType::WALL] = load_texture("assets/textures/wall.png");
    textures[TextureType::PLAYER] = load_texture("assets/textures/player.png");
    textures[TextureType::H_DOOR_CLOSED] =
        load_texture("assets/textures/h_door_closed.png");
    textures[TextureType::H_DOOR_OPEN] =
        load_texture("assets/textures/h_door_open.png");
    textures[TextureType::V_DOOR_CLOSED] =
        load_texture("assets/textures/v_door_closed.png");
    textures[TextureType::V_DOOR_OPEN] =
        load_texture("assets/textures/v_door_open.png");
}

GLuint TextureManager::load_texture(const char* file_path)
{
    GLuint texture;
    int tex_width, tex_height;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    auto image =
        SOIL_load_image(file_path, &tex_width, &tex_height, 0, SOIL_LOAD_RGBA);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_width, tex_height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

GLuint TextureManager::get_texture(TextureType of_type)
{
    return textures[of_type];
}