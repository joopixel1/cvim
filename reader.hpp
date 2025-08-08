#ifndef READER_HPP
#define READER_HPP

#define ARROW_LEFT 1000
#define ARROW_RIGHT 1001
#define ARROW_UP 1002
#define ARROW_DOWN 1003
#define PAGE_UP 1004
#define PAGE_DOWN 1005
#define HOME_KEY 1006
#define END_KEY 1007
#define DEL_KEY 1008

class Reader {
public:
  int readKey();
};

#endif // READER_HPP
