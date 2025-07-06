
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
