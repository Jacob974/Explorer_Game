# Explorer Game
## What this Game is
This is a 2D game I'm making with SDL. It will be an open world game where you can explore and do things

---
## Tools/Dependencies
* SDL2
* SDL_image
* Git
* For Linux, GCC and Make
* For Windows and Mac, MinGW

---
## How to Install Tools/Dependencies
* Debian/Ubuntu
  1. First, update the package manager just to be safe
     ```
     sudo apt update
     ```
  1. Download gcc
     ```
     sudo apt install gcc
     ```
  1. Download make
     ```Bash
     sudo apt install make
     ```
  1. Download git
     ```
     sudo apt install git
     ```
  1. Download SDL
     ```
     sudo apt-get install libsdl2-2.0
     sudo apt-get install libsdl2-dev
     sudo apt-get install libsdl2-image-dev
     ```
* Other Linux Distros
    * The installation process for other distros is more or less the same as with Debian/Ubuntu. Just make sure you're using the correct package manager
* Windows/Mac
    1. Download and install Git and MinGW. You will have to do this manually as these operation systems don't have package managers
    1. Download the binaries for SDL2 and SDL_image or compile the source code yourself
---
## How to Download the Repository
1. Open a terminal and type in the following command
   ```
   git clone https://github.com/Jacob974/Explorer_Game
   ```
1. You should see a folder with the name "Explorer_Game"
1. If you have the SDL binaries, put them into the "bin" directory

---
## How to Build
Type in the following command
   ```
   make
   ```
If it doesn't work, make sure you are in the "Explorer_Game" directory

---
## How to Run
Type in the following command
```
./bin/main.exe
```