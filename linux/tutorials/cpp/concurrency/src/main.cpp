#include "threadpool.h"
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

class Sum {
  public:
    Sum(int x = 0, int y = 0) {
        sum = x + y;
        omtx = new std::mutex;
    }
    ~Sum() { delete omtx; }
    int sum = 0;
    std::mutex* omtx;
    void printSum(int x = 0, int y = 0) {
        std::mutex mtx;
        omtx->lock();
        // std::unique_lock<std::mutex> ul(*omtx);
        sum = x + y;
        std::cout << "Sum = " << sum
                  << " Thread_ID = " << std::this_thread::get_id() << std::endl;
        for (int i = 0; i < sum; i++) {
            std::cout << "--Sum = " << --sum
                      << " Thread_ID = " << std::this_thread::get_id()
                      << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        // ul.unlock();
        omtx->unlock();
    }
};

void one(int x, int y) { std::cout << " one " << std::endl; }
void two() { std::cout << " two " << std::endl; }

// обертка над методом объекта
//  decltype(auto) ass_fun(A &a, int arg) { return a.CFun(arg); }
void ass_fun(A& a, int arg) { return a.CFun(arg); }

int main(int argc, char* argv[]) {

    try {
        MyThreadPool executor{10};
        A a;

        std::future<void> nom_fun = executor.commit(fun, 1);
        std::future<int> functor_fun = executor.commit(gfun{}, 2);
        std::future<int> s_cls_fun = executor.commit(a.Afun, 3);
        std::future<void> nom_cls_fun = executor.commit(ass_fun, a, 4);
        std::future<void> one_func = executor.commit(one, 2, 3);

        std::cout << " main thread: " << std::this_thread::get_id()
                  << std::endl;
        nom_fun.get();
        std::cout << "Результат вычисления функции return ---> "
                  << functor_fun.get() << " "
                  << std::endl; // Ожидание получения результата
        std::cout << "Результат вычисления функции return ---> "
                  << s_cls_fun.get() << " "
                  << std::endl; // Ожидание получения результата
        nom_cls_fun.get();
        one_func.get();

        // return 0;
    } catch (std::exception& e) {
        std::cout << e.what() << std::this_thread::get_id() << e.what()
                  << std::endl;
    }

    std::cout << "\nSTART" << " Thread_ID = " << std::this_thread::get_id()
              << std::endl;

    Sum sum(1, 2);

    std::thread t1(&Sum::printSum, sum, 1, 2);
    std::thread t2(&Sum::printSum, sum, 3, 4);
    t1.join();
    t2.join();

    return 0;
}
