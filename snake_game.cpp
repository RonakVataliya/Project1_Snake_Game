#include <iostream>
#include <conio.h> // For _kbhit() and _getch() to handle keyboard input
#include <ctime> // For random seed initialization
#include <fstream> // For file operations (saving/loading high scores)
#include <windows.h> // For console manipulation functions like color and cursor position

using namespace std;

struct Node
{
    int x, y;
    Node *next;
    Node(int x, int y) : x(x), y(y), next(nullptr) {}
};

class SnakeGame
{
private:
    int score, high_score;
    int fruit_x, fruit_y;
    char fruit_type;
    int length, breadth;
    int speed;
    char dir;
    bool gameover;
    Node *head; // Head of the snake
    Node *tail; // Tail of the snake
    HANDLE hConsole; // Handle for console screen manipulation
    int food_color;

public:
    SnakeGame(int l, int b, int game_speed) : length(l), breadth(b), speed(game_speed)
    {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        hide_cursor(); // Hide the blinking cursor
        reset();
        load_high_score();
    }

    void hide_cursor() // Hides the console cursor for a cleaner display
    {
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hConsole, &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(hConsole, &cursorInfo);
    }

    void reset()
    {
        score = 0;
        gameover = false;
        dir = 'R';
        head = new Node(6, 5); // Create initial snake of length 3
        Node *mid = new Node(5, 5);
        tail = new Node(4, 5);
        head->next = mid;
        mid->next = tail;
        generate_food();
    }

    void generate_food()
    {
        fruit_x = rand() % (breadth - 2) + 1;
        fruit_y = rand() % (length - 2) + 1;
        char food_types[] = {'@', '$', 'B', '+', '*'};
        fruit_type = food_types[rand() % 5];

        // Assign a random color for the food (Red, Yellow, Cyan, Magenta, White)
        int colors[] = {12, 14, 11, 13, 15};
        food_color = colors[rand() % 5];
    }

    void gotoxy(int x, int y) // Moves the cursor to the specified position on the console
    {
        COORD pos = {short(x), short(y)};
        SetConsoleCursorPosition(hConsole, pos);
    }

    void draw() // Draws the game board, snake, and food
    {
        gotoxy(0, 0);
        cout << "\nYour Score: " << score << "  High Score: " << high_score << endl;
        SetConsoleTextAttribute(hConsole, 7);
        for (int i = 0; i < breadth; i++)
            cout << "#";
        cout << endl;
        for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < breadth; j++)
            {
                if (j == 0 || j == breadth - 1)
                {
                    SetConsoleTextAttribute(hConsole, 7);
                    cout << "#";
                }
                else if (i == fruit_y && j == fruit_x)
                {
                    SetConsoleTextAttribute(hConsole, food_color);
                    cout << fruit_type;
                }
                else
                {
                    bool printed = false;
                    Node *temp = head;
                    while (temp)
                    {
                        if (temp->x == j && temp->y == i)
                        {
                            SetConsoleTextAttribute(hConsole, 10);
                            cout << (temp == head ? 'O' : 'o');
                            printed = true;
                            break;
                        }
                        temp = temp->next;
                    }
                    if (!printed)
                    {
                        SetConsoleTextAttribute(hConsole, 7);
                        cout << " ";
                    }
                }
            }
            cout << endl;
        }

        SetConsoleTextAttribute(hConsole, 7);

        for (int i = 0; i < breadth; i++)
            cout << "#";
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
        int prev_x = head->x, prev_y = head->y;
        switch (dir)
        {
        case 'L':
            head->x--;
            break;
        case 'R':
            head->x++;
            break;
        case 'U':
            head->y--;
            break;
        case 'D':
            head->y++;
            break;
        }
        if (head->x >= breadth - 1 || head->x <= 0 || head->y >= length || head->y <= -1)
        {
            gameover = true;
            return;
        }
        Node *temp = head->next;
        int temp_x, temp_y;
        while (temp)
        {
            temp_x = temp->x;
            temp_y = temp->y;
            temp->x = prev_x;
            temp->y = prev_y;
            prev_x = temp_x;
            prev_y = temp_y;
            temp = temp->next;
        }
        if (head->x == fruit_x && head->y == fruit_y)
        {
            score += 10;
            generate_food();
            Node *new_tail = new Node(prev_x, prev_y);
            tail->next = new_tail;
            tail = new_tail;
        }
        temp = head->next;
        while (temp)
        {
            if (temp->x == head->x && temp->y == head->y)
            {
                gameover = true;
                return;
            }
            temp = temp->next;
        }
    }

    void save_high_score() // Save highscore in file
    {
        if (score > high_score)
        {
            ofstream file("highscore.txt");
            file << score;
            file.close();
        }
    }

    void load_high_score() // Retrieve the highscore from file
    {
        ifstream file("highscore.txt");
        if (file)
            file >> high_score;
        else
            high_score = 0;
        file.close();
    }

    // Runs the game loop
    bool run()
    {
        while (!gameover)
        {
            draw();
            input();
            update();
            Sleep(speed);
        }

        save_high_score();
        return restart_prompt();
    }

    bool restart_prompt()
    {
        SetConsoleTextAttribute(hConsole, 7);
        cout << "\nGAME OVER! Final Score: " << score << "\nPress 'R' to Restart or any other key to Exit." << endl;
        return (_getch() == 'r' || _getch() == 'R');
    }
};

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    cout << "Instructions:\n";
    cout << "Use 'W' or Up Arrow to Move Up\n";
    cout << "Use 'S' or Down Arrow to Move Down\n";
    cout << "Use 'A' or Left Arrow to Move Left\n";
    cout << "Use 'D' or Right Arrow to Move Right\n";
    cout << "Press 'Q' to Quit\n";
    cout << "Press 'R' after game over to Restart\n\n";
    int difficulty, speed;
    cout << "Choose difficulty level\n 1: Easy\n 2: Medium\n 3: Hard\n ";
    cin >> difficulty;
    speed = (difficulty == 1) ? 100 : (difficulty == 2) ? 70

                                                        : 5;
                                                        system("cls");

    bool play_again = true;

    while (play_again)
    {
        SnakeGame game(20, 40, speed);
        play_again = game.run();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout << "Thanks for playing!" << endl;

        
    }
}
