#include <iostream>
#include "csvparser.h"

const char *CURRENTFILE = "passwords.csv"; // PATH to store password in .csv

/**
 * @param argc If equal to 1, will bring up help.txt.
 *             If equal to 2, will choose which flag is being used.
 *             If equal to 3, will use argv[2] as the PUBLIC KEY.
 */
int main(int argc, char **argv)
{
    std::string key = "PUBLICKEY"; // Default key, EDITABLE
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
        if (argc > 2 && strcmp(argv[2], "") != 0)
        {
            key = argv[2];
            std::cout << "NOTE: A custom key is being used: " + key << std::endl;
        }
        if (flags.find('r') != std::string::npos)
        {
            readfl(CURRENTFILE, key);
        }
        else if (flags.find('w') != std::string::npos)
        {
            writefl(CURRENTFILE, key);
        }
        else if (flags.find('e') != std::string::npos)
        {
            editfl(CURRENTFILE, key);
        }
        else
        {
            std::cout << "unknown flag" << std::endl;
        }
    }
    return 0;
}