<h1 align="center">Simple Operating System</h1>

![Operating System Photo](/OS_Screenshot.png)

## Steps

### Steps Completed:

- [x] Step 1: Write the function `writeSector()`
- [x] Step 2: Add `dir` command to the shell
- [x] Step 3: Write function `deleteFile()`
- [x] Step 4: Write the function `writeFile()`
- [x] Step 5: Add `copy` command to the shell
- [x] Step 6: Add `create` command to shell

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

### Clear Line Function

- Clears the console line.

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
