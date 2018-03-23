//test case 1 for project 2

#include <stdio.h>
#include <stdlib.h>
#include "uthread.h"

void threadFunc(int);

int* returnValue;

int main() {
  printf("testing starts ....\n");
  uthread_init();
  uthread_create(threadFunc, 1, 0);       
  uthread_yield();
  printf("back to main\n");
  uthread_exit(&returnValue);
  return 0;
}

void threadFunc(int val) {
  printf("in threadFunc with value %d\n", val);
  uthread_yield();
}
