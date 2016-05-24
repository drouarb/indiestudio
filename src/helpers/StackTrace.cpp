//
// Created by greg on 22/05/16.
//

#include <execinfo.h>
#include <cstddef>
#include <cstdio>
#include <csignal>
#include <string.h>
#include <iostream>
#include "StackTrace.h"

void StackTrace::displayStackTrace()
{
  void *array[128];
  int size;

  size = backtrace(array, 128);
  backtrace_symbols_fd(array, size, 2);
}

void StackTrace::init()
{
  signal(SIGSEGV, &handler);
}

void StackTrace::handler(int signal)
{
  std::cerr << "RECV signal: " << strsignal(signal) << std::endl;
  std::cerr << "STACKTRACE" << std::endl;
  displayStackTrace();
  std::cerr << "END STACKTRACE" << std::endl;
}





