#include "moutain.h"
#include <iostream>
#include <random>
#include <vector>
#include <SDL.h>
#include "renderer.h"

Mountain::Mountain(size_t grid_width, size_t grid_height, int x, int y)
    : grid_width(grid_width),
      grid_height(grid_height), x(x), y(y)
{
}

SDL_Point Mountain::get_mountain() const
{
  return location;
}

std::vector<Coordinate> Mountain::getCoordinates() const
{
  return coordinates;
}
