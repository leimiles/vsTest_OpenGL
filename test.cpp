#include <iostream>
using namespace std;
#include <stdarg.h>


void fun01(int count, ...)
{
    va_list elements_Pointer;
    va_start(elements_Pointer, count);
    const char* arg1 = va_arg(elements_Pointer, const char*);
    const char* arg2 = va_arg(elements_Pointer, const char*);
    std::cout << arg1 << std::endl;
    std::cout << arg2 << std::endl;
}


int main()
{

}




