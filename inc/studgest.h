/*
** Filename     : studgest.h for StudGest project
** Made by      : Alexis Pleney, Razvan Stan
** Started on   : 10/12/19 13:29:10
** Description  : Fichier Header
*/

//#ifdef SUTDGEST_H
//#define SUTDGEST_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <error.h>
#include <math.h>

#include "cJSON.h"

/* clearScreen */
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define LOADFILE_SIZE 1024
#define MAX_COLS_LEN 10

/* Structures */
typedef struct mark {
    int idM;
    int coef;
    float mark;
    struct mark *next;
} Mark;

typedef struct course {
  int idC;
  char *name;
  int coef;
  struct mark *mark;
  struct course *next;
} Course;

typedef struct student {
    int id;
    char *firstname;
    char *lastname;
    char *class;
    int promotion;
    struct course *course;
    struct student *next;
} Student;

typedef struct listStudent {
  Student *first;
} ListStudent;

/* counter.c */
int nbOfStudent(ListStudent *);
int nbOfMarks(Mark *);
int nbOfCourses(Course *);

/* course.c */
Mark *createMark(int , float);
Course *createCourse(char *, int);
void freeMark(Mark **);
void freeCourse(Course **);
Mark *findByIdM(Mark *, int);
Course *findByIdC(Course *, int);
Mark *addMark(Mark *);
Course *addCourse(Course *);
Mark *lastMark(Mark *);
Course *lastCourse(Course *);
void showMarks(Mark *);
void showCourses(Course *);
void addCourseAndMark(Course *);
void addForAll(ListStudent *);
void addForOne(ListStudent *);
void addForOnePromotion(ListStudent *, int);
Mark *makeListMark(Mark *, Mark *);
Course *makeListCourse(Course *, Course *);
float way(Mark *);
float generalMeans(Course *);
float generalMeansClass(ListStudent *,const char *);
void freeAllMarks(Mark **);
void freeAllCourses(Course **);
void modCourse(Course *);
void modMark(Mark *);

/* draw.c */
void drawArrBar(int, int *);
void drawCell(int, char *, int);
void drawArrHead(int, int, int *, int, char [][MAX_COLS_LEN]);
void drawArrBody(int, int, int *, Student *);
void drawMenuBar(int);
void drawMenuRow(int);
void drawMenuText(int, char *);
void menuBanner(int, char *);
void menuText();

/* file.c */
void saveFile(ListStudent *);
ListStudent *loadFile(ListStudent *);

/* json.c */
cJSON *isObjNull(cJSON *);
char *structToJSON(ListStudent *);
ListStudent *JSONToStruct(char *, ListStudent *);

/* main.c */
void clearScreen();
void checkBackToMenu(char *);
void backToMenu();
void quit();
void menu();

/* listStudent.c */
ListStudent *setupFirst(Student *);
void freeList(ListStudent **);
void viewStudents(ListStudent *);
ListStudent *findById(ListStudent *, int);
void delStudent(ListStudent **);
void viewStudent(Student *[],int);
void sortByFirstname(ListStudent *);
void sortByLastname(ListStudent *);
void sortByGeneralMeans(ListStudent *);
void showStudentOfOnePromotion(ListStudent *, int);
void drawArrBody2(int, int, int *, Student *[]);

/* student.c */
Student *createStudent(char *, char *, char *, int);
void freeStudent(Student **);
void listStudent(ListStudent *);
ListStudent *addStudent(ListStudent *);
ListStudent *createList(ListStudent *, Student *);
void infoStudent(ListStudent *);
void addNoteStudent(ListStudent *);
void freeAll(ListStudent **);
void modChoice(ListStudent *);
void modStudent(Student *);

/* utils.c */
char *itoa(int);
int doesFileExist(char *);
void repeatChar(char, int);
void *initArr(int *, int);
int intlen(int);
int getMax(int, int);
int getNumber(int, int, int, char *);
char *getString(int, int, char *);
void clearBuffer();
int stringIsInt(char *);
void *fmalloc(int);
float getFloat(int, int, int);
void writeFile(const char *, const char *, char *);

/* counter.c */
int nbOfStudent(ListStudent *);
int nbOfMarks(Mark *);
int nbOfCourses(Course *);

//#endif
