#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>
#include "SDL.h"
#include "snake.h"
#include "moutain.h"

class Renderer
{
public:
  Renderer() = default;
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  // void Render(Snake const snake, SDL_Point const &food,
  //             std::vector<std::shared_ptr<Mountain>> const &mountains);
  void Render(Snake const snake, SDL_Point const &food, SDL_Point const &mountain);
  void UpdateWindowTitle(int score, int fps);

  std::shared_ptr<Mountain> &GetMountains() { return mountain; };
  void placeMountains(const std::vector<std::shared_ptr<Mountain>> &mountains) const;

private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  SDL_Texture *mountainTexture;
  std::vector<std::shared_ptr<Mountain>> mountains;
  std::shared_ptr<Mountain> mountain;
  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif