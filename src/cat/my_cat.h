#ifndef MY_CAT
#define MY_CAT

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

struct flags {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
};

void check_option(int argc, char **argv, struct flags *flag);
void cat_print(char **argv, struct flags *flag);

void option_N(int *q, char *new_string, char *flag_string);
void option_B(char value, int *q, char *new_string);
void option_E(char value, char *flag_string);
void option_T(char *value);
void option_S(char value, char new_string, char *flag_string);
void option_V(char *value);

#endif