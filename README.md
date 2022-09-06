# **Shell Assignment**

**Goal:** The purpose is to construct a user-defined interactive shell application capable of creating and managing new processes.
The shell should be capable of launching a process from a system programme such as emacs, gedit, or any user-defined executable. The shell is built to meet a variety of criteria and requirements.

-----

## **File Structure:**

1. `headers.h`: It includes library calls, global variable and structure declarations, and fixed size containers. This file is used by other files and stores their function declarations.
2. `main.c`: Declares the initialization conditions for the entire terminal. Initiates the home state and accepts input.
3. `utility.c`:File containing routines for altering input format, tokenizing input arguments depending on spaces, and deleting excess spaces from input.
4. `prompt.c`: 

