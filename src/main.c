/*
** Filename     : main.c for StudGest project
** Made by      : Alexis Pleney, Razvan Stan
** Started on   : 10/12/19 13:27:34
** Description  : Fichier Main
*/

#include "studgest.h"

ListStudent *list = NULL;

void clearScreen() {
  system(CLEAR);
  usleep(100000);
}

void quit() {
  if (list)
    freeAll(&list);
  printf("Quitter\n");
  exit(0);
}

void checkBackToMenu(char *buf) {
  if (strcmp(buf, "r") == 0) {
   clearScreen();
   menu();
  }
  else if (strcmp(buf, "q") == 0)
   quit();
}

void backToMenu() {
  printf("\n\nr = retour, q = quitter\n");
  char input = getChar();

  while (input != 'r' && input != 'q') {
    printf("r = retour, q = quitter\n");
    input = getChar();
  }
  if (input == 'r') {
    clearScreen();
    menu();
  }
  else if (input == 'q')
    quit();
}

void menu() {
  menuText();
  int choice = 0;

  while (choice < 1 || choice > 7) {
    choice = getInt(1, 1, 9, "Entrez votre choix");
    switch (choice) {
      case 1:
        listStudent(list);
        backToMenu();
        break;
      case 2:
        list = addStudent(list);
        backToMenu();
        break;
      case 3:
        delStudent(&list);
        backToMenu();
        break;
      case 4:
        modChoice(list);
        backToMenu();
        break;
      case 5:
        addNoteStudent(list);
        backToMenu();
        break;
      case 6:
        infoStudent(list);
        backToMenu();
        break;
      case 7:
        saveFile(list);
        backToMenu();
        break;
      case 8:
        list = loadFile(list);
        backToMenu();
        break;
      case 9:
        quit();
        break;
      default:
        clearScreen();
        printf("Erreur: Choix non reconnu\n\n");
        menu();
        break;
      }
  }
}

int main(int ac, char **av) {
  clearScreen();
  menuBanner(30, "Student Manager ");

  menu();
	//config(); // Fichier de config
	return 0;
}
