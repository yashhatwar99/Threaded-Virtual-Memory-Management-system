
#include "Task.h"
#include "MemoryManager.h"
#include "IOManager.h"

// IOManager Class functions

// The function processTraceFile reads the trace file and processes the requests
// It takes the trace file and the tasks as input
// It reads the trace file line by line and processes the requests
// It reads the task identifier, logical address and size from the trace file
// It validates the task identifier and converts the logical address to integer
// It converts the size to pages and requests memory for each page
// It prints error messages for invalid task identifier and invalid hexadecimal address
// It prints error message for malformed line
extern int total_pages_used;
extern std::map<std::string, Task*> tasks;
extern int current_page_size; // Current page size as per Trace file input
extern MemoryManager memManager;


    void IOManager::processTraceFile(const std::string &traceFile) {
        std::ifstream file(traceFile);
        std::string line;

        if (!file.is_open()) {
            std::cerr << "Error opening file: " << traceFile << std::endl;
            return;
        }

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string taskIdentifier, logicalAddressHex, sizeStr;

            // Parse the line according to the expected format
            if (std::getline(iss, taskIdentifier, ':') &&
                std::getline(iss, logicalAddressHex, ':') &&
                std::getline(iss, sizeStr)) {

                // Trim leading and trailing whitespace from each field
                taskIdentifier.erase(std::remove_if(taskIdentifier.begin(), taskIdentifier.end(), ::isspace), taskIdentifier.end());
                logicalAddressHex.erase(std::remove_if(logicalAddressHex.begin(), logicalAddressHex.end(), ::isspace), logicalAddressHex.end());
                sizeStr.erase(std::remove_if(sizeStr.begin(), sizeStr.end(), ::isspace), sizeStr.end());

                std::string taskId = taskIdentifier;
                taskId.erase(std::remove(taskId.begin(), taskId.end(), 'T'), taskId.end());

                // Validate and convert the task identifier
                if (taskIdentifier.empty() || tasks.find(taskIdentifier) == tasks.end()) {
                    tasks[taskIdentifier] = new SingleLevelTask(std::stoi(taskId));
                    std::cerr << "Created new task identifier: " << taskIdentifier << std::endl;
                }
                
                // Convert hex address to integer
                int logicalAddress;
                try {
                    logicalAddress = std::stoi(logicalAddressHex, nullptr, 16);
                } catch (const std::invalid_argument &e) {
                    std::cerr << "Invalid hexadecimal address: " << logicalAddressHex << std::endl;
                    continue;
                }

                // Convert size to pages
                // If its MB then convert to KB by multiplying by 1024
                // If its KB, keep it as is

                int sizeInKB = 0;
                if (sizeStr.back() == 'B') {
                    if (sizeStr[sizeStr.length() - 2] == 'K') {
                        sizeInKB = std::stoi(sizeStr.substr(0, sizeStr.length() - 2));
                    } else if (sizeStr[sizeStr.length() - 2] == 'M') {
                        sizeInKB = std::stoi(sizeStr.substr(0, sizeStr.length() - 2)) * 1024;
                    }
                }

                // current_page_size is the page size as per the trace file name
                int pagesRequired = sizeInKB / current_page_size; 

                if(sizeInKB % current_page_size != 0) {
                    pagesRequired++;
                }

                total_pages_used += pagesRequired;

                int startingLogicalAddress = logicalAddress/current_page_size;
                // Request memory for each page
                for (int i = 0; i < pagesRequired; ++i) {
                    int virtualPage = startingLogicalAddress + i;
                    tasks[taskIdentifier]->requestMemory(virtualPage);
                }
            } else {
                // The trace file line did not work as per format
                // Hence Error message
                std::cerr << "Malformed line: " << line << std::endl;
            }
        }

        file.close();
    }
