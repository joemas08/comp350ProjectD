// Joseph Masone
// Natalio Gomes
// COMP350-001
// November 27, 2023

void printString(char *);
void printChar(char);
int readString(char *);
void readSector(char *, int);
void writeSector(char *, int);
void handleInterrupt21(int);
void readFile(char *, char *, int *);
void writeFile(char *, char *, int);
void deleteFile(char *);
void executeProgram(char *name);
void terminate();
int lengthOfString(char *str);

void main() {

  makeInterrupt21();
  interrupt(0x21, 8, "this is a test message", "testmg", 3);
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

int readString(char *string) {

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
  return i;
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

void writeSector(char *buffer, int sector) {
  int ah = 3;
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

  case 6:
    writeSector(bx, cx);
    break;

  case 7:
    deleteFile(bx);
    break;

  case 8:
    writeFile(bx, cx, dx);
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

void writeFile(char *buffer, char *filename, int numberOfSectors) {
  char map[512];
  char dir[512];
  char sector[512];
  int fileEntry = 0;
  int entryIndex = -1;
  int sectorIndex = -1;
  int nameLength;
  int i;
  int j;
  int k;

  readSector(map, 1);
  readSector(dir, 2);

  for (fileEntry = 0; fileEntry < 512; fileEntry += 32) {

    if (dir[fileEntry] == '\0') {
      entryIndex = fileEntry;
      break;
    }
  }

  if (entryIndex == -1) {
    return;
  }

  nameLength = lengthOfString(filename);

  for (i = 0; i < nameLength && i < 6; i++) {
    dir[entryIndex + i] = filename[i];
  }

  for (i = nameLength; i < 6; i++) {
    dir[entryIndex + i] = '\0';
  }

  for (i = 0; i < numberOfSectors; i++) {
    for (j = 3; j < 256; j++) {
      if (map[j] == '\0') {
        sectorIndex = j;
        break;
      }
    }

    if (sectorIndex == -1) {
      return;
    }

    map[sectorIndex] = 0xFF;

    dir[entryIndex + 6 + i] = sectorIndex;

    for (k = 0; k < 512; k++) {
      sector[k] = buffer[i * 512 + k];
    }

    writeSector(sector, sectorIndex);
  }

  for (i = numberOfSectors; i < 16; i++) {
    dir[entryIndex + 6 + i] = 0;
  }

  writeSector(map, 1);
  writeSector(dir, 2);
}

void deleteFile(char *filename) {
  char map[512];
  char dir[512];
  int fileEntry;
  int check = 6;

  readSector(map, 1);
  readSector(dir, 2);

  for (fileEntry = 0; fileEntry < 512; fileEntry += 32) {

    if (dir[fileEntry] == filename[0] && dir[fileEntry + 1] == filename[1] &&
        dir[fileEntry + 2] == filename[2] &&
        dir[fileEntry + 3] == filename[3] &&
        dir[fileEntry + 4] == filename[4] &&
        dir[fileEntry + 5] == filename[5]) {

      dir[fileEntry] = '\0';

      while (dir[fileEntry + check] != 0) {

        map[dir[fileEntry + check]] = '\0';
        check++;
      }
      check = 6;
    }
  }
  writeSector(map, 1);
  writeSector(dir, 2);
}

void executeProgram(char *name) {
  char buffer[13312];
  int sectorsRead;
  int segment = 0x2000;
  int offset = 0;
  int i;

  readFile(name, buffer, &sectorsRead);

  for (i = 0; i < 13312; i++) {

    putInMemory(segment, offset, buffer[i]);
    offset++;
  }

  launchProgram(segment);
}

int lengthOfString(char *str) {
  int length = 0;
  while (str[length] != '\0') {
    length++;
  }
  return length;
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
