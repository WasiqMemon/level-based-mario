# CS 224 OOP and Design Methodologies, Fall 2020
# Final Project: Level Based Mario

The final project for this course required the development of a game using C++ and SDL 2.0.

## Group Members
- _Wasiq Hussain_
- _Sameer Pervez_
- _Marium Rehman_
- _Kumail Rizvi_

## Youtube Demo Link

https://youtu.be/XsSUT4Xu9o4

## Application

### RULES TO PLAY:
- Use W, A, S, and D keys to move Up, Left, Down, Right respectively.
- Mario has 3 lives.
- There are 3 enemies Goombas, Hammer Bro, and Spiny.
- Kill Goombas by jumping on top of it.
- Hitting any enemy from right or left side (or top in case of spiny) will cost you one life.
- Collect coins after popping them up from mysterious itemblocks (by hitting them from bottom).
- Hammer Bro pushes back or repels mario.

### LEVELS:
Every level has two levelparts (screens). Once you cross to another level, you cannot return to the previous one.
- Level 01: It is placed in day time with easy difficulty.
- Level 02: It is placed in night time with medium difficulty.
- Level 03: It is placed in a castle with hard difficulty.

### SAVE and LOAD:
Whenever you cross a level, the system saves your lives' and coins' count in a text file.
Even if you quit the game or die in that level, pressing "Load" button next time on start screen will take you to that particular level.

### Gameplay:
![alt text](https://github.com/WasiqMemon/level-based-mario/blob/main/images/day_gameplay.png)

## SDL 2.0 Setup 

To install SDL 2.0 and other libraries, follow intsructions from [here](http://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/mingw/index.php).

## How to Compile?

- Open these files in VSCode or any other code editor.
- Open terminal and put this command to compile everything:

	g++ *.cpp -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

- Run the game by this command:

	.\a.exe
  
## Credits:

All sprites, backgrounds, and sounds were taken from Mario Mayhem website.
- https://www.mariomayhem.com/downloads/sprites/

