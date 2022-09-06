# **Shell Assignment**

[![forthebadge](https://forthebadge.com/images/badges/made-with-c.svg)](https://forthebadge.com)
[![forthebadge](https://forthebadge.com/images/badges/open-source.svg)](https://forthebadge.com)

**Goal:** The purpose is to construct a user-defined interactive shell application capable of creating and managing new processes.
The shell should be capable of launching a process from a system programme such as emacs, gedit, or any user-defined executable. The shell is built to meet a variety of criteria and requirements.

-----

## **File Structure:**

1. `headers.h`: It includes library calls, global variable and structure declarations, and fixed size containers. This file is used by other files and stores their function declarations.
2. `main.c`: Declares the initialization conditions for the entire terminal. Initiates the home state and accepts input.
3. `utility.c`:File containing routines for altering input format, tokenizing input arguments depending on spaces, and deleting excess spaces from input.
4. `prompt.c`: Displays the prompt in the terminal window in desired `<username@system_name:curr_dir>` format.
5. `cd.c`: Code for manipulating terminal directories.
6. `echo.c`: Code for printing arguments from the given input to the terminal in the appropriate format.
7. `ls.c`: All files and folders are displayed based on flags and target directories. Depending on the path type, displays output in colour as well.
8. `pinfo.c`: The shell program's process-related information is printed in the appropriate output format. For output, the files `/proc/%d/stat` and `/proc/%d/exe` are used.
9. `discover.c`: Custom discover command that mimics the fundamentals of the find command The command searches a directory structure for files. Contained code that handles flags and target directories that function recursively and print the desired output.
10. `history.c`: Implements a 'history' command that is equivalent to the LINUX history command. The history.txt file is used to save and load commands.
11. `history.txt`: Text file that stores the number of input arguments as well as the arguments themselves.
----

## **Execution:**

```c++
$ make //Builds the code by itself
$ ./a.out //To start running the terminal (displays the terminal prompt after successful build.)
```
-----

