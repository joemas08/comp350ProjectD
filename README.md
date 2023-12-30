<div align="center">
  <h1>Operating System Project</h1>
  
  [![C](https://img.shields.io/badge/C-99-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
  [![Assembly](https://img.shields.io/badge/Assembly-x86-green.svg)](https://en.wikipedia.org/wiki/X86_assembly_language)
  [![Shell](https://img.shields.io/badge/Shell-bash-yellow.svg)](https://www.gnu.org/software/bash/)
  
  Small operating system written in C and developed on Linux Mint
</div>



![Operating System Photo](/OS_Screenshot.png)

## Features

### Type Command

- Prints the contents of a file.
- **Usage:** `type FILENAME`

### Exec Command

- Executes a file.
- **Usage:** `exec FILENAME`

### Copy Command

- Copies a file.
- **Usage:** `copy FILENAME NEWFILENAME`

### Create Command

- Creates a new file.
- **Usage:** `create FILENAME`

### Directory Listing Command

- Lists all files on the system.
- **Usage:** `dir`

### Print Character Function

- Prints a single character.

### Main Shell Loop

- Continuously accepts user input and executes corresponding commands.

### Help Information

- Provides help information for each command if typed on its own:
  - `del`: Delete a file.
  - `dir`: List all files on the system.
  - `type`: Print out contents of a file.
  - `exec`: Execute a file.
  - `copy`: Copy a file.
  - `create`: Create a new file.
  - `help`: Show commands for the system.

### Usage Notes

- Ensure file names are 6 characters long for relevant commands.
- Handle file not found scenarios and provide error messages.

## Installation

Follow these steps to set up the project locally:

1. Clone the repository:

   ```bash
   git clone https://github.com/joemas08/comp350ProjectD.git

   ```

## Usage

Run the Operating System:

1. Compile with
   ```bash
    ./compileOS.sh
   ```
2. Run with
   ```bash
   java -jar simulator.jar
   ```
   `Boot with disk.img file`
