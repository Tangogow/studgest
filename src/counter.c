/*
** Filename     : counter.c for StudGest project
** Made by      : Alexis Pleney, Razvan Stan
** Started on   : 07/02/20 19:43:21
** Description  : Fichier des compteurs
*/

#include "studgest.h"

int nbOfStudent(ListStudent *list) {
	int i = 0;

  Student *tmp = list->first;
	while (tmp != NULL) {
		++i;
		tmp = tmp->next;
	}
	return i;
}

int nbOfMarks(Mark *list) {
	int i = 0;

	while (list != NULL) {
		i++;
		list = list->next;
	}
  return i;
}

int nbOfCourses(Course *list) {
	int i = 0;

	while (list != NULL) {
		i++;
		list = list->next;
	}
	return i;
}
