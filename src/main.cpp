#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include <fstream>
#include <string>
#include "util.h"
using namespace std;
int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  std::cout << "Game Controls: " << "\n\t Arrow Keys : Directions \n\t r : Refresh \n\t q : Quit";
  Game game(kGridWidth, kGridHeight);
  game.highestScore = Util::getStoredHighestScore();
  std::cout << "\n\nPrevious Highest Score: " << game.GetHighestScore() << "\n";
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "\nGame has terminated successfully!\n";
  Util::writeNewHighestScore(game.GetHighestScore());
  std::cout << "Highest Score: " << game.GetHighestScore() << "\n";
  std::cout << "Your Score: " << game.GetScore() << "\n";
  std::cout << "Snake Size: " << game.GetSize() << "\n";
  return 0;
}