#ifndef TIME_HPP
#define TIME_HPP

#include <ctime>

class Time {
    private:
        clock_t timeStart, timeStop;
    public:
        Time() {};
        void start();
        void stop();
        double elapsed();
};

#endif