#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>
#include "rapidcsv/rapidcsv.h"
#include "easy-encryption/encrypt.h"

const unsigned int MAXCOL = 3;
const char *COL1 = "Profiles";
const char *COL2 = "Passwords";
const char *COL3 = "Usernames";

/**
 * @brief Reads from 'passwords.csv' using rapidcsv lib.
 * 
 * @param filename File path to 'passwords.csv'.
 * 
 * @param key Public key used for encryption. Uses easy-encryption lib.
 */
void readfl(const char *filename, std::string key)
{
    std::cout << "Reading from file..." << std::endl;
    std::vector<std::string> v;
    std::string profile;
    try
    {
        rapidcsv::Document doc(filename);
        v = doc.GetColumn<std::string>(COL1);
        std::cout << "Profiles in FILE: " + std::string(filename) << std::endl;
        for (std::string p : v)
        {
            std::cout << p << "\n";
        }
        std::cout << "Retrieving data from profile/";
        std::getline(std::cin, profile);
        rapidcsv::Document docWithRowHeader(filename, rapidcsv::LabelParams(0, 0));
        v = docWithRowHeader.GetRow<std::string>(profile);
        std::cout << "Info on profile/" + profile << std::endl;
        std::cout << "Password: " << decrypt(v.at(0), key) << "\n";
        std::cout << "Username: " << v.at(1) << "\n";
    }
    catch (const std::ios_base::failure &ex)
    {
        std::cout << "No csv file with the name '" + std::string(filename) + "' found in the directory." << std::endl;
        return;
    }
    catch (const std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
        return;
    }
}

/**
 * @brief Writes to 'passwords.csv'.
 * 
 * @param filename File path to 'passwords.csv'.
 * 
 * @param key Public key used for encryption. Uses easy-encryption lib.
 */
void writefl(const char *filename, std::string key)
{
    std::cout << "Write Mode:" << std::endl;
    std::ofstream file;
    std::string profile, password, username;
    std::vector<std::string> v;
    try
    {
        rapidcsv::Document doc(filename);
        file.open(filename, std::fstream::out | std::fstream::app);
        v = doc.GetColumn<std::string>(COL1);
    }
    catch (const std::ios_base::failure &ex)
    {
        std::cout << "No csv file with the name '" + std::string(filename) + "' found in the directory." << std::endl;
        file.close();
        return;
    }
    catch (const std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
        file.close();
        return;
    }
    std::cout << "Enter 'quit()' to exit this mode." << std::endl;
    std::cout << "Profile: ";
    std::getline(std::cin, profile);
    while (std::find(v.begin(), v.end(), profile) != v.end())
    {
        std::cout << "Profile '" + profile + "' already exists." << std::endl;
        std::cout << "Enter another profile or 'quit()'" << std::endl;
        std::cout << "Profile: ";
        std::getline(std::cin, profile);
    }
    if (profile == "quit()")
    {
        file.close();
        return;
    }
    std::cout << "Password: ";
    std::getline(std::cin, password);
    std::cout << "Username: ";
    std::getline(std::cin, username);
    if (profile.empty())
    {
        profile = "NULL";
    }
    if (password.empty())
    {
        password = "NULL";
    }
    if (username.empty())
    {
        username = "NULL";
    }
    file << profile + "," + encrypt(password, key) + "," + username + "\n";
    file.close();
}

/**
 * @brief Reads and writes from/to 'passwords.csv' using rapidcsv lib.
 * 
 * @param filename File path to 'passwords.csv'.
 * 
 * @param key Public key used for encryption. Uses easy-encryption lib.
 */
void editfl(const char *filename, std::string key)
{
    std::cout << "Overwrite Mode:" << std::endl;
    std::ofstream file, tmp;
    std::string profile;
    std::vector<std::string> profiles, passwords, usernames;
    std::string entry[MAXCOL] = {"NULL"};
    try
    {
        rapidcsv::Document doc(filename);
        profiles = doc.GetColumn<std::string>(COL1);
        passwords = doc.GetColumn<std::string>(COL2);
        usernames = doc.GetColumn<std::string>(COL3);
        file.open(filename, std::fstream::out | std::fstream::app);
    }
    catch (const std::ios_base::failure &ex)
    {
        std::cout << "No csv file with the name '" + std::string(filename) + "' found in the directory." << std::endl;
        file.close();
        return;
    }
    catch (const std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
        file.close();
        return;
    }
    for (std::string p : profiles)
    {
        std::cout << p << std::endl;
    }
    std::cout << "Edit profile/";
    std::getline(std::cin, profile);
    if (std::find(profiles.begin(), profiles.end(), profile) == profiles.end())
    {
        std::cout << "Unable to locate " + profile + " in FILE: " + filename << std::endl;
        file.close();
        return;
    }
    for (unsigned i = 0; i < profiles.size(); ++i)
    {
        if (profile == profiles.at(i))
        {
            std::cout << "Enter 'delete()' or 'erase()' to remove a profile." << std::endl;
            std::cout << "New Profile: ";
            std::getline(std::cin, entry[0]);
            if (entry[0] == "delete()" || entry[0] == "erase()")
            {
                // Delete account
                profiles.erase(profiles.begin() + i);
                passwords.erase(passwords.begin() + i);
                usernames.erase(usernames.begin() + i);
                std::cout << "Deleting info associated with profile/" + profile << std::endl;
            }
            else
            {
                while (std::find(profiles.begin(), profiles.end(), entry[0]) != profiles.end())
                {
                    std::cout << "Profile '" + entry[0] + "' already exists." << std::endl;
                    std::cout << "Enter another profile or 'quit()'" << std::endl;
                    std::cout << "Profile: ";
                    std::getline(std::cin, entry[0]);
                }
                if (entry[0] == "quit()")
                {
                    file.close();
                    return;
                }
                std::cout << "Password: ";
                std::getline(std::cin, entry[1]);
                std::cout << "Username: ";
                std::getline(std::cin, entry[2]);
                if (entry[0].empty())
                {
                    entry[0] = "NULL";
                }
                if (entry[1].empty())
                {
                    entry[1] = "NULL";
                }
                if (entry[2].empty())
                {
                    entry[2] = "NULL";
                }
                profiles.at(i) = entry[0];
                passwords.at(i) = encrypt(entry[1], key);
                usernames.at(i) = entry[2];
            }
            break;
        }
    }
    file.close();
    tmp.open("tmp.csv");
    tmp << std::string(COL1) + "," + COL2 + "," + COL3 + "\n";
    for (unsigned i = 0; i < profiles.size(); ++i)
    {
        tmp << profiles.at(i) + "," + passwords.at(i) + "," + usernames.at(i) + "\n";
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

#endif // CSVPARSER_H