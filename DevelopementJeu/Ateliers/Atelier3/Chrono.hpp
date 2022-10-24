#pragma once
#include <chrono>

using namespace std::chrono;
class Chrono {   
private:

public:
    steady_clock::time_point start;
    Chrono()
    {
        start = std::chrono::steady_clock::now();
    }
    void reset()
    {
        start = std::chrono::steady_clock::now();
    }

    size_t delta() {
        return duration_cast<nanoseconds>(steady_clock::now() - start).count() / 1000000000.0;
    }
};