#pragma once

#include <memory>

#include "../system/IndependentSystemManager.h"
#include "../system/SystemManager.h"

namespace ECS
{
class SystemEngine
{
    // Singleton
  public:
    static SystemEngine& get_instance()
    {
        static SystemEngine instance;
        return instance;
    }

  private:
    SystemEngine();
    SystemEngine(SystemEngine const&) = delete;
    void operator=(SystemEngine const&) = delete;

    //

  private:
    std::unique_ptr<System::SystemManager> system_manager;
    std::unique_ptr<System::IndependentSystemManager>
        independent_system_manager;

  public:
    template<class T>
    void create_system()
    {
        system_manager->create_system<T>();
    }

    template<class T>
    void create_active_system()
    {
        system_manager->create_active_system<T>();
    }

    template<class T>
    void destroy_system()
    {
        system_manager->destroy_system<T>();
    }

    template<class T>
    void enable_system()
    {
        system_manager->enable_system<T>();
    }

    template<class T>
    void disable_system()
    {
        system_manager->disable_system<T>();
    }

    template<class T>
    void create_independent_system()
    {
        independent_system_manager->create_system<T>();
    }

    template<class T>
    void destroy_independent_system()
    {
        independent_system_manager->destroy_system<T>();
    }

    template<class T>
    void enable_independent_system()
    {
        independent_system_manager->enable_system<T>();
    }

    template<class T>
    void disable_independent_system()
    {
        independent_system_manager->disable_system<T>();
    }
};
}; // namespace ECS