#pragma once

class Timer
{
  private:
    float last_frame_timestamp = 0;

  public:
    static float delta_time;

  public:
    Timer();
    ~Timer();

    void update_timer();
};
