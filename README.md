CPPND: Capstone Snake Game Example

This is a modified snake game project which is using base starter repo for the Capstone project in the Udacity C++ Nanodegree Program. The code for whcih was inspired by this excellent StackOverflow post and set of responses.

Dependencies for Running Locally

    cmake >= 3.7
        All OSes: click here for installation instructions
    make >= 4.1 (Linux, Mac), 3.81 (Windows)
        Linux: make is installed by default on most Linux distros
        Mac: install Xcode command line tools to get make
        Windows: Click here for installation instructions
    SDL2 >= 2.0
        All installation instructions can be found here
        Note that for Linux, an apt or apt-get installation is preferred to building from source.
    gcc/g++ >= 5.4
        Linux: gcc / g++ is installed by default on most Linux distros
        Mac: same deal as make - install Xcode command line tools
        Windows: recommend using MinGW

Basic Build Instructions

    Clone this repo.
    Make a build directory in the top level directory: mkdir build && cd build
    Compile: cmake ./ && make
    Run it: ./SnakeGame.
    
Game Controls: 

    Arrow Keys : Directions 
           r : Refresh 
           q : Quit
           
           
Known Bug: Sometimes new food is not apprearing on screen when snake get one food. 
Resolution: If this situation occus while playing, please hit "r" and it will refresh the game.
