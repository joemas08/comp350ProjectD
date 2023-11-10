// Joseph Masone
// Natalio Gomes
// COMP350-001
// November 15, 2023

void main() {

  while (1) {

    char input[50];

    syscall(0, "SHELL> ");

    syscall(1, input);

    syscall(0, "\r\nBad Command!\r\n");
  }
}
