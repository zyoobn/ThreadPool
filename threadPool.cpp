#include <iostream>
#include "threadPool.h"

std::mutex printMtx;

int main() {
    threadPool tp(5);
    for (int i = 1; i <= 10; ++i) {
        tp.enqueue([] (int i, int j) {
            std::unique_lock<std::mutex> lock(printMtx);
            std::cout << "1 : " << i << " + " << j << " = " << i + j << std::endl; 
            // std::this_thread::sleep_for(std::chrono::seconds(1));
        }, i, i * 10);
        tp.enqueue([] (int i) {
            std::unique_lock<std::mutex> lock(printMtx);
            std::cout << "2 : " << i << std::endl; 
            // std::this_thread::sleep_for(std::chrono::seconds(1));
        }, i);
        tp.enqueue([] () {
            std::unique_lock<std::mutex> lock(printMtx);
            std::cout << "3 : " << "over" << std::endl; 
            // std::this_thread::sleep_for(std::chrono::seconds(1));
        });
    }
    return 0;
}
 