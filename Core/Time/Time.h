#ifndef TIME_H
#define TIME_H

class Time
{
public:
    static Time& instance();
    static double get_delta_time();
    static double get_time();

private:
    Time(const Time& obj) = delete;
    void operator=(const Time& obj) = delete;
    Time();

    double _timeStep                = 1.0 / 60.0;
    double _time                    = 0;
    double _deltaTime               = 0;
    double _lastUpdateTime          = 0;
    
    friend class Application;
};

#endif // !TIME_H
