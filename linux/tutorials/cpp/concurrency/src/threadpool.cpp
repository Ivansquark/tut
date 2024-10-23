#include "threadpool.h"

void fun(int arg) { // Тест обычной функции
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Вызов обычной функции fun1 ----> arg =" << arg << " Обработка потока ------>"
              << std::this_thread ::get_id() << std::endl;
}

int gfun::operator()(int arg) { // Функциональный тест
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Функтор вызова gfun ----> arg = " << arg << " Поток обработки ------> " << std::this_thread ::get_id()
              << std::endl;
    return arg;
}

int A::Afun(int arg) { // Статическая функция
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "Вызов статической функции класса Afun ----> arg = " << arg << " Поток обработки ------> "
              << std::this_thread ::get_id() << std::endl;
    return arg;
}

void A::CFun(int arg) { // Обычные функции
    std::this_thread::sleep_for(std::chrono::seconds(4));
    std::cout << "Вызов обычной функции класса Cfun ----> arg = " << arg << " Обработка потока ------> "
              << std::this_thread ::get_id() << std::endl;
}
