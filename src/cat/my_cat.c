#include "my_cat.h"

int main(int argc, char **argv) {
  if (argc > 1) {
    struct flags flag = {0};
    check_option(argc, argv, &flag);
    cat_print(argv, &flag);
  }
  return 0;
}

void check_option(int argc, char **argv, struct flags *flag) {
  struct option long_options[] = {{"number", 0, 0, 'n'},
                                  {"number-nonblank", 0, 0, 'b'},
                                  {"squeeze-blank", 0, 0, 's'},
                                  {0, 0, 0, 0}};
  int option;
  while ((option = getopt_long(argc, argv, "beEnstTv", long_options, NULL))) {
    if (option == -1) break;
    switch (option) {
      case 'b':
        flag->b = 1;
        break;
      case 'e':
        flag->e = 1;
        flag->v = 1;
        break;
      case 'E':
        flag->e = 1;
        flag->v = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 't':
        flag->t = 1;
        flag->v = 1;
        break;
      case 'T':
        flag->t = 1;
        flag->v = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      default:
        exit(1);
    }
  }
}

void cat_print(char **argv, struct flags *flag) {
  FILE *fp;
  int i = optind;

  while (argv[i]) {
    if ((fp = fopen(argv[i], "r")) == NULL) {
      fprintf(stderr, "No such file or directory");
      exit(1);
    } else {
      char cur;
      int q = 1;
      char new_string = 1;
      char flag_string = 0;
      while ((cur = fgetc(fp)) != EOF) {
        if (flag->s) {
          option_S(cur, new_string, &flag_string);
        }
        if (flag->b) {
          option_B(cur, &q, &new_string);
          flag->n = 0;
        }
        if (flag->n) {
          option_N(&q, &new_string, &flag_string);
        }
        if (flag->t) {
          option_T(&cur);
        }
        if (flag->e) {
          option_E(cur, &flag_string);
        }
        if (flag->v) {
          option_V(&cur);
        }

        if (cur != '\n') {
          new_string = 0;
        } else {
          new_string = 1;
        }

        if (flag_string != 2) {
          printf("%c", cur);
        }
      }
    }
    i++;
    fclose(fp);
  }
}

void option_N(int *q, char *new_string, char *flag_string) {
  if (*new_string == 1 && *flag_string != 2) {
    printf("%6d\t", *q);
    *q += 1;
  }
}

void option_B(char value, int *q, char *new_string) {
  if (value != '\n' && *new_string == 1) {
    printf("%6d\t", *q);
    *q += 1;
  }
}

void option_E(char value, char *flag_string) {
  if (value == '\n' && *flag_string != 2) {
    printf("$");
  }
}

void option_T(char *value) {
  if (*value == '\t') {
    printf("^");
    *value += 64;
  }
}

void option_S(char value, char new_string, char *flag_string) {
  if (value == '\n' && new_string == 1) {
    if (value == '\n' && *flag_string > 0) {
      *flag_string = 2;
    } else {
      *flag_string = 1;
    }
  } else {
    *flag_string = 0;
  }
}

void option_V(char *value) {
  if (*value >= 0 && *value <= 31 && *value != 10 && *value != 9) {
    printf("^");
    *value += 64;
  } else if (*value == 127) {
    printf("^");
    *value = 63;
  }
}