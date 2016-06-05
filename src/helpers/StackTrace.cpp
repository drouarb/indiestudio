//
// Created by greg on 22/05/16.
//

#include <stdio.h>
#include <signal.h>
#ifdef _WIN32
struct sigcontext {};
#else
#include <execinfo.h>
#include <execinfo.h>
#endif
#include <cstddef>
#include <cstdio>
#include <csignal>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include "StackTrace.h"

void StackTrace::displayStackTrace()
{
#ifndef _WIN32
	void *array[128];
  int size;

  size = backtrace(array, 128);
  backtrace_symbols_fd(array, size, 2);
#endif
}

void bt_sighandler(int sig, struct sigcontext ctx)
{
#ifndef _WIN32
  void *trace[16];
  char **messages = (char **) NULL;
  int i, trace_size = 0;

  static int j = 0;

  if (j)
    std::exit(-1);

  if (sig == SIGSEGV)
    std::cerr << "Got signal " << sig << ", faulty address is , " << ctx.cr2 <<
    std::endl;
  else
    std::cerr << "Got signal " << sig << std::endl;

  trace_size = backtrace(trace, 16);
  /* overwrite sigaction with caller's address */
//  trace[1] = (void *)ctx.eip;
  messages = backtrace_symbols(trace, trace_size);
  /* skip first stack frame (points here) */
  std::cerr << "[bt] Execution path:" << std::endl;
  for (i = 1; i < trace_size; ++i)
    {
      std::cerr << "[bt] #" << i << ", " << messages[i] << "\t\t -" << std::endl;

      /* find first occurence of '(' or ' ' in message[i] and assume
       * everything before that is the file name. (Don't go beyond 0 though
       * (string terminator)*/
      size_t p = 0;
      while (messages[i][p] != '(' && messages[i][p] != ' '
	     && messages[i][p] != 0)
	++p;

      char syscom[256];
//      std::stringstream ss;
//      ss << "addr2line " << (void *)p << " -e " << trace[i];
      sprintf(syscom, "addr2line %p -e %.*s", trace[i], p, messages[i]);
      //last parameter is the file name of the symbol
      ::system(syscom);
    }
  ::exit(0);
#endif
}

void StackTrace::init()
{
#ifndef _WIN32
//  signal(SIGSEGV, &handler);
//  signal(SIGABRT, &handler);

  struct sigaction sa;

  sa.sa_handler = (__sighandler_t) bt_sighandler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;

  sigaction(SIGSEGV, &sa, NULL);
//  sigaction(SIGUSR1, &sa, NULL);
  sigaction(SIGABRT, &sa, NULL);
#endif
}

void StackTrace::handler(int signal)
{
#ifndef _WIN32
  static int i = 0;

  if (i)
    std::exit(-1);
  i++;
  std::cerr << "RECV signal: " << strsignal(signal) << std::endl;
  std::cerr << "STACKTRACE" << std::endl;
  displayStackTrace();
  std::cerr << "END STACKTRACE" << std::endl;
#endif
}





