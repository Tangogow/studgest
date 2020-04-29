/*
** Filename     : file.c for StudGest project
** Made by      : Alexis Pleney, Razvan Stan
** Started on   : 10/12/19 13:27:34
** Description  : Fichier de gestion des fichiers sauvegarde
*/

#include "studgest.h"

void saveFile(ListStudent *list) {
  char *filename;

  printf("-- SAUVEGARDE --\n");
  if (list == NULL) {
    printf("Liste vide, sauvegarde annulé\n");
    backToMenu();
  }
  filename = getString(30, 2, "Nom fichier sauvegarde");
  while (doesFileExist(filename) != -1) {
    checkBackToMenu(filename);
    printf("Erreur: Fichier '%s' existe déjà\n", filename);
    filename = getString(30, 2, "Nom fichier sauvegarde");
  }

  writeFile(filename, structToJSON(list), "w");
  printf("Sauvegarde effectué dans '%s'\n", filename);
  backToMenu();
}

ListStudent *loadFile(ListStudent *list) {
  char *filename;
  char *buf = malloc(LOADFILE_SIZE);

  printf("-- CHARGEMENT --\n");
  filename = getString(30, 2, "Fichier à charger");
  while (doesFileExist(filename) == -1) {
    checkBackToMenu(filename);
    printf("Erreur: Fichier '%s' n'existe pas\n", filename);
    filename = getString(30, 2, "Fichier à charger");
  }
  readFile(filename, buf);
  printf("Fichier '%s' chargé\n", filename);
  return JSONToStruct(buf, list);
}
