#include <iostream>
#include <string>

int main(int ac, char **av)
{
    // argv[1] will be 'sample'
    std::string s;
    if (ac > 1)
        s = av[1];
    if (s.find('s') != std::string::npos)
        std::cout << "working" << std::endl;
    else
        std::cout << "not working" << std::endl;
    return 0;
}