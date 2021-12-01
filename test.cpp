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

int main()
{
    fun02("wawa", "kobe", "deko");
    int i = 10;
    int b = 11;
    std::cout << (i = 0) << std::endl;

    /*
        while (0)
        {
            std::cout << "wazz" << std::endl;
        }
        */
}




