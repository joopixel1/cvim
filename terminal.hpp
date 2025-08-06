#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include <termios.h>

class Terminal {
public:
  static Terminal &getInstance();

private:
  termios original;

  Terminal();

public:
  Terminal(const Terminal &) = delete;
  Terminal &operator=(const Terminal &) = delete;

public:
  ~Terminal();

private:
  void changeTerminalFromCanonicalToRawMode();
  void changeTerminalFromRawToCanonicalMode();
};

#endif // TERMINAL_HPP
