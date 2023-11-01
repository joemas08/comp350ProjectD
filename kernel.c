// Joseph Masone
// Natalio Gomes
// COMP350-001
// November 2, 2023

void printString(char*);
void printChar(char);
void readString(char*);
void readSector(char*, int);
void handleInterrupt21(int);

void main() { 

    // Step 1
    //printString("Hello World\0");

    // Step 2
    //char line[80];
    //printString("Enter Line: \0");
    //readString(line);
    //printChar('\n');
    //printString(line);

    // Step 3
    //char buffer[512];
    //readSector(buffer, 30);
    //printString(buffer);

    // Step 4
    //makeInterrupt21();
    //interrupt(0x21,0,0,0,0);

    // Step 5
    //char line[80];
    //makeInterrupt21();
    //interrupt(0x21,1,line,0,0);
    //interrupt(0x21,0,line,0,0);

    while(1);
}

void printString(char* string) {
   while(*string != 0x0) {  
       char al = *string;
       char ah = 0xe;
       int ax = ah * 256 + al;
       interrupt(0x10,ax,0,0,0);
       string++;
    }
}

void printChar(char c) {
    char al = c;
    char ah = 0xe;
    int ax = ah * 256 + c;
    interrupt(0x10,ax,0,0,0);
}

void readString(char* string) {

    char ah = 0x0;
    int ax = 0;
    int i = 0;

    for(i = 0; i < 79;) {
        char letter = interrupt(0x16,ax,0,0,0);

        if (letter == 8) {
            if (i <= 0) {
                i = 0;
            } else {
                i -= 1;
                printChar('\b');
                printChar(' ');
                printChar('\b');
            }
        } else if (letter == 13){
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


void readSector(char* buffer, int sector) {
    int ah = 2;
    int al = 1;
    int ch = 0;
    int cl = sector + 1;
    int dh = 0;
    int dl = 0x80;
    
    int ax = ah*256+al;
    int bx = buffer;
    int cx = ch*256+cl;
    int dx = dh*256+dl;

    interrupt(0x13,ax,bx,cx,dx);

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

        default:
            printString("Error!\0");

    }
}
