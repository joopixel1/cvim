#include "processor.hpp"
#include "reader.hpp"
#include "terminal.hpp"
#include <cctype>
#include <unistd.h>

int main() {
  Processor processor;
  Reader reader;

  Terminal::getInstance().refresh();
  for (int key = reader.readKey(); true; key = reader.readKey()) {
    processor.processKey(key);
    Terminal::getInstance().refresh();
  }

  return 0;
}