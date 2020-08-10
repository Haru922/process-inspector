#include "process-inspector.h"

char *
get_pid_command (unsigned int pid)
{
  int i = 0;
  FILE *fp = NULL;
  char *p = NULL;
  char buf[CMD_MAX+1] = { 0, };
  char *cmd = NULL;

  snprintf (buf, PATH_MAX+1, "/proc/%u/cmdline", pid);
  printf ("buf: %s\n", buf);
  fp = fopen (buf, "r");
  if (fp) {
    for (i=0; i<CMD_MAX+1; i++)
      buf[i] = '\0';
    fgets (buf, CMD_MAX+1, fp);
    fclose (fp);
    if (buf) {
      cmd = (char *) calloc (1, sizeof (char) * (CMD_MAX+1));
      snprintf (cmd, CMD_MAX+1, "%s", buf);
      p = strchr (buf, '\0');
      while (p && p[1]) {
        strncat (cmd, " ", CMD_MAX);
        strncat (cmd, p+1, CMD_MAX);
        p = strchr (p+1, '\0');
      }
    }
  }

  return cmd;
}

char *
get_pid_abspath (unsigned int pid)
{
  char buf[PATH_MAX+1] = { 0, };

  snprintf (buf, PATH_MAX+1, "/proc/%u/exe", pid);

  return realpath (buf, NULL);
}
