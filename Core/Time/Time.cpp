#include "Time.h"

Time& time = Time::instance();

Time::Time()
{
}

Time& Time::instance()
{
    static Time instance;
    return instance;
}

double Time::get_delta_time()
{
    return Time::instance()._deltaTime;
}

double Time::get_time()
{
    return Time::instance()._time;
}
