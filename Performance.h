#ifndef _PERFORMANCE_H_
#define _PERFORMANCE_H_
#include <iostream>
#include "Task.h"
#include <chrono>

// extern std::map<std::string, Task*> tasks;

class Performance {
    public:
        time_t start_time;
        time_t end_time;
        std::map<std::string,long int>execution_times;
        long int TotalMemoryUsage;
        
        Performance();
        time_t InitializeStartTime();
        time_t InitializeEndTime();
        time_t CalculateTotalTimeAndStore(std::string task_name);

        void storeFileAndExecutionTime(std::string, long int milliseconds);

        int resetPerformanceStats();

        void printTotalStatistics();
        void printExecutionTimes();
        void printTotalMemoryUsage();

        int addToMemoryUsage(long int memorySize);
        int deleteFromMemoryUsage(long int memorySize);
};


#endif