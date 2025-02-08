#include <iostream>
#include <conio.h>
#include <vector>
#include <ctime>
#include <fstream>
#include <windows.h>

using namespace std;

class snake_game
{
private:
    int score, high_score;
    int head_x, head_y;
    int fruit_x, fruit_y;
    char fruit_type;
    int length, breadth;
    vector<pair<int, int>> snake;
    vector<pair<int, int>> obstacles;
    int speed; 
    char dir;
    bool gameover;
    int gridsize;
    string snake_name; 

public:
   
    snake_game(int l, int b, string name, int game_speed)
    {
        length = l;
        breadth = b;
        snake_name = name;  
        speed = game_speed; 
        load_high_score();
        reset();
    }

    void reset()
    {
        head_x = length / 2;
        head_y = breadth / 2;
        score = 0;
        gameover = false;
        dir = 'U';
        snake.clear();
        snake.push_back({head_x, head_y});
        snake.push_back({head_x, head_y - 1});

        generate_food();
        generate_obstacles();
    }

    void generate_food()
    {
        fruit_x = rand() % (breadth - 2) + 1;
        fruit_y = rand() % (length - 2) + 1;
        for (auto i : snake)
        {
            if (i.first == fruit_x && i.second == fruit_y)
            {
                generate_food();
                break;
            }
        }
        char food_types[] = {'@', '$', 'B', '+', '*'};
        fruit_type = food_types[rand() % 5];
    }

    void generate_obstacles()
    {
        obstacles.clear();
        for (int i = 0; i < 5; i++)
        {
            obstacles.push_back({rand() % breadth, rand() % length});
        }
    }

    void draw()
    {
        system("cls");
        cout << "Snake's Name: " << snake_name << endl; \
        for (int i = 0; i < breadth + 2; i++)
            cout << "#";
        cout << endl;
        for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < breadth; j++)
            {
                if (j == 0)
                    cout << "#";
                if (i == head_y && j == head_x)
                    cout << "O";
                else if (i == fruit_y && j == fruit_x)
                    cout << fruit_type;
                else
                {
                    bool printed = false;
                    for (auto it : snake)
                    {
                        if (it.first == j && it.second == i)
                        {
                            cout << "o";
                            printed = true;
                            break;
                        }
                    }
                    for (auto obs : obstacles)
                    {
                        if (obs.first == j && obs.second == i)
                        {
                            cout << "X";
                            printed = true;
                            break;
                        }
                    }
                    if (!printed)
                        cout << " ";
                }
                if (j == breadth - 1)
                    cout << "#";
            }
            cout << endl;
        }
        for (int i = 0; i < breadth + 2; i++)
            cout << "#";
        cout << "\nScore of your pet " << snake_name <<": "<< score << "  High Score: " << high_score << endl;
    }

    void input()
    {
        if (_kbhit())
        {
            switch (_getch())
            {
            case 'a':
            case 75:
                if (dir != 'R')
                    dir = 'L';
                break;
            case 'd':
            case 77:
                if (dir != 'L')
                    dir = 'R';
                break;
            case 'w':
            case 72:
                if (dir != 'D')
                    dir = 'U';
                break;
            case 's':
            case 80:
                if (dir != 'U')
                    dir = 'D';
                break;
            case 'q':
                gameover = true;
                break;
            }
        }
    }

    void update()
    {   
        pair<int, int> prev = snake[0], temp;
        snake[0] = {head_x, head_y};
        for (size_t i = 1; i < snake.size(); i++)
        {
            temp = snake[i];
            snake[i] = prev;
            prev = temp;
        }
        switch (dir)
        {
        case 'L':
            head_x--;
            break;
        case 'R':
            head_x++;
            break;
        case 'U':
            head_y--;
            break;
        case 'D':
            head_y++;
            break;
        }
        if (head_x >= breadth)
            gameover = true;
        else if (head_x < 0)
            gameover = true;
        if (head_y >= length)
            gameover = true;
        else if (head_y < 0)
            gameover = true;
        if (head_x == fruit_x && head_y == fruit_y)
        {
            
            
                score += (fruit_type == '@') ? 10 : (fruit_type == '$') ? 20
                                                                        : 50;
            generate_food();
            snake.push_back(snake.back());
        }
        for (auto obs : obstacles)
        {
            if (obs.first == head_x && obs.second == head_y)
                gameover = true;
        }
        for (size_t i = 1; i < snake.size(); i++)
        {
            if (snake[i].first == head_x && snake[i].second == head_y)
                gameover = true;
        }
    }

    void save_high_score()
    {
        if (score > high_score)
        {
            ofstream file("highscore.txt");
            file << score;
            file.close();
        }
    }

    void load_high_score()
    {
        ifstream file("highscore.txt");
        if (file)
            file >> high_score;
        else
            high_score = 0;
        file.close();
    }

    bool run()
    {   
        while (!gameover)
        {
            draw();
            input();
            update();
            Sleep(speed); // Speed is determined by the difficulty
        }
        save_high_score();
        return restart_prompt();
    }

    bool restart_prompt()
    {
        cout << "\nGAME OVER! Final Score: " << score << "\nPress 'R' to Restart or any other key to Exit." << endl;
        return (_getch() == 'r' || _getch() == 'R');
    }
};

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    bool play_again = true;
    string snake_name;
    int difficulty;

    cout << "Enter your pet snake's name: ";
    cin >> snake_name;

    

    cout << "Choose difficulty level (1: Easy, 2: Medium, 3: Hard): ";
    cin >> difficulty;

    // Set speed based on difficulty
    int speed = 100;
    if (difficulty == 1)
        speed = 150;
    else if (difficulty == 2)
        speed = 100;
    else if (difficulty == 3)
        speed = 50;

    while (play_again)
    {
        snake_game game(20, 2 * 20, snake_name, speed); // Pass speed to the game
        play_again = game.run();
    }
    cout << "Thanks for playing!" << endl;
    return 0;
}
