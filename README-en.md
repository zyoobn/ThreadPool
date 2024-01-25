# Project Name: Simple Thread Pool Implementation in C++

## Project Overview

This project is an implementation of a thread pool in C++. A thread pool is a mechanism for executing tasks using multiple threads efficiently. It manages and reuses threads effectively, reducing the overhead of creating and destroying threads frequently. The thread pool supports task submission and asynchronous execution, providing a simple interface for users.

## Project Features

1. **Thread Management:** The thread pool automatically manages the creation, destruction, and reuse of threads, reducing the overhead of frequent thread creation and destruction.

2. **Task Queue:** Tasks to be executed are managed using a task queue, ensuring tasks are executed in the order they are submitted.

3. **Asynchronous Execution:** Users can submit various tasks, such as functions and lambda expressions, for asynchronous execution.

4. **Flexible Configuration:** Users can configure the thread pool by specifying the number of threads to adapt to different application scenarios.

5. **Safety:** Mutex locks and condition variables are used to ensure thread safety.

## Usage

1. Place `ThreadPool.h` and `ThreadPool.cpp` in the same directory.

2. Compile `ThreadPool.cpp` using the clang++ compiler to generate the executable file.

    ```
    clang++ -std=c++17 ThreadPool.cpp -o thread_pool_example
    ```

3. Run the generated executable file.

    ```
    ./thread_pool_example
    ```

## Example Output
```
139758528738880
1 : 1 + 10 = 11
139758553916992
2 : 1
139758553916992
3 : over
139758562325440
11 12
139758537131584
1 : 2 + 20 = 22
139758537131584
2 : 2
139758562309696
3 : over
139758562325440
22 24
139758553916992
1 : 3 + 30 = 33
139758545524288
2 : 3
139758545524288
3 : over
139758562325440
33 36
139758537131584
1 : 4 + 40 = 44
139758537131584
2 : 4
139758562325440
44 48
139758562309696
3 : over
139758562309696
1 : 5 + 50 = 55
139758545524288
2 : 5
139758562325440
55 60
139758537131584
3 : over
```
## Project Structure

-   **ThreadPool.h:** Contains the declaration and definition code for the `ThreadPool` class, defining the main logic of the thread pool.

-   **ThreadPool.cpp:** Contains the main function and example code, demonstrating how to use different features of the `ThreadPool`.

-   **thread_pool_example:** Binary executable file of the `ThreadPool.cpp` code.

-   **README.md:** Project introduction.

-   **LICENSE:** Usage license.

**Author:** Zyoobn **Date:** 2024/1/26
