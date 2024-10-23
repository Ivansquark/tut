#ifndef O_H
#define O_H

//------------------- C -------------------------------------------------------
extern "C" {
void addHandler(int i, void (*f)());
void call(int i);
void addFunctions(void (*f)());
void callFunctions();
}
//------------------- static --------------------------------------------------
class ObsMan {
  public:
    static void addHandler(int i, void (*f)()) { events[i] = f; }
    static void call(int i) { events[i](); }
    static void (*events[10])();
};

template <int i, typename... Classes>
class ObsStat {
  public:
    ObsStat() { ObsMan::addHandler(i, handler); }
    static void handler() { (Classes::run(), ...); }
};

//------------------- dynamic -------------------------------------------------
class ObsManDyn {
  public:
    static void addHandler(int i, void (*f)()) { events[i] = f; }
    static void call(int i) { events[i](); }
    static void (*events[10])();
};
class ObsInterface {
  public:
    virtual void run() = 0;
};

class ObsDyn {
  public:
    ObsDyn(int i) { ObsManDyn::addHandler(i, handler); }
    static void addObj(ObsInterface* obj) {
        int count = 0;
        for (auto&& i : objs) {
            if (!i) {
                objs[count] = obj;
                return;
            }
            count++;
        }
    }
    static void handler() {
        for (auto&& i : objs) {
            if (i) {
                i->run();
            }
        }
    }

    static ObsInterface* objs[2];
};
#endif // O_H
