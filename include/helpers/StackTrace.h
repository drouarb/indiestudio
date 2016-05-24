//
// Created by greg on 22/05/16.
//

#ifndef GAUNTLET_STACKTRACE_H
#define GAUNTLET_STACKTRACE_H


class StackTrace
{
 public:
  static void init();
  static void handler(int signal);
  static void displayStackTrace();
};


#endif //GAUNTLET_STACKTRACE_H
