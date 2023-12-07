# Simple Shell

## Description

This is a simple C shell program that reads user input, tokenizes it, and executes the commands. The shell is designed to be interactive and capable of executing commands from the system's PATH.

## Table of Contents

- [Usage](#usage)
- [Functions](#functions)
- [License](#license)

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

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.

