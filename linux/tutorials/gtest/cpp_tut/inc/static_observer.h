#ifndef STATIC_OBSERVER
#define STATIC_OBSERVER

#include <iostream>

static constexpr auto SIZE = 20;

template <typename... Args>
void pri(Args&&... args) {
    ((std::cout << std::forward<Args>(args) << " "), ...,
     (std::cout << std::endl));
}

class ObserverManager {
  public:
    static void (*fPtr[SIZE])();
    static void call(auto x) { fPtr[x](); }
    static void addHandler(void (*ptr)(), auto num) { fPtr[num] = ptr; }
};

template <int num, typename... Subscribed>
class Observer {
  public:
    Observer() { ObserverManager::addHandler(handler, num); }

  private:
    static void handler() { (Subscribed::handler(), ...); }
};

class Test1 {
  public:
    static void handler() { pri("Test1"); }
};
class Test2 {
  public:
    static void handler() { pri("Test2"); }
};

#endif // STATIC_OBSERVER
