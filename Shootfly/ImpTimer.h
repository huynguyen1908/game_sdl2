
#ifndef IMP_TIMER_H_
#define IMP_TIMER_H_
#include "define.h"

class ImpTimer
{
public:
    ImpTimer();
    void start();
    void stop();
    int get_ticks();
    bool is_started();

private:
    int start_tick_;
    bool is_started_;
};

#endif