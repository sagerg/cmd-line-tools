#include <iostream>
#include <string>
#include <fstream>

void writefl(const char *filename)
{
    std::ofstream file;
    std::string username, password, etc;
    file.open(filename, std::fstream::out | std::fstream::app);
    std::cout << "Info:" << std::endl;
    try
    {
        std::cout << "Username: ";
        std::getline(std::cin, username);
        std::cout << "Password: ";
        std::getline(std::cin, password);
        std::cout << "Etc: ";
        std::getline(std::cin, etc);
    }
    catch (const std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
        return;
    }
    file << username + "," + password + "," + etc + "\n";
    file.close();
}

void test()
{
    const char *FILENAME = "test.csv";
    writefl(FILENAME);
}

int main()
{
    unsigned int rv = 0;
    try
    {
        test();
    }
    catch (const std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
        rv = 1;
    }
    return rv;
}