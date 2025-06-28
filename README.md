<div align="center">
  <img src="https://i.ibb.co/W4BbX6FL/Screenshot-from-2025-06-24-12-50-29.png" alt="Project score">
</div>

# minishell

 This is my Minishell project: a small Bash-like shell written in C as part of the 42 common core. It parses and executes user commands, handles pipes and redirections, and manages signals and child processes with proper system calls.  
We had to rebuild key parts of a shell from scratch: quoting, environment variables, file descriptors, fork/exec logic, and more.  
It was a deep dive into Unix internals and low-level system programming. Everything from process creation to memory management was handled manually, using a range of standard and POSIX libraries (such as `unistd.h`, `fcntl.h`, `signal.h`, and `readline.h`) to interact with the system. Overall, this project gave me a much clearer understanding of what a shell actually does under the hood.  

## Table of Contents

- [About](#minishell)
- [Usage](#usage)
- [Example](#example)
- [Features](#features)
- [Note on Project State](#note-on-project-state)
- [Known Issues & Fix Suggestions](#known-issues--fix-suggestions)
- [Credits](#credits)
- [License](#license)

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
The minishell project is covering a lot of ground, and the best way to check all of its features would be to use the program directly.  

<details>
  <summary><strong>Basic</strong></summary>
  <p>This example shows a basic <code>echo</code> command with a redirection to a file <code>output</code>.</p>
<img src="https://github.com/user-attachments/assets/df54efc1-0609-4753-a9d2-1e9185492a45" alt="minishell_basic" />
<p>Quoting forces a literal interpretation of special characters such as <code>|</code> or <code>&gt;</code>.</p>
  <img src="https://github.com/user-attachments/assets/5fce475a-d2ae-4047-b4a6-df76d0b2e97c" alt="minishell_double_quote" />
</details>

<details>
  <summary><strong>Empty</strong></summary>
  <p>This example is to test empty commands. A simple line return, nothing quoted, and space quoted.</p>
  <img src="https://github.com/user-attachments/assets/ffb13913-a55f-4b87-845a-c43b83397dad" alt="minishell_empty" />
</details>

<details>
  <summary><strong>Redirections</strong></summary>
  <p>The next example is showing support of the multiple input redirections in random order, before and after the main command.<br>
  As you can see, only the last file is used for the redirection while the previous files are created if they don't exist.</p>
  <img src="https://github.com/user-attachments/assets/e93ff3d6-a88f-4fb0-8271-b037b4379b56" alt="minishell_redir" />

  <p>Same for multiple output redirections. The redirections work without spaces or with quotes.</p>
  <img src="https://github.com/user-attachments/assets/7f7b3178-2aaa-43a3-807c-691c8dc760eb" alt="minishell_redir_2" />

  <p>If no command is used, the file is emptied just like <code>Bash</code> would do.</p>
  <img src="https://github.com/user-attachments/assets/02b314c2-539b-492b-9909-ec171540aba3" alt="minishell_redir_3" />
</details>

<details>
  <summary><strong>Heredocs</strong></summary>
  <p>This section demonstrates <code>heredoc</code> support. You can combine <code>heredocs</code> just as you can with simple redirections.<br>
  If a <code>pipe</code> ends the command line, <code>heredocs</code> are resolved first, and then the program displays the appropriate prompt for the remaining <code>pipe</code>.</p>
  <img src="https://github.com/user-attachments/assets/ddd9b0c5-cc7f-404e-afb8-ba112def9266" alt="minishell_heredoc_pipe" />
</details>

<details>
  <summary><strong>Pipes</strong></summary>
  <p>This example demonstrates a simple command using <code>pipes</code>.</p>
  <img src="https://github.com/user-attachments/assets/ebc7c9cb-6a78-465b-a41f-f7acaa22ed9a" alt="minishell_pipe_1" />
  <p>This example shows heredoc behavior with pipes. As long as the last command ends with a <code>pipe</code>, a new prompt will open.<br>
Once a command does not end with a <code>pipe</code>, the multiple commands are merged into a single one.</p>
  <img src="https://github.com/user-attachments/assets/dcf19219-a10f-4e70-95eb-9868fce021dd" alt="minishell_pipe_end" />
</details>

<details>
  <summary><strong>Echo</strong></summary>
  <p>This first example will show the basic behavior of <code>echo</code> when used with multiple quotes mixed.</p>
  <img src="https://github.com/user-attachments/assets/109d88ec-1cbc-4a6b-b7ab-8a8ce99b278b" alt="minishell_echo_1" />

  <p>The <code>echo</code> builtin is also supporting the use of the <code>-n</code> flag.</p>
  <img src="https://github.com/user-attachments/assets/f17c1141-aec7-40c5-8115-3b36eee6dc95" alt="minishell_echo_n" />

  <p>We can go a little further by exporting a variable containing spaces in our environment.<br>
  Then depending on the quotes used, the expansion will vary, either splitting the variable or not.</p>
  <img src="https://github.com/user-attachments/assets/1d08b70b-bff1-43f6-ba93-d7319d7c4653" alt="minishell_echo_export" />
</details>

<details>
  <summary><strong>Cd</strong></summary>
  <p>The following examples will showcase the <code>cd</code> behavior.</p>
  <img src="https://github.com/user-attachments/assets/8522052a-81f4-4ee9-af47-aa1e8a6f0335" alt="minishell_cd_1" />

  <p>Here we can see it fail on a locked directory, and a missing directory.</p>
  <img src="https://github.com/user-attachments/assets/9280b27f-18f5-4339-95c8-b151ccd8cbb3" alt="minishell_cd_2" />

  <p>The following image is showing the <code>cd</code> command used with <code>..</code> and <code>.</code> in accordance to the subject.<br>
  We use <code>pwd</code> to check that we are in the correct directory, even though the current working directory is updated directly in the prompt.</p>
  <img src="https://github.com/user-attachments/assets/dea4832c-b444-4d11-820f-8e5cfec30227" alt="minishell_cd_dot_2" />
</details>

<details>
  <summary><strong>Exit</strong></summary>
  <p>If a value contained in a <code>long long</code> is passed to the <code>exit</code> command, it will be used as the returned value.</p>
  <img src="https://github.com/user-attachments/assets/bc9f4ef4-0d0b-4d68-a2e1-a47761480ba9" alt="minishell_exit_1" />

  <p>That only works when using a numeric value.</p>
  <img src="https://github.com/user-attachments/assets/129bfcd7-7285-4b91-9681-f1c0f3093497" alt="minishell_exit_5" />

  <p>And with a single argument.</p>
  <img src="https://github.com/user-attachments/assets/8034b6cb-c38a-477d-84d7-c5d6deb07de8" alt="minishell_exit_6" />

  <p>If no value is passed to the <code>exit</code> command, then the last command status is returned.<br>
  Here we test this by first using <code>ctrl + c</code> to set the status to 130, then we exit. The returned value is indeed 130.</p>
  <img src="https://github.com/user-attachments/assets/33eb0e65-67fe-4861-b0df-eebb560d357b" alt="minishell_exit_7" />
</details>

<details>
  <summary><strong>Errors</strong></summary>
  <p>Here I used the <code>ls</code> command to show the possible file errors and the ways the program is dealing with them.<br>
  As you can see, the correct error messages and returned values are used, even when using a redirection or not.</p>
  <img src="https://github.com/user-attachments/assets/f6ca1552-2c66-40fe-87d5-563120604dc8" alt="minishell_full_perm" />
</details>

<details>
  <summary><strong>Path</strong></summary>
  <p>This example is used to show that removing the <code>PATH</code> will stop relative commands from executing, but absolute commands should still work.<br>
  Adding a <code>PATH</code> again should allow for the execution of the commands found in that <code>PATH</code>.</p>
  <img src="https://github.com/user-attachments/assets/bc039d91-7081-4a10-adff-116ac43fb208" alt="minishell_path" />
</details>

<details>
  <summary><strong>Wildcards</strong></summary>
  <p>Finally we can see the wildcard support in the following examples. First we check that we can get all the files expanded.<br>
  Then only the folders, only the hidden files, only the hidden folders, only the hidden folders containing <code>it</code> at the end, and finally only the hidden folders containing <code>i</code> followed by a <code>t</code> at the end.</p>
  <img src="https://github.com/user-attachments/assets/ebbac2d3-7fc8-4a41-bbbc-63c911c15245" alt="minishell_wildcard" />

  <p>We also can check the wildcard behavior when used with redirections, or quotes.</p>
  <img src="https://github.com/user-attachments/assets/0dbd7a4e-681c-47ac-b47c-b4c2eb3a8032" alt="minishell_wildcard_2" />
</details>

## Note on Project State

All projects from my 42 cursus are preserved in their state immediately following their final evaluation. While they may contain mistakes or stylistic errors, I've chosen not to alter them. This approach provides a clear and authentic timeline of my progress and learning journey as a programmer.

## Known Issues & Fix Suggestions

WIP:
- Ctrl+C in a heredoc doesn't line return  
- ![bug_ctrlc_minishell](https://github.com/user-attachments/assets/d7ffa033-9af8-463e-9915-27a1d4027c55)

- Killing a vim session inside minishell will make the prompt messy

## Credits

This project was developed in collaboration with another student, who contributed to the implementation of built-in commands, signal handling, and provided valuable debugging support.

## License

[MIT](https://choosealicense.com/licenses/mit/)  
