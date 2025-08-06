#include "terminal.hpp"
#include "utils.hpp"
#include <cassert>
#include <termios.h>
#include <unistd.h>

Terminal &Terminal::getInstance() {
  static Terminal instance;
  return instance;
}

Terminal::Terminal() { changeTerminalFromCanonicalToRawMode(); }

Terminal::~Terminal() { changeTerminalFromRawToCanonicalMode(); }

void Terminal::changeTerminalFromCanonicalToRawMode() {
  ensure(tcgetattr(STDIN_FILENO, &original) == 0, "tcgetattr");
  termios raw = original;
  raw.c_iflag &=
      ~(BRKINT | ICRNL | INPCK | ISTRIP |
        IXON); // turn off ^S, ^Q, ^M, ^C, parity checking, 8th bit stripping,
  raw.c_oflag &= ~(OPOST); // ^turn off output processing,
  raw.c_cflag |= (CS8);    // turns off bitmasking,
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN |
                   ISIG); // turn off echo, canonical mode, ^C, ^Z, ^V,
  raw.c_cc[VMIN] =
      0; // minimum number of bytes of input needed before read() can return.
  raw.c_cc[VTIME] = 1; // maximum amount of time to wait before read() returns.
  ensure(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == 0, "tcsetattr");
}

void Terminal::changeTerminalFromRawToCanonicalMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
}
