#include <stdio.h>

void leak() {

  char name[128];
  printf(
      "LEAK OVER HERE -----------------------------> %p\nPlease help me!!!\n",
      name);

  fgets(name, 256, stdin);
}

int main() {
  setvbuf(stdout, NULL, _IONBF, 0);
  leak();
  return 0;
}
