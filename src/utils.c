/*
** Filename     : utils.c for StudGest project
** Made by      : Alexis Pleney, Razvan Stan
** Started on   : 10/12/19 21:14:34
** Description  : Fichier fonctions utilitaires
*/

#include "studgest.h"

int checkIfStrOdd(int width, char *str) {
  if ((width % 2 != 0 && strlen(str) % 2 == 0) || (width % 2 == 0 && strlen(str) % 2 != 0))
    return 0;
  else
    return 1;
}

char *itoa(int i) {
  char *str = malloc(intlen(i) * sizeof(char));

  snprintf(str, sizeof(str), "%d", i);
  return str;
}

int doesFileExist(char *filename) {
  return access(filename, F_OK);
}

void repeatChar(char c, int n) {
  for (int i = 0; i < n; i++)
    printf("%c", c);
}

int getMax(int old, int new) {
  if (old > new)
    return old;
  else
    return new;
}

void *initArr(int *arr, int size) {
  for (int i = 0; i < size; i++)
    arr[i] = 0;
  return arr;
}

int floatlen(float i) { /*without .00*/
  return floor(log10(abs(i))) + 1;
}

int intlen(int i) {
  return floor(log10(abs(i))) + 1;
}

int isStringEmpty(char *str) {
  if (str[0] == '\0')
    return 0;
  else
    return 1;
}

int stringIsInt(char *str) {
  int len = strlen(str);

  for (int i = 0; i < len; i++) {
    if (!isdigit(str[i]))
      return -1;
  }
  return 0;
}

int stringIsFloat(char *str) {
  int len = strlen(str);

  for (int i = 0; i < len; i++) {
    if (!isdigit(str[i]) && str[i] != '.')
      return -1;
  }
  return 0;
}

void clearBuffer() {
  int c = 0;
  while (c != '\n' && c != EOF)
    c = getchar();
}

char getChar() {
  char *str;
  str = getString(1, 1, "");
  return str[0];
}

char *getString(int len, int min, char *text) {
  len += 1;
  char input[len];
  char *pos = NULL;

  if (isStringEmpty(text))
    printf("%s : ", text);
  if (fgets(input, len, stdin) != NULL) {
    pos = strchr(input, '\n');
    if (pos != NULL)
      *pos = '\0';
    else
      clearBuffer();
  }
  else
    clearBuffer();

  return strdup(input);
}

float getFloat(int len, int min, int max) {
  len += 1;
  char input[len];
  float choice = -1.0;
  char *pos = NULL;

  while (choice < 0) {
    if (fgets(input, len, stdin) != NULL) {
      pos = strchr(input, '\n');
      if (pos != NULL)
        *pos = '\0';
      else
        clearBuffer();
    }
    else
      clearBuffer();

    if (stringIsFloat(input) == 0) {
      choice = atof(input);
      if (choice < min || choice > max)
        choice = -1;
    }
    if (choice == -1)
      return -1;
  }
  return choice;
}

int getInt(int len, int min, int max, char *text) {
  len += 3;
  char input[len];
  int choice = -1;
  char *pos = NULL;

  if (isStringEmpty(text))
    printf("%s: ", text);
  while (choice < 0) {
    if (fgets(input, len, stdin) != NULL) {
      pos = strchr(input, '\n');
      if (pos != NULL)
        *pos = '\0';
      else
        clearBuffer();
    }
    else
      clearBuffer();

    if (stringIsInt(input) == 0) {
      choice = atoi(input);
      if (choice < min || choice > max)
        choice = -1;
    }
    if (choice == -1)
      return -1;
  }
  return choice;
}

void *fmalloc(int size) {
  void *buf;

  if (buf = malloc(sizeof(char) * (size + 1)) == NULL)
    error(1, 12, "Malloc error");
  return buf;
}

char *readFile(const char *name, char *buf) {
  FILE *fp;
  long len;

  if ((fp = fopen(name, "r")) != NULL) {
    if (fseek(fp, 0, SEEK_END) != 0)
      error(1, 1, "fseek end");
    if ((len = ftell(fp)) == -1)
      error(1, 1, "ftell err");
    if (fseek(fp, 0, SEEK_SET) != 0)
      error(1, 1, "fseek set");
    //buf = malloc(len * sizeof(char));
    fread(buf, sizeof(char), len, fp);
    fclose(fp);
  }
  else
    error(1, 2, "Chemin ou nom de fichier incorrect");
  return buf;
}

void writeFile(const char *name, const char *str, char *mode) {
  FILE *fp;

  if ((fp = fopen(name, mode)) != NULL) {
    fputs(str, fp);
    fclose(fp);
  }
}
