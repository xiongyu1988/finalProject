#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate {
public:
  Coordinate(int x, int y) : x(x), y(y) {}

  int getXCoordinate() const { return x; }
  int getYCoordinate() const { return y; }

private:
  int x;
  int y;
};

#endif
