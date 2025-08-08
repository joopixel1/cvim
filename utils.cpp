#include "utils.hpp"
#include "terminal.hpp"
#include <cstdlib>
#include <stdio.h>

void ensure(const bool condition, const char *msg) {
  if (condition)
    return;

  Terminal::getInstance().clear();

  perror(msg); // Prints the message plus system error
  exit(1);     // Exits immediately — no stack trace
}