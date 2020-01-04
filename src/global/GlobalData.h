#pragma once

namespace Global
{

class GlobalData
{
    // Singleton
  public:
    static GlobalData& get_instance()
    {
        static GlobalData instance;
        return instance;
    }

  private:
    GlobalData() {}
    GlobalData(GlobalData const&) = delete;
    void operator=(GlobalData const&) = delete;

    //

  public:
    constexpr static int max_map_size = 250;
};
}; // namespace Global