#include "MemoryManager.h"
#include "Task.h"
#include "IOManager.h"
#include "config.h"
#include "Performance.h"

int total_pages_used;

// Memory Manager 
MemoryManager::MemoryManager(int total_pages) {
        totalPages = total_pages;
        for (int i = 0; i < totalPages; ++i) {
            availablePages.insert(i);
        }
}

void MemoryManager::SetTotalPages(int total_pages){
    int totalPages = total_pages;
    for (int i = 0; i < totalPages; ++i) {
        availablePages.insert(i);
    }
}

int MemoryManager::allocatePage() {
        if (availablePages.empty()) {
            std::cerr << "No available pages to allocate." << std::endl;
            return -1; // Return -1 if no pages are available
        }
        int allocatedPage = *availablePages.begin();
        availablePages.erase(availablePages.begin());
        return allocatedPage;
    }

void MemoryManager::deallocatePage(int page) {
        if (page < 0 || page >= totalPages) {
            std::cerr << "Invalid page number." << std::endl;
            return;
        }
        availablePages.insert(page);
}

int MemoryManager::availablePageCount() const {
        return availablePages.size();
}

void MemoryManager::printAvailablePages() const {
        std::cout << "Available Pages: ";
        for (int page : availablePages) {
            std::cout << page << " ";
        }
        std::cout << std::endl;
}

void MemoryManager::resetMemoryManager() {
        availablePages.clear();
        totalPages = 0;
}

// Two global variables
// one a map of all tasks 
// and the other to store the current page size under consideration

std::map<std::string, Task*> tasks;
int current_page_size;
MemoryManager memManager(1);

// Main function
int main() {
    Performance perf = Performance();

    SingleLevelTask task1(1);
    TwoLevelTask task2(2);

    long long unsigned int num_pages = PHYSICAL_MEMORY_SIZE_16GB/PAGE_SIZE_1KB;

    memManager = MemoryManager((int)num_pages);
    
    tasks["T1"] = &task1;
    tasks["T2"] = &task2;

    // List of trace files to process
    std::vector<std::string> traceFiles = {
        "tracefile_1KB_8GB_16GB.txt",
        "tracefile_2KB_4GB_8GB.txt",
        "tracefile_4KB_4GB_4GB.txt"
    };

    // Process each trace file
    // Instead of making a loop, since its only three
    // Copied the code three times

    // Process trace file 1 - tracefile_1KB_8GB_16GB.txt

    auto start = std::chrono::high_resolution_clock::now();
    current_page_size = PAGE_SIZE_1KB;

    IOManager::processTraceFile("tracefile_1KB_8GB_16GB.txt");

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    perf.storeFileAndExecutionTime("tracefile_1KB_8GB_16GB.txt", duration.count());
    
    // Execution finished for first file
    // Print task data for all tasks in tasks variable 

    std::cout << "\n\nTrace File tracefile_1KB_8GB_16GB output: "<< std::endl;

    for (auto it=tasks.begin(); it!=tasks.end(); ++it) {
        it->second->printTaskData();
    }
    std::cout << "\nRemaining Available Pages: " << memManager.availablePageCount() << std::endl;


    memManager.resetMemoryManager();
    tasks.clear();
    // Process trace file 2 - tracefile_2KB_4GB_8GB.txt
    num_pages = PHYSICAL_MEMORY_SIZE_8GB/PAGE_SIZE_2KB;
    memManager.SetTotalPages(int(num_pages));
    current_page_size = PAGE_SIZE_2KB;

    start = std::chrono::high_resolution_clock::now();

    IOManager::processTraceFile("tracefile_2KB_4GB_8GB.txt");;

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    perf.storeFileAndExecutionTime("tracefile_2KB_4GB_8GB.txt", duration.count());


    // Execution finished for first file
    // Print task data for all tasks in tasks variable 

    std::cout << "\n\nTrace File tracefile_2KB_4GB_8GB output: "<< std::endl;
    for (auto it=tasks.begin(); it!=tasks.end(); ++it) {
        it->second->printTaskData();
    }
    std::cout << "\nRemaining Available Pages: " << memManager.availablePageCount() << std::endl;
    

    memManager.resetMemoryManager();
    tasks.clear();

     // Process trace file 3 - tracefile_4KB_4GB_4GB.txt

    num_pages = PHYSICAL_MEMORY_SIZE_4GB/PAGE_SIZE_4KB;
    memManager.SetTotalPages((int)num_pages);

    current_page_size = PAGE_SIZE_4KB;
    
    start = std::chrono::high_resolution_clock::now();

    IOManager::processTraceFile("tracefile_4KB_4GB_4GB.txt");

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    perf.storeFileAndExecutionTime("tracefile_4KB_4GB_4GB.txt", duration.count());

    // Execution finished for first file
    // Print task data for all tasks in tasks variable 

    std::cout << "\n\nTrace File tracefile_4KB_4GB_4GB output: "<< std::endl;

    for (auto it=tasks.begin(); it!=tasks.end(); ++it) {
        it->second->printTaskData();
    }
    std::cout << "\nRemaining Available Pages: " << memManager.availablePageCount() << std::endl;

    // Consolidated run output
    std::cout << "\nPerformance Statistics: " << std::endl;
    perf.printTotalStatistics();
    //int x;
    //std::cin >> x;

    return 0;
}