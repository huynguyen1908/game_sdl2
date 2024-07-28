
#ifndef IMP_TIMER_H_
#define IMP_TIMER_H_
#include "define.h"

class ImpTimer
{
public:
    ImpTimer();
    void start();
    void stop();
    void pause();
    void unpause();
    int get_ticks();
    bool is_started();
    bool is_paused();

private:
    //time at started
    int start_tick_;
    int paused_ticks_;

    bool is_paused_;
    bool is_started_;
};

#endif