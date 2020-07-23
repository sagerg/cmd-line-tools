#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>
#include "../rapidcsv/rapidcsv.h"

const char *CURRENTFILE = "passwords.csv";

const unsigned int MAXCOL = 3;
const char *COL1 = "Usernames";
const char *COL2 = "Passwords";
const char *COL3 = "Etc";

void readfl(const char *filename);
void writefl(const char *filename);
void editfl(const char *filename);

int main(int argc, char **argv)
{
    std::string flags;
    if (argc == 1)
    {
        std::string line;
        std::ifstream file;
        try
        {
            file.open("help.txt");
            while (std::getline(file, line))
            {
                std::cout << line << '\n';
            }
            file.close();
        }
        catch (const std::exception &ex)
        {
            std::cout << ex.what() << std::endl;
            return 1;
        }
    }
    else if (argc > 1)
    {
        flags = argv[1];
        if (flags.find('r') != std::string::npos)
        {
            readfl(CURRENTFILE);
        }
        else if (flags.find('w') != std::string::npos)
        {
            writefl(CURRENTFILE);
        }
        else if (flags.find('e') != std::string::npos)
        {
            editfl(CURRENTFILE);
        }
        else
        {
            std::cout << "unknown flag" << std::endl;
        }
    }
    return 0;
}

void readfl(const char *filename)
{
    std::cout << "Reading from file..." << std::endl;
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
        std::cout << "No csv file with the name " + std::string(CURRENTFILE) + " found in the directory." << std::endl;
        return;
    }
}

void writefl(const char *filename)
{
    std::cout << "Write Mode:" << std::endl;
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
        std::cout << "No csv file with the name " + std::string(CURRENTFILE) + " found in the directory." << std::endl;
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

void editfl(const char *filename)
{
    std::cout << "Overwrite Mode:" << std::endl;
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
        std::cout << "No csv file with the name " + std::string(CURRENTFILE) + " found in the directory." << std::endl;
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
    try
    {
        remove(filename);
        rename("tmp.csv", filename);
    }
    catch (const std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
        return;
    }
}