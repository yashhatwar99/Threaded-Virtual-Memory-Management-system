#ifndef _IO_MANAGER_H_
#define _IO_MANAGER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <set>
#include <chrono>
#include <unordered_map>
#include "Task.h"
#include "config.h"

class IOManager {
public:
    static void processTraceFile(const std::string &traceFile);
};

#endif // _IO_MANAGER_H_ // End of IOManager.h
