# Minishell42

A small and simple shell inspired by Bash, but with significantly fewer features.

![Demo](assets/demo.gif)

## Description

This project involved creating our own shell with specific required functionalities, using Bash as a reference. While it doesn’t fully replicate Bash, it implements many of its core features.

Minishell may lack the extensive capabilities of Bash, but it includes essential functionalities such as syntax error detection, command execution, input/output redirection, and piping. Additionally, it provides basic support for environment variables on a smaller scale.

We implemented some built ins such as **echo**, **exit**, **cd**, **pwd**, **export**, **unset** and **env** mostly without options as the requeriments asked.

You can try to execute commands by passing the binary path or if it's directory is stated in the $PATH environment variable you can execute just like any other command

## Getting Started

### Dependencies

- **Operating System**: Unix-based OS (Linux or macOS).
- **Library**: GNU Readline.

#### Installation on Linux:
Ensure you have the readline library installed. You can install it using the package manager for your distribution:
- **Debian/Ubuntu**: `sudo apt install libreadline-dev`
- **macOS**: `brew install readline`

### Installing

1. **Clone the Repository**  
   Download the project by running:  
   
        git clone git@github.com:Artur-2k/Minishell.git
   

2. **Navigate to the Project Directory**

        
        cd Minishell/
        

3. **Compile the Program**

    Build the project by running:

        make all

### Executing program

Now just execute the minishell program and use it as if you were in bash

```
./minishell
```

```
echo Hello World!
export my_var=value
env | grep my_var
ls
...
```

## Authors

Contributors names and contact info

Artur Carvalho: [Github](https://github.com/Artur-2k)

Davi Melo: [Github](https://github.com/Davi0805)
