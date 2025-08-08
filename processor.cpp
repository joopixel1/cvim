#include "processor.hpp"
#include "reader.hpp"
#include "terminal.hpp"
#include "utils.hpp"
#include <cstdlib>

void Processor::_moveCursor(int key) {
  auto &config = Terminal::getInstance().config;
  switch (key) {
  case ARROW_LEFT:
    if (config.x != 0)
      config.x--;
    break;
  case ARROW_RIGHT:
    if (config.x != config.cols - 1)
      config.x++;
    break;
  case ARROW_UP:
    if (config.y != 0)
      config.y--;
    break;
  case ARROW_DOWN:
    if (config.y != config.rows - 1)
      config.y++;
    break;
  case HOME_KEY:
    config.x = 0;
    break;
  case END_KEY:
    config.x = config.cols - 1;
    break;
  }
}

void Processor::processKey(int key) {
  switch (key) {
  case CTRL_KEY('q'):
    Terminal::getInstance().clear();
    exit(0);
    break;

  case PAGE_UP:
  case PAGE_DOWN: {
    int times = Terminal::getInstance().config.rows;
    while (times--)
      _moveCursor(key == PAGE_UP ? ARROW_UP : ARROW_DOWN);
  } break;

  case ARROW_UP:
  case ARROW_DOWN:
  case ARROW_LEFT:
  case ARROW_RIGHT:
  case HOME_KEY:
  case END_KEY:
    _moveCursor(key);
    break;
  }
}
