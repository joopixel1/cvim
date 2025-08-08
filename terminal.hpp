#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include <termios.h>

struct TerminalConfig {
  int rows;
  int cols;
  int x;
  int y;
};

class Terminal {
public:
  static Terminal &getInstance();

private:
  termios _original;

public:
  TerminalConfig config;

private:
  Terminal();

public:
  Terminal(const Terminal &) = delete;
  Terminal &operator=(const Terminal &) = delete;

public:
  ~Terminal();

private:
  void _changeTerminalFromCanonicalToRawMode();
  void _changeTerminalFromRawToCanonicalMode();
  void _initTerminalConfig();

public:
  char read();
  void clear();
  void refresh();
};

#endif // TERMINAL_HPP
