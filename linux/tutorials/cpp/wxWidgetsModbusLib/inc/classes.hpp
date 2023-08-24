#ifndef CLASSES_HPP_
#define CLASSES_HPP_

class InterruptManager
{
public:
    inline static void (*IsrVi[10])()={nullptr};
    static void AddHandler(void (*Fptr)(),int x)
    {
        IsrVi[x] = Fptr;        
    }
    static void call(int x){IsrVi[x]();}
};
//void (*InterruptManager::IsrVi[10])()= {nullptr};
class Interruptable
{
public:
    virtual ~Interruptable(){}
    virtual void run()=0;
};
template<int x>
class InterruptableClasses
{
public:
    static void setVector(){InterruptManager::AddHandler(InterruptHandler,x);}
    static void addClass(Interruptable* classs)
    {
        for(int i=0;i<10;i++)
        {
            if(arrClasses[i]==nullptr)
            {
                arrClasses[i]=classs;break;
            }
        }
    }
    static void InterruptHandler()
    {
        for(int i=0;i<10;i++)
        {
            if(arrClasses[i]!=nullptr)
            {
                arrClasses[i]->run();
            }
        }
    }
private:
    static Interruptable* arrClasses[10];
};
template<int x>
Interruptable* InterruptableClasses<x>::arrClasses[10]={nullptr};

class Adder: public Interruptable
{
public:
    void run()override
    {
        add();
    }
    void add(){if(&x!=nullptr){*x=*x+1;}}
    int* x=nullptr;
};
class Subber: public Interruptable
{
public:
    void run()override
    {
        sub();
    }
    void sub(){if(&x!=nullptr){*x=*x-10;}}
    int* x=nullptr;
};


#endif //CLASSES_HPP_