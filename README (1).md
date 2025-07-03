
# Time Measurement Project

## Overview

This project contains three C programs (`time.c`, `time_pipe.c`, and `time_sharedmemory.c`) that demonstrate different inter-process communication (IPC) methods to measure the time taken to execute a command. The goal is to compare the performance and effectiveness of using basic `fork()`, pipes, and shared memory for inter-process communication, and determine the most efficient method for time measurement.

## Files

1. **`time.c`**:
   - The simplest approach, using `fork()` to create a child process that executes a command. The parent process measures the time before and after the execution without any inter-process communication.
   
2. **`time_pipe.c`**:
   - This version adds a pipe to transfer the start time from the child process to the parent process. The parent measures the end time and calculates the difference.
   
3. **`time_sharedmemory.c`**:
   - This implementation uses shared memory to store the start time recorded by the child process. The parent process accesses this shared memory to compute the time elapsed after the command execution.

4. **`Makefile`**:
   - A makefile is provided to compile each of these C programs. It automates the build process for easier execution.

### Compilation

To compile the programs, run the following command in the project directory:

```bash
make
```

This will generate three executable files: `time`, `time_pipe`, and `time_sharedmemory`.

### Running the Programs

To run any of the programs, use the following syntax:

```bash
./time <command> [args...]
```

For example, to measure the time taken to list files using `ls`, you can run:

```bash
./time ls
```

Repeat similar commands for `time_pipe` and `time_sharedmemory`.

## Comparison of Approaches

1. **Basic Fork (`time.c`)**:
   - **Description**: This program uses `fork()` to create a child process. The parent process records the start time and waits for the child to complete before recording the end time.
   - **Pros**: Simple and easy to implement.
   - **Cons**: Timing can be slightly inaccurate, as the parent measures the time before the child starts executing the command.

2. **Pipe (`time_pipe.c`)**:
   - **Description**: The child records the start time and sends it to the parent via a pipe. The parent calculates the elapsed time once the child finishes.
   - **Pros**: More accurate, as the child process records the time just before command execution.
   - **Cons**: Requires setting up and managing the pipe, which adds a small overhead.

3. **Shared Memory (`time_sharedmemory.c`)**:
   - **Description**: The child writes the start time to a shared memory segment, which the parent reads after the child finishes executing the command.
   - **Pros**: Efficient and allows for faster data exchange compared to pipes.
   - **Cons**: Shared memory management can be complex, and the program needs to ensure proper attachment and detachment of memory segments.

## Conclusion

- **Accuracy**: The pipe and shared memory approaches provide more accurate timing compared to the basic `fork()` method, as the child process directly records the start time.
- **Efficiency**: The shared memory approach is slightly more efficient than using pipes because it avoids the need for data to travel through a pipe buffer. However, shared memory requires more careful management.
- **Complexity**: The basic `fork()` method is the easiest to implement, while shared memory adds complexity with memory management but improves performance.


<!---
Tanishka15/Tanishka15 is a ✨ special ✨ repository because its `README.md` (this file) appears on your GitHub profile.
You can click the Preview link to take a look at your changes.
--->
