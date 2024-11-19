#include "main.h"
#include "pthread.h"
#include "time.h"
#include "wait.h"
#include <bits/move.h>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <stdio.h>
#include <thread>
#include <unistd.h>
#include <utility>

void threadFunction1();
void threadFunction2();

std::condition_variable cv;
std::mutex mut;

bool task(const std::string& str) {
    std::cout << str << std::endl;
    if (str == "exit") {
        return true;
    } else
        return false;
}

void initPromise(std::promise<const std::string&>& pr, const std::string& str) {
    std::cout << "Promise " << str << std::endl;
    if (str == "opa") {
        pr.set_value(str);
    } else {
        std::string str1 = "wrong";
        const_cast<std::string&>(str) = str1;
        pr.set_value(str);
    }
}

class Print {
  public:
    void print(int x) { std::cout << "print - " << x << std::endl; }
};

int main(int argc, char** argv) {
    int data = 5;
    std::unique_ptr<Print> up = std::make_unique<Print>();
    // auto upl = [up = std::move(up)](){up->print(data);};
    auto uplb = std::bind([&](int data) { up->print(data); }, std::move(data));

    uplb();
    int a = 5;
    auto aa = [&]() { std::cout << "a=" << a << std::endl; };
    aa();
    // Tcp::instance();
    std::string aaa = "aaa";

    auto asyncLaunch = std::async(
        std::launch::async,
        [&](const std::string& s) {
            std::cout << "Async Launch " << aaa << s
                      << " ID: " << std::this_thread::get_id() << std::endl;
        },
        "async");
    auto asyncDeffered = std::async(
        std::launch::deferred,
        [&](const std::string& s) {
            std::cout << "Async Launch " << aaa << s
                      << " ID: " << std::this_thread::get_id() << std::endl;
        },
        "deffered");

    std::cout << "Main ID: " << std::this_thread::get_id() << std::endl;
    asyncLaunch.get();
    auto aDefFunc = [&]() { asyncDeffered.get(); };
    std::thread sDef(aDefFunc);
    sDef.detach();

    // std::thread thr1(threadFunction1);
    // std::thread thr2(threadFunction2);
    std::promise<const std::string&> p;
    std::future<const std::string&> futt = p.get_future();
    // if parameters sets to thread by reference => must use std::ref
    std::cin >> aaa;
    std::thread thrPromise(initPromise, std::ref(p), std::ref(aaa));
    thrPromise.join();
    sleep(1);
    std::cout << futt.get();
    while (1) {
        std::cin >> aaa;
        std::function<bool(const std::string&)> func = task;
        std::packaged_task<bool(const std::string&)> pTask(func);
        std::future<bool> fut = pTask.get_future();
        // packeged task must only move
        std::thread thrFuture(std::move(pTask), aaa.data());
        if (fut.get()) _exit(0);
        thrFuture.join();
    }

    // thr1.join();
    // thr2.join();
    return 0;
}

void threadFunction1() {
    std::cout << "new c++ thread ID: " << std::this_thread::get_id()
              << std::endl;
    while (1) {
        sleep(2);
        std::cout << "Thread 1 start and sleep" << std::endl;
        std::cout << "Thread 1 notify_one " << std::endl;
        cv.notify_one();
        // auto end = std::chrono::system_clock::now();
        // time_t end_time = std::chrono::system_clock::to_time_t(end);
        // std::string str = ctime(&end_time);
        // To sleep a thread for 200 Milliseconds
        // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        // system("clear");
    }
}

void threadFunction2() {
    std::cout << "threadFunction2 ID: " << std::this_thread::get_id()
              << std::endl;
    while (1) {
        sleep(1);
        std::cout << "Thread2 start and wait for notify_one" << std::endl;
        std::unique_lock<std::mutex> lock(mut);
        cv.wait(lock);
        std::cout << "Thread 2 was notify_one" << std::endl;
        // sleep(1);
        std::cout << std::endl;
    }
}
