/* Simple class to manage an InterruptIn based tachometer reading */

#ifndef TACH_H
#define TACH_H

#include "mbed.h"
#include <chrono>

class Tach
{
public:
    Tach(PinName tach_pin);
    uint32_t getRPM();
    void setCalculationInterval(chrono::milliseconds t);

    void reset();
    void start();
    void stop();

private:
    volatile int _tach_isr_count = 0;
    uint64_t _tach_rpm = -1; //last RPM calculated. 64bit since intermediate value is large.
    chrono::milliseconds _tach_update_interval_ms = 1000ms;
    Timer _rpm_timer; //TODO replace with LowPowerTimer since we only need millisecond accuracy
    //time_t _last_tach_count_reset_time = 0;

    Ticker _tach_rpm_ticker;
    InterruptIn _tach_in;

    void tach_isr();
    void tach_rpm_tick();

};


#endif