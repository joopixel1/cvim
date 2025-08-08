#include "reader.hpp"
#include "terminal.hpp"

int Reader::readKey() {
  char c = Terminal::getInstance().read();

  // READ ARROW KEYS
  if (c == '\x1b') {
    c = Terminal::getInstance().read();
    if (c != '[')
      return '\x1b';

    c = Terminal::getInstance().read();
    if (c >= '0' and c <= '9') {
      if (Terminal::getInstance().read() != '~')
        return '\x1b';

      switch (c) {
      case '1':
        return HOME_KEY;
      case '3':
        return DEL_KEY;
      case '4':
        return END_KEY;
      case '5':
        return PAGE_UP;
      case '6':
        return PAGE_DOWN;
      case '7':
        return HOME_KEY;
      case '8':
        return END_KEY;
      }
    }

    else {
      switch (c) {
      case 'A':
        return ARROW_UP;
      case 'B':
        return ARROW_DOWN;
      case 'C':
        return ARROW_RIGHT;
      case 'D':
        return ARROW_LEFT;
      case 'H':
        return HOME_KEY;
      case 'F':
        return END_KEY;
      }
    }

    return '\x1b';
  }

  return c;
}