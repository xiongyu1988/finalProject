#ifndef MOUNTAIN_H
#define MOUNTAIN_H

#include "SDL.h"
#include <vector>
#include "snake.h"
#include "coordinates.h"

class Mountain
{
public:
  Mountain(size_t grid_width, size_t grid_height, int x, int y);
  int x;
  int y;
  SDL_Point get_mountain() const;

  // Getter
  std::vector<Coordinate> getCoordinates() const;

private:
  SDL_Point location;
  std::vector<Coordinate> coordinates;
  size_t grid_width;
  size_t grid_height;
};

#endif