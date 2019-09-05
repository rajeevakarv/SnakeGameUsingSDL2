#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  /*enum Game_Stage{
    NORMAL,
    SPECIAL_FOOD,
    BONUS
  };*/
  static Game_Stage gameStage;
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  int GetHighestScore() const;
  int SetHighestScore(int val);
  int highestScore{0};
  void decreaseSpeed();
  static SDL_TimerID timer_id;
  static Uint32 bonus_timer_callbackfunc(Uint32 interval, void *param);
  static Uint32 spcl_food_timer_callbackfunc(Uint32 interval, void *param);

 private:
  Snake snake;
  SDL_Point food, food2;
  SDL_Point spcl_food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  int score_for_bonus{5};

  void PlaceFood();
  void PlaceFood2();
  void RemoveFood2();
  void PlaceSpclFood();
  void Update();
};

#endif