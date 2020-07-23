#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>
#include "../rapidcsv/rapidcsv.h"

const char *COL1 = "Usernames";
const char *COL2 = "Passwords";
const char *COL3 = "Etc";

void writefl(const char *filename)
{
    std::ofstream file;
    std::string username, password, etc;
    std::vector<std::string> v;
    try
    {
        rapidcsv::Document doc(filename);
        file.open(filename, std::fstream::out | std::fstream::app);
        v = doc.GetColumn<std::string>(COL1);
    }
    catch (const std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
        return;
    }
    std::cout << "Info:" << std::endl;
    std::cout << "Username: ";
    std::getline(std::cin, username);
    while (std::find(v.begin(), v.end(), username) != v.end())
    {
        std::cout << "Username '" + username + "' already exists." << std::endl;
        std::cout << "Enter another username or quit()" << std::endl;
        std::cout << "Username: ";
        std::getline(std::cin, username);
    }
    if (username == "quit()")
    {
        return;
    }
    std::cout << "Password: ";
    std::getline(std::cin, password);
    std::cout << "Etc: ";
    std::getline(std::cin, etc);
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