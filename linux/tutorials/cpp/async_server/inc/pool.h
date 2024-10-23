#ifndef POOL_H
#define POOL_H

#include <atomic>
#include <chrono>
#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <optional>
#include <queue>
#include <thread>
//! brief main class that implements basic thread pool;

template <typename T> class ThreadsafeQueue {
    std::queue<T, std::deque<T>> queue_;
    mutable std::mutex mutex_;

    // Moved out of public interface to prevent races between this
    // and pop().
  public:
    ThreadsafeQueue() = default;
    ThreadsafeQueue(const ThreadsafeQueue<T> &) = delete;
    ThreadsafeQueue &operator=(const ThreadsafeQueue<T> &) = delete;
    ThreadsafeQueue(ThreadsafeQueue<T> &&other) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_ = std::move(other.queue_);
    }
    virtual ~ThreadsafeQueue() {}

    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }
    unsigned long size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }
    // return T or nothing
    std::optional<T> pop() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (queue_.empty()) {
            //return {};
            return nullptr;
        }
        T tmp = queue_.front();
        queue_.pop();
        return tmp;
    }
    void push(const T &item) {
        std::lock_guard<std::mutex> lock(mutex_);
        // queue_.push(item);
        queue_.emplace(item);
    }
};

class Pool {
  public:
    Pool() : stop(false), maxThreads(false) {
        // fill threadpool with threads
        for (count = 0; count < MaxThreadNum; count++) {
            workers.emplace_back([this] {
                while (!stop) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> ul(mut);
                        currentWaitThreadsNumber++;
                        // for avoid unwanted wake ups
                        while (!g_notified) {
                            cv.wait(ul);
                        }
                        g_notified.store(false);
                        if (!currentQueueSize && stop.load()) {
                            // for properly exit
                            return;
                        }
                        if (!que.empty()) {
                            task = std::move(*que.pop());
                            currentQueueSize--;
                        }
                        // std::cout << "Queu_size: " << currentQueueSize << std::endl;
                        if (currentQueueSize <= 0) {
                            currentQueueSize = 0;
                            zeroQueue = true;
                        } else {
                            zeroQueue = false;
                        }
                        currentWaitThreadsNumber--;
                    }
                    // call function
                    if (task) {
                        task();
                    }
                    // std::lock_guard<std::mutex> lg(mut);
                    if (maxThreads) {
                        // threads > maxThreadNumber
                        if (zeroQueue) {
                            maxThreads = false; // all tasks are done => wait for new tasks
                        } else {
                            // TODO: find max threads to wake up
                            mut.lock();
                            int threadsToWakeUp =
                                ((int)currentQueueSize > maxThreads)
                                    ? ((int)currentWaitThreadsNumber)
                                    : (((int)currentWaitThreadsNumber > (maxThreads - (int)currentQueueSize))
                                           ? (maxThreads - (int)currentQueueSize)
                                           : ((int)currentWaitThreadsNumber));

                            // std::cout << " thread notify" << threadsToWakeUp << std::endl;
                            mut.unlock();
                            for (int i = 0; i <= threadsToWakeUp; i++) {
                                g_notified.store(true);
                                cv.notify_one();
                            }
                        }
                    }
                }
            });
        }
    }
    ~Pool() {
        for (int i = 0; i < MaxThreadNum; i++) {
            stop = true;
            workers[i].join(); // execute all tasks in pool
        }
        cv.notify_all();
    }
    // Add task (any function) to queue
    template <typename T, typename... Args> decltype(auto) addTask(T &func, Args &&...args) {
        using RetType = decltype(func(args...)); // get return type of function

        //std::cout << "Add Task: " << std::this_thread::get_id() << std::endl;
        // bind to function address function with any parameters
        // on stack
        // std::function<void()> f = std::bind(std::forward<T>(func), std::forward<Args>(args)...);
        // que.push(f);
        //
        //
        // in heap
        // std::shared_ptr<std::function<void()>> task =
        //    std::make_shared<std::function<void()>>(std::bind(std::forward<T>(func), std::forward<Args>(args)...));

        //    shared_ptr wrapper cause packaged_task cannot be copied
        std::shared_ptr<std::packaged_task<RetType()>> task = std::make_shared<std::packaged_task<RetType()>>(
            std::bind(std::forward<T>(func), std::forward<Args>(args)...));
        std::future<RetType> future = task->get_future();
        std::lock_guard<std::mutex> t(mut);
        que.push([task = task](){
            (*task)(); // dereference and call
        });
        currentQueueSize++;
        zeroQueue = false;
        if (currentQueueSize < (currentWaitThreadsNumber)) {
            g_notified.store(true);
            cv.notify_one();
            //std::cout << "first notify" << std::endl;
        } else {
            maxThreads = true;
        }

        return future;
        //} // mutex unlock()
    }
    void setStop(bool var) { stop.store(var); }

  private:
    std::mutex mut;
    ThreadsafeQueue<std::function<void()>> que;
    std::atomic<bool> stop;
    std::atomic<bool> maxThreads;
    std::atomic<bool> zeroQueue{false};
    std::atomic<bool> g_notified{false};
    std::atomic<int> currentQueueSize = 0;
    std::atomic<uint8_t> count = 0;
    std::condition_variable cv;
    std::vector<std::thread> workers;

    static std::atomic<int> currentWaitThreadsNumber;
    static constexpr auto MaxThreadNum = 8;
};

#endif // POOL_H
