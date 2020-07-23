# Command Line Tools

This repo is a collection of CLI apps, scripts, etc. Mostly built with C++.

- Password Manager: CSV file management encrypted with B64.
- Lookup: Search the internet in the terminal.

# Password Manager

- Main File: password.cpp
- Encryption based on Base64 and Vigenere cipher.
- Compatibility with Linux/Unix and MacOS.
- Store passwords in a local csv file.
- Create your own csv file or use `init` to create one with proper format.
- Format for csv file: `password` uses `csvparser.h` to read the csv file. File must have three (3) headers in order: **Usernames,Passwords,Etc**

## Usage:

Read from a csv file: `./app r`

```sh
Usernames in current CSV:
John Doe
Retrieving data from u/ |
```

Write a new entry: `./app w`

```sh
Write Mode:
Info:
Username: |
```

Edit or delete an entry: `./app e`

```sh
John Doe
Tim Apple
Edit u/ |
```

How-to page: `./app`

By default, your csv file shoud be named 'passwords.csv'. To change this and use any filename, edit line 4 of 'passwords.cpp'. Then compile with gcc or clang with -std=c++11 or up.

# Lookup

- Main File: lookup.cpp
- Lookup takes all command line arguments as query for web searching.
- Compatibility with Linux/Unix and MacOS.

### If installed, these flags will open specific browsers:

- `-g`: opens with Google Chrome
- `-f`: opens with Firefox
- `-s`: opens with Safari
- `i`: opens with IE
- `-help`: displays how-to page
- `-w`: for entering an absolute URL

## Usage:

- Searches 'how many ounces in a cup' in your default browser: `./lookup How many ounces in a cup`
- Searches using Google Chrome (if installed): `./lookup -g how to use git`
- Bring up how-to page: `./lookup -help`

### Is that it?

Fow now, yes. Will update this every now and then. :-)

### People

- Thanks to github/philipperemy, for b64 and vignere cipher,
- And to github/d99kris for rapidcsv

### Todos

- Write MORE Tests
- Add more CLI tools

## License

BSD 3 Clause

Last updated: Jul 2020
