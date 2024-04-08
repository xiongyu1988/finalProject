#include "moutain.h"
#include <iostream>
#include <random>
#include <vector>
#include <SDL.h>
#include "renderer.h"

Mountain::Mountain(int grid_width, int grid_height) 
    : grid_width(grid_width), 
      grid_height(grid_height) {
}


SDL_Point Mountain::get_mountain() const {
  return location;
}

std::vector<Coordinate> Mountain::getCoordinates() const {
  return coordinates;
}

