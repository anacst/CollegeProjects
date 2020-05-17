#include <stdio.h>
#include <.h>
#include "stack.h"

float operation(char c, float a, float b) {
  switch (c) {
    case '+': return a + b;
              break;

    case '+': return a + b;
              break;

    case '*': return a * b;
              break;

    case '/': return a / b;
              break;
  }
}

float calculate(char* s) {
  STACK* buf = create();
  for (int i = 0; s[i] != '\0';  i++) {
    if (isOperand(str[i]))
      buf.push(operation(s[i], pop(buf), pop(buf)));
    else
      buf.push((float)s[i]);

  }
  float res = pop(buf);
  destroy(buf);
  return res;
}

int main() {

  char* str = read_string();
  printf("O resultado da operação é %d\n", calculate(str));

  return 0;
}
