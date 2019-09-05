#include "game.h"
#include <iostream>
#include "SDL.h"
#include <thread>
#include "snake.h"

SDL_TimerID Game::timer_id = NULL;
Game_Stage Game::gameStage = Game_Stage::NORMAL;
Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)),
      random_h(0, static_cast<int>(grid_height)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food, spcl_food, food2);
    if(snake.refreshFood){  //bug fix if random function wont work.
      	PlaceFood();
      	snake.refreshFood  = false;
      	if(gameStage == BONUS){
          PlaceFood2();
        }
    }

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, GetHighestScore(), score_for_bonus, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
  if(score > highestScore){
    highestScore = score;
  	std::cout << "\nCongratulations! you hit the new highest score : " + std::to_string(score);
  }
}

//Places normal food
void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

//Places second food
void Game::PlaceFood2() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      Game::food2.x = x;
      Game::food2.y = y;
      return;
    }
  }
}

void Game::RemoveFood2() {
  food2.x = -1;
  food2.y = -1;
}

//Places special food
void Game::PlaceSpclFood() {
  int spcl_x, spcl_y;
  while (true) {
    spcl_x = random_w(engine);
    spcl_y = random_h(engine);
    
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(spcl_x, spcl_y)) {
      spcl_food.x = spcl_x;
      spcl_food.y = spcl_y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  if(gameStage == SPCL_FOOD_TIMEOUT){
    score_for_bonus = 5; //reset the bunus;
    gameStage = NORMAL;
  }

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);
  
  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    switch(gameStage){
    case NORMAL:
      Snake::speed += 0.01;
      score_for_bonus--;
      if(score_for_bonus  == 0){ //as soon we get 5 food, bonus.
          if(!Snake::isSpecialFoodActive) {
              //std::cout<<"\nyou ate 5 more food. Level up!!";
              PlaceSpclFood();
              Snake::isSpecialFoodActive = true;
              gameStage = SPECIAL_FOOD;
            	Game::timer_id = SDL_AddTimer(10*1000, spcl_food_timer_callbackfunc, NULL);
          }
        }
      break;
    case SPECIAL_FOOD:
        Snake::speed += 0.01;
      	break;
    case BONUS:
      break;
   }
  }
  else if(food2.x == new_x && food2.y == new_y){  //check for food2
    switch(gameStage){
      case NORMAL:
      case SPECIAL_FOOD:
        RemoveFood2();
        break;
      case BONUS:
        score++;
        PlaceFood2();
    	  // Grow snake and increase speed.
    	  snake.GrowBody();
        break;
    }
  }
  else if(spcl_food.x == new_x && spcl_food.y == new_y){  //check for special food
    if(gameStage == SPECIAL_FOOD){
      SDL_RemoveTimer(Game::timer_id); //remove spclfood timer
    	Game::timer_id = SDL_AddTimer(15*1000, bonus_timer_callbackfunc, NULL);
    
   		score_for_bonus = 5; //reset the bonus counter.
    	Snake::speed += 0.1;
    	Snake::isSpecialFoodActive = false;
    	gameStage = BONUS;
    }
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }
int Game::GetHighestScore() const { return highestScore; }
int Game::SetHighestScore(int val) { highestScore = val; }

Uint32 Game::bonus_timer_callbackfunc(Uint32 interval, void *param)
{
  	//std::cout << "\nBonus timer is timed out!\n";
    
  	Snake::speed -= 0.1;
  	SDL_RemoveTimer(Game::timer_id);
    Game::gameStage = NORMAL;
    return 0;
}

Uint32 Game::spcl_food_timer_callbackfunc(Uint32 interval, void *param)
{
  	//std::cout << "\nspcl food timer is timed out!\n";
  	SDL_RemoveTimer(Game::timer_id);
  	if(Snake::isSpecialFoodActive){
    	Snake::isSpecialFoodActive = false;
      Game::gameStage = SPCL_FOOD_TIMEOUT;
    }
    return 0;
}

void Game::decreaseSpeed(){
	Snake::speed -= 0.5;
}