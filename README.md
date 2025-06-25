   <div align="center">
  <img src="https://i.ibb.co/W4BbX6FL/Screenshot-from-2025-06-24-12-50-29.png" alt="Project score">
</div>

# minishell

 This is my Minishell project: a small Bash-like shell written in C as part of the 42 common core. It parses and executes user commands, handles pipes and redirections, and manages signals and child processes with proper system calls.  
We had to rebuild key parts of a shell from scratch: quoting, environment variables, file descriptors, fork/exec logic, and more.  
It was a deep dive into Unix internals and low-level system programming. Everything from process creation to memory management was handled manually, using a range of standard and POSIX libraries (such as `unistd.h`, `fcntl.h`, `signal.h`, and `readline.h`) to interact with the system. Overall, this project gave me a much clearer understanding of what a shell actually does under the hood.  

## Usage

To compile the program, navigate to the project root and run:  
```bash
make
# or
make bonus
```

![Minishell compiling](https://github.com/user-attachments/assets/e0f29a5f-1b22-4f1c-b402-055fd333b20f)  

Then you can start the program like this:  
```bash
./minishell
```

## Example

![Minishell demo](https://github.com/user-attachments/assets/56ccdaf8-9669-44b4-a6bc-3904160a811a)  

## Features

In the following examples I will try to present most of the features supported, but not everything is shown here.  

### Basic:  
![minishell_basic](https://github.com/user-attachments/assets/df54efc1-0609-4753-a9d2-1e9185492a45)  
![minishell_return_value](https://github.com/user-attachments/assets/a5463496-940b-4609-a2c3-a33e3f521b2b)  
![minishell_double_quote](https://github.com/user-attachments/assets/5fce475a-d2ae-4047-b4a6-df76d0b2e97c)  

### Empty:  
![minishell_empty](https://github.com/user-attachments/assets/ffb13913-a55f-4b87-845a-c43b83397dad)  

### Redirections:  
![minishell_redir](https://github.com/user-attachments/assets/e93ff3d6-a88f-4fb0-8271-b037b4379b56)  
![minishell_redir_2](https://github.com/user-attachments/assets/7f7b3178-2aaa-43a3-807c-691c8dc760eb)  
![minishell_redir_3](https://github.com/user-attachments/assets/02b314c2-539b-492b-9909-ec171540aba3)  

### Heredocs:  
![minishell_heredoc](https://github.com/user-attachments/assets/4257c447-f46a-44ef-8dda-7662f9a6d49a)  
![minishell_heredoc_pipe](https://github.com/user-attachments/assets/ddd9b0c5-cc7f-404e-afb8-ba112def9266)  

### Pipes:  
![minishell_pipe_1](https://github.com/user-attachments/assets/ebc7c9cb-6a78-465b-a41f-f7acaa22ed9a)  
![minishell_pipe_2](https://github.com/user-attachments/assets/25f270c8-6932-478a-a39c-1f4430907981)  
![minishell_pipe_end](https://github.com/user-attachments/assets/dcf19219-a10f-4e70-95eb-9868fce021dd)  

### Echo:  
![minishell_echo_1](https://github.com/user-attachments/assets/109d88ec-1cbc-4a6b-b7ab-8a8ce99b278b)  
![minishell_echo_export](https://github.com/user-attachments/assets/1d08b70b-bff1-43f6-ba93-d7319d7c4653)  
![minishell_echo_n](https://github.com/user-attachments/assets/f17c1141-aec7-40c5-8115-3b36eee6dc95)  

### Cd:  
![minishell_cd_1](https://github.com/user-attachments/assets/8522052a-81f4-4ee9-af47-aa1e8a6f0335)  
![minishell_cd_2](https://github.com/user-attachments/assets/9280b27f-18f5-4339-95c8-b151ccd8cbb3)  
![minishell_cd_dot](https://github.com/user-attachments/assets/0827dff4-8a5b-4f30-8a77-97101020eafc)  
![minishell_cd_dot_2](https://github.com/user-attachments/assets/dea4832c-b444-4d11-820f-8e5cfec30227)  

### Exit:  
![minishell_exit_1](https://github.com/user-attachments/assets/bc9f4ef4-0d0b-4d68-a2e1-a47761480ba9)  
![minishell_exit_5](https://github.com/user-attachments/assets/129bfcd7-7285-4b91-9681-f1c0f3093497)  
![minishell_exit_6](https://github.com/user-attachments/assets/8034b6cb-c38a-477d-84d7-c5d6deb07de8)  
![minishell_exit_7](https://github.com/user-attachments/assets/33eb0e65-67fe-4861-b0df-eebb560d357b)  

### Errors:  
![minishell_full_perm](https://github.com/user-attachments/assets/f6ca1552-2c66-40fe-87d5-563120604dc8)  

### Path:  
![minishell_path](https://github.com/user-attachments/assets/bc039d91-7081-4a10-adff-116ac43fb208)  

### Wildcards:  
![minishell_wildcard](https://github.com/user-attachments/assets/ebbac2d3-7fc8-4a41-bbbc-63c911c15245)  
![minishell_wildcard_2](https://github.com/user-attachments/assets/0dbd7a4e-681c-47ac-b47c-b4c2eb3a8032)  

## Note on Project State

All projects from my 42 cursus are preserved in their state immediately following their final evaluation. While they may contain mistakes or stylistic errors, I've chosen not to alter them. This approach provides a clear and authentic timeline of my progress and learning journey as a programmer.

## Known Issues & Fix Suggestions


## Credits

This project was developed in collaboration with another student, who contributed to the implementation of built-in commands, signal handling, and provided valuable debugging support.

## License

[MIT](https://choosealicense.com/licenses/mit/)  
