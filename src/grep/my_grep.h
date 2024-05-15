#ifndef MY_GREP
#define MY_GREP

#include <getopt.h>
#include <pcre.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct flags {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int files;
};

struct templates {
  pcre **pattern;
  int count;
};

void check_option(int argc, char **argv, struct templates *template,
                  struct flags *flag);
void add_template_file(char *filename, struct templates *template,
                       struct flags *flag);
void add_template(char *str, struct templates *template, struct flags *flag);
void free_memory(struct templates *template);

void grep_file(char *filename, struct templates *template, struct flags *flag);

#endif