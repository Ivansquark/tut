#ifndef ALLOCATE_H
#define ALLOCATE_H

// standard new delete overloading
#define LOGGING

#ifdef LOGGING
    #include <iostream>
#endif

#ifdef LOGGING
static size_t mem_allocated;
/*
void* operator new(size_t n) noexcept {
    void* ptr = malloc(n);
    if (ptr != nullptr) { mem_allocated += n; }
    std::cout << "Mem_allocated: " << mem_allocated << std::endl;
    return ptr;
}
void* operator new[](size_t n) {
    void* ptr = malloc(n);
    if (ptr != nullptr) { mem_allocated += n; }
    std::cout << "Mem_allocated arr: " << mem_allocated << std::endl;
    return ptr;
}

void operator delete(void* ptr, size_t n) {
    if (ptr != nullptr) { mem_allocated -= n; }
    std::cout << "Mem_deallocated: " << mem_allocated << std::endl;
    free(ptr);
}

void operator delete(void* ptr) {
    std::cout << "Mem_deallocated: " << mem_allocated << std::endl;
    free(ptr);
}
void operator delete[](void* ptr, size_t n) {
    if (ptr != nullptr) { mem_allocated -= n; }
    std::cout << "Mem_deallocated arr: " << mem_allocated << std::endl;
    free(ptr);
}

void operator delete[](void* ptr) {
    std::cout << "Mem_deallocated arr: " << mem_allocated << std::endl;
    free(ptr);
}
*/
//void* operator new(size_t n, std::nothrow_t) { return malloc(n); }
//------------------------------------------------

#endif
struct S {
    int x = 0;
    double d = 0.0;
    void* operator new(size_t n) {
        void* ptr = malloc(n);
        if (ptr != nullptr) { mem_allocated += n; }
        std::cout << "Mem_allocated: " << mem_allocated << std::endl;
        return ptr;
    }
    void operator delete(void* ptr, size_t n) {
        if (ptr != nullptr) { mem_allocated -= n; }
        std::cout << "Mem_deallocated: " << mem_allocated << std::endl;
        free(ptr);
    }
    void* operator new(size_t, S* ptr) {
        std::cout << "Mem_allocated constructed: " << mem_allocated
                  << std::endl;
        return ptr;
    }
    void* operator new(size_t n, std::nothrow_t) { return malloc(n); }
};


#endif // ALLOCATE
