
#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <set>
#include "config.h"
#include <algorithm> // std::remove_if

class MemoryManager {
private:
    std::set<int> availablePages; // Set of available pages in memory
    int totalPages;

public:
    MemoryManager(int total_pages);
    int allocatePage();
    void deallocatePage(int page) ;
    int availablePageCount() const;
    void printAvailablePages() const;

    void resetMemoryManager();
    void SetTotalPages(int total_pages);

};

#endif // MEMORY_MANAGER_H  // End of MemoryManager.h