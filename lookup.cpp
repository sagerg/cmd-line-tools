#include <string>
#include <iostream>
#include <unordered_map>

int isInMap(std::unordered_map<std::string, std::string> m, std::string key);
void displayHelp();

int main(int argc, char **argv)
{
    // Flags for program
    const std::unordered_map<std::string, std::string> FLAGS{
        {"-g", " -a \"Google Chrome\" "},
        {"-f", " -a \"Firefox\" "},
        {"-s", " -a \"Safari\" "},
        {"-i", " -a \"Internet Explorer\" "},
        {"-w", ""},
        {"-help", ""},
    };
    std::string url = "open";
    std::string s = "";
    std::string q = " https://www.google.com/search?q=";
    int wFlagSet = 0;
    int hasQuery = 0;
    if (argc > 1)
    {
        for (int i = 1; i < argc; ++i)
        {
            if (isInMap(FLAGS, argv[i]))
            {
                if (i < 3 && strcmp(argv[i], "-w") == 0)
                {
                    s += " https://";
                    wFlagSet = 1;
                }
                else if (i < 2 && strcmp(argv[i], "-help") == 0)
                {
                    break;
                }
                else if (!wFlagSet)
                {
                    s += FLAGS.at(argv[i]);
                }
            }
            else if (wFlagSet)
            {
                s += argv[i];
            }
            else
            {
                q += argv[i] + std::string("+");
                hasQuery = 1;
            }
        }
        url.append(s);
        if (hasQuery)
        {
            url.append(q);
        }
    }
    else
    {
        url = "open https://www.google.com/";
    }
    if (argc > 1 && strcmp(argv[1], "-help") == 0)
        displayHelp();
    else
        system(url.c_str());
}

int isInMap(std::unordered_map<std::string, std::string> m, std::string key)
{
    // Key is not present
    if (m.find(key) == m.end())
        return 0;
    return 1;
}

void displayHelp()
{
    std::cout << "\n\n";
    for (int i = 0; i < 15; i++)
        std::cout << "- -";
    std::cout << "\n";
    std::cout << "Usable Flags:\n";
    std::cout << "'-g': Google Chrome\n'-f': Firefox\n'-s': Safari\n'-i': IE\n'-w': For specific websites\n'-help': man page";
    std::cout << "\n";
    for (int i = 0; i < 15; i++)
        std::cout << "- -";
    std::cout << "\n\n";
}