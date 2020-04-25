# cmd-line-tools

Cmd line tools for productivity.

> Compile the program to run (using make or gcc/g++ in linux / macOS).

### 'lookup'

Quick search from the terminal to a browser.

To run:

```
./lookup <optional: -browser_flag> <optional: '-w'> <optional: search query or wesbite>
```

Examples:\
`./lookup -g how to use git` opens Google Chrome and searches "how to use git".\
`./lookup -s -w www.github.com` open Safari and goes directly to the Github website.\
`./lookup what is valgrind` opens default browser and searches "what is valgrind".\
and `./lookup` just opens "google.com".

### 'watch'

Quick link to YouTube search.

To run:

```
./watch <optional: search query>
```

### 'password'

Stores password in a file.\
Passwords written to file will be encrypted.\
File path: (home director)/passwords\

To run: `./password`

Any feedback is greatly appreciated!
