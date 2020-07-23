#include <iostream>
#include <fstream>
#include "../easy-encryption/encrypt.h"

const char *FILENAME = "passwords.csv";

int main()
{
    std::string k = "SAMPLEKEY";
    std::string password = "password";
    std::ofstream file(FILENAME);
    file << "Usernames,Passwords,Etc\n";
    file << "John Doe," + encrypt(password, k) + ",NULL\n";
    file.close();
    return 0;
}