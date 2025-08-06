#include "utils.hpp"
#include <cstdlib>
#include <stdio.h>

void ensure(const bool condition, const char *msg) {
  if (condition)
    return;

  perror(msg); // Prints the message plus system error
  exit(1);     // Exits immediately — no stack trace
}