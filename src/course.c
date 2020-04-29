/*
** Filename     : main.arrRow for StudGest project
** Made by      : Alexis Pleney, Razvan Stan
** Started on   : 18/01/20 00:54:52
** Description  : Fichier course and mark
*/

#include "studgest.h"

Mark *createMark(int coef, float m) {
  Mark *mark = malloc(sizeof(Mark));

  mark->idM = 1;
  mark->coef = coef;
  mark->mark = m;
  mark->next = NULL;
  return mark;
}

Course *createCourse(char *name, int coef) {
  Course *c = malloc(sizeof(Course));

  c->name = malloc(sizeof(name) * sizeof(char));
  c->idC = 1;
  strcpy(c->name,name);
  c->coef = coef;
  c->mark = NULL;
  c->next = NULL;
  return c;
}

void freeMark(Mark **mark) {
  free(*mark);
  if (!(*mark))
    printf("\nFail to free mark");
  *mark = NULL;
}

void freeCourse(Course **c) {
  free((*c)->name);
  free(*c);
  if (!(*c))
    printf("\nFail to free course");
  *c = NULL;
}

Mark *findByIdM(Mark *list,int idM) {
  Mark *m;

  if (list == NULL)
    return NULL;
  m = list;
  while (m !=NULL) {
    if (m->idM == idM)
      return m;
    m = m->next;
  }
  return NULL;
}

Course *findByIdC(Course *list, int idC) {
  Course *c;

  if (list == NULL)
    return NULL;
  c = list;
  while (c !=NULL) {
    if (c->idC == idC)
      return c;
      c = c->next;
  }
  return NULL;
}

Mark *addMark(Mark *mark) {
  Mark *new;
  int coef;
  float grade;

  printf("-- AJOUTER NOTE --\n");
  coef = getInt(1, 1, 5, "Coef ");
  if (coef == -1)
    coef = 1;
  printf("Note :");
  grade = getFloat(5, 0, 20);
  if (grade == -1)
    grade = 1;
  new = createMark(coef, grade);

  return makeListMark(mark, new);
}

Course *addCourse(Course *cs) {
  Course *new;
  int coef;
  char *name;

  printf("-- AJOUTER COURS --\n");
  coef = getInt(1, 1, 5, "Coef");
  if (coef == -1)
    coef = 1;
  name = getString(30, 3, "Nom");
  new = createCourse(name,coef);

  return makeListCourse(cs,new);
}

Mark *lastMark(Mark *grade) {
  Mark *m;

  if (!grade)
    return NULL;

  m = grade;
  while (m != NULL) {
    if (m->next == NULL)
      return m;
    m = m->next;
  }
}

Course *lastCourse(Course *courses) {
  Course *c;

  if (!courses)
    return NULL;

  c = courses;
  while (c !=NULL) {
    if (c->next == NULL)
      return c;
    c = c->next;
  }
}

void showMarks(Mark *grades) {
  Mark *m;

  if (!grades)
    printf("\n-- Aucune note --\n");
  m = grades;
  while (m != NULL) {
    printf("ID note : %d Coef : %d Note : %.2f\n", m->idM, m->coef, m->mark);
    m = m->next;
  }
}

void showCourses(Course *courses) {
  Course *c;

  if (!courses)
    printf("\n-- Pas de cours -- ");
  c = courses;
  while (c != NULL) {
    printf("%d : %s coef : %d\n", c->idC, c->name, c->coef);
    c = c->next;
  }
  printf("\n\n");
}

void addCourseAndMark(Course *course) {
  Course *c;
  course = addCourse(course);
  c = course;
  c = lastCourse(course);
  c->mark = addMark(c->mark);
}

void addForAll(ListStudent *list) {
  Student *s;
  Course *c;
  int choice = -1;

  s = list->first;
  while (s != NULL) {
    printf("Student %s %s %s\n", s->firstname, s->lastname, s->class);
    if (!s->course) {
      s->course = addCourse(s->course);
      s->course->mark = addMark(s->course->mark);
    }
    else {
      printf("\n\n0 : Créer un nouveau cours\n");
      showCourses(s->course);
      choice = getInt(1, 0, 1000, "ID cours");
      if (choice == 0)
        addCourseAndMark(s->course);
      else {
        c = findByIdC(s->course, choice);
        if (!c)
          printf("Pas de cours trouve\n");
        else {
          c->mark = addMark(c->mark);
        }
      }
    }
  choice = -1;
  s = s->next;
  }
}

void addForOne(ListStudent *list) {
  Student *s;
  Course *course;
  int choice = -1;

  s = list->first;
  while (s != NULL) {
    printf("Student id : %d : Nom : %s : Prenom : %s : classe : %s\n",s->id,s->firstname,s->lastname,s->class);
    s = s->next;
  }
  choice = getInt(1, 1, 1000, "ID Student");
  s = findById(list,choice);
  if (s) {
    printf("\n\n0 : Créer un nouveau cours\n");
    showCourses(s->course);
    choice = getInt(1, 0, 1000, "ID cours");
    if (choice == 0) {
      if (s->course)
        addCourseAndMark(s->course);
      else {
        s->course = addCourse(s->course);
        s->course->mark = addMark(s->course->mark);
      }
    }
    else {
      course = findByIdC(s->course, choice);
      if(course) {
        showMarks(course->mark);
        course->mark = addMark(course->mark);
      }else {
        printf("Cours non trouve\n");
      }
    }
  }
}

void addForOnePromotion(ListStudent *list, int promo) {
  Student *s;
  Course *course;
  int choice = -1;
  s = list->first;

  while (s != NULL) {
    if (promo == s->promotion) {
      printf("Student %s %s %s\n", s->firstname, s->lastname, s->class);
      if (!s->course) {
        s->course = addCourse(s->course);
        s->course->mark = addMark(s->course->mark);
      }
      else {
        printf("\n\n0 : Créer un nouveau cours\n");
        showCourses(s->course);
        choice = getInt(1, 0, 1000, "ID cours");
        if (choice == 0)
          addCourseAndMark(s->course);
        else {
          course = findByIdC(s->course, choice);
          if (!course)
            printf("Pas de cours trouve\n");
          else {
            course->mark = addMark(course->mark);
          }
        }
      }
    }
  choice = -1;
  s = s->next;
  }
}

Mark *makeListMark(Mark *mark, Mark *new) {
  Mark *startMark;
  int id = 0;

  if (!mark)
    mark = new;
  else {
    startMark = mark;
    while (1) {
      if (startMark->next == NULL) {
        id = startMark->idM;
        new->idM = ++id;
        startMark->next = new;
        break;
      }
      startMark = startMark->next;
    }
  }
  return mark;
}

Course *makeListCourse(Course *course, Course *new) {
  Course *startCourse;
  int id = 0;

  if (!course)
    course = new;

  else {
    startCourse = course;
    while (1) {
      if (startCourse->next == NULL) {
        id = startCourse->idC;
        new->idC = ++id;
        startCourse->next = new;
        break;
      }
      startCourse = startCourse->next;
    }
  }
  return course;
}

float way(Mark *list) {
  int coef = 0;
  float sum = 0;

  if (!list)
    return 0;

  while (list != NULL) {
    sum += list->coef * list->mark;
    coef += list->coef;
    list = list->next;
  }

  return sum / coef;
}

float generalMeans(Course *list) {
  int coef = 0;
  float sum = 0;

  if (!list)
    return 0;

  while (list !=NULL) {
    coef += list->coef;
    sum += way(list->mark) * list->coef;
    list = list->next;
  }

  return sum / coef;
}

float generalMeansClass(ListStudent *list, const char *class) {
  Student *startList;
  float sum = 0;
  int counter = 0;
  startList = list->first;

  while (startList != NULL) {
    if (strcmp(startList->class, class) == 0) {
      sum += generalMeans(startList->course);
      counter++;
    }
    startList = startList->next;
  }

  return sum / counter;
}

void freeAllMarks(Mark **lists) {
  Mark *m;

  while (*lists != NULL) {
    m = (*lists)->next;
    freeMark(&(*lists));
    if (*lists) {
      printf("\n Error free of mark 2!");
      exit(1);
    }
    *lists = m;
  }
}

void freeAllCourses(Course **lists) {
  Course *c;

  while (*lists != NULL) {
    if ((*lists)->mark) {
      freeAllMarks(&((*lists)->mark));
      if ((*lists)->mark) {
        printf("\n Error free of mark 1!\n");
        exit(1);
      }
    }
    c = (*lists)->next;
    freeCourse(&(*lists));
    if (*lists) {
      printf("\n Error free of course");
      exit(1);
    }
    *lists = c;
  }
}

void modCourse(Course *cs) {
  int coef;
  char *name;

  menuBanner(31, "Modifier un cours ");
  coef = getInt(1, 1, 5, "Coef");
  if (coef == -1)
    coef = 1;
  name = getString(30, 3, "Nom");
  cs->coef = coef;
  strcpy(cs->name, name);
  printf("\nModification enregistre !\n");
}


void modMark(Mark *m) {
  int coef;
  float grade;

  menuBanner(31, "Modifier une note ");
  coef = getInt(1, 1, 5, "Coef ");
  if (coef == -1)
    coef = 1;
  printf("Note :");
  grade = getFloat(5, 0, 20);
  if (grade == -1)
    grade = 0;
  m->coef = coef;
  m->mark = grade;
  printf("\nModification enregistre !\n");
}
