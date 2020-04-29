/*
** Filename     : student.c for StudGest project
** Made by      : Alexis Pleney, Razvan Stan
** Started on   : 10/12/19 13:27:34
** Description  : Fichier étudiants
*/

#include "studgest.h"

int id = 1;

Student *createStudent(char *firstname, char *lastname, char *class, int promotion) {
  Student *s = malloc(sizeof(Student));

  s->firstname = malloc(sizeof(firstname) * sizeof(char));
  s->lastname = malloc(sizeof(lastname) * sizeof(char));
  s->class = malloc(sizeof(class) * sizeof(char));
  s->promotion = promotion;
  strcpy(s->firstname, firstname);
  strcpy(s->lastname, lastname);
  strcpy(s->class, class);
  s->next = NULL;
  s->id = id;
  id++;

  return s;
}

void freeStudent(Student **s) {
  if ((*s)->course) {
      freeAllCourses(&((*s)->course));
      if ((*s)->course) {
        printf("\n Erreur free course\n");
        exit(1);
      }
    }
  (*s)->id = 0;
  free((*s)->firstname);
  free((*s)->lastname);
  (*s)->promotion = 0;
  free((*s)->class);
  free(*s);
  *s = NULL;
}

void listStudent(ListStudent *list) {
  int choice = 0;
  int promo = 0;

  printf("-- LISTE --\n");
  if (!list)
    printf("Liste vide");
  else {
    printf("1 : Lister les élèves​\n");
    printf("2 : Lister les élèves d’une promotion\n");
    choice = getInt(1, 1, 3, "Choice");
    if (choice == 1) {
      printf("1 : Trier par nom\n");
      printf("2 : Trier par prénom\n");
      printf("3 : Trier par promotion\n");
      printf("4 : Trier par moyenne\n");
      printf("5 : Par default\n");
      choice = getInt(1, 1, 5, "Choice");
      if (choice == 1)
        sortByLastname(list);
      if (choice == 2)
        sortByFirstname(list);
      if (choice == 3)
        sortByPromotion(list);
      if (choice == 4)
        sortByGeneralMeans(list);
      if (choice == 5)
        viewStudents(list);
      choice = 0;
    }
    if (choice == 2) {
      promo = getInt(5, 2010, 2100, "Promotion");
      if (promo != -1)
        showStudentOfOnePromotion(list,promo);
      else
        printf("La promotion n'est pas valide\n");
    }
  }
}

ListStudent *addStudent(ListStudent *list) {
  Student *new;
  char *firstname;
  char *lastname;
  int promotion;
  char *class;

  printf("-- AJOUT ETUDIANT --\n");
  firstname = getString(30, 3, "Prénom");
  lastname = getString(30, 3, "Nom");
  class = getString(10, 10, "Classe");
  promotion = getInt(5, 2010, 2100, "Promotion");
  if (promotion < 2010 || promotion > 2100)
    promotion = 2010;
  new = createStudent(firstname, lastname, class, promotion);

  return createList(list,new);
}

ListStudent *createList(ListStudent *list,Student *new) {
  Student *startList;

  if (!list)
    list = setupFirst(new);
  else {
    startList = list->first;
    while (1) {
      if (startList->next == NULL) {
        startList->next = new; // add the new student at the list
        break;
      }
      startList = startList->next; // next student
    }
  }
  return list;
}

void infoStudent(ListStudent *list) {
  printf("-- DETAIL ETUDIANT --\n");
  Student *student;
  Course *course;
  int id = getInt(1, 1, 1000, "ID Etudiant");
  student = findById(list, id);

  if (student) {
    printf("\n\nID : %d\n", student->id);
    printf("Nom : %s\n", student->lastname);
    printf("Prénom : %s\n", student->firstname);
    printf("Classe : %s\n", student->class);
    printf("Promotion : %d\n", student->promotion);
    printf("%d notes\n", nbOfCourses(student->course));
    if (student->course) {
      printf("Moyenne générale : %0.2f\n",generalMeans(student->course));
      course = student->course;
      while (course != NULL) {
        printf("\nID course : %d nom : %s coef : %d moyen : %0.2f\n",course->idC,course->name,course->coef,way(course->mark));
        printf("%d cours\n", nbOfMarks(course->mark));
        showMarks(course->mark);
        course = course->next;
      }
    }
    else
      printf("\nAucun étudiant ne trouve\n");
  }
}

void addNoteStudent(ListStudent *list) {
  int choice = 0;
  int promo = 0;

  printf("-- AJOUT NOTE --\n");
  if (!list)
    printf("\n-- Pas d'etudiant --\n");
  else {
    printf("1 : Entrez une note pour tous les étudiants\n");
    printf("2 : Entrez une note pour un étudiant\n");
    printf("3 : Entrez une note pour tous les étudiants d'une promotion\n");
    choice = getInt(1, 1, 3, "Choix");

    if (choice == 1)
      addForAll(list);
    if (choice == 2)
      addForOne(list);
    if (choice == 3) {
      promo = getInt(5, 2010, 2100, "Promotion");
      if (promo != -1)
        addForOnePromotion(list, promo);
      else
        printf("La promotion n'est pas valide\n");
    }
  }
}

void freeAll(ListStudent **lists) {
  Student *free;
  Student *next;

  printf("check");
  free = (*lists)->first;
  freeList(&(*lists));
  while (free != NULL) {
    if (free->course) {
      freeAllCourses(&(free->course));
      if (free->course) {
        printf("\n Erreur free course\n");
        exit(1);
      }
    }
    next = free->next;
    freeStudent(&free);
    if (free) {
      printf("\n Erreur free student");
      exit(1);
    }
    free = next;
  }
}

void modChoice(ListStudent *list) {
  Student *tmp;
  Course *tmp2;
  Mark *tmp3;
  int id = 0;
  int choice = 0;

  printf("\n1 : Modifier un élève\n");
  printf("2 : Modifier un cours\n");
  printf("3 : Modifier une note\n");
  choice = getInt(1, 1, 3, "Choix:");
  if (choice > 0 && choice < 4) {
    printf("\n");
    viewStudents(list);
    id = getInt(1, 1, 1000, "ID Etudiant");
    tmp = findById(list, id);
    if (tmp != NULL) {
      if (choice == 1)
        modStudent(tmp);
      else {
        printf("\n");
        showCourses(tmp->course);
        id = getInt(1, 1, 1000, "ID cours");
        tmp2 = findByIdC(tmp->course, id);
        if (tmp2 != NULL) {
          if (choice == 2)
            modCourse(tmp2);
          else {
            showMarks(tmp2->mark);
            printf("\n");
            id = getInt(1, 1, 1000, "ID note");
            tmp3 = findByIdM(tmp2->mark, id);
            if (tmp3 != NULL)
              modMark(tmp3);
            else
              printf("Aucune note trouvée avec l'id %d \n", id);
          }
        }
        else
          printf("Aucun cours trouvé avec l'id %d \n", id);
      }
    }
    else
      printf("Aucun etudiant trouvé avec l'id %d \n", id);
  }
  else
    printf("Erreur: Choix non reconnu\n\n");
}

void modStudent(Student *student) {
  char *firstname;
  char *lastname;
  char *class;
  int promotion;

  menuBanner(31," MODIFICATION ETUDIANT ");
  printf("\n");
  firstname = getString(30, 3, "Prénom");
  lastname = getString(30, 3, "Nom");
  class = getString(10, 10, "Classe");
  promotion = getInt(5, 2010, 2100, "Promotion");
  strcpy(student->firstname, firstname);
  strcpy(student->lastname, lastname);
  strcpy(student->class, class);
  student->promotion = promotion;
  printf("\nModification enregistre !\n");
}
