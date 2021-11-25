#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

const char* fun()
{
    std::string str = "waaaaaaaaaaaaa";
    return str.c_str();
}

int main()
{
    const char* cs1 = fun();
    const char* cs2 = cs1;
    cout << cs2 << endl;
    cout << cs2 << endl;
    cout << cs1 << endl;
    cout << cs1 << endl;
    cout << cs2 << endl;

    cout << "-- OpenGL and Miles --" << endl;
    return 0;
}


