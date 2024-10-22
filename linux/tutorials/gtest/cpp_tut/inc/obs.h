#ifndef OBS_H
#define OBS_H

//-------------------- static -------------------------------------------------
class SubManager {
  public:
    static void addHandler(int i, void (*ptr)()) { fptr[i] = ptr; }
    static void call(int i) { fptr[i](); }

  private:
    static void (*fptr[10])();
};

template <int i, typename... Subs>
class Obs {
  public:
    Obs() { SubManager::addHandler(i, handler); }

  private:
    static void handler() { (Subs::run(), ...); }
};

//-------------------- dinamyc ------------------------------------------------
class SubManVirt {
  public:
    static void addHandler(int i, void (*ptr)()) { fPtr[i] = ptr; }
    static void call(int i) { fPtr[i](); }
  private:
    static void (*fPtr[10])();
};

class ObjVirt {
  public:
    virtual void run() = 0;
};

class ObsVirt {
  public:
    ObsVirt(int i) { SubManVirt::addHandler(i, handler); }
    static void addObj(ObjVirt* obj) {
        for (int i = 0; i < 2; i++) {
            if (!virtClasses[i]) {
                virtClasses[i] = obj;
                return;
            }
        }
    }
    static void handler() {
        for (int i = 0; i < 2; i++) {
            if (virtClasses[i]) {
                virtClasses[i]->run();
            }
        }
    }
    static ObjVirt* virtClasses[2];
};

#endif // OBS_H
