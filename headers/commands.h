#pragma once

#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, 0}                    \
  }

static const char *COMMAND_TERMINAL[] = {"alacritty", 0};
static const char *COMMAND_PROGRAM_LAUNCHER[] = {"rofi","-show","run", 0};
static const char *COMMAND_SCREENSHOT[] = {"flameshot","gui", 0};
static const char *COMMAND_VOLUME[] = {"my-volume-controller", 0};
static const char *COMMAND_YAZI_DOWNLOADS[] = {"alacritty","-e","yazi","~/Downloads", 0};
static const char *COMMAND_YAZI_HOME[] = {"alacritty","-e","yazi", 0};
