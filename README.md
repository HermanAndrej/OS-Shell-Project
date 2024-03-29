# IT 204 - Operating Systems Course Shell Project

## Group Members:
1. Arman Ćulah
2. Andrej Herman

## Submission Directory Listing:
- shell.c
- README.md
- Additional IDE files

## Outline of Assignment Implementation:
- Implemented a command-line shell in C.
- Included commands: wc, grep, cmatrix, df, tiger, pokemon, thirsty, pwgen, help, and ls.
- Handled input/output redirection using freopen.
- Implemented functionalities for each command, including ASCII art display.
- Utilized fork and exec to execute commands in child processes.
- Implemented parsing of command-line arguments.
- Displayed appropriate error messages for invalid commands or file operations.
- Made additional implementation for Windows systems.

## Instructions for Compiling Programs/Scripts:
1. Compile the `main.c` file using a C compiler.
   - Example (GCC): `gcc shell.c -o myshell`
2. Run the compiled executable.
   - Example: `./myshell`

## Challenges Encountered:
- Handling input/output redirection required careful manipulation of file descriptors and buffering.
- Ensuring proper parsing of command-line arguments and handling different command options efficiently.
- Handling errors and edge cases gracefully to prevent crashes or unexpected behavior.
- Integrating ASCII art display within the shell while maintaining readability and usability.
- Testing the shell thoroughly to identify and fix bugs or unexpected behavior.
- Collaborating effectively within the group to coordinate tasks, share knowledge, and resolve conflicts or discrepancies.

## Sources/Tutorials Used:
- stackoverflow.com
- github.com
- youtube.com
- LMS materials

## Implementation Issues:
- Output redirection doesn't behave as intended, the functionality works, but after performing the output redirection shell stops asking for input.
