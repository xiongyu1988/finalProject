#include "snake.h"
#include <cmath>
#include <iostream>

#include "renderer.h"
const std::size_t screen_width = 640;
const std::size_t screen_height = 640;
const std::size_t grid_width = 32;
const std::size_t grid_height = 32;
Renderer renderer(screen_width, screen_height, grid_width, grid_height);

void Snake::Update()
{

  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)}; // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)}; // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y)
  {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead()
{
  switch (direction)
  {
  case Direction::kUp:
    head_y -= speed;
    break;

  case Direction::kDown:
    head_y += speed;
    break;

  case Direction::kLeft:
    head_x -= speed;
    break;

  case Direction::kRight:
    head_x += speed;
    break;
  }

  // Check if the snake will hit the boundary
  if (static_cast<double>(head_x) < 0. || static_cast<double>(head_y) < 0. ||
      static_cast<int>(head_x) >= grid_width || static_cast<int>(head_y) >= grid_height)
  {
    game_over = true;
    return;
  }
// std::vector<SDL_Point> mountains;
// for (const auto& mountain : renderer.GetMountains()) {
//   SDL_Point point;
//   point.x = mountain->x;
//   point.y = mountain->y;
//   mountains.push_back(point);
// }
//   //std::vector<SDL_Point> moutains = renderer.GetMountains();
//   // Check if the snake's head has hit a mountain
//   for (const auto &mountain : mountains)
//   {
//     if (static_cast<int>(head_x) == mountain.x && static_cast<int>(head_y) == mountain.y)
//     {
//       game_over = true;
//       return;
//     }
//   }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell)
{
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing)
  {
    // Remove the tail from the vector.
    body.erase(body.begin());
  }
  else
  {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body)
  {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y)
    {
      alive = false;
    }
  }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y)
{
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y))
  {
    return true;
  }
  for (auto const &item : body)
  {
    if (x == item.x && y == item.y)
    {
      return true;
    }
  }
  return false;
}