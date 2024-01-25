#include <iostream>
#include "threadPool.h"

std::mutex printMtx;

int main() {
    threadPool tp(5);
    for (int i = 1; i <= 5; ++i) {
        int a = tp.enqueue([] (int i, int j) {
            std::unique_lock<std::mutex> lock(printMtx);
            std::cout << std::this_thread::get_id() << std::endl;
            std::cout << "1 : " << i << " + " << j << " = " << i + j << std::endl; 
            // std::this_thread::sleep_for(std::chrono::seconds(1));
            return i + j;
        }, i, i * 10).get();
        int b = tp.enqueue([a] (int i) {
            std::unique_lock<std::mutex> lock(printMtx);
            std::cout << std::this_thread::get_id() << std::endl;
            std::cout << "2 : " << i << std::endl; 
            // std::this_thread::sleep_for(std::chrono::seconds(1));
            return a + i;
        }, i).get();
        tp.enqueue([a, b] () {
            std::unique_lock<std::mutex> lock(printMtx);
            std::cout << std::this_thread::get_id() << std::endl;
            std::cout << "3 : " << "over" << std::endl; 
            // std::this_thread::sleep_for(std::chrono::seconds(1));
        });
        std::unique_lock<std::mutex> lock(printMtx);
        std::cout << std::this_thread::get_id() << std::endl;
        std::cout << a << ' ' << b << std::endl;
    }
    return 0;
}
 