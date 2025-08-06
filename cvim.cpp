#include "terminal.hpp"
#include "utils.hpp"
#include <cctype>
#include <iostream>
#include <unistd.h>

using std::cout;

int main() {
  Terminal::getInstance();

  for (; true;) {
    char c = 0;
    ensure(read(STDIN_FILENO, &c, 1) >= 0 or errno == EAGAIN, "read");

    if (!c)
      continue;

    if (iscntrl(c)) {
      cout << (int)c << "\r\n";
    } else {
      cout << (int)c << " " << c << "\r\n";
    }

    if (c == 'q')
      break;
  }

  return 0;
}