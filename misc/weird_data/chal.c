#include <stdio.h>
#include <string.h>

void xor(char *str, int key) {
  int len = strlen(str);
  for (int i = 0; i < len; i++) {
    str[i] = str[i] ^ key;
  }
}

int main() {
  int num;
  char flag[] = {'z','m','\x7f','R','V','T','B','[','\x08','W','\r','K','@','f',']','\r','M','\r','D'};

  printf("Please input a number between 1 and 1000:\n");
  scanf("%i", &num);

  if (num == 57) {
    xor(flag, num);
    printf("%s\n", flag);
  }
  else {
    printf("Wrong number!\n");
  }
}
