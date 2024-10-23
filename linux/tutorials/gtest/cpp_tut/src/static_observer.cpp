#include "static_observer.h"

void (*ObserverManager::fPtr[SIZE])() = {nullptr};
