#ifndef _TASK_H_
#define _TASK_H_

#include "MemoryManager.h"


class Task {
protected:
    int taskId;
    int pageHits;
    int pageMisses;

public:
    Task(int id);
    
    virtual void requestMemory(int virtualPage) = 0;
    virtual void releaseMemory(int virtualPage) = 0;
    virtual size_t getPageTableMemoryUsage() const = 0;

    int getPageHits() const;
    int getPageMisses() const;
    void printTaskData();
    virtual ~Task() noexcept = default;
};

extern std::map<std::string, Task*> tasks;

class SingleLevelTask : public Task {
private:
    std::unordered_map<int, int> pageTable;

public:
    SingleLevelTask(int id);
    void requestMemory(int virtualPage) override;
    void releaseMemory(int virtualPage) override;
    size_t getPageTableMemoryUsage() const override;
};

// Two Level Task Class
class TwoLevelTask : public Task {
private:
    std::unordered_map<int, std::unordered_map<int, int>> pageTable;

public:
    TwoLevelTask(int id);
    void requestMemory(int virtualPage) override;
    void releaseMemory(int virtualPage) override;
    size_t getPageTableMemoryUsage() const override;
 
};


#endif