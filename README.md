# cmd-line-tools
Cmd line tools for productivity.
Compile the program to run (using make or gcc/g++ in linux / macOS).<br/><br/>
### 'password.cpp'
Stores password in a file.\
Passwords written to file will be encrypted.\
File path: `home directory/passwords`
To run: `./password`
A menu numbered 1 to 4 will be displayed in terminal.<br/><br/>
### 'lookup.cpp'
Quick search from the terminal to a browser.
To run:
```
./lookup <optional: -browser_flag> <optional specifier: '-w'> <optional: search query or wesbite>
```
Examples:<br/><br/>
`./lookup -g how to use git` opens Google Chrome and searches "how to use git".\
`./lookup -s -w www.github.com` opens Safari and goes directly to the Github website.\
`./lookup what is valgrind` opens default browser and searches "what is valgrind".\
`./lookup -help` brings up all the flags that can be used with the program.\
and `./lookup` just opens "google.com".<br/><br/><br/>
| Flags         | Meaning       |
| ------------- |:-------------:|
| -g            | Google Chrome |
| -f            | Firefox       |
| -s            | Safari        |
| -i            | Internet Explorer |
| -help         | List of flags |
| -w            | Site specifier|\
`./lookup -help` has all the flags for specific browsers.<br/><br/>
### 'watch.cpp'
Quick link to YouTube search.
To run:
```
./watch <optional: search query>
```
Example: `./watch lo fi` will pull up YouTube with query "lo+fi".<br/><br/><br/>
Any feedback is greatly appreciated!
