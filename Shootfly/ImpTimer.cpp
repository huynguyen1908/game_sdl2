

#include "ImpTimer.h"

ImpTimer::ImpTimer()
{
  start_tick_ = 0;
  is_started_ = false;
}

void ImpTimer::start()
{
  is_started_ = true;
  start_tick_ = SDL_GetTicks();
}

void ImpTimer::stop()
{
  is_started_ = false;
}

int ImpTimer::get_ticks()
{
    if (is_started_ == true)
    {
        int tick = SDL_GetTicks();
        tick = tick - start_tick_;
        return tick;

    }

    return 0;
}

bool ImpTimer::is_started()
{
  return is_started_;
}
