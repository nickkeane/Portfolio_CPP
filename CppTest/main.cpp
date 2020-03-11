#include <iostream>
#include <boost/timer/timer.hpp>
#include <boost/chrono.hpp>
#include <cmath>

#include <easy/profiler.h>

using namespace boost::timer;
using namespace boost::chrono;

int main() {

    high_resolution_clock::time_point start = high_resolution_clock::now();
    for (int i = 0; i < 1000000; ++i) {
        std::pow(1.234, i);
    }
    high_resolution_clock::time_point end = high_resolution_clock::now();
    long long delta = (end - start).count();

    //auto hrc = boost::chrono::high_resolution_clock::now();
    //hrc.time_since_epoch();

    // TODO: Library / DLL not found? 0xc0000135 => STATUS_DLL_NOT_FOUND
    // TODO: Static Linkage works, but Shared does not, figure this out
    std::cout << delta << std::endl;
    return 0;
}