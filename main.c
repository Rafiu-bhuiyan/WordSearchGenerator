#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_WORDS 50
#define MAX_WORD_LEN 30
#define MAX_GRID 50

char grid[MAX_GRID][MAX_GRID];
char solution[MAX_GRID][MAX_GRID];
int GRID_SIZE;

typedef struct {
    int dx, dy;
} Direction;

Direction directions[] = {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0},
    {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
};




int is_valid_position(int x, int y, int dx, int dy, const char* word) {    //To be continued
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        int nx = x + dx * i;
        int ny = y + dy * i;
        if (nx < 0 || ny < 0 || nx >= GRID_SIZE || ny >= GRID_SIZE)
            return 0;
        if (grid[nx][ny] != '.' && grid[nx][ny] != word[i])
            return 0;
    }
    return 1;
}





void place_word(const char* word) {
    int placed = 0, attempts = 100;
    int len = strlen(word);
    while (!placed && attempts--) {
        int dir_index = rand() % 8;
        Direction dir = directions[dir_index];
        int x = rand() % GRID_SIZE;
        int y = rand() % GRID_SIZE;

        if (is_valid_position(x, y, dir.dx, dir.dy, word)) {
            for (int i = 0; i < len; i++) {
                int nx = x + dir.dx * i;
                int ny = y + dir.dy * i;
                grid[nx][ny] = word[i];
                solution[nx][ny] = word[i];
            }
            placed = 1;
        }
    }
    if (!placed) {
        printf("Could not place word: %s\n", word);
    }
}

void fill_grid() {
    for (int i = 0; i < GRID_SIZE; i++)
        for (int j = 0; j < GRID_SIZE; j++)
            if (grid[i][j] == '.')
                grid[i][j] = 'A' + rand() % 26;
}

void print_grid(char matrix[MAX_GRID][MAX_GRID]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}

void print_solution() {
    printf("\nSolution Grid (only words shown):\n");
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            printf("%c ", solution[i][j] ? solution[i][j] : '.');
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL));
    char words[MAX_WORDS][MAX_WORD_LEN];
    int word_count;

    printf("Enter grid size (max %d): ", MAX_GRID);
    scanf("%d", &GRID_SIZE);
    getchar();

    if (GRID_SIZE <= 0 || GRID_SIZE > MAX_GRID) {
        printf("Invalid grid size.\n");
        return 1;
    }

    printf("Enter number of words (max %d): ", MAX_WORDS);
    scanf("%d", &word_count);
    getchar();

    if (word_count <= 0 || word_count > MAX_WORDS) {
        printf("Invalid number of words.\n");
        return 1;
    }

    for (int i = 0; i < word_count; i++) {
        printf("Enter word %d: ", i + 1);
        fgets(words[i], MAX_WORD_LEN, stdin);
        words[i][strcspn(words[i], "\n")] = '\0';
        for (int j = 0; words[i][j]; j++)
            words[i][j] = toupper(words[i][j]);
    }


    for (int i = 0; i < GRID_SIZE; i++)
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = '.';
            solution[i][j] = 0;
        }


    for (int i = 0; i < word_count; i++)
        place_word(words[i]);

    fill_grid();

    printf("\nWord Search Puzzle:\n");
    print_grid(grid);

    printf("\nWords to find:\n");
    for (int i = 0; i < word_count; i++)
        printf("%s\n", words[i]);

    print_solution();

    return 0;
}


