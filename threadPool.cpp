#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <memory>
#include <future>
#include <functional>
#include <condition_variable>

class threadPool {
public:
    threadPool(const size_t& numThreads = std::thread::hardware_concurrency()) : shutDown(false) {
        for (int i = 0; i < numThreads; ++i) {
            threads.emplace_back([this] () {
                while (true) {
                    std::unique_lock<std::mutex> lock(mtx);
                    // std::cout << tasks.size() << ' ' << shutDown << '\n';
                    condition.wait(lock, [this]() {
                        return (!tasks.empty() || shutDown);
                    });

                    if (shutDown && tasks.empty()) {
                        return;
                    }

                    std::function<void()> task = std::move(tasks.front());
                    tasks.pop();
                    lock.unlock();

                    task();
                }
            });
        }
    }

    ~threadPool() {
        std::unique_lock<std::mutex> lock(mtx);
        shutDown = true;
        lock.unlock();

        condition.notify_all();
        for (auto &t : threads) {
            if (t.joinable()) {
                t.join();
            }
        }
    }

    template<typename F, typename... Args> 
    void enqueue(F&& func, Args&&... args) {
        std::function<decltype(func(args...))()> f = std::bind(std::forward<F>(func), std::forward<Args>(args)...);
        auto taskPtr = std::make_shared<std::packaged_task<decltype(func(args...))()>>(f);
        std::function<void()> task = [taskPtr]() {
            (*taskPtr)();
        };
        std::unique_lock<std::mutex> lock(mtx);
        tasks.emplace(task);
        lock.unlock();

        condition.notify_one();
    }
private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;

    std::mutex mtx;
    std::condition_variable condition;

    bool shutDown;
};

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
