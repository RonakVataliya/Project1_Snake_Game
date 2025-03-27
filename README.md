# 🐍 Snake Game (C++)


## Authors

- [VIKAS](https://github.com/Vikas-soni11)
- [TAKSH](https://github.com/Taksh-1105)
- [DHAVAL](https://github.com/Dhaval1306)
- [RONAK](https://github.com/RonakVataliya)

## 📜 Table of Contents
- Prerequisites
- Project Description
- Key Features
- Prerequisites
- Installation
- How To Play
- Data Structure Analysis
- Important Data Members
- Key Member functions
- Code Structure
- License
- Contact
- Future Improvements



## ✨Project Description

This project shows how to develop classic Snake Game using C++
programming language.It shows the usage of important concepts in Object Oriented Programming Langauge. 

Players get to guide the snake on a 2D plane, eating fruits that appear randomly and trying not to crash into the walls of the game or the snake's body. Since the snake grows longer after eating, navigation gets trickier as points are added to the player's score and the snake crashes, or the player quits. 


## 🌟Key Features

1. Interactive Gameplay: The player controls the snake's movement using keyboard keys (W,,A, S, D,↑,←,↓,→).  
2. Dynamic Snake Growth: Eating fruits causes the snake to grow
3. Random Food Generation: Food (*) is placed at random positions that do not overlap the snake.  
4. Game Termination: The game ends if the snake collides with the walls or itself.  
5. Score Tracking: The player's score increases by 10 points with each fruit consumed. Stores high score until the highscore.txt is deleted.  
6. Real-time Input Handling: Supports non-blocking keyboard input using conio.h.  
7. Windows Supported:It supports only Windows OS as we are using windows.h library.  
8. Multiple-fruit system Different types of fruit emerge at different score of the user.

## 🧰Prerequisites
- A C++ compiler (e.g., g++)
- Windows Operating System

## 🛠Installation 

To run the Snake game, follow these steps:

1.  Clone the Repository:
    bash
    $ git clone [https://github.com/RonakVataliys/snake-game-cpp.git](https://github.com/yourusername/snake-game-cpp.git)
    $ cd snake-game-cpp
    
2.  Compile the Code (using g++):
    bash
    $ g++ snake_game.cpp -o snake_game.exe  # For Windows
    $ g++ snake_game.cpp -o snake_game
    
3.  Run the Game:
    bash
    $ ./snake_game.exe  # For Windows   
    $ ./snake_game
    
---
---
## 🎮 How To Play
- Run the game and follow on-screen instructions.
- 🎯 Select your difficulty level
  - 🟢 Press 1 for Easy
  - 🟡 Press 2 for Medium
  - 🔴 Press 3 for Hard
- 🍎 Goal: Eat food to grow and avoid hitting the walls and obstacles(X).
- 🔄 Press R to restart or Q to exit after Game Over.
 🕹 Controls

| Key        | Action                                      |
|-----------|---------------------------------------------|
| W or ↑  | ⬆ Move Up                                |
| A or ←  | ⬅ Move Left                              |
| S or ↓  | ⬇ Move Down                              |
| D or →  | ➡ Move Right                             |
| Q  | ❌ Exit the Game                          |
| R      | 🔄 Restart the Game and Select Difficulty Again |
 🔥 Difficulty Levels

| Level      | Sleeptime (ms delay) | Difficulty              |
|-----------|----------------|-------------------------|
| 1 - Easy   | 150 ms         | 🟢 Best for beginners   |
| 2 - Medium | 100 ms         | 🟡 Balanced challenge  |
| 3 - Hard   |  50 ms          | 🔴 Fast-paced gameplay |


## 📚Data Structures Analysis

## 🔹 Data Structures Used

### Linked List (Node Structure) 

*  Stores the snake’s body.
*  Enables efficient insertion and deletion of body segments.

### 2D Grid Representation (std::pair<int, int>) 🗺

*   Tracks the snake's head, body, and food position.



## Snake Game - Object-Oriented Structure

This document outlines the object-oriented structure of the Snake game.

## Object-Oriented Structure

| Class                     | Responsibility                                                                    |
|---------------------------|---------------------------------------------------------------------------------|
| snake_game               | Handles game logic, rendering, movement, collision detection.                     |
| list(pair(int, int)) snake | Stores the snake's body using a linked list.                                     |
| pair(int, int) food    | Stores the food's position in the grid.                                          |

### 🏷Important Data Members:

*   🏅 score: (int) The player's current score.
*   🏆 high_score: (int) The highest score achieved.
*   📍 head_x: (int) The x-coordinate of the snake's head.
*   📍 head_y: (int) The y-coordinate of the snake's head.
*   🍎 fruit_x: (int) The x-coordinate of the fruit.
*   🍎 fruit_y: (int) The y-coordinate of the fruit.
*   🍇 fruit_type: (char) The type of fruit (determines score/effect).
*   📏 length: (int) The length of the game grid (rows).
*   📐 breadth: (int) The breadth of the game grid (columns).
*   ⛓ snake: (vector<pair<int, int>>) Stores the coordinates of the snake's body segments.
*   💨 speed: (int) The game speed (delay between updates).
*   ➡ dir: (char) The current direction of the snake ('U', 'D', 'L', 'R').
*   💀 gameover: (bool) Flag indicating if the game is over.
*   🔢 gridsize: (int) Unused in the provided code.  (Could be removed or used in a future implementation).


### ⚙Key Member Functions
* 🏗snake_game(int l, int b): Constructor. Initializes the game with the given length and breadth.
*   🔄 reset(): Resets the game state (new game).
*   🍎 generate_food(): Generates new food at a random position.
*   🚧 generate_obstacles(): Generates new obstacles at random positions.
*   🎨 draw(): Draws the game board, snake, food, obstacles, score, and high score.
*   ⌨ input(): Handles player input (arrow keys for movement, 'q' to quit).
*   ⬆ update(): Updates the game state (moves the snake, checks for collisions, etc.).
*   💾 save_high_score(): Saves the high score to a file.
*   📂 load_high_score(): Loads the high score from a file.
*   ▶ run(): The main game loop. Handles drawing, input, and updating until game over.
*   ❓ restart_prompt(): Asks the player if they want to restart the game. 

---
## 📁 Code Structure
📂 Snake_Game_C++/  
│── 📄 README.md  
│── 📄 snake_game.cpp  
│── 📄 LICENSE  
│── 📄 snake_game.exe

## 📜 License
MIT License

Copyright (c) 2025 RonakVataliya

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.



## 🚀Future Improvements
✅ Make it cross-platform using ncurses (Linux/Mac).    
✅ Improve graphics with colored UI and animations.     
✅ Add different food types that provide unique effects (e.g., speed boost, slow motion).
✅ Obstacles can be added for better difficulty and overall experience.
✅"Toroidal Gameplay"♾ that means teleportation of snake from one edge to another.
## 📞 Contact
💡Found a bug or have suggestions? Open an issue or reach out:
-> 📧 Email : 202401241@daiict.ac.in
-> GitHub : https://github.com/Taksh-1105


🎉 Thanks for going through this project! We Hope you enjoy playing! 🚀
