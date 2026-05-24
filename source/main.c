#include <X11/X.h>
#include <X11/Xft/Xft.h>
#include <X11/Xlib.h>
#include <X11/Xproto.h>
#include <X11/Xutil.h>
#include <X11/cursorfont.h>
#include <X11/keysym.h>

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

#include <wm_client.c>
#include <wm_event.c>
#include <wm_input.c>
#include <wm_monitor.c>
#include <wm_stack.c>
#include <wm_tile.c>

#include <globals.c>

void handle_args(int argc, char *argv[]) {
  if (argc == 2 && !strcmp("-v", argv[1]))
    die("dwm-");
  else if (argc != 1)
    die("usage: dwm [-v]");
  if (!setlocale(LC_CTYPE, "") || !XSupportsLocale())
    fputs("warning: no locale support\n", stderr);
  if (!(dpy = XOpenDisplay(NULL)))
    die("dwm: cannot open display");
}

int error_handler(Display *display, XErrorEvent *event) {
    // TODO: Handle error handling //
    return 0;
}

int main(int argc, char *argv[]) {
  handle_args(argc, argv);

  const char *home_dir = getenv("HOME");

  if (home_dir == NULL) {
    fprintf(stderr, "ERROR: Could not get home directory.\n");
    return 1;
  }

  char script_path[256];
  snprintf(script_path, sizeof(script_path), "%s/%s", home_dir,
           ".config/dwm/run");

  checkotherwm();
  setup();
  XSetErrorHandler(error_handler);
  scan();

  if (fork() == 0) {
    char* args[] = {script_path,NULL};
    execv(script_path,args);
    // TODO: generate log file 
    perror("Error: ~/.config/dwm/run");
    exit(1);
  }

  run();
  cleanup();
  XCloseDisplay(dpy);
  return 0;
}
