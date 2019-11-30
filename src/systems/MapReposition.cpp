#include "MapReposition.h"

#include "../components/GameComponents.h"

MapReposition::MapReposition()
{
    obj_moved_delegate = Event::EventDelegate<MapReposition, ObjectMoved>(
        this, &MapReposition::on_object_reposition);
}

void MapReposition::subscribe()
{
    Event::EventEngine::get_instance().add_listener<ObjectMoved>(
        &obj_moved_delegate);
}

void MapReposition::unsubscribe()
{
    Event::EventEngine::get_instance().remove_listener<ObjectMoved>(
        &obj_moved_delegate);
}

void MapReposition::on_enable()
{
    subscribe();
}

void MapReposition::on_disable()
{
    unsubscribe();
}

void MapReposition::on_object_reposition(const ObjectMoved* event)
{

    auto nav_data = ECS::ECEngine::get_instance().get_component<NavigationData>(
        event->object_id);

    if (nav_data != nullptr) {
        nav_data->current_position = event->new_pos;
    }
}