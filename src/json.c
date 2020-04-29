/*
** Filename     : json.c for StudGest project
** Made by      : Alexis Pleney, Razvan Stan
** Started on   : 19/12/19 19:00:13
** Description  : Fichier Parser JSON
*/

#include "studgest.h"

cJSON *isObjNull(cJSON *obj) {
  if (obj == NULL) {
    printf("Erreur, fichier incorrect ou corrumpu");
    backToMenu();
  }
  else
    return obj;
}

ListStudent *JSONToStruct(char *buf, ListStudent *list) {
  cJSON *root = cJSON_Parse(buf);
  Student *s = NULL;
  Course *c = NULL;
  Mark *m = NULL;

  cJSON *title = isObjNull(cJSON_GetObjectItem(root, "title"));
  if (list != NULL) {
    printf("Liste: '%s' détécté\n", title->valuestring);
    char *input = getString(1, 1, "Fusionner la liste et la liste locale ? [y/n]");
    if (input[0] == 'n')
      freeAll(&list);
  }
  cJSON *arrStudent = isObjNull(cJSON_GetObjectItem(root, "student"));

  int i = 0;
  cJSON *S = NULL;
  cJSON_ArrayForEach(S, arrStudent) {
    cJSON *student = isObjNull(cJSON_GetArrayItem(arrStudent, i));
    cJSON *idS = isObjNull(cJSON_GetObjectItem(student, "idS"));
    cJSON *first = isObjNull(cJSON_GetObjectItem(student, "first"));
    cJSON *last = isObjNull(cJSON_GetObjectItem(student, "last"));
    cJSON *prom = isObjNull(cJSON_GetObjectItem(student, "prom"));
    cJSON *class = isObjNull(cJSON_GetObjectItem(student, "class"));
    s = createStudent(first->valuestring, last->valuestring, class->valuestring, prom->valueint);
    list = createList(list, s);
    cJSON *arrCourses = cJSON_GetObjectItem(student, "courses");

    int j = 0;
    cJSON *C = NULL;
    cJSON_ArrayForEach(C, arrCourses) {
      cJSON *course = isObjNull(cJSON_GetArrayItem(arrCourses, j));
      cJSON *idC = isObjNull(cJSON_GetObjectItem(course, "idC"));
      cJSON *nameC = isObjNull(cJSON_GetObjectItem(course, "nameC"));
      cJSON *coefC = isObjNull(cJSON_GetObjectItem(course, "coefC"));
      cJSON *arrMarks = cJSON_GetObjectItem(course, "marks");
      c = makeListCourse(c, createCourse(nameC->valuestring, coefC->valueint));

      int k = 0;
      cJSON *M = NULL;
      cJSON_ArrayForEach(M, arrMarks) {
        cJSON *marks = cJSON_GetArrayItem(arrMarks, k);
        cJSON *idM = isObjNull(cJSON_GetObjectItem(marks, "idM"));
        cJSON *coefM = isObjNull(cJSON_GetObjectItem(marks, "coefM"));
        cJSON *mark = isObjNull(cJSON_GetObjectItem(marks, "mark"));
        m = makeListMark(m, createMark(coefM->valueint, mark->valuedouble));
        k++;
      }
      c->mark = m;
      m = NULL;
      j++;
    }
    s->course = c;
    c = NULL;
    i++;
	}
  end:
  cJSON_Delete(root);

  return list;
}

char *structToJSON(ListStudent *list) {
  cJSON *monitor = cJSON_CreateObject();
  char *string = NULL;
  Student *s;
  Course *c;
  Mark *m;

  char *input = getString(20, 1, "Nom de la liste");
  int nbStudents = nbOfStudent(list);
  s = list->first;

  cJSON_AddStringToObject(monitor, "title", input);
  for (int i = 0; i < nbStudents; i++) {
    cJSON *arrStudent = cJSON_CreateArray();
    cJSON *arrCourses = cJSON_CreateArray();
    cJSON *arrMarks = cJSON_CreateArray();

    cJSON *student = cJSON_CreateObject();
    cJSON_AddItemToObject(monitor, "student", arrStudent);
    cJSON_AddNumberToObject(student, "idS", s->id);
    cJSON_AddStringToObject(student, "first", s->firstname);
    cJSON_AddStringToObject(student, "last", s->lastname);
    cJSON_AddNumberToObject(student, "prom", s->promotion);
    cJSON_AddStringToObject(student, "class", s->class);
    cJSON_AddItemToObject(student, "courses", arrCourses);

    int nbCourses = nbOfCourses(s->course);
    cJSON *courses[nbCourses];
    c = s->course;

    for (int j = 0; j < nbCourses; j++) {
      int nbMarks = nbOfMarks(c->mark);
      cJSON *marks[nbMarks];
      m = c->mark;

      courses[j] = cJSON_CreateObject();
      cJSON_AddNumberToObject(courses[j], "idC", c->idC);
      cJSON_AddStringToObject(courses[j], "nameC", c->name);
      cJSON_AddNumberToObject(courses[j], "coefC", c->coef);
      cJSON_AddItemToObject(courses[j], "marks", arrMarks);

      for (int k = 0; k < nbMarks; k++) {
        marks[k] = cJSON_CreateObject();
        cJSON_AddNumberToObject(marks[k], "idM", m->idM);
        cJSON_AddNumberToObject(marks[k], "coefM", m->coef);
        cJSON_AddNumberToObject(marks[k], "mark", m->mark);
        cJSON_AddItemToArray(arrMarks, marks[k]);
        m = m->next;
      }
      cJSON_AddItemToArray(arrCourses, courses[j]);
      c = c->next;
    }
    cJSON_AddItemToArray(arrStudent, student);
    s = s->next;
  }
  string = cJSON_Print(monitor);
  if (string == NULL) {
    fprintf(stderr, "Failed to print monitor.\n");
  }

  end:
  cJSON_Delete(monitor);
  return string;
}
