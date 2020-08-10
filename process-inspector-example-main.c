#include "process-inspector.h"

int main (int argc, char **argv) {
  unsigned int pid = 0;
  char *abspath = NULL;
  char *cmd = NULL;
  
  fprintf (stdout, "** cmd_parser **\n");
  for (;;) {
    pid = 0;
    fprintf (stdout, "PID(0-32768): ");
    fscanf (stdin, "%u", &pid);
    if (pid == 0)
      break;

    abspath = get_pid_abspath (pid);
    cmd = get_pid_command (pid);
    fprintf (stdout, "abspath: %s\ncmd: %s\n", abspath, cmd);
    if (abspath) {
      free (abspath);
      abspath = NULL;
    }
    if (cmd) {
      free (cmd);
      cmd = NULL;
    }
  }
  fprintf (stdout, "EXIT\n");

  exit (EXIT_SUCCESS);
}
