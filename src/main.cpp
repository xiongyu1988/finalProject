#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "snake.h"
#include <thread>

#include <mutex>

std::mutex game_mutex;

constexpr std::size_t kFramesPerSecond{60};
constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
constexpr std::size_t kScreenWidth{640};
constexpr std::size_t kScreenHeight{640};
constexpr std::size_t kGridWidth{32};
constexpr std::size_t kGridHeight{32};

Controller controller;

void render()
{
  // while (true) {
  //  Lock the mutex while accessing game
  std::lock_guard<std::mutex> lock(game_mutex);

  Snake snake;
  // access bool game_over from shake
  bool gameStatus = snake.get_game_over();
  if (!gameStatus)
  {
    std::cout << "Hit the Wall, Game Over!\n";
  }
  // Delay to control the frame rate
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void gameLogic()
{
  // Lock the mutex while accessing game
  std::lock_guard<std::mutex> lock(game_mutex);
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
  Snake snake;
  // access bool game_over from shake
  bool gameStatus = snake.get_game_over();
  if (!gameStatus)
  {
    std::cout << "Score: " << game.GetScore() << "\n";
    std::cout << "Size: " << game.GetSize() << "\n";
  }
}

int main()
{
  srand(time(NULL));

  std::thread renderThread(render);
  std::thread gameLogicThread(gameLogic);
  gameLogicThread.join();
  renderThread.join();

  return 0;
}