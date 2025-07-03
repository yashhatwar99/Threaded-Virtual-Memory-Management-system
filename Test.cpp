#include <iostream>
#include "config.h"
#include <fstream>
#include <sstream>
#include <pthread.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include <unordered_map>


using namespace std;

// Function to generate a random address aligned to the page size
long generateAlignedAddress(long startAddr) {
    long offset = (rand() % 250) * PAGESIZE;  // Example random offset range
    return startAddr + offset;
}

// Function to write to a file
void writeToFile(string filename, string text) {
    ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << text << endl;
    } else {
        cout << "Unable to open file" << endl;
    }
    file.close();
}

long generateSizetoRead() {
    return ((rand() % 10) + 1) * PAGESIZE;
}

int generate_a_random_taskid(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Generate a random number between 0 and 4
int generate_a_random_number() {
    return rand() % 5;
}
int generateAndStore(int taskid, int numbers_in_task_id, const string& filename) {
    if (filename.empty()) {
        cerr << "Error: Filename is empty for task " << taskid << endl;
        return -1;
    }

    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return -1;
    }

    long totalMemoryUsed = 0;
    const long MAX_MEMORY_PER_TASK = 10000;  // 🚨 Reduce memory cap to 10MB

    long textAddr, dataAddr;
    long sizetext, sizedata;
    vector<string> buffer;  // ✅ Use vector instead of stringstream to reduce memory allocation

    for (int i = 0; i < numbers_in_task_id; i++) {
        if (totalMemoryUsed > MAX_MEMORY_PER_TASK) break;  // ✅ Enforce memory limit

        textAddr = generateAlignedAddress(TEXT_SECTION_START);
        sizetext = generateSizetoRead();
        totalMemoryUsed += sizetext;
        buffer.push_back("T" + to_string(taskid) + ":0x" + to_string(textAddr) + ":" + to_string(sizetext) + " KB");

        dataAddr = generateAlignedAddress(DATA_SECTION_START);
        sizedata = generateSizetoRead();
        totalMemoryUsed += sizedata;
        buffer.push_back("T" + to_string(taskid) + ":0x" + to_string(dataAddr) + ":" + to_string(sizedata) + " KB");

        if (i % 100 == 0) {  // 🚀 Batch write every 100 entries to avoid excessive I/O
            for (const string& entry : buffer) {
                file << entry << "\n";
            }
            buffer.clear();
            file.flush();
        }
    }

    for (const string& entry : buffer) {  // Write remaining data
        file << entry << "\n";
    }
    file.close();
    return 0;
}





// Struct to pass data to threads
struct TaskInfo {
    int taskid;
    int numbers_in_task_id;
    string filename;
};

// Thread function wrapper
void* generateAndStoreWrapper(void* arg) {
    TaskInfo* taskInfo = (TaskInfo*)arg;
    generateAndStore(taskInfo->taskid, taskInfo->numbers_in_task_id, taskInfo->filename);
    return NULL;
}

// Function to create and run a thread for each task
void createAndRunThreads(int num_tasks, int numbers_in_task_id) {
    if (num_tasks <= 0) return;  // Prevent invalid calls

    vector<pthread_t> threads(num_tasks);
    vector<TaskInfo*> taskInfos(num_tasks);

    for (int i = 0; i < num_tasks; i++) {
        int taskID = i + 1;  // ✅ Ensure task IDs start at 1

        string filename = to_string(taskID) + ".txt";
        if (filename.empty()) {
            cerr << "Error: Filename is empty for task " << taskID << endl;
            continue;  // 🚨 Prevent invalid task creation
        }

        taskInfos[i] = new TaskInfo{taskID, numbers_in_task_id / 5, filename};

        if (pthread_create(&threads[i], NULL, generateAndStoreWrapper, taskInfos[i]) != 0) {
            cerr << "Error creating thread for task " << taskID << endl;
            delete taskInfos[i];  // Cleanup on failure
        }
    }

    for (int i = 0; i < num_tasks; i++) {
        pthread_join(threads[i], NULL);
        delete taskInfos[i];  // ✅ Ensure proper cleanup
    }
}




void mergeFiles(vector<string>& filenames, const string& outputFilename) {
    unordered_map<string, long> memoryUsage;
    ofstream outputFile(outputFilename, ios::out | ios::trunc);

    if (!outputFile.is_open()) {
        cerr << "Unable to open output file: " << outputFilename << endl;
        return;
    }

    for (const auto& filename : filenames) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            continue;
        }

        stringstream buffer;
        buffer << file.rdbuf();  // ✅ Read the entire file at once (much faster)

        string line;
        while (getline(buffer, line)) {
            outputFile << line << "\n";  // ✅ Write to final output file
            
            // Extract memory usage
            size_t firstColon = line.find(":");
            size_t lastColon = line.rfind(":");

            if (firstColon != string::npos && lastColon != string::npos && firstColon != lastColon) {
                string taskID = line.substr(0, firstColon);
                long memorySize = stol(line.substr(lastColon + 1));

                memoryUsage[taskID] += memorySize;
            }
        }

        file.close();
    }

    outputFile.close();
    cout << "Merged all files into " << outputFilename << endl;

    // Print total memory usage per task
    cout << "\nMemory Usage Per Task:" << endl;
    for (const auto& entry : memoryUsage) {
        cout << entry.first << " used " << entry.second << " KB" << endl;
    }
}



// Main function
#include <chrono>

int main() {
    srand(time(0));
    vector<string> filenames;

    // Start timing
    auto start_time = chrono::high_resolution_clock::now();

    // Run all threads in parallel
    createAndRunThreads(10, 200);

    for (int i = 1; i <= 10; i++) {
        filenames.push_back(to_string(i) + ".txt");
    }

    string outputFilename = "tracefile.txt";
    mergeFiles(filenames, outputFilename);

    // Stop timing
    auto end_time = chrono::high_resolution_clock::now();
    cout << "Total Execution Time: "
         << chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count()
         << " ms" << endl;

    return 0;
}

