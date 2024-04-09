#include "renderer.h"
#include <iostream>
#include <string>
#include "readParameter.h"
#include "coordinates.h"

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height)
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window)
  {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer)
  {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Load the mountain image
  SDL_Surface *mountainSurface = SDL_LoadBMP("../imag/mountain.bmp");
  if (mountainSurface == nullptr)
  {
    std::cerr << "Failed to load mountain image: " << SDL_GetError() << "\n";
    return;
  }
  if (!mountainSurface)
  {
    std::cerr << "Failed to load mountain image: " << SDL_GetError() << std::endl;
  }
  // Create a texture from the surface
  mountainTexture = SDL_CreateTextureFromSurface(sdl_renderer, mountainSurface);
  if (mountainTexture == nullptr)
  {
    std::cerr << "Failed to create mountain texture: " << SDL_GetError() << "\n";
    return;
  }
  if (!mountainTexture)
  {
    std::cerr << "Failed to create mountain texture: " << SDL_GetError() << std::endl;
  }
  SDL_FreeSurface(mountainSurface);

  // Read the number of mountains from the params.txt file
  ReadParameter reader("../data/params.txt");
  int numMountains = reader.getNumMountains();
  // std::cout << "Number of mountains: " << numMountains << std::endl;
  //  Generate random positions for the mountains
  for (int i = 0; i < numMountains; ++i)
  {
    int x = rand() % grid_width;
    int y = rand() % grid_height;
    std::shared_ptr<Mountain> mountain = std::make_shared<Mountain>(grid_width, grid_height, x, y);
    mountains.push_back(mountain);
    // std::cout << "Mountain " << i << " coordinates: (" << mountain->x << ", " << mountain->y << ")\n";
  }
}

Renderer::~Renderer()
{
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const &food, SDL_Point const &mountain)
{
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // // Render mountains
  // for (const SDL_Point& mountain : mountains) {
  //   SDL_Rect mountainRect;
  //   mountainRect.x = mountain.x * block.w;
  //   mountainRect.y = mountain.y * block.h;
  //   mountainRect.w = block.w; // Set the width of the mountain
  //   mountainRect.h = block.h; // Set the height of the mountain
  //   SDL_RenderCopy(sdl_renderer, mountainTexture, NULL, &mountainRect);
  // }

  // Place the mountains
  placeMountains(mountains);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body)
  {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive)
  {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  }
  else
  {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps)
{
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::placeMountains(const std::vector<std::shared_ptr<Mountain>> &mountains) const
{
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  for (const auto &mountain : mountains)
  {
    // Check for nullptr
    if (!mountain || !sdl_renderer || !mountainTexture)
    {
      std::cerr << "Null pointer error in placeMountains\n";
      continue; // Skip this iteration
    }

    // Place the mountain on the grid
    SDL_Rect mountainRect;
    mountainRect.x = mountain->x * block.w;
    mountainRect.y = mountain->y * block.h;
    // std::cout << "Mountain coordinates: (" << mountain->x << ", " << mountain->y << ")\n";
    mountainRect.w = block.w; // Set the width of the mountain
    mountainRect.h = block.h; // Set the height of the mountain
    SDL_RenderCopy(sdl_renderer, mountainTexture, NULL, &mountainRect);
  }
}