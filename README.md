# Command Line Tools

This repo is a collection of CLI apps, scripts, etc. Mostly built with C++.

- Password Manager: CSV file manager encrypted with B64 & Vigenere cipher.
- LOOKUP: Search the internet in the terminal.

# Password Manager

- Main File: PASS.cpp
- Encryption based on Base64 and Vigenere cipher.
- Compatibility with Linux/Unix and MacOS and uses C++11.
- Use `init.cpp` to create a CSV file locally with formatted headers.
- CSV should have three (3) headers in order: **Profiles,Passwords,Usernames**.
- If you're going to make your own file, leave a newline after the headers.

## Usage

cd to `cmd-line-tools` directory and compile using g++ or a Makefile from there.
Move the binary file or executable to any directory afterwards.
Make sure `passwords.csv` is in the same directory as the executable.

```sh
cd cmd-line-tools/src
make PASS
mv PASS ../FOO_DIRECTORY/PASS
```

### Read Mode

PASS will print all profiles to the terminal. Pick one from the list by typing after 'profile/'.

```sh
./PASS r
Profiles in current CSV:
GitHub
Twitter
Facebook
Retrieving data from profile/ **GitHub**
```

### Write Mode

Add a profile in Write Mode. You can 'quit()' to exit this mode.

```sh
./PASS w
Write Mode:
Info:
Profile: **Twitter**
Password: **xyz**
Username: **John Doe**
```

### Edit Mode:

PASS will print all profiles to the terminal. Pick one to edit from the list by typing after 'profile/'.
The options 'delete()' or 'erase()' is available if you'd like to delete a profile.

```sh
./PASS e
GitHub
Twitter
Facebook
Edit profile/ **Twitter**
```

### Man Page

`help.txt` must be in the same directory as the executable for it to display anything.

```sh
./PASS
FOO HELP PAGE
```

### Public Key

By default, the public key being used for encryption is 'PUBLICKEY' but you can enter your own **custom public key** each time you enter a mode or write an entry. Just remember what it was beforehand.

```sh
./PASS [mode] [CUSTOM PUBLIC KEY]
```

### Additonal Notes

By default, your CSV file shoud be named 'passwords.csv'.
To change this and use any CSV file, edit line 4 of 'passwords.cpp'.
Compile with C++11 or up.

# Quick Lookup

- Main File: LOOK.cpp
- Lookup takes all command line arguments as query for web searching.
- Compatibility with Linux/Unix and MacOS.
- Compile with g++ and C++11 or up.

```sh
cd cmd-line-tools
g++ -std=c++11 -o LOOK LOOK.cpp
```

### If installed, these flags will open specific browsers:

- `-g` - Opens with Google Chrome
- `-f` - Opens with Firefox
- `-s` - Opens with Safari
- `-i` - Opens with IE

### Other options

- `-help` - Displays how-to page
- `-w` - Enter an absolute URL

## Usage:

- `./LOOK How many ounces in a cup` - Searches 'how many ounces in a cup' in your default browser.
- `./LOOK -g how to use git` - Searches 'how to use git' using Google Chrome (if installed).
- `./LOOK -help` - Bring up how-to page.

### Is that it?

Fow now, yes. Will update this every now and then. :-)

### People

- Thanks to github/philipperemy, for b64 and vignere cipher,
- And to github/d99kris for rapidcsv

### Todos

- Write MORE Tests
- Add more CLI tools

## License

BSD 3-Clause

Last updated: Jul 2020
