
# Producer-Consumer Problem Implementation

This project implements the classic Producer-Consumer problem in C++. The implementation includes both bounded and unbounded queues for managing the produced and consumed items. The project is structured to allow easy compilation and execution using CMake or a provided makefile.



![ex3pic](https://user-images.githubusercontent.com/84729141/171872599-72bb22f4-d1bd-4647-bf61-540295babfe4.png)



## Project Structure

- **BoundedQ.h / UnboundedQ.h**: These header files define the classes and methods for the bounded and unbounded queues, respectively. These queues are used to manage the items produced by producers and consumed by consumers.

- **ex3.cpp**: The main source file that contains the logic for the producer-consumer problem. It handles the creation of producer and consumer threads and manages their interaction through the queues.

- **config.txt**: A configuration file that may contain parameters or settings for the producer-consumer problem, such as the number of producers, consumers, or the queue size.

- **CMakeLists.txt**: The CMake configuration file used for building the project.

- **makeFile**: A traditional makefile for compiling the project without CMake.

## Prerequisites

- **C++ Compiler**: Make sure a C++ compiler is installed on your machine (e.g., g++).
- **CMake**: (Optional) CMake can be used for easier building and management of the project.

## How to Build and Run

### Using CMake

1. **Navigate to the project directory**:
   ```bash
   cd OS_Producer_Consumer-master
   ```

2. **Create a build directory and navigate to it**:
   ```bash
   mkdir build && cd build
   ```

3. **Run CMake to generate the build files**:
   ```bash
   cmake ..
   ```

4. **Build the project**:
   ```bash
   make
   ```

5. **Run the compiled program**:
   ```bash
   ./ProducerConsumer
   ```

### Using the Makefile

1. **Navigate to the project directory**:
   ```bash
   cd OS_Producer_Consumer-master
   ```

2. **Run the make command**:
   ```bash
   make -f makeFile
   ```

3. **Run the compiled program**:
   ```bash
   ./ProducerConsumer
   ```

## Configuration

- **config.txt**: Modify this file to adjust the parameters of the producer-consumer problem, such as the number of producers, consumers, and the size of the queue.


