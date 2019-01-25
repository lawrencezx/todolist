#include "todolist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static void usage (FILE *st)
/*
 * Print usage information on stream st.
 *
 */
{
  fprintf (st, "Usage:  %s [options]\n", PROJECT);
  fprintf (st, "        -d date  set date, i.e. set date 2020.1.1\n");
  fprintf (st, "        -h       print usage information\n");
  fprintf (st, "        -l date  list todolist\n");
  fprintf (st, "        -m t/e   set mode time/energy mode\n");
  fprintf (st, "        -r num   remove list item by order number\n");
  fprintf (st, "        -w num   edit todolist\n");
}

static void usage_short (FILE *st)
/*
 * Print abbreviated usage information on stream st.
 *
 */
{
  fprintf(st, "Usage: %s [options]\n", PROJECT);
  fprintf(st, "Try '%s -h' for more information\n", PROJECT);
}

static void usage_long (FILE *st)
/*
 * Print usage information on stream st, including a header text.
 *
 */
{
  fprintf(st, "%s - lists your to-do list and helps you manage your energy\n", PROJECT);
  fprintf(st, "       (c) Lawrence Zou <email: iwatchnima@gmail.com>\n");
  fprintf(st, "       wed page: not created yet!\n");
  usage (st);
}

static int process_commandline(int argc, char *argv[])
/*
 * Process command line options.
 *
 *  argc, argv   command line as passed to main())
 *
 *  RETURNS:   == 0 success, continue
 *             == 1 success, but terminate anyway (e.g. help/version)
 *             != 0/1 error
 *
 */
{
  if (argc >= 2 && argv[1] != NULL
      && (strcmp(argv[1], "--help") == 0|| strcmp(argv[1], "-?") == 0))
  {
    usage_long(stdout);
    return 1;
  }
  /*TO DO*/
  return -1;
}

int main(int argc, char *argv[]) 
{
  int rc;

  #ifdef DEBUG
    fprintf(stderr, "TODOLIST STARTING ...\n");
  #endif

  /*
   * Prrocess command line options
   */
  #ifdef DEBUG
    fprintf(stderr, "Parsing Command Line ...\n");
  #endif
  rc = process_commandline(argc, argv);
  if (rc == 1) {
    exit (EXIT_SUCCESS);
  }
  if (rc) {
    exit (EXIT_FAILURE);
  }

  /*TO DO*/

  return EXIT_SUCCESS;
}
