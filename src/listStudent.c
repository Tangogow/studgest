/*
** Filename     : ListStudent.c for StudGest project
** Made by      : Alexis Pleney, Razvan Stan
** Started on   : 10/12/19 13:27:34
** Description  : Fichier Etudiant
*/

#include "studgest.h"

ListStudent *setupFirst(Student *student) {
  ListStudent *s = malloc(sizeof(ListStudent));
  s->first = student;

  return s;
}

void freeList(ListStudent **list) {
  free(*list);
  *list = NULL;
}

void viewStudents(ListStudent *firstStudent) {
  int cols = 5;
  int rows = nbOfStudent(firstStudent);
  int len = 10;
  char head[cols][len];
  int width[cols];

  strcpy(head[0], "ID");
  strcpy(head[1], "Prenom");
  strcpy(head[2], "Nom");
  strcpy(head[3], "Classe");
  strcpy(head[4], "Promotion");
  width[0] = 5;
  width[1] = 15;
  width[2] = 15;
  width[3] = 10;
  width[4] = 15;

  menuBanner(31,"Liste des etudiants");
  drawArrHead(cols, rows, width, 100, head);
  drawArrBody(cols, rows, width, firstStudent->first);
}

ListStudent *findById(ListStudent *list, int id) {
  Student *s;

  if (list == NULL)
    return NULL;
  s = list->first;
  while (s !=NULL) {
    if (s->id == id)
      return s;
    s = s->next;
  }
  return NULL;
}

void delStudent(ListStudent **lists) {
  if (!(*lists))
    printf("Il n'y a toujours pas de dossier d'etudiant\n");
  else {
    Student *previous;
    Student *s;

    printf("\n-- SUPPRESSION ETUDIANT --\n");
    int id = getInt(1, 1, 100, "Id");
    if ((*lists)->first->id == id) {
      if ((*lists)->first->next == NULL) {
        freeStudent(&((*lists)->first));
        freeList(&(*lists));
      }
      else {
       s = (*lists)->first->next;
       freeStudent(&((*lists)->first));
       (*lists)->first = s;
      }
    }
    else {
      s = (*lists)->first->next;
      previous = (*lists)->first;
      while (s != NULL) {
        if (s->id == id) {
          if (s->next != NULL) {
            previous->next = s->next;
            freeStudent(&s);
            break;
          }
          else {
            freeStudent(&s);
            previous->next = NULL;
            break;
          }
        }
        previous = s;
        s = s->next;
      }
    }
    printf("\n-- SUPPRESSION REUSSIE --\n");
  }
}

void showStudentOfOnePromotion(ListStudent *list, int promo) {
  Student *s;
  int count = 0;

  printf("\n");
  s = list->first;
  while (s != NULL) {
    if (s->promotion == promo) {
      count++;
    }
    s = s->next;
  }
  printf("%d\n", count);
  Student *array[count];
  int i = 0;
  s = list->first; // first student of the list
  while (s != NULL) { // view all of the list
    if(s->promotion == promo) {
      array[i] = s;
      i++;
    }
    s = s->next;
  }
  viewStudent(array,count);
}

void viewStudent(Student *student[],int rows) {
  int cols = 6;
  int len = 10;
  char head[cols][len];
  int width[cols];

  strcpy(head[0], "ID");
  strcpy(head[1], "Prenom");
  strcpy(head[2], "Nom");
  strcpy(head[3], "Classe");
  strcpy(head[4], "Promotion");
  strcpy(head[5], "Moyenne generale");
  width[0] = 5;
  width[1] = 15;
  width[2] = 15;
  width[3] = 10;
  width[4] = 15;
  width[5] = 20;

  menuBanner(31,"Liste des etudiants");
  drawArrHead(cols, rows, width, len, head);
  drawArrBody2(cols, rows, width, student);
}

void sortByFirstname(ListStudent *list) {
  int count = nbOfStudent(list);
  Student *students[count];
  Student *s = list->first;
  int i = 0;

  while (s != NULL) {
    students[i]=s;
    i++;
    s = s->next;
  }

  s = NULL;
  for (i = 0; i < count; i++) {
    for (int j = i + 1; j < count; j++) {
      if (strcoll(students[i]->firstname,students[j]->firstname) > 0) {
        s = students[i];
        students[i] = students[j];
        students[j] = s;
      }
    }
  }
  viewStudent(students,count);
}

void sortByLastname(ListStudent *list) {
  int count = nbOfStudent(list);
  Student *students[count];
  Student *s = list->first;
  int i = 0;

  while (s != NULL) {
    students[i]=s;
    i++;
    s = s->next;
  }

  s = NULL;
  for (i = 0; i < count; i++) {
    for (int j = i + 1; j < count; j++) {
      if (strcoll(students[i]->lastname,students[j]->lastname) > 0) {
        s = students[i];
        students[i] = students[j];
        students[j] = s;
      }
    }
  }
  viewStudent(students,count);
}

void sortByGeneralMeans(ListStudent *list) {
  int count = nbOfStudent(list);
  Student *students[count];
  Student *s = list->first;
  int i = 0;
  float mean1, mean2;

  while (s != NULL) {
    students[i]=s;
    i++;
    s = s->next;
  }

  s = NULL;
  for (i = 0; i < count; i++) {
    mean1 = generalMeans(students[i]->course);
    for (int j = i + 1; j < count; j++) {
      mean2 = generalMeans(students[j]->course);
      if (mean1 < mean2) {
        s = students[i];
        students[i] = students[j];
        students[j] = s;
      }
    }
  }
  viewStudent(students,count);
}

void sortByPromotion(ListStudent *list) {
  int count = nbOfStudent(list);
  Student *students[count];
  Student *s = list->first;
  int i = 0;

  while (s != NULL) {
    students[i] = s;
    i++;
    s = s->next;
  }

  s = NULL;
  for (i = 0; i < count; i++) {
    for (int j = i + 1; j < count; j++) {
      if (students[i]->promotion > students[j]->promotion) {
        s = students[i];
        students[i] = students[j];
        students[j] = s;
      }
    }
  }
  viewStudent(students,count);
}

void drawArrBody2(int cols, int rows, int *width, Student *s[]) {
  for (int i = 0; i < rows; i++) {
    drawCell(s[i]->id, NULL, width[0]);
    drawCell(-1, s[i]->firstname, width[1]);
    drawCell(-1, s[i]->lastname, width[2]);
    drawCell(-1, s[i]->class, width[3]);
    drawCell(s[i]->promotion, NULL, width[4]);
    if (s[i]->course) {
      drawCell(generalMeans(s[i]->course), NULL, width[5]);
    }
    printf("|\n");
  }
  drawArrBar(cols, width);
}
