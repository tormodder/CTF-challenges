#include <stdio.h>

volatile int a = 2;

unsigned long hash(char *str) {
  unsigned long hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + c; // hash * 33 + c

  return hash;
}

void main() {
  if (a > 3) {
    unsigned long x = hash("CTFkom{not the flag}");
    printf("You are right! 2 is larger than 3!\nCTFkom{%lx}", x);
  } else {
    printf("Unfortunately 2 is less than 3.\n");
  }
}
