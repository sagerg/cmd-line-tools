// Searches YouTube in default browser

#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    std::string url = "open https://www.youtube.com/";
    std::string s = "results?search_query=";
    if (argc > 0)
    {
        // Append all string arguments to url
        for (int i = 1; i < argc; ++i)
            s += argv[i] + std::string("+");
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
        std::cout << "man:\n";
        std::cout << "'./watch <search query>' Makes a youtube search query from the terminal in your default browser.\n'-help': man page";
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