// Joseph Masone
// Natalio Gomes
// COMP350-001
// November 15, 2023

void printString(char *);
void printChar(char);
void readString(char *);
void readSector(char *, int);
void handleInterrupt21(int);
void readFile(char *, char *, int *);
void executeProgram(char *name);
void terminate();

void main() {

  // Step 1
  // char buffer[13312];
  // int sectorsRead;
  // makeInterrupt21();
  // interrupt(0x21,3,"messag",buffer,&sectorsRead);

  // if(sectorsRead>0) {
  //     interrupt(0x21,0,buffer,0,0);
  // } else {
  //     interrupt(0x21,0,"messag not found\r\n",0,0);
  // }

  // Step 2
  // makeInterrupt21();
  // interrupt(0x21, 4, "tstpr1", 0, 0);

  // Step 3
  // makeInterrupt21();
  // interrupt(0x21, 4, "tstpr2", 0, 0);

  // Step 4
  makeInterrupt21();
  interrupt(0x21, 4, "shell", 0, 0);

  while (1)
    ;
}

void printString(char *string) {
  while (*string != 0x0) {
    char al = *string;
    char ah = 0xe;
    int ax = ah * 256 + al;
    interrupt(0x10, ax, 0, 0, 0);
    string++;
  }
}

void printChar(char c) {
  char al = c;
  char ah = 0xe;
  int ax = ah * 256 + c;
  interrupt(0x10, ax, 0, 0, 0);
}

void readString(char *string) {

  char ah = 0x0;
  int ax = 0;
  int i = 0;

  for (i = 0; i < 79;) {
    char letter = interrupt(0x16, ax, 0, 0, 0);

    if (letter == 8) {
      if (i <= 0) {
        i = 0;
      } else {
        i -= 1;
        printChar('\b');
        printChar(' ');
        printChar('\b');
      }
    } else if (letter == 13) {
      string[i] = 13;
      string[i + 1] = 10;
      string[i + 2] = 0;
      return;
    } else {
      string[i] = letter;
      printChar(string[i]);
      i++;
    }
  }
}

void readSector(char *buffer, int sector) {
  int ah = 2;
  int al = 1;
  int ch = 0;
  int cl = sector + 1;
  int dh = 0;
  int dl = 0x80;

  int ax = ah * 256 + al;
  int bx = buffer;
  int cx = ch * 256 + cl;
  int dx = dh * 256 + dl;

  interrupt(0x13, ax, bx, cx, dx);
}

void handleInterrupt21(int ax, int bx, int cx, int dx) {
  switch (ax) {
  case 0:
    printString(bx);
    break;

  case 1:
    readString(bx);
    break;

  case 2:
    readSector(bx, cx);
    break;

  case 3:
    readFile(bx, cx, dx);
    break;

  case 4:
    executeProgram(bx);
    break;

  case 5:
    terminate();
    break;

  default:
    printString("Error!\0");
  }
}

void readFile(char *name, char *buffer, int *sectorsRead) {

  char dir[512];
  int fileEntry;
  readSector(dir, 2);

  for (fileEntry = 0; fileEntry < 512; fileEntry += 32) {
    if (dir[fileEntry] == name[0] && dir[fileEntry + 1] == name[1] &&
        dir[fileEntry + 2] == name[2] && dir[fileEntry + 3] == name[3] &&
        dir[fileEntry + 4] == name[4] && dir[fileEntry + 5] == name[5]) {

      int check = 6;
      while (dir[fileEntry + check] != 0) {

        readSector(buffer, dir[fileEntry + check]);
        buffer += 512;
        *sectorsRead += 1;
        check += 1;
      }
    }
  }
}

void executeProgram(char *name) {
  char buffer[512];
  int sectorsRead;
  int segment = 0x2000;
  int offset = 0;
  int i;

  readFile(name, buffer, &sectorsRead);

  for (i = 0; i < 512; i++) {

    putInMemory(segment, offset, buffer[i]);
    offset++;
  }

  launchProgram(segment);
}

void terminate() {

  char shellname[6];
  shellname[0] = 's';
  shellname[1] = 'h';
  shellname[2] = 'e';
  shellname[3] = 'l';
  shellname[4] = 'l';
  shellname[5] = '\0';

  interrupt(0x21, 4, shellname, 0, 0);
}
