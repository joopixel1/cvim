#include "terminal.hpp"
#include "utils.hpp"
#include <cassert>
#include <sstream>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

using std::ostringstream;
using std::string;

/*-----Internal Functions-------------- */

/*-------------- Terminal Class definitions-------*/

Terminal &Terminal::getInstance() {
  static Terminal instance;
  return instance;
}

Terminal::Terminal() {
  _changeTerminalFromCanonicalToRawMode();
  _initTerminalConfig();
}

Terminal::~Terminal() { _changeTerminalFromRawToCanonicalMode(); }

void Terminal::_changeTerminalFromCanonicalToRawMode() {
  ensure(tcgetattr(STDIN_FILENO, &_original) == 0, "tcgetattr");
  termios raw = _original;
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

void Terminal::_changeTerminalFromRawToCanonicalMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &_original);
}

void Terminal::_initTerminalConfig() {
  config.x = 0;
  config.y = 0;

  struct winsize ws;
  ensure(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) != -1 && ws.ws_col != 0,
         "initTerminalConfig: ioctl");
  config.cols = ws.ws_col;
  config.rows = ws.ws_row;
}

char Terminal::read() {
  int numReads;
  char c = 0;
  while ((numReads = ::read(STDIN_FILENO, &c, 1)) == 0)
    ;

  ensure(numReads != -1 or errno == EAGAIN, "readKey");
  return c;
}

void Terminal::clear() {
  write(STDOUT_FILENO, "\x1b[2J", 4); // J is for clearing screen
  write(STDOUT_FILENO, "\x1b[H", 3);  // H is for setting cursor position
}

void Terminal::refresh() {
  ostringstream oss;
  oss << "\x1b[?25l"; // ?25 l and h command for setting mode such as no cursor
  oss << "\x1b[H";    // H is for setting cursor position

  for (int i = 0; i < config.rows; i++) {
    if (i == config.rows / 3) {
      string welcomeText = "Kilo editor -- version " + string(CVIM_VERSION);
      int padding = (config.cols - welcomeText.size()) / 2;
      if (padding > 0) {
        oss << "~" << std::string(padding - 1, ' '); // left margin
      }

      oss << welcomeText.substr(0, config.cols); // prevent overflow
    } else {
      oss << "~";
    }

    oss << "\x1b[K"; // K erases the rest of the line
    if (i < config.rows - 1)
      oss << "\r\n";
  }

  oss << "\x1b[" << config.y << ";" << config.x
      << "H";         // H is for setting cursor position
  oss << "\x1b[?25h"; // ?25 l and h command for setting mode such as cursor

  string output = oss.str();
  write(STDOUT_FILENO, output.c_str(), output.size());
}