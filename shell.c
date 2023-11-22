// Joseph Masone
// Natalio Gomes
// COMP350-001
// November 15, 2023

void type(char *fileName);
void exec(char *filename);
void dir();
void clearLine();
void printChar(char character);

void main() {

  while (1) {

    char input[50];

    clearLine();

    syscall(0, "SHELL> \0");

    syscall(1, input);

    // Check for type command
    if (input[0] == 't' && input[1] == 'y' && input[2] == 'p' &&
        input[3] == 'e' && input[4] == ' ' && input[11] == '\r') {

      char fileName[6];
      int i;
      for (i = 0; i < 6; i++) {
        fileName[i] = input[i + 5];
      }

      type(fileName);

      // Check for exec command
    } else if (input[0] == 'e' && input[1] == 'x' && input[2] == 'e' &&
               input[3] == 'c' && input[4] == ' ' && input[11] == '\r') {

      char fileName[6];
      int i;

      for (i = 0; i < 6; i++) {
        fileName[i] = input[i + 5];
      }

      exec(fileName);

      // Small help menu for del command
    } else if (input[0] == 'd' && input[1] == 'e' && input[2] == 'l') {
      clearLine();
      syscall(0, "del is a command to delete a file\0");
      clearLine();
      syscall(0, "*del FILENAME* is the format for the del command\0");
      clearLine();
      syscall(0, "FILENAME must be 6 characters long\0");

    } else if (input[0] == 'd' && input[1] == 'i' && input[2] == 'r') {
      clearLine();
      dir();

      // Small help menu for type command
    } else if (input[0] == 't' && input[1] == 'y' && input[2] == 'p' &&
               input[3] == 'e') {
      clearLine();
      syscall(0, "type is a command to print out contents of a file\0");
      clearLine();
      syscall(0, "*type FILENAME* is the format for the type command\0");
      clearLine();
      syscall(0, "FILENAME must be 6 characters long\0");

      // Small help menu for exec command
    } else if (input[0] == 'e' && input[1] == 'x' && input[2] == 'e' &&
               input[3] == 'c') {
      clearLine();
      syscall(0, "exec is a command to execute a file\0");
      clearLine();
      syscall(0, "*exec FILENAME* is the format for the type command\0");
      clearLine();
      syscall(0, "FILENAME must be 6 characters long\0");

    } else {

      clearLine();
      syscall(0, "Bad command!\0");
    }
  }
}

void exec(char *fileName) {
  char buffer[512];
  int sectorsRead = 0;

  // Call readFile on file name passed
  syscall(3, fileName, buffer, &sectorsRead);

  // If sectors wasn't incremented by readFile call, file wasn't found
  if (sectorsRead == 0) {

    clearLine();
    syscall(0, "File not found!\0");
  } else {
    clearLine();
    syscall(4, fileName);
  }
}

void type(char *fileName) {

  char buffer[512];
  int sectorsRead = 0;

  // Call readFile on file name passed
  syscall(3, fileName, buffer, &sectorsRead);

  // If sectors wasn't incremented by readFile call, file wasn't found
  if (sectorsRead == 0) {

    clearLine();
    syscall(0, "File not found!\0");

  } else {
    clearLine();
    syscall(0, buffer);
  }
}

void dir() {

  char buffer[512];
  char filename[7];
  int i = 0;
  int fileEntry = 0;

  syscall(2, buffer, 2);

  for (fileEntry = 0; fileEntry < 512; fileEntry += 32) {
    if (buffer[fileEntry] != '\0') {
      for (i = 0; i < 6; i++) {
        filename[i] = buffer[fileEntry + i];
      }

      filename[i] = '\0';
      syscall(0, filename);
      clearLine();
    }
  }
}

void clearLine() { syscall(0, "\r\n\0"); }
