/*
** Filename     : draw.c for StudGest project
** Made by      : Alexis Pleney, Razvan Stan
** Started on   : 10/12/19 18:57:22
** Description  : Fichier d'affichage menu
*/

#include "studgest.h"

void drawArrBar(int cols, int *width) {
  for (int i = 0; i < cols; i++) {
    printf("+");
    repeatChar('-', width[i]);
  }
  printf("+\n");
}

void drawCell(int i, char *str, int width) {
  int len;

  printf("|");
  if (str != NULL)
    len = (width - strlen(str)) / 2;
  else if (i != -1) {
    len = (width - intlen(i)) / 2;
    str = itoa(i);
  }
  else
    strcpy(str, "error");

  for (int j = 0; j < len; j++)
    printf(" ");
  printf("%s", str);
  if (checkIfStrOdd(width, str) == 0)
    len += 1;
  for (int j = 0; j < len; j++)
    printf(" ");
}

void drawArrHead(int cols, int rows, int *width, int len, char head[][MAX_COLS_LEN]) {
  drawArrBar(cols, width);
 
  for (int i = 0; i < cols; i++)
    drawCell(-1, head[i], width[i]);
  printf("|\n");
  drawArrBar(cols, width);
}

void drawArrBody(int cols, int rows, int *width, Student *s) {
  for (int i = 0; i < rows; i++) {
    drawCell(s->id, NULL, width[0]);
    drawCell(-1, s->firstname, width[1]);
    drawCell(-1, s->lastname, width[2]);
    drawCell(-1, s->class, width[3]);
    drawCell(s->promotion, NULL, width[4]);
    printf("|\n");
    s = s->next;
  }
  drawArrBar(cols, width);
}

void drawMenuBar(int size) {
  printf("+");
  repeatChar('-', size);
  printf("+\n");
}

void drawMenuRow(int size) {
  printf("|");
  repeatChar(' ', size);
  printf("|\n");
}

void drawMenuText(int width, char *text) {
  int len = (width - strlen(text)) / 2;
  printf("|");
  repeatChar(' ', len);
  printf(text);
  repeatChar(' ', len);
  printf("|\n");
}

void menuBanner(int width, char *text) {
  width -= 2;
  drawMenuBar(width);
  drawMenuRow(width);
  drawMenuText(width, text);
  drawMenuRow(width);
  drawMenuBar(width);
}

void menuText() {
  printf("    --- MENU ---\n");
  printf("1: Lister élèves\n");
  printf("2: Ajouter élève\n");
  printf("3: Supprimer élève\n");
  printf("4: Modifier élève\n");
  printf("5: Ajouter note\n");
  printf("6: Details élève\n");
  printf("7: Sauvegarder\n");
  printf("8: Charger\n");
  printf("9: Quitter\n\n");
}
