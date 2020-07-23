#include <iostream>
#include "csvparser.h"

const char *CURRENTFILE = "passwords.csv";

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