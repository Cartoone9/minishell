<div align="center">
  <img src="https://i.ibb.co/W4BbX6FL/Screenshot-from-2025-06-24-12-50-29.png" alt="Project score">
</div>

# minishell

 This is my Minishell: a small Bash-like shell written in C as part of the 42 common core. It parses and executes user commands, handles pipes and redirections, and manages signals and child processes with proper system calls.  
We had to rebuild key parts of a shell from scratch: quoting, environment variables, file descriptors, fork/exec logic, and more.  
It was a deep dive into Unix internals and low-level system programming. Everything from process creation to memory management was handled manually, using a range of standard and POSIX libraries (such as `unistd.h`, `fcntl.h`, `signal.h`, and `readline.h`) to interact with the system. Overall, this project gave me a much clearer understanding of what a shell actually does under the hood.  

## Usage

To compile the program, navigate to the project root and run:  
```bash
make
# or
make bonus
```

![Minishell compiling](https://i.ibb.co/Xkzj1bGC/compile-minishell.gif)  

Then you can start the program like this:  
```bash
./minishell
```

## Example

![Minishell demo](https://github.com/user-attachments/assets/56ccdaf8-9669-44b4-a6bc-3904160a811a)

## Features


## Note on Project State

All projects from my 42 cursus are preserved in their state immediately following their final evaluation. While they may contain mistakes or stylistic errors, I've chosen not to alter them. This approach provides a clear and authentic timeline of my progress and learning journey as a programmer.

## Known Issues & Fix Suggestions


## Credits

This project was developed in collaboration with another student, who contributed to the implementation of built-in commands, signal handling, and provided valuable debugging support.

## License

[MIT](https://choosealicense.com/licenses/mit/)  
