#include "SpriteDirectionFlip.h"

#include "../components/GameComponents.h"

SpriteDirectionFlip::SpriteDirectionFlip()
{
    flip_delegate = Event::EventDelegate<SpriteDirectionFlip, ObjectMoved>(
        this, &SpriteDirectionFlip::flip_sprite);
}

void SpriteDirectionFlip::subscribe()
{
    Event::EventEngine::get_instance().add_listener<ObjectMoved>(
        &flip_delegate);
}
void SpriteDirectionFlip::unsubscribe()
{

    Event::EventEngine::get_instance().remove_listener<ObjectMoved>(
        &flip_delegate);
}

void SpriteDirectionFlip::on_enable()
{
    subscribe();
}

void SpriteDirectionFlip::on_disable()
{
    unsubscribe();
}

void SpriteDirectionFlip::flip_sprite(const ObjectMoved* event)
{

    auto oriented_sprite =
        ECS::ECEngine::get_instance().get_component<OrientedSprite>(
            event->object_id);

    if (event->new_direction != oriented_sprite->current_direction) {
        auto render_data =
            ECS::ECEngine::get_instance().get_component<MeshRenderData>(
                event->object_id);

        render_data->texture.atlas_offset =
            oriented_sprite->texture_sprite_coords[event->new_direction];

        oriented_sprite->current_direction = event->new_direction;
    }
}