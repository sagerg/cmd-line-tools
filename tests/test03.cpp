#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include "../rapidcsv/rapidcsv.h"

const unsigned int MAXCOL = 3;
const char *COL1 = "Usernames";
const char *COL2 = "Passwords";
const char *COL3 = "Etc";

void editfl(const char *filename)
{
    std::ofstream file, tmp;
    std::string username;
    std::vector<std::string> usernames, passwords, etc;
    std::string entry[MAXCOL];
    try
    {
        rapidcsv::Document doc(filename);
        usernames = doc.GetColumn<std::string>(COL1);
        passwords = doc.GetColumn<std::string>(COL2);
        etc = doc.GetColumn<std::string>(COL3);
        file.open(filename);
    }
    catch (const std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
        return;
    }
    for (std::string u : usernames)
    {
        std::cout << u << std::endl;
    }
    std::cout << "Edit u/";
    std::getline(std::cin, username);
    if (std::find(usernames.begin(), usernames.end(), username) == usernames.end())
    {
        std::cout << "Unable to locate " + username + "in FILE: " + filename << std::endl;
        return;
    }
    for (unsigned i = 0; i < usernames.size(); ++i)
    {
        if (username == usernames.at(i))
        {
            std::cout << "New Info:" << std::endl;
            std::cout << "Username: ";
            std::getline(std::cin, entry[0]);
            if (entry[0] == "delete()" || entry[0] == "erase()")
            {
                // DELETE VECTOR ELEMENT FOR ALL VECTORS
                usernames.erase(usernames.begin() + i);
                passwords.erase(passwords.begin() + i);
                etc.erase(etc.begin() + i);
            }
            else
            {
                while (std::find(usernames.begin(), usernames.end(), entry[0]) != usernames.end())
                {
                    std::cout << "Username '" + entry[0] + "' already exists." << std::endl;
                    std::cout << "Enter another username or quit()" << std::endl;
                    std::cout << "Username: ";
                    std::getline(std::cin, entry[0]);
                }
                if (username == "quit()")
                {
                    return;
                }
                std::cout << "Password: ";
                std::getline(std::cin, entry[1]);
                std::cout << "Etc: ";
                std::getline(std::cin, entry[2]);
                usernames.at(i) = entry[0];
                passwords.at(i) = entry[1];
                etc.at(i) = entry[2];
            }
            break;
        }
    }
    file.close();
    tmp.open("tmp.csv");
    tmp << std::string(COL1) + "," + COL2 + "," + COL3 + "\n";
    for (unsigned i = 0; i < usernames.size(); ++i)
    {
        tmp << usernames.at(i) + "," + passwords.at(i) + "," + etc.at(i) + "\n";
    }
    tmp.close();
    remove(filename);
    rename("tmp.csv", filename);
}

void test()
{
    const char *FILENAME = "test.csv";
    editfl(FILENAME);
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