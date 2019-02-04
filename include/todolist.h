#ifndef TODOLIST_H
#define TODOLIST_H

/* #define DEBUG*/

#define VIEW_LEN 20 /* words to be displayed every line*/


#define PROJECT "todolist"                 /* name if program */
#define VERSION "--VERSION--"              /* current release of project */


typedef struct {
  int date;
  int r;                                   /* remove list iterm */
  int w;                                   /* write todo list */
} opt_t;

extern opt_t opt;

#endif
