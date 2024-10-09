#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void intro();
void variableOverwrite();
void variableOverwrite2();
void returnFunctionIntro();
void returnFunction();

int main() {
  setvbuf(stdout, NULL, _IONBF, 0);

  intro();
  return 0;
}

void intro() {
  printf("\t\t\t\t------------------------------\n");
  printf("\t\t\t\t|                            |\n");
  printf("\t\t\t\t|    welcome to how2pwn!     |\n");
  printf("\t\t\t\t|                            |\n");
  printf("\t\t\t\t------------------------------\n\n\n");

  printf(
      "This challenge is a is a beginner-friendly guided tour of some "
      "fundamental exploitation techniques for 32-bit binaries.\nWe'll cover "
      "some theory about memory layout in 32-bit binaries and show you how you "
      "can use this knowledge to exploit\nthe way a computer "
      "functions "
      "to make a program bend to your will.\n\n"
      "Some side notes before we start:\n\n"
      "\t• To test this binary locally you may have to install the 32 bit "
      "    version of glibc.\n"
      "\tOn debian based distros like kali or ubuntu this can be done with "
      "these commands:\n\n"
      "\t\tsudo dpkg --add-architecture i386\n"
      "\t\tsudo apt-get update\n"
      "\t\tsudo apt-get install libc6:i386 libncurses5:i386 libstdc++6:i386\n\n"
      "\t• This binary has PIE, NX and canaries disabled, this means:\n"
      "\t\t• PIE      -> all the addresses in the binary will be the same "
      "(i.e. not randomized) :every time it is run.\n"
      "\t\t• NX       -> We can inject malicious code onto the stack and "
      "execute it, which we'll do in the last part.\n"
      "\t You can check this yourself using a program called 'checksec' which "
      "also comes bundles with pwntools.\n\n"
      "To solve this challenge I recomend using the python module pwntools and "
      "the pwndbg plugin for gdb.\n\n"
      "A resource which might be nice for this challenge and for further "
      "learning: https://ir0nstone.gitbook.io/notes/binexp/stack\n"
      "And a video series that is very relevant for this challenge: "
      "https://www.youtube.com/"
      "watch?v=wa3sMSdLyHw&list=PLHUKi1UlEgOIc07Rfk2Jgb5fZbxDPec94\n"
      "Ready? Let's pwn.\n\n"
      "(press any key to continue)");

  getchar();
  variableOverwrite();
}

void variableOverwrite() {
  printf(
      "When a binary is run it is allocated a specific place in the RAM of the "
      "computer."
      "This segment of memory is further subdivided into different sections.\n "
      "We'll not go into detail on the different memory regions here, if you "
      "want "
      "to learn more you can read more about this here: "
      "https://sh4dy.com/notes/pwn/userland_stack\n\n"
      "What we will focus on is the stack. The stack is where local variables "
      "and function calls are stored. It is placed at the very top of the "
      "allocated memory space and grows\n downward toward lower memory "
      "addresses. It looks like this:\n\n"
      "|-------------------------|\n"
      "| Caller Function Frame   |\n"
      "|-------------------------|\n"
      "| Previous EBP            |\n"
      "|-------------------------|\n"
      "|          ...            |\n"
      "|-------------------------|\n"
      "| Return Address          |\n"
      "|-------------------------|\n"
      "| Current EBP             |\n"
      "|-------------------------|\n"
      "| Local Variables         |\n"
      "| ...                     |\n"
      "|-------------------------|\n\n"
      "For each of the coming challenges, you'll learn to write exploits that "
      "target each of these parts of the stack.\nFor now ignore the rest and "
      "let's focus on local variables.\n\n"
      "When I declare a local variable it is placed on the stack. This sounds "
      "unproblematic doesn't it?\n"
      "The problem arises if I for example declare char array (or string if "
      "you're fancy) and then don't\n do bounds checking when I take user "
      "input, like if I use a function like gets(). This means that the user\n "
      "can write beyond the space I allocated to the char array, overwrite "
      "other\n variables and even (as we'll see later) change the control flow "
      "of the program\n\n"
      "Now I'll declare two variables on the stack and take your input with a "
      "vulnerable function.\nI'll place this input in a char array. What you "
      "need to do is overwrite the other variable to continue.\nRemember to "
      "reverse this binary using either idafree or ghidra to see how large the "
      "char array is.\n\n");

  char a[16];
  bool t = false;
  printf("$ ");
  gets(a);

  if (t) {
    printf("You did it! t = 0x%X\nlet's move on.\n", t);
    variableOverwrite2();
  } else {
    printf("Looks like something went wrong, t = 0x%X\n\n", t);
    exit(0);
  }
}

void variableOverwrite2() {
  printf("In this challenge you will overwrite a variable much like the last "
         "challenge.\nHowever this time you can't overwrite it with whatever "
         "you want. I'm going to\n be looking for the very specific value "
         "0xdeadbeef (note this is a number) in the variable.\n");

  char a[16];
  int i = 0;
  printf("$ ");
  gets(a);

  if (i == 0xdeadbeef) {
    printf("You did it again! i = 0x%x\nLet's move on.\n", i);
    returnFunctionIntro();
  } else {
    printf("Sorry, i =/= 0xdeadbeef, i = 0x%x\n", i);
    exit(0);
  }
}

void returnFunctionIntro() {
  printf(
      "In this sub-challenge you will force the program to jump to a "
      "function which is never called.\n"
      "How is this possible? Let's revisit a part of the stack layout we "
      "saw earlier:\n\n"
      "|-------------------------|\n"
      "| Return Address          |\n"
      "|-------------------------|\n"
      "| Current EBP             |\n"
      "|-------------------------|\n"
      "| Local Variables         |\n"
      "| ...                     |\n"
      "|-------------------------|\n\n"
      "When a function is called, a sequence of instructions called the "
      "'function prologue' are set in motion\n"
      "During the function prologue the current value of eip (the instruction "
      "pointer) is pushed onto the stack\n"
      "and becomes what is called the 'return address' in the above diagram. "
      "Then ebp (base pointer) gets set equal to esp (stack pointer).\n"
      "In this way a new, local stack frame is established for the function in "
      "question. After the prologue, the esp is decremented\n"
      "and values are pushed on and popped off the stack to suit the programs "
      "needs. Once execution of a function is complete\n"
      "what is known as the 'function epilogue' happens. The role of the "
      "function epilogue\n"
      "is to restore the previous stack frame. As such it needs to pop the "
      "value of the return address into eip.\n\nSo now I'll give you a buffer, "
      "you have to overflow both the buffer and ebp, and then overflow the "
      "return address\n"
      "with the address of the function 'returnFunction()' (use gdb to find "
      "the address).\n");

  char a[16];
  printf("$ ");
  gets(a);
}

void returnFunction() { system("cat flag.txt"); }
