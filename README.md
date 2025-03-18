# 🌟 42 Minishell Project

<div align="center">

# Welcome to **Minishell**! 

This project is our implementation of a simplified **Shell**, which is part of the **42 coding school** curriculum. As a team of two, we worked together to create a minimalist version of bash that can interpret commands, handle executables, and implement various shell functionalities. This project required us to dive deep into processes, file descriptors, and command interpretation.

Our implementation follows a structured pipeline approach with distinct processing stages from prompt display to command execution. This solution handles various shell features like redirections, pipes, environment variables, and built-in commands.

<div align="left">
Key aspects of our collaborative implementation include:
- **Command parsing and execution** system
- **Signal handling** for keyboard interrupts
- **Built-in commands** like echo, cd, pwd, etc.
- **Redirections and pipes** management
- **Environment variables** expansion
</div>

Minishell
Language
License

</div>

---

## 📚 Table of Contents

<details>
<summary>Click to expand</summary>

- [📍 Overview](#overview)
- [✨ Features](#features)
- [🧠 Project Workflow](#project-workflow)
- [👥 Contributors](#contributors)
- [🚀 Getting Started](#getting-started)
- [🖥️ Usage](#usage)
- [⚙️ Testing](#testing)
- [🤝 Contributing](#contributing)
- [📜 License](#license)

</details>

---

## 📍 Overview

The **Minishell** project involves creating a simplified version of a Unix shell, specifically taking **bash** as a reference. A shell serves as the primary interface between the user and the operating system, interpreting commands and executing programs.

We worked together to create a shell that handles:
- **Command interpretation** 🔍
- **Program execution** ⚡
- **Shell built-ins** 🛠️
- **Signal handling** 🚨

This collaborative project challenged us to understand how shells work under the hood, dealing with processes, file descriptors, and command parsing while providing a smooth user experience.

---

## ✨ Features

- 🖥️ **Interactive Prompt**: Displays a prompt when waiting for new commands.
- 📜 **Command History**: Maintains a working history of commands.
- 🔍 **Path Resolution**: Searches and launches executables based on PATH or given paths.
- ✏️ **Command Line Editing**: Basic command line editing capabilities.

- 🔣 **Special Character Handling**:
  - Handles quotes (`'` and `"`) (unmatching quotes simply displays an error message)
  - Manages redirections (`<`, `>`, `<<`, `>>`)
  - Processes pipes (`|`)
  - Interprets environment variables (`$`)

- 🛠️ **Built-in Commands**:
  - `echo` with `-n` option
  - `cd` with relative or absolute path
  - `pwd` without options
  - `export` to set environment variables
  - `unset` to remove environment variables
  - `env` to display environment
  - `exit` to terminate the shell

- 🚨 **Signal Handling**:
  - `Ctrl-C`: Displays a new prompt on a new line
  - `Ctrl-D`: Exits the shell
  - `Ctrl-\`: No action

---

## 🧠 Project Workflow

Our minishell implementation follows a clear sequential workflow that transforms user input into executed commands:

### **1. Setting Up the Prompt**

We begin by displaying a customized prompt to the user using the readline library.

### **2. Reading Input with Readline**

We use the readline library to capture user input and manage command history.

### **3. Syntax Checking**

Before further processing, we validate the input to ensure it follows proper shell syntax, checking for:
- Matching quotes
- Valid operator usage
- Proper command structure

### **4. Tokenization Process**

Once syntax is verified, we break down the input string into meaningful tokens. 

### **5. Heredoc Application**

For commands with heredoc operators (`<<`), we collect multi-line input until a delimiter is encountered.

### **6. Pipe Management**

When commands include pipes, we set up the necessary pipes and file descriptors to connect command outputs to inputs.

### **7. Redirection Handling**

We process input/output redirections by opening appropriate files and redirecting standard I/O.

### **8. Command Execution**

Finally, we execute the commands, distinguishing between built-ins and external programs:
- Built-ins are executed directly within the shell process
- External commands are executed through forking and execve

This structured workflow ensures each command is properly processed and executed while handling all shell functionalities.

---

## 👥 Contributors

This project was developed collaboratively by two 42 students:

- **Melanie Reis (melaniereis)** - Mainly focused on parsing, signal handling, tokenization, redirections, and heredocs.
- **Miguel Meireles (m3irel3s)** - Mainly focused on command execution, shell variables, and pipes.

We worked closely together throughout the project, often collaborating on tasks and sharing responsibilities to ensure a cohesive and well-structured implementation. Our collaborative approach involved regular code reviews, task division, and occasional pair programming sessions.
Our teamwork was essential in achieving a comprehensive and functional Minishell implementation.

---

## 🚀 Getting Started

### 📦 Prerequisites

Before running the project, make sure you have the following installed:

- **`cc`** or any compatible C compiler
- **`make`** utility to build the project
- **`readline`** library for command line editing

### 🔧 Installation

1. Clone the repository:
```bash
git clone https://github.com/m3irel3s/41_Minishell.git
```

2. Navigate to the project directory and build:
```bash
cd minishell
make
```

This will compile the project and generate the executable `minishell`.

---

## 🖥️ Usage

To start the shell, simply run:
```bash
./minishell
```

### Command Syntax

Our Minishell supports the following syntax elements:

- **Simple Commands**: `ls -l`, `echo hello`
- **Redirections**: 
  - Input: `cat < file.txt`
  - Output: `ls > output.txt`
  - Append: `echo hello >> log.txt`
  - Heredoc: `cat << EOF`

- **Pipes**: `ls -l | grep ".c"`
- **Environment Variables**: `echo $HOME`
- **Exit Status**: `echo $?`

### Examples

1. **Basic command execution**:
```bash
minishell> ls -la
```

2. **Using redirections**:
```bash
minishell> cat < input.txt > output.txt
```

3. **Using pipes**:
```bash
minishell: > ls -l | grep ".c" | wc -l
```


5. **Using built-in commands**:
```bash
minishell: > cd /tmp
minishell: > pwd
minishell: > echo Hello, $USER!
```

5. **Environment variable operations**:
```bash 
minishell: > export NAME=value
minishell: > env | grep NAME
minishell: > unset NAME
```

---

## ⚙️ Testing

To ensure your shell is working correctly, test the following scenarios:

- **Basic Commands**: Test simple Unix commands like `ls`, `cat`, `grep`.
- **Built-ins**: Test all built-in commands with various arguments.
- **Redirections**: Test all types of redirections with different combinations.
- **Pipes**: Test multiple piped commands with varying complexity.
- **Quotes**: Test commands with single and double quotes, including nested quotes.
- **Environment Variables**: Test variable expansion in different contexts.
- **Signals**: Test how the shell responds to Ctrl-C, Ctrl-D, and Ctrl-\.

### Edge Cases to Test

- Commands with very long arguments
- Handling of non-existent commands
- Multiple redirections in a single command
- Nested quotes and escape characters
- Empty input
- Invalid syntax

---

## 🤝 Contributing

Contributions to improve the Minishell project are welcome. Please follow these steps:

1. Fork the repository
2. Create a new branch (`git checkout -b feature/improvement`)
3. Make your changes
4. Commit your changes (`git commit -m 'Add some feature'`)
5. Push to the branch (`git push origin feature/improvement`)
6. Open a Pull Request

---

## 📜 License

This project is licensed under the MIT License - see the LICENSE file for details.

---

<div align="center">
  Made with ❤️ by two passionate 42 School students
</div>


