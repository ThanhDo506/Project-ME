#ifndef TIME_H
#define TIME_H

class Time
{
public:
    static Time& instance();
    double deltaTime() const;
    double time() const;

private:
    Time(const Time& obj) = delete;
    void operator=(const Time& obj) = delete;
    Time();
    double _timeStep = 1.0 / 60.0;
    double _time;
    double _deltaTime;
    double _lastUpdatedTime;
    double _timeSinceStartScene;
    
    friend class Application;
};

#endif // !TIME_H
