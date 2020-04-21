#include <iostream>
#include <string>
#include <fstream>

const std::string HOME = getenv("HOME");
const std::string PATH = HOME + "/Documents/passwords.txt";
const std::string DEF_PASS = "password"; // <-- lol

//I/O BUFFER FOR READ/WRITE
struct Record
{
  std::string description;
  std::string name;
  std::string password;
  // bool isDeleted // <-- TODO
};

void addPass(std::fstream &);
void viewPass(std::fstream &);
void editPass(std::fstream &);
std::string encrypt(std::string, std::string const &);
std::string decrypt(std::string const &, std::string const &);

int main()
{
  using namespace std;

  string pass;
  fstream inFile;
  int choice;

  //LOG IN
  cout << "password: ";
  getline(cin, pass);
  while (pass != DEF_PASS)
  {
    cout << "password: ";
    getline(cin, pass);
  }

  //MENU
  do
  {
    cout << "\n1. Add Password\n";
    cout << "2. View Passwords\n";
    cout << "3. Change Existing Password\n";
    cout << "4. Quit\n\n";
    do
    {
      cout << "> ";
      cin >> choice;
      while (cin.fail()) //catch cin fail
      {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "> ";
        cin >> choice;
      }
    } while (choice < 1 || choice > 4);
    switch (choice)
    {
    case 1:
      addPass(inFile);
      break;
    case 2:
      viewPass(inFile);
      break;
    case 3:
      editPass(inFile);
    }
  } while (choice != 4);
  return 0;
}

//TODO DELETE FUNCTION
//TODO SEARCH FUNCTION

//ADD PASSWORD TO END OF FILE
void addPass(std::fstream &inFile)
{
  using namespace std;

  //OPEN FILE
  inFile.open(PATH, ios::binary | ios::app | ios::out);
  Record r; //struct as input buffer

  cin.ignore(256, '\n');
  cin.clear();

  //WRITE TO STRUCT
  cout << "\nDescription: ";
  getline(cin, r.description);
  cout << "Username: ";
  getline(cin, r.name);
  cout << "Password: ";
  getline(cin, r.password);
  r.password = encrypt(r.password, r.name); //encrypt pass

  //WRITE TO FILE
  inFile.write(reinterpret_cast<char *>(&r), sizeof(r));
  inFile.close();
}

//VIEW ALL RECORDS
void viewPass(std::fstream &inFile)
{
  using namespace std;

  //OPEN FILE
  inFile.open(PATH, ios::binary | ios::in);
  Record r;     //struct as input buffer
  Record check; //storage for checking EOF
  int record;   //storage for individual record

  cin.ignore(256, '\n');
  cin.clear();

  cout << "\nDATA:\n---------------------------------\n";
  for (int i = 0; inFile.read(reinterpret_cast<char *>(&check), sizeof(check)); i++)
  {
    inFile.seekg((i * sizeof(Record)), ios::beg); //move cursor to each record in file
    inFile.read(reinterpret_cast<char *>(&r), sizeof(r));
    cout << "RECORD " << i + 1 << "\n";
    cout << "\nDescription: " + r.description;
    cout << "\n---------------------------------\n";
  }

  //PICK RECORD TO VIEW
  cout << "\nRecord: ";
  cin >> record;

  while (cin.fail()) //catch cin fail
  {
    cin.clear();
    cin.ignore(256, '\n');
    cout << "Record: ";
    cin >> record;
  }

  //DISPLAY RECORD
  if (record >= 1)
  {
    record--;
    //set eofbit to 1
    //bc eofbit was 0 from reading file til EOF
    inFile.clear();
    //move cursor by record
    inFile.seekg((record * sizeof(Record)), ios::beg);
    //read data in that part of the file
    inFile.read(reinterpret_cast<char *>(&r), sizeof(r));
    cout << "\n//////////////////////////////////////\n";
    cout << "\nDescription: " + r.description;
    cout << "\nUsername: " + r.name;
    cout << "\nPassword: " + decrypt(r.password, r.name); //decrypt pass
    cout << "\n\n//////////////////////////////////////\n";
  }
  inFile.close();
}

//EDIT RECORD BY NUMBER
void editPass(std::fstream &inFile)
{
  using namespace std;

  //OPEN FILE
  inFile.open(PATH, ios::binary | ios::in | ios::ate | ios::out);
  Record r;   //struct as input buffer
  int record; //stores record number

  //VIEW RECORD
  cout << "\nRecord Number: ";
  cin >> record;

  while (cin.fail()) //catch cin fail
  {
    cin.clear();
    cin.ignore(256, '\n');
    cout << "Record Number: ";
    cin >> record;
  }

  if (record >= 1)
  {
    record--;
    inFile.seekg((record * sizeof(Record)), ios::beg);    //move cursor to record to be displayed
    inFile.read(reinterpret_cast<char *>(&r), sizeof(r)); //read from file
    cout << "\nCurrent Data:\n";
    cout << "Description: " << r.description << "\n";
    cout << "Username: " << r.name << "\n";
    cout << "Password: " << decrypt(r.password, r.name) << "\n"; //decrypt pass

    //EDIT DATA
    cin.ignore(256, '\n');
    cin.clear();

    cout << "\nEdit Data:\nDescription: ";
    getline(cin, r.description);
    cout << "Username: ";
    getline(cin, r.name);
    cout << "New Password: ";
    getline(cin, r.password);
    r.password = encrypt(r.password, r.name);              //encrypt pass
    inFile.seekp((record * sizeof(Record)), ios::beg);     //move cursor to record to be edited
    inFile.write(reinterpret_cast<char *>(&r), sizeof(r)); //write edits to binary file in correct position
  }
  inFile.close();
}

// key is now const&
std::string encrypt(std::string msg, std::string const &key)
{
  // Side effects if the following is not written:
  // In my case, division by 0.
  // In the other case, stuck in an infinite loop.
  if (!key.size())
    return msg;

  for (std::string::size_type i = 0; i < msg.size(); ++i)
    msg[i] ^= key[i % key.size()];
  return msg;
}

// Rewritten to use const& on both parameters
std::string decrypt(std::string const &msg, std::string const &key)
{
  return encrypt(msg, key); // lol
}