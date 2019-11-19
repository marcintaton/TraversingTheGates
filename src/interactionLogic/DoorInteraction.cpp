#include "DoorInteraction.h"

void DoorInteraction::OnKick(const Kick* event)
{
    auto door_data =
        ECS::ECEngine::get_instance().get_component<DoorData>(event->target);

    if (door_data->closed == true) {
        door_data->sturdiness--;
        if (door_data->sturdiness <= 0) {
            open_door(event->target, door_data);
        }
    }
}

void DoorInteraction::OnUse(const Use* event)
{
    auto door_data =
        ECS::ECEngine::get_instance().get_component<DoorData>(event->target);

    if (door_data->closed == true && door_data->locked == false) {
        open_door(event->target, door_data);
    } else if (door_data->closed == false) {
        close_door(event->target, door_data);
    }
}

void DoorInteraction::open_door(ECS::EntityId door_id,
                                std::shared_ptr<DoorData> door_data)
{
    door_data->locked = false;
    door_data->closed = false;

    auto render_data =
        ECS::ECEngine::get_instance().get_component<MeshRenderData>(door_id);

    render_data->texture.atlas_offset = door_data->open_textue_index;

    auto nav_data =
        ECS::ECEngine::get_instance().get_component<NavigationData>(door_id);
    nav_data->passable = true;
}

void DoorInteraction::close_door(ECS::EntityId door_id,
                                 std::shared_ptr<DoorData> door_data)
{
    door_data->closed = true;

    auto render_data =
        ECS::ECEngine::get_instance().get_component<MeshRenderData>(door_id);

    render_data->texture.atlas_offset = door_data->closed_texture_index;

    auto nav_data =
        ECS::ECEngine::get_instance().get_component<NavigationData>(door_id);
    nav_data->passable = false;
}
