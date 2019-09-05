#include "renderer.h"
#include <iostream>
#include <string>
#include "game.h"

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const &food, SDL_Point const &spcl_food, SDL_Point const &food2) {
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

  // Render special food
  if(Snake::isSpecialFoodActive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x80, 0x00, 0xFF);
    block.x = spcl_food.x * block.w;
    block.y = spcl_food.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  if(Game::gameStage == BONUS && (food2.x != -1) &&(food2.y != -1) ){
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
    block.x = food2.x * block.w;
    block.y = food2.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int highScore, int score_for_bonus, int fps) {
  std::string title;
  switch(Game::gameStage) {
      case NORMAL:
      title = "Snake Score: " + std::to_string(score) +  "| Food needed for bonus: " + std::to_string(score_for_bonus)
       + "| FPS: " + std::to_string(fps);
      break;
      case SPECIAL_FOOD:
      title = "Snake Score: " + std::to_string(score) +  "| Previous Highest score : " + std::to_string(highScore)
       + "| FPS: " + std::to_string(fps);
      break;
      case BONUS:
      title = "Snake Score: " + std::to_string(score) +  "| Previous Highest score : " + std::to_string(highScore)
       + "| FPS: " + std::to_string(fps);
      break;
      default:
      title = "Snake Score: " + std::to_string(score) +  "| Previous Highest score : " + std::to_string(highScore)
       + "| FPS: " + std::to_string(fps);
      break;
  }
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
