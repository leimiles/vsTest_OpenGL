#include <iostream>
#include <stdarg.h>

// if there's no number of args, 
void fun01(int count, ...)
{
    va_list elements_Pointer;
    va_start(elements_Pointer, count);
    const char* arg1 = va_arg(elements_Pointer, const char*);
    const char* arg2 = va_arg(elements_Pointer, const char*);
    std::cout << arg1 << std::endl;
    std::cout << arg2 << std::endl;
}

void fun02(const char* name01, ...)
{
    va_list elements_Pointer;
    va_start(elements_Pointer, name01);
    const char* arg1 = va_arg(elements_Pointer, const char*);
    const char* arg2 = va_arg(elements_Pointer, const char*);
    std::cout << arg1 << std::endl;
    std::cout << arg2 << std::endl;
    va_end(elements_Pointer);
}

template<typename T>
void fun03(T t)
{
    std::cout << t << std::endl;

}

void fun04(int i = 10)
{
    std::cout << i << std::endl;
}

void (*pointer)(int);

int main()
{
    pointer = fun04;
    pointer(12);
}




