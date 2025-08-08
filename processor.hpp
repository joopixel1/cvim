#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

class Processor {
private:
  void _moveCursor(int key);

public:
  void processKey(int key);
};

#endif // PROCESSOR_HPP
