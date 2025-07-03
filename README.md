
# 🧠 Memory Management System using Multithreading

A virtual memory management simulation built in **C++** with multithreaded task handling, performance tracking, and modular architecture. This system mimics how operating systems manage tasks, allocate memory, and monitor performance—serving as a practical learning project in OS concepts and system-level programming.

---

## 📌 Project Highlights

- 🧵 **Multithreading**: Executes multiple tasks concurrently using POSIX threads.
- 📚 **Virtual Memory Simulation**: Simulates address translation, memory allocation, and page hit/miss tracking.
- 📊 **Performance Metrics**: Tracks task execution time, physical memory usage, and virtual memory stats.
- ⚙️ **Modular Design**: Clean separation of logic via `Task`, `MemoryManager`, `IOManager`, and `Performance` classes.

---

## 🧱 File Structure

```
📦 Memory-Management-System-multithreading/
├── I/O Components
│   ├── IOManager.cpp
│   ├── IOManager.h
│
├── Memory Management
│   ├── MemoryManager.cpp
│   ├── MemoryManager.h
│
├── Performance Monitoring
│   ├── Performance.cpp
│   ├── Performance.h
│
├── Tasks
│   ├── Task.cpp
│   ├── Task.h
│
├── Core Execution
│   ├── Test.cpp              # Entry point for the program
│   ├── config.h              # Configuration constants
│   ├── Makefile              # Build script
│
├── Compiled Binaries
│   ├── memory_management_system
│   ├── test_mem_manager
│   ├── test_memory_manager
│
├── Documentation
│   ├── README.md
```

---

## 🛠️ Setup Instructions

### ✅ Prerequisites
- C++ Compiler (e.g., `g++`)
- `make` utility (on Linux/macOS or Windows via WSL)

### ⚙️ Build the Project

```bash
make
```

### ▶️ Run the Executable

```bash
./memory_management_system
```

### ❌ Clean Build Files

```bash
make clean
```

---

## 🧪 Sample Output (What to Expect)

After execution, the system will output:

- ⏱️ **Execution Time per Task**
- 📈 **Total Memory Used**
- 🔁 **Page Hits & Misses**
- 📉 **Free Physical Memory Left**

*Output is printed to the terminal via the `Performance` module.*

---

## 🧠 Concepts Implemented

- Multithreading with `pthread`
- Virtual-to-physical memory mapping
- Page table lookup simulation
- Performance measurement using timers
- Makefile-based modular C++ build

---

## 📖 Example Use Case

```cpp
// Creating a task and launching with memory reference simulation
Task task("task1", "tracefile_1KB_8GB_16GB.txt");
task.run();

// Measuring performance
Performance::log(task);
```

---

## 🏗️ Modules Overview

| Module          | Purpose                                                  |
|-----------------|----------------------------------------------------------|
| `Task`          | Simulates processes/tasks with memory traces             |
| `MemoryManager` | Allocates memory, maps pages, tracks usage               |
| `IOManager`     | Handles file reading, trace parsing                      |
| `Performance`   | Tracks time taken, memory used, page stats               |
| `config.h`      | Defines page size, physical/virtual memory constants     |
| `Test.cpp`      | Main entry for program execution                         |

---

## 👩‍💻 Author

**Tanishka Randive**  
📍 BTech AI & Data Engineering @ IIT Ropar  
🔗 [GitHub](https://github.com/Tanishka15) | [LinkedIn](https://www.linkedin.com/in/tanishka-randive-42639b275/)

---

## 📝 License

This project is intended for educational purposes. Contributions are welcome!  
Feel free to fork, modify, and use it in your own OS or systems coursework.

---

## ⭐ Show Your Support

If this project helped you understand memory management better, please consider giving it a ⭐ and sharing it with your peers!
