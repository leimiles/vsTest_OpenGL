#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
    std::ifstream file;
    file.exceptions(std::fstream::badbit | std::fstream::failbit);
    file.open("test1.txt");
    if (file.is_open())
    {
        std::cout << "working!" << std::endl;
    }
    else
    {
        std::cout << "not working!" << std::endl;
    }
    file.close();

    cout << "OpenGL and Miles" << endl;
    return 0;
}
