#include <chrono>
#include "time.hpp"

void Time::start() {
    this->timeStart = clock();
}

void Time::stop() {
    this->timeStop = clock();
}

double Time::elapsed() {
    double elapsed_secs = double(this->timeStop - this->timeStart) / CLOCKS_PER_SEC;
    return elapsed_secs;
}