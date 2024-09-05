#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void generate_name(char *str, int length) {
  const char charset[] =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  int charsetSize = sizeof(charset) - 1;

  srand(time(NULL));

  for (int i = 0; i < length; i++) {
    int index = rand() % charsetSize;
    str[i] = charset[index];
  }

  str[length] = '\0';
}

int main() {
  char myName[10];
  char guess[20];

  setvbuf(stdout, NULL, _IONBF, 0);

  generate_name(myName, 10);

  printf("What is my name?\n");
  gets(guess);

  if (strcmp(myName, guess) == 0) {
    printf("CTFkom{Guessed_c0rr3ctly!!}\n");
  } else {
    printf("No, my name is: %s\n", myName);
  }
}
