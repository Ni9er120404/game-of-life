#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define Y 25
#define X 80

void input_matrix(int game_screen[Y][X], int number_of_file);
void update_matrix(int game_screen[Y][X], int new_game_screen[Y][X]);
int count_neighbors(int game_screen[Y][X], int i, int j);
int decision(int neighbors, int condition);
void replace(int new_game_screen[Y][X], int game_screen[Y][X]);
void print_matrix(int game_screen[Y][X]);

int main() {
    int number_of_file, s;
    int game_screen[Y][X], new_game_screen[Y][X];
    scanf("%d %d", &number_of_file, &s);
    input_matrix(game_screen, number_of_file);
    while (1) {
        usleep(s * 100000);
        system("clear");
        print_matrix(game_screen);
        update_matrix(game_screen, new_game_screen);
        replace(new_game_screen, game_screen);
    }
    return 0;
}

void input_matrix(int game_screen[Y][X], int number_of_file) {
    FILE *file;
    char filename[20];
    sprintf(filename, "../data/data_%d.txt", number_of_file);
    file = fopen(filename, "r");
    int c;
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            c = fgetc(file);
            if (c == '0') {
                game_screen[i][j] = 0;
            } else if (c == '1') {
                game_screen[i][j] = 1;
            }
        }
        while ((c = fgetc(file)) != '\n' && c != EOF)
            ;
    }
    fclose(file);
}

void update_matrix(int game_screen[Y][X], int new_game_screen[Y][X]) {
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            int neighbors = count_neighbors(game_screen, i, j);
            new_game_screen[i][j] = decision(neighbors, game_screen[i][j]);
        }
    }
}

int count_neighbors(int game_screen[Y][X], int i, int j) {
    int count = 0;
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            if (y == 0 && x == 0) {
                continue;
            }
            int new_x = i + y;
            int new_y = j + x;
            if (new_x >= 0 && new_x < Y && new_y >= 0 && new_y < X) {
                count += game_screen[new_x][new_y];
            }
        }
    }
    return count;
}

int decision(int neighbors, int condition) {
    if (condition == 1) {
        if (neighbors < 2 || neighbors > 3) {
            return 0;
        } else {
            return 1;
        }
    } else {
        if (neighbors == 3) {
            return 1;
        } else {
            return 0;
        }
    }
}

void replace(int new_game_screen[Y][X], int game_screen[Y][X]) {
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            game_screen[i][j] = new_game_screen[i][j];
        }
    }
}

void print_matrix(int game_screen[Y][X]) {
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            if (game_screen[i][j] == 0) {
                printf(" ");
            } else {
                printf("@");
            }
        }
        printf("\n");
    }
}