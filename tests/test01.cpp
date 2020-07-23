#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../rapidcsv/rapidcsv.h"

void readfl(const char *filename)
{
    std::vector<std::string> v;
    std::string username;
    try
    {
        rapidcsv::Document doc(filename);
        v = doc.GetColumn<std::string>("Usernames");
        std::cout << "Usernames in current CSV:" << std::endl;
        for (std::string u : v)
        {
            std::cout << u << "\n";
        }
        std::cout << "Retrieving data from u/";
        std::getline(std::cin, username);
        rapidcsv::Document docWithRowH(filename, rapidcsv::LabelParams(0, 0));
        v = docWithRowH.GetRow<std::string>(username);
        std::cout << "Details found in u/" + username << std::endl;
        for (std::string info : v)
        {
            std::cout << info << "\n";
        }
    }
    catch (const std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
        return;
    }
}

void test()
{
    const char *FILENAME = "test.csv";
    readfl(FILENAME);
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