# Simple Shell

## Description

This is a simple C shell program that reads user input, tokenizes it, and executes the commands. The shell is designed to be interactive and capable of executing commands from the system's PATH.

## Table of Contents

- [Usage](#usage)
- [Functions](#functions)
- [Expected Output](#output)

## Usage

To use this shell, run the compiled executable in your terminal: bash ./simple_shell

You will be presented with a prompt (`$: `). Enter your commands and press enter to execute them.

## Functions

This program consists of several functions:

- `read_line`: Reads a line of input from the user.
- `tokenize_line`: Tokenizes the input line into separate words.
- `get_path`: Retrieves the system's PATH.
- `search_in_path`: Searches for an executable in the system's PATH.
- `path_search`: Calls `get_path` and `search_in_path` to find and execute the command.

## Expected Output

The program starts by displaying a prompt (`$: `) in the terminal. The user can then enter a command and press enter to execute it. The shell will then tokenize the command, search for the executable in the system's PATH, and execute the command if it's found.

Here's an example of how the program might behave: $: ls

The `ls` command lists the files and directories in the current directory. The output might look something like this: bash file1 file2 file3 directory1 directory2

If the user enters a command that's not found in the system's PATH, the shell will display an error message: $: command_not_found

The output might look something like this: Command not found: command_not_found

The shell will continue to display the prompt and accept commands until it's terminated by the user.

