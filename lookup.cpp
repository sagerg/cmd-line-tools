// Googles cmd line arguments
// e.g. ./goog Hello World!
// Flags: '-g':Google Chrome, '-f':Firefox, '-s':Safari, '-i':IE, '-w':specifier, '-help':legend
// e.g. ./goog -g -w www.github.com

#include <string>
#include <iostream>
#include <unordered_map>

int isInMap(std::unordered_map<std::string, std::string> m, std::string key);

int main(int argc, char **argv)
{
    // Flags for program
    const std::unordered_map<std::string, std::string> FLAGS{
        {"-g", " -a \"Google Chrome\" "},
        {"-f", " -a \"Firefox\" "},
        {"-s", " -a \"Safari\" "},
        {"-i", " -a \"Internet Explorer\" "},
        {"-w", " "},
        {"-help", " "},
    };
    int wSet = 0;
    std::string flag = "";
    std::string url = "open https://www.google.com/"; // Opens default browser
    if (argc > 2 && isInMap(FLAGS, argv[1]))          // Check if there are flags
    {
        flag = FLAGS.at(argv[1]);
        url = ("open") + flag;
        // Check if there is specifier
        if (strcmp(argv[1], "-w") == 0 || strcmp(argv[2], "-w") == 0)
        {
            std::string site = (argc == 3 ? argv[2] : argv[3]);
            url += std::string("https://") + site;
            wSet = 1; // If specifier is present, search directly
        }
    }
    if (argc > 1 && !wSet)
    {
        std::string s = "search?q=";
        // Append arguments to url
        for (int i = 1; i < argc; ++i)
        {
            if (!isInMap(FLAGS, argv[i]))
                s += argv[i] + std::string("+");
        }
        if (isInMap(FLAGS, argv[1]))
            url.append("https://www.google.com/");
        url.append(s);
    }
    // Display help
    if (argc > 1 && strcmp(argv[1], "-help") == 0)
    {
        std::cout << "\n\n";
        for (int i = 0; i < 15; i++)
            std::cout << "- -";
        std::cout << "\n";
        // --
        std::cout << "Usable Flags:\n";
        std::cout << "'-g': Google Chrome\n'-f': Firefox\n'-s': Safari\n'-i': IE\n'-w': For specific websites\n'-help': man page";
        // --
        std::cout << "\n";
        for (int i = 0; i < 15; i++)
            std::cout << "- -";
        std::cout << "\n\n";
    }
    else
        system(url.c_str());
    return 0;
}

// Check map for key
int isInMap(std::unordered_map<std::string, std::string> m, std::string key)
{
    // Key is not present
    if (m.find(key) == m.end())
        return 0;
    return 1; // Key is present
}