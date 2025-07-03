
#include "Task.h"
#include "MemoryManager.h"

extern MemoryManager memManager;


    Task::Task(int id) : taskId(id), pageHits(0), pageMisses(0) {}

    int Task::getPageHits() const {
        return pageHits;
    }

    int Task::getPageMisses() const {
        return pageMisses;
    }

    void Task::printTaskData() {
        std::cout << "Task ID: " << taskId << std::endl;
        std::cout << "Page Hits: " << pageHits << std::endl;
        std::cout << "Page Misses: " << pageMisses << std::endl;
    }

    SingleLevelTask::SingleLevelTask(int id) : Task(id) {}

    void SingleLevelTask::requestMemory(int virtualPage)  {
        if (pageTable.find(virtualPage) != pageTable.end()) {
            ++pageHits;
        } else {
            int physicalPage = memManager.allocatePage();
            if (physicalPage != -1) {
                pageTable[virtualPage] = physicalPage;
                ++pageMisses;
            }
        }
    }

    void SingleLevelTask::releaseMemory(int virtualPage)  {
        auto it = pageTable.find(virtualPage);
        if (it != pageTable.end()) {
            memManager.deallocatePage(it->second);
            pageTable.erase(it);
        }
    }

    size_t SingleLevelTask::getPageTableMemoryUsage() const  {
        return pageTable.size() * sizeof(std::pair<int, int>);
    }

// Two Level Task Class

    TwoLevelTask::TwoLevelTask(int id) : Task(id) {}

    void TwoLevelTask::requestMemory(int virtualPage)  {
        int outerIndex = virtualPage >> 10;
        int innerIndex = virtualPage & 0x3FF;

        if (pageTable[outerIndex].find(innerIndex) != pageTable[outerIndex].end()) {
            ++pageHits;
        } else {
            int physicalPage = memManager.allocatePage();
            if (physicalPage != -1) {
                pageTable[outerIndex][innerIndex] = physicalPage;
                ++pageMisses;
            }
        }
    }

    void TwoLevelTask::releaseMemory(int virtualPage)  {
        int outerIndex = virtualPage >> 10;
        int innerIndex = virtualPage & 0x3FF;

        auto outerIt = pageTable.find(outerIndex);
        if (outerIt != pageTable.end()) {
            auto innerIt = outerIt->second.find(innerIndex);
            if (innerIt != outerIt->second.end()) {
                memManager.deallocatePage(innerIt->second);
                outerIt->second.erase(innerIt);
                if (outerIt->second.empty()) {
                    pageTable.erase(outerIt);
                }
            }
        }
    }

    size_t TwoLevelTask::getPageTableMemoryUsage() const  {
        size_t memoryUsage = 0;
        for (const auto &outerEntry : pageTable) {
            memoryUsage += sizeof(std::pair<int, std::unordered_map<int, int>>);
            memoryUsage += outerEntry.second.size() * sizeof(std::pair<int, int>);
        }
        return memoryUsage;
    }

