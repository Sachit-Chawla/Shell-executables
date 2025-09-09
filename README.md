Simple Shell with Command History

Table of Contents

Overview
Features
Getting Started
Usage
Command History
Contributing
License
Overview

This project implements a simple shell program that allows users to execute commands and maintain a history of recently executed commands. The shell supports basic features like command execution, command history, and retrieval of recent commands using specific syntax.

Features

Execute commands in a child process.
Maintain a history of the last 10 commands executed.
Retrieve and execute the most recent command using !!.
Retrieve and execute any command from the history using !N, where N is the command number.
Display the command history with process IDs.
Getting Started

To build and run the shell, follow these steps:

Compile the source code: Use a C compiler like gcc to compile the code:
gcc main.c

Run the shell: Start the shell by executing:
./a.out

Usage
Once the shell is running, you can enter commands just like you would in a normal terminal. The shell will wait for your input, execute the command, and display the output.

Command Examples
To execute a command:
ls -l
To see the command history:
history
To execute the most recent command:
!!
To execute a specific command from history (for example, the 3rd command):
!3

Command History
The shell keeps track of the last 10 commands executed. You can view the command history by typing history. The history will show the command ID, process ID, and the command itself.

Notes
The shell does not add the command !! to the history when executed.
If there are no commands in the history, attempting to execute !! or !N will display a message indicating that no command is available.
