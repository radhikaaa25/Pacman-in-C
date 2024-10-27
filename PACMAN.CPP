#include <graphics.h>
#include <conio.h> // For kbhit() and getch()
#include <stdio.h>
#include <stdlib.h> // For rand()
#include <string.h> // For itoa()
#include <dos.h>
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

#define MAZE_ROWS 10
#define MAZE_COLS 10
#define CELL_SIZE 40

int pacmanX = 60, pacmanY = 60; // Initial position of Pacman
int pacmanRadius = 15;
int stepSize = 40;  // Adjust step size to match cell size
int score = 100;    // Start with a score of 100
int numBalls = 8;
char scoreText[20]; // String to hold the score text
int ballsEatenCount = 0; // Track the number of balls Pacman has eaten
int gameOver = 0; // Flag to check if the game is over

// Define the maze structure using a 2D array
int maze[MAZE_ROWS][MAZE_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

// Ball (pellet) positions
int ballX[8];
int ballY[8];
int ballEaten[8] = {0, 0, 0, 0, 0, 0, 0, 0}; // Flags to track if the ball is eaten

// Function to draw the maze
void drawMaze() {
    setcolor(WHITE);
    for (int i = 0; i < MAZE_ROWS; i++) {
        for (int j = 0; j < MAZE_COLS; j++) {
            if (maze[i][j] == 1) {
                int x1 = j * CELL_SIZE;
                int y1 = i * CELL_SIZE;
                int x2 = x1 + CELL_SIZE;
                int y2 = y1 + CELL_SIZE;
                rectangle(x1, y1, x2, y2); // Draw walls
                floodfill((x1 + x2) / 2, (y1 + y2) / 2, WHITE);
            }
        }
    }
}

// Function to randomly spawn balls at valid positions in the maze
void spawnBalls() {
    srand(time(0)); // Seed for random number generation
    for (int i = 0; i < numBalls; i++) {
        int validPosition = 0;
        while (!validPosition) {
            int x = rand() % MAZE_COLS;
            int y = rand() % MAZE_ROWS;
            if (maze[y][x] == 0) { // Ensure ball is not placed on a wall
                ballX[i] = x * CELL_SIZE + CELL_SIZE / 2;
                ballY[i] = y * CELL_SIZE + CELL_SIZE / 2;
                validPosition = 1;
            }
        }
    }
}

// Function to draw the balls (pellets)
void drawBalls() {
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLUE);
    for (int i = 0; i < numBalls; i++) {
        if (!ballEaten[i]) {
            fillellipse(ballX[i], ballY[i], 5, 5); // Draw ball if not eaten
        }
    }
}

// Function to erase Pacman by drawing a black circle over its old position
void erasePacman(int x, int y) {
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(x, y, pacmanRadius, pacmanRadius);
}

// Function to draw Pacman
void drawPacman(int x, int y, int openMouth) {
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    fillellipse(x, y, pacmanRadius, pacmanRadius);

    setcolor(BLACK);
    if (openMouth) {
        pieslice(x, y, 30, 330, pacmanRadius); // Open mouth
    } else {
        pieslice(x, y, 10, 350, pacmanRadius); // Closed mouth
    }
}

// Function to display the score on the screen
void displayScore() {
    setcolor(WHITE);
    setbkcolor(BLACK); // Set background to black for better visibility
    // Erase previous score by drawing a black rectangle over it
    bar(0, 0, 150, 30);

    // Convert score to string and display it
    sprintf(scoreText, "Score: %d", score);
    outtextxy(10, 10, scoreText);
}

// Function to check and display Game Over message
void checkGameOver() {
    if (ballsEatenCount == numBalls || score <= 0) {
        setcolor(RED);
        setbkcolor(BLACK);
        outtextxy(200, 200, "GAME OVER");
        gameOver = 1; // Set the game over flag
    }
}

// Function to detect if Pacman has eaten a ball
void checkBallCollision() {
    for (int i = 0; i < numBalls; i++) {
        if (!ballEaten[i]) {
            if (abs(pacmanX - ballX[i]) < 15 && abs(pacmanY - ballY[i]) < 15) {
                ballEaten[i] = 1;       // Mark the ball as eaten
                ballsEatenCount += 1;   // Increment balls eaten count
                score += 10;            // Increase score
                drawPacman(pacmanX, pacmanY, 0); // Close mouth after eating
                delay(200);             // Brief delay to show mouth closing
                drawPacman(pacmanX, pacmanY, 1); // Open mouth again
                displayScore();         // Update score on screen
                checkGameOver();        // Check if the game is over
            }
        }
    }
}

// Function to handle Pacman movement and wall collision detection
void movePacman() {
    int ch;

    if (kbhit()) { // Check for key press
        ch = getch();
        int newX = pacmanX, newY = pacmanY;

        switch (ch) {
            case UP:
                newY -= stepSize;
                break;
            case DOWN:
                newY += stepSize;
                break;
            case LEFT:
                newX -= stepSize;
                break;
            case RIGHT:
                newX += stepSize;
                break;
        }

        // Check if the new position is within bounds and not hitting a wall
        int row = newY / CELL_SIZE;
        int col = newX / CELL_SIZE;
        if (maze[row][col] == 0) { // If no wall, move Pacman
            erasePacman(pacmanX, pacmanY); // Erase current Pacman
            pacmanX = newX;
            pacmanY = newY;
            drawPacman(pacmanX, pacmanY, 1); // Redraw Pacman at new position
            checkBallCollision(); // Check if Pacman eats any balls
        } else {
            // If Pacman tries to cross a wall, deduct points and keep him in place
            if (score > 0) {
                score -= 5; // Deduct 5 points for hitting a wall
                displayScore(); // Update score on screen
                checkGameOver(); // Check if the game is over
            }
        }
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI"); // Turbo C path to BGI files

    drawMaze();  // Draw maze walls
    spawnBalls(); // Randomly place balls in the maze
    drawBalls();  // Draw the balls
    displayScore(); // Display initial score

    while (!gameOver) { // Run the game loop while gameOver is false
        drawPacman(pacmanX, pacmanY, 1); // Draw Pacman
        delay(100);                      // Delay for smoother frame rate
        movePacman();                    // Handle movement

        if (getch() == 27) break; // Exit if 'ESC' is pressed
    }

    closegraph(); // Close graphics mode
    return 0;
}
