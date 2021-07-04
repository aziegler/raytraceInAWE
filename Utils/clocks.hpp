//
// Created by axell on 7/4/2021.
//

#ifndef RAYTRACER_CLOCKS_HPP
#define RAYTRACER_CLOCKS_HPP
#include <chrono>
#include <map>
#include <string>
using namespace std;
using namespace std::chrono;

typedef high_resolution_clock Clock;
typedef Clock::time_point ClockTime;

namespace perfclock{
    static std::map<std::string,Clock::duration> logs;
    static std::map<string,ClockTime> ongoingLogs;

    void startLog(string function_name){
        ongoingLogs[function_name] = high_resolution_clock::now();
    }

    void stopLog(string function_name){
        ClockTime  endTime = high_resolution_clock::now();
        auto duration = endTime - ongoingLogs[function_name];
        logs[function_name] += duration;
    }

    void printRecap() {
        std::cerr << endl << "----------------Time Recap-------------------------" <<endl;
        for (auto it = logs.begin(); it != logs.end(); ++it) {
            std::cerr << it->first << " took " <<  duration_cast<seconds>(it->second).count() << " seconds." <<endl;
        }
    }


    void printExecutionTime(Clock::duration duration) {
        auto execution_time_ns = duration_cast<nanoseconds>(duration).count();
        auto execution_time_ms = duration_cast<microseconds>(duration).count();
        auto execution_time_sec = duration_cast<seconds>(duration).count();
        auto execution_time_min = duration_cast<minutes>(duration).count();
        auto execution_time_hour = duration_cast<hours>(duration).count();

        cout << "\nExecution Time: ";
        if (execution_time_hour > 0)
            cout << "" << execution_time_hour << " Hours, ";
        if (execution_time_min > 0)
            cout << "" << execution_time_min % 60 << " Minutes, ";
        if (execution_time_sec > 0)
            cout << "" << execution_time_sec % 60 << " Seconds, ";
        if (execution_time_ms > 0)
            cout << "" << execution_time_ms % long(1E+3) << " MicroSeconds, ";
        if (execution_time_ns > 0)
            cout << "" << execution_time_ns % long(1E+6) << " NanoSeconds, ";
    }
}
#endif //RAYTRACER_CLOCKS_HPP
