//
// Created by greg on 22/05/16.
//

#include <execinfo.h>
#include <cstddef>
#include <cstdio>
#include <unistd.h>
#include "StackTrace.h"

void StackTrace::displayStackTrace()
{
  void *array[128];
  int size;

  size = backtrace(array, 128);
  backtrace_symbols_fd(array, 128, STDERR_FILENO);
}

