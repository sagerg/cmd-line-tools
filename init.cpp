#include <iostream>
#include <fstream>
#include "easy-encryption/encrypt.h"

const char *FILENAME = "passwords.csv";

int main()
{
    std::string k = "PUBLICKEY";
    std::string password = "password1XYZ";
    std::ofstream file(FILENAME);
    file << "Profiles,Passwords,Usernames\n";
    file << "GitHub," + encrypt(password, k) + ",John Doe\n";
    file.close();
    return 0;
}