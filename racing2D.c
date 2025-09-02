#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define WIDTH 30
#define HEIGHT 20
#define ENEMIES 3

char userID[50];  // Player ID
int carPos = WIDTH / 2;
int enemyX[ENEMIES], enemyY[ENEMIES];
int score = 0, level = 1;
int speed = 120;

void gotoxy(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() {
    CONSOLE_CURSOR_INFO ci;
    ci.dwSize = 25;
    ci.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}

void drawBorder() {
    for (int i = 0; i <= HEIGHT; i++) {
        gotoxy(0, i); printf("|");
        gotoxy(WIDTH, i); printf("|");
    }
}

void drawCar() {
    gotoxy(carPos, HEIGHT - 2); printf("A");
     }

void eraseCar() {
     gotoxy(carPos, HEIGHT - 2); printf(" ");
 }

void drawEnemy(int i) {
     gotoxy(enemyX[i], enemyY[i]); printf("V");
     }

void eraseEnemy(int i) {
     gotoxy(enemyX[i], enemyY[i]); printf(" ");
      }
int collision(int i) {
     return (enemyY[i] == HEIGHT - 2 && enemyX[i] == carPos);
 }

void resetEnemy(int i) {
     enemyX[i] = (rand() % (WIDTH - 2)) + 1; enemyY[i] = 1;
      }

void gameOver() {
    Beep(400, 500);
    system("cls");
    printf("\n\n\tGame Over!\n");
    printf("\tPlayer: %s\n", userID);
    printf("\tYour score: %d\n", score);
    printf("\tLevel reached: %d\n", level);
    printf("\n\tPress any key to exit...\n");
    getch();
    exit(0);
}

void startScreen() {
    system("cls");
    printf("\n\n\tRacing Mania 2D\n");
    printf("\tUse 'A' to move left\n");
    printf("\tUse 'D' to move right\n");
    printf("\tAvoid the enemy cars!\n");
    printf("\n\tPress any key to start...\n");
    Beep(880, 150);
    Beep(988, 150);
    Beep(1047, 150);
    getch();
}

int main() {
    srand(time(0));
    hideCursor();


    printf("Enter your User ID: ");
    scanf("%s", userID);

    startScreen();

    for (int i = 0; i < ENEMIES; i++) {
        resetEnemy(i);
        enemyY[i] = -(i * 5);
    }

    drawBorder();

    while (1) {
        if (_kbhit()) {
            char ch = _getch();
            eraseCar();
            if ((ch == 'a' || ch == 'A') && carPos > 1) { carPos--; Beep(600, 30); }
            else if ((ch == 'd' || ch == 'D') && carPos < WIDTH - 1) { carPos++; Beep(600, 30); }
        }

        for (int i = 0; i < ENEMIES; i++) {
            eraseEnemy(i);
            enemyY[i]++;
            if (enemyY[i] > HEIGHT - 1) {
                score++;
                Beep(700, 40);
                resetEnemy(i);
                if (score % 5 == 0) { level++; if (speed > 30) speed -= 10; Beep(1000, 100); Beep(1200, 100); }
            }
            drawEnemy(i);
            if (collision(i)) gameOver();
        }

        drawCar();

        gotoxy(WIDTH + 5, 1); printf("Player: %s", userID);
        gotoxy(WIDTH + 5, 2); printf("Score: %d", score);
        gotoxy(WIDTH + 5, 3); printf("Level: %d", level);

        Sleep(speed);
    }
}
