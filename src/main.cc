// -*- mode: C++; indent-tabs-mode: nil; c-basic-offset: 2; -*-

/*! @file main.cc
  @brief Main entry point for the application
*/

#ifdef    HAVE_CONFIG_H
#  include "../config.h"
#endif // HAVE_CONFIG_H

extern "C" {
#ifdef    HAVE_LOCALE_H
# include <locale.h>
#endif // HAVE_LOCALE_H

#ifdef    HAVE_STDIO_H
# include <stdio.h>
#endif // HAVE_STDIO_H

#ifdef    HAVE_UNISTD_H
#  include <sys/types.h>
#  include <unistd.h>
#endif // HAVE_UNISTD_H

#include "gettext.h"
}

#include "openbox.hh"
#include "otk/util.hh"

int main(int argc, char **argv) {
  // initialize the locale
  if (!setlocale(LC_ALL, ""))
    printf("Couldn't set locale from environment.\n");
  bindtextdomain(PACKAGE, LOCALEDIR);
  bind_textdomain_codeset(PACKAGE, "UTF-8");
  textdomain(PACKAGE);

  ob::Openbox openbox(argc, argv);
  openbox.eventLoop();

  if (openbox.doRestart()) {
    const std::string &prog = openbox.restartProgram();
    if (!prog.empty()) {
      execl("/bin/sh", "/bin/sh", "-c", prog.c_str(), NULL); 
      perror(prog.c_str());
    }
    
    // fall back in case the above execlp doesn't work
    execvp(argv[0], argv);
    execvp(otk::basename(argv[0]).c_str(), argv);
  }
}
