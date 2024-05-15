#include "my_grep.h"

int main(int argc, char **argv) {
  if (argc > 1) {
    struct flags flag = {0};
    struct templates template = {
        .count = 0,
        .pattern = NULL,
    };
    check_option(argc, argv, &template, &flag);
    if (!flag.e) {
      if (optind < argc) {
        add_template(argv[optind++], &template, &flag);
      }
    }
    if (argc - optind > 1) {
      flag.files = 1;
    }
    for (int i = optind; i < argc; i++) {
      grep_file(argv[i], &template, &flag);
    }
    if (template.count > 0) {
      free_memory(&template);
    }
  }
  return 0;
}

void check_option(int argc, char **argv, struct templates *template,
                  struct flags *flag) {
  int option;
  while ((option = getopt_long(argc, argv, "e:ivclnhsf:o", NULL, NULL)) != -1) {
    switch (option) {
      case 'e':
        flag->e = 1;
        add_template(optarg, template, flag);
        break;
      case 'i':
        flag->i = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      case 'c':
        flag->c = 1;
        break;
      case 'l':
        flag->l = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 'h':
        flag->h = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 'f':
        flag->f = 1;
        flag->e = 1;
        add_template_file(optarg, template, flag);
        break;
      case 'o':
        flag->o = 1;
        break;
      default:
        exit(1);
    }
  }
}

void add_template_file(char *filename, struct templates *template,
                       struct flags *flag) {
  size_t len = 0;
  char *str = NULL;
  FILE *fp = fopen(filename, "r");
  if (fp) {
    while (getline(&str, &len, fp) != EOF) {
      if (str) {
        if (str[strlen(str) - 1] == '\n') {
          str[strlen(str) - 1] = '\0';
        }
      }
      add_template(str, template, flag);
    }
  }
  if (fp) fclose(fp);
  if (str) free(str);
}

void add_template(char *str, struct templates *template, struct flags *flag) {
  const char *error;
  int erroffset;
  pcre *re = pcre_compile(str, ((flag->i) ? PCRE_CASELESS : 0), &error,
                          &erroffset, NULL);
  if (re) {
    template->count++;
    template->pattern =
        realloc(template->pattern, template->count * sizeof(pcre *));
    template->pattern[template->count - 1] = re;
  }
}

void free_memory(struct templates *template) {
  if (template->pattern) {
    for (int i = 0; i < template->count; i++) {
      if (template->pattern[i]) pcre_free(template->pattern[i]);
    }
    free(template->pattern);
  }
}

void grep_file(char *filename, struct templates *template, struct flags *flag) {
  int filecnt = 0;
  size_t len = 0;
  char *str = NULL;
  FILE *fp = fopen(filename, "r");
  int ovector[30];
  int strnum = 0;
  int end = 0;
  int strcol = 0;
  int strcnt = 0;
  if (fp) {
    if (flag->c) {
      while (getline(&str, &len, fp) != EOF) {
        strcol++;
        for (int i = 0; (i < template->count); i++) {
          if ((pcre_exec(template->pattern[i], NULL, str, strlen(str), 0, 0,
                         ovector, 30)) > 0) {
            strcnt++;
          }
        }
      }
      if (strcnt > 0 || ((strcol - strcnt) > 0 && flag->v)) {
        filecnt = 1;
      }
      if (flag->files && !flag->h) {
        printf("%s:", filename);
      }
      if (flag->l) {
        printf("%d\n", filecnt);
      } else {
        printf("%d\n", (flag->v ? strcol - strcnt : strcnt));
      }
    }

    if (flag->l) {
      fseek(fp, 0, 0);
      while (getline(&str, &len, fp) != EOF) {
        for (int i = 0; i < template->count && !end; i++) {
          if (((flag->v ? -1 : 1) * pcre_exec(template->pattern[i], NULL, str,
                                              strlen(str), 0, 0, ovector, 30)) >
              0) {
            printf("%s\n", filename);
            end = 1;
          }
        }
      }
    } else if (flag->o && !flag->v) {
      while ((getline(&str, &len, fp) != EOF)) {
        strnum++;
        for (int i = 0; (i < template->count); i++) {
          unsigned int offset = 0;
          len = strlen(str);
          int rc;
          while (offset < len &&
                 (rc = pcre_exec(template->pattern[i], 0, str, strlen(str),
                                 offset, 0, ovector, 30)) > 0) {
            for (int j = 0; j < rc; ++j) {
              if (flag->files && !flag->h) {
                printf("%s:", filename);
              }
              if ((flag->n)) {
                printf("%d:", strnum);
              }

              for (size_t k = ((ovector[2 * j] > 0) ? ovector[2 * j] : 0);
                   k < (strlen(str) < (size_t)ovector[2 * j + 1]
                            ? strlen(str)
                            : (size_t)ovector[2 * j + 1]);
                   k++) {
                printf("%c", str[k]);
              }
              printf("\n");
            }
            offset = ovector[1];
          }
        }
      }
    } else {
      while (getline(&str, &len, fp) != EOF) {
        end = 0;
        strnum++;
        for (int i = 0; (i < template->count) && (!end); i++) {
          if ((pcre_exec(template->pattern[i], NULL, str, strlen(str), 0, 0,
                         ovector, 30)) > 0) {
            end = 1;
          }
        }
        if (flag->v) end = !end;
        if (end) {
          if (flag->files && !flag->h) {
            printf("%s:", filename);
          }
          if ((flag->n)) {
            printf("%d:", strnum);
          }
          printf((str[strlen(str) - 1] == '\n' ? "%s" : "%s\n"), str);
        }
      }
    }
  } else {
    if (!flag->s) fprintf(stderr, "No such file: %s\n", filename);
  }
  if (fp) fclose(fp);
  if (str) free(str);
}