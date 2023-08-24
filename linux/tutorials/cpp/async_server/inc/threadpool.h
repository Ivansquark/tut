#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

class MyThreadPool {
  public:
    MyThreadPool(int thread_size = 4) : _stop(false), _free_size(thread_size) {
        for (int i = 0; i < thread_size; i++) {
            i++;
            _wokers.emplace_back([this] {
                {
                // lock mutex till brakets close
                    std::lock_guard<std::mutex> t{_m};
                    std::cout << "thread " << std::this_thread::get_id() << " has been created" << std::endl;
                }
                // switch threads thats take tasks from queue
                while (!this->_stop) {
                    std::function<void()> task;
                    {
                    //! Stops all threads untill new task get pushed in queue
                        std::unique_lock<std::mutex> lock{_m};
                        //conditional variable requires unique_lock before wait
                        //wait unlocks mutex and stopped thread while not get signal of conditional wariable
                        cv.wait(lock, [this] { return _stop.load() || !_task_list.empty(); });
                        if (_stop && _task_list.empty()) {
                            return;
                        }
                        task = std::move(_task_list.front());
                        //decrease queue
                        _task_list.pop();
                    }
                    _free_size--;
                    // call task
                    task();
                    _free_size++;
                }
            });
        }
    }

    template <class F, class... Args> decltype(auto) commit(F &&f, Args &&...args) {
        if (_stop.load()) {
            throw std::runtime_error("thread pool has been closed");
        }
        using RetType = decltype(f(args...));
        auto task = std::make_shared<std::packaged_task< RetType()>>( // Возвращаемое значение RecType, параметр void
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));
       // auto task = std::make_shared<std::packaged_task<decltype(f(args...))>>( // Возвращаемое значение RecType, параметр void
       //     [&](){f(std::forward<Args>(args)...);}
       // );


        // Добавить задачу в очередь
        std::future<RetType> future = task->get_future();
        { // Блокировка оператора текущего блока lock_guard - это класс инкапсуляции
            std::lock_guard<std ::mutex> lock{_m}; // стека мьютекса, lock () при создании, unlock () при разрушении
            _task_list.emplace([task] { (*task)(); });
        }
        // wake up one thread for work
        cv.notify_one(); // разбудить поток для выполнения

        return future;
    }

    int free_size() { return _free_size; }

    ~MyThreadPool() {
        _stop.store(true);
        cv.notify_all(); // wake up all threads 
        for (std::thread &woker : _wokers) {
            if (woker.joinable())
                woker.join(); // Ожидание завершения задачи
        }
    }
    void setStop(std::atomic<bool> state) {
        _stop.store(state);
    }

  private:
    using Tast = std::function<void()>;
    std::vector<std::thread> _wokers; // Рабочий поток
    std::queue<Tast> _task_list;      // очередь задач
    std::mutex _m;                    // переменная синхронизации
    std::atomic<int> _free_size;      // Свободный поток
    std::atomic<bool> _stop;          // Завершить ли
    std::condition_variable cv;       // Блокировка условий
};

void fun(int arg);

struct gfun {
    int operator()(int arg);
};

class A {
  public:
    static int Afun(int arg = 0);
    void CFun(int arg);
};

#endif // THREADPOOL_H
