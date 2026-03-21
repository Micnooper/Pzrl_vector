#include <iostream>
#include <cstdlib>
#include <ctime> 

int main()
{   
    double* data = new double[5];
    srand(time(NULL));
    for (size_t i = 0; i < 5; ++i)
    {
        data[i] = rand() % 20;
    }
    for (size_t i = 0; i < 5; ++i)
    {
        data[i] = data[i+1];
    }
    for (size_t i = 0; i < 5; ++i)
    {
        std::cout << data[i] << " ";
    }
    delete[] data;
    std::cout << std::endl;
    return 0;
}