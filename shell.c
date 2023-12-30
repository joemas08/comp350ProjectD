// Joseph Masone
// COMP350-001

void type(char *fileName);
void exec(char *filename);
void copy(char *filename, char *newFilename);
void create(char *filename);
void dir();
void clearLine();
void printChar(char character);

void main() {

  while (1) {

    char input[50];

    clearLine();

    syscall(0, "SHELL> \0");

    syscall(1, input);

    // Check for valid commands with correct args
    if (input[0] == 't' && input[1] == 'y' && input[2] == 'p' &&
        input[3] == 'e' && input[4] == ' ' && input[11] == '\r') {

      char fileName[6];
      int i;
      for (i = 0; i < 6; i++) {
        fileName[i] = input[i + 5];
      }

      type(fileName);

    } else if (input[0] == 'e' && input[1] == 'x' && input[2] == 'e' &&
               input[3] == 'c' && input[4] == ' ' && input[11] == '\r') {

      char fileName[6];
      int i;

      for (i = 0; i < 6; i++) {
        fileName[i] = input[i + 5];
      }

      exec(fileName);

    } else if (input[0] == 'd' && input[1] == 'e' && input[2] == 'l' &&
               input[10] == '\r') {

      char fileName[6];
      int i;

      for (i = 0; i < 6; i++) {
        fileName[i] = input[i + 4];
      }

      syscall(7, fileName);

    } else if (input[0] == 'c' && input[1] == 'r' && input[2] == 'e' &&
               input[3] == 'a' && input[4] == 't' && input[5] == 'e' &&
               input[6] == ' ' && input[13] == '\r') {

      char fileName[6];
      int i;

      for (i = 0; i < 6; i++) {
        fileName[i] = input[i + 7];
      }

      create(fileName);

    } else if (input[0] == 'c' && input[1] == 'o' && input[2] == 'p' &&
               input[3] == 'y' && input[4] == ' ' && input[11] == ' ' &&
               input[18] == '\r') {

      char fileName[6];
      char newFileName[6];
      int i = 0;

      for (i = 0; i < 6; i++) {
        fileName[i] = input[i + 5];
        newFileName[i] = input[i + 12];
      }

      copy(fileName, newFileName);

      // Small help menu for each command if typed on their own
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

    } else if (input[0] == 't' && input[1] == 'y' && input[2] == 'p' &&
               input[3] == 'e') {
      clearLine();
      syscall(0, "type is a command to print out contents of a file\0");
      clearLine();
      syscall(0, "*type FILENAME* is the format for the type command\0");
      clearLine();
      syscall(0, "FILENAME must be 6 characters long\0");

    } else if (input[0] == 'e' && input[1] == 'x' && input[2] == 'e' &&
               input[3] == 'c') {
      clearLine();
      syscall(0, "exec is a command to execute a file\0");
      clearLine();
      syscall(0, "*exec FILENAME* is the format for the type command\0");
      clearLine();
      syscall(0, "FILENAME must be 6 characters long\0");

    } else if (input[0] == 'c' && input[1] == 'o' && input[2] == 'p' &&
               input[3] == 'y') {
      clearLine();
      syscall(0, "copy is a command to copy a file\0");
      clearLine();
      syscall(
          0,
          "*copy FILENAME NEWFILENAME* is the format for the copy command\0");
      clearLine();
      syscall(0, "FILENAME and NEWFILENAME must be 6 characters long\0");

    } else if (input[0] == 'c' && input[1] == 'r' && input[2] == 'e' &&
               input[3] == 'a' && input[4] == 't' && input[5] == 'e') {
      clearLine();
      syscall(0, "create is a command to create a new file\0");
      clearLine();
      syscall(0, "*create FILENAME* is the format for the create command\0");
      clearLine();
      syscall(0, "FILENAME must be 6 characters long\0");

    } else if (input[0] == 'h' && input[1] == 'e' && input[2] == 'l' &&
               input[3] == 'p') {
      clearLine();
      syscall(0, "type:\t\t print out contents of a file\0");
      clearLine();
      syscall(0, "dir: \t\t list all files on the system\0");
      clearLine();
      syscall(0, "exec:\t\t execute a file\0");
      clearLine();
      syscall(0, "create: create a new file\0");
      clearLine();
      syscall(0, "copy:\t\t copy a file\0");
      clearLine();
      syscall(0, "del: \t\t delete a file\0");
      clearLine();
      syscall(0, "help:\t\t show commands for the system\0");
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

void create(char *filename) {
  char buffer[512];
  int bytesRead = 0;

  clearLine();
  syscall(0, "--Start Typing--");
  clearLine();

  while (1) {
    bytesRead = syscall(1, buffer);
    if (buffer[0] == '\r' && bytesRead < 2) {
      break;
    }
    clearLine();
    bytesRead = 0;
    syscall(8, buffer, filename, 1);
  }
}

void copy(char *filename, char *newFile) {
  char buffer[512];
  int sectorsRead = 0;

  // Call readFile on the original file
  syscall(3, filename, buffer, &sectorsRead);

  if (sectorsRead == 0) {
    clearLine();
    syscall(0, "File not found!\0");
  } else {
    // Call writeFile with new file name
    syscall(8, buffer, newFile, sectorsRead);
  }
}

void clearLine() { syscall(0, "\r\n\0"); }
