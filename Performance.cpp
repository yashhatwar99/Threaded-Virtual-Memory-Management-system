#include "Performance.h"

extern int total_pages_used;
extern int current_page_size;

Performance::Performance() {
    start_time = 0;
    end_time = 0;
    TotalMemoryUsage = 0;   
}

void Performance::storeFileAndExecutionTime(std::string file_name, long int microsecs){
    execution_times[file_name] = microsecs;
}

time_t Performance::InitializeStartTime(){
    
    start_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    return start_time;
}

time_t Performance::InitializeEndTime(){
    
    end_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    return end_time;
}

time_t Performance::CalculateTotalTimeAndStore(std::string file_name){
    time_t total_time = end_time - start_time;
    execution_times[file_name] = total_time*1000000; // Convert to microsecs
    return total_time;
}

int Performance::resetPerformanceStats(){
    start_time = 0;
    end_time = 0;
    TotalMemoryUsage = 0;
    execution_times.clear();
    return 0;
}

void Performance::printExecutionTimes(){
    std::cout << "Execution Times: " << std::endl;
    for(auto it = execution_times.begin(); it != execution_times.end(); ++it){
        std::cout << it->first << " : " << it->second << " microsecs" << std::endl;
    }
}

void Performance::printTotalMemoryUsage(){
    TotalMemoryUsage=total_pages_used*current_page_size;
    std::cout << "Total Memory Usage: " << TotalMemoryUsage << " bytes" << std::endl;
}


void Performance::printTotalStatistics(){
    printExecutionTimes();
    printTotalMemoryUsage();
}

int Performance::addToMemoryUsage(long int memorySize){
    TotalMemoryUsage += memorySize;
    return 0;
}

int Performance::deleteFromMemoryUsage(long int memorySize){
    TotalMemoryUsage -= memorySize;
    return 0;
}