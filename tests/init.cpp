#include <iostream>
#include <fstream>

int main()
{
    const char *FILENAME = "test.csv";
    const unsigned int ROWSIZE = 5;
    std::string users[ROWSIZE] = {"John Doe", "Joe Apple", "Suzan Salo", "Joni Vien", "Apple Tim"};
    std::ofstream file(FILENAME);
    for (int i = 0; i < ROWSIZE; ++i)
    {
        if (!i)
        {
            file << "Usernames,Passwords,Etc\n";
        }
        std::string tmp = "";
        std::string etc = "";
        for (int j = 0; j < ROWSIZE; ++j)
        {
            tmp += 'a' + rand() % 26;
            etc += 'a' + rand() % 26;
        }
        file << users[i] + "," + tmp + "," + etc + "\n";
    }
    file.close();
    return 0;
}