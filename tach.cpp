#include "tach.h"

//the tach interrupt is initialized using the initializer list
Tach::Tach(PinName tach_pin): _tach_in(tach_pin)
{
    _tach_in.mode(PullDown);
    _tach_in.rise(callback(this, &Tach::tach_isr));
    _tach_rpm_ticker.attach(callback(this, &Tach::tach_rpm_tick), _tach_update_interval_ms);

    start(); //start tach at construction time
}

uint32_t Tach::getRPM()
{
    return _tach_rpm;
}

void Tach::setCalculationInterval(chrono::milliseconds t)
{
    _tach_update_interval_ms = t;
    _tach_rpm_ticker.detach();
    _tach_rpm_ticker.attach(callback(this, &Tach::tach_rpm_tick), _tach_update_interval_ms);

    //reset the count since the ticker is restarted
    reset();
}

void Tach::tach_isr()
{
    _tach_isr_count++;
}

void Tach::tach_rpm_tick()
{
    //times 60 seconds per minute, divided by 2 pulses per rotation, convert to microseconds (*10^6), divide by elapsed time in microseconds
    //time_t current_time = time(NULL);
    chrono::microseconds elapsed = _rpm_timer.elapsed_time();
    _tach_rpm = (uint64_t)_tach_isr_count;
    _tach_rpm = _tach_rpm * 60 / 2 * 1000000 / elapsed.count();

    //ok since write to an integer is atomic, but if it was a larger data structure we would probably need to disable the interrupt to reset everything
    reset();
    //_last_tach_count_reset_time = time(NULL);
}

void Tach::reset()
{
    _tach_isr_count = 0;
    _rpm_timer.reset();
}

void Tach::start()
{
    _rpm_timer.start();
}

void Tach::stop()
{
    _rpm_timer.stop();
}