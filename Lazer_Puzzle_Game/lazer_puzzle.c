#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100

#define COLOR_RED     "\033[1;31m"
#define COLOR_GREEN   "\033[1;32m"
#define COLOR_BLUE    "\033[1;34m"
#define COLOR_YELLOW  "\033[1;33m"
#define COLOR_MAGENTA "\033[1;35m"
#define COLOR_RESET   "\033[0m"

int level = 1;
int shooted = 0;
int target = 0;
int startx = 1;
int starty = 1;
int startdirecx = 1;
int startdirecy = 0;

int get_size = 0;
char matrix[MAX_SIZE][MAX_SIZE];
int light_color[MAX_SIZE][MAX_SIZE][3];
int light_path[MAX_SIZE][MAX_SIZE];
int source_location;



void matrix_filler() {
    int i, j;
    for (i = 0; i < get_size; i++) {
        for (j = 0; j < get_size; j++) {
            if (i == 0 || j == 0 || j == get_size - 1 || i == get_size - 1) {
                matrix[i][j] = '#';
            }
            else {
                matrix[i][j] = '.';
            }
        }
    }
}


void matrix_shower() {
    int i, j;
    printf("\n      LEVEL %d\n\n", level);
    printf("    ");

    for (j = 0; j < get_size; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    for (i = 0; i < get_size; i++) {
        printf("%2d ", i);

        for (j = 0; j < get_size; j++) {

            if (level <= 3) {
                if (light_path[i][j] == 1 && matrix[i][j] == '.') {
                    printf("%s  *%s", COLOR_YELLOW, COLOR_RESET);
                }
                else if (matrix[i][j] == 'K') {
                    printf("%s  K%s", COLOR_YELLOW, COLOR_RESET);
                }
                else if (matrix[i][j] == 'H') {
                    printf("%s  H%s", COLOR_YELLOW, COLOR_RESET);
                }
                else if (i == 0 || j == 0 || j == get_size - 1 || i == get_size - 1) {
                    printf("%s  #%s", COLOR_MAGENTA, COLOR_RESET);
                }
                else {
                    printf("%3c", matrix[i][j]);
                }
            }

            else {

                if (light_path[i][j] == 1 && matrix[i][j] == '.') {
                    if (light_color[i][j][0] == 1)      printf("%s  *%s", COLOR_RED, COLOR_RESET);
                    else if (light_color[i][j][1] == 1) printf("%s  *%s", COLOR_GREEN, COLOR_RESET);
                    else if (light_color[i][j][2] == 1) printf("%s  *%s", COLOR_BLUE, COLOR_RESET);
                    else                                printf("%s  *%s", COLOR_YELLOW, COLOR_RESET);
                }

                else {
                    char obj = matrix[i][j];

                    if ((obj == '/' || obj == '\\' || obj == '+') && light_path[i][j] == 1) {

                        if (light_color[i][j][0] == 1)      printf("%s  %c%s", COLOR_RED, obj, COLOR_RESET);
                        else if (light_color[i][j][1] == 1) printf("%s  %c%s", COLOR_GREEN, obj, COLOR_RESET);
                        else if (light_color[i][j][2] == 1) printf("%s  %c%s", COLOR_BLUE, obj, COLOR_RESET);
                        else                                printf("%s  %c%s", COLOR_YELLOW, obj, COLOR_RESET);
                    }
                    else {
                        if (obj == 'R')      printf("%s  R%s", COLOR_RED, COLOR_RESET);
                        else if (obj == 'G') printf("%s  G%s", COLOR_GREEN, COLOR_RESET);
                        else if (obj == 'B') printf("%s  B%s", COLOR_BLUE, COLOR_RESET);

                        else if (obj == 'x') printf("%s HR%s", COLOR_RED, COLOR_RESET);
                        else if (obj == 'y') printf("%s HG%s", COLOR_GREEN, COLOR_RESET);
                        else if (obj == 'z') printf("%s HB%s", COLOR_BLUE, COLOR_RESET);

                        else if (obj == 'H') printf("%s  H%s", COLOR_YELLOW, COLOR_RESET);
                        else if (obj == 'K') printf("%s  K%s", COLOR_YELLOW, COLOR_RESET);
                        else if (i == 0 || j == 0 || j == get_size - 1 || i == get_size - 1) {
                            printf("%s  #%s", COLOR_MAGENTA, COLOR_RESET);
                        }
                        else printf("%3c", obj);
                    }

                }
            }
        }
        printf("\n");
    }
}



void engine(int startx, int starty, int directionx, int directiony, int current_color) {
    int new_xdirect, new_ydirect;
    if (startx < 0 || startx >= get_size || starty < 0 || starty >= get_size) return;
    light_path[starty][startx] = 1;
    light_color[starty][startx][current_color] = 1;
    char object = matrix[starty][startx];
    if (object == '#') return;
    if (object == 'H') {
        shooted++;
        return;
    }
    if (object == 'x') {
        if (light_color[starty][startx][0] == 1) {
            shooted++;
            return;
        }
        else return;
    }
    if (object == 'y') {
        if (light_color[starty][startx][1] == 1) {
            shooted++;
            return;
        }
        else return;
    }
    if (object == 'z') {
        if (light_color[starty][startx][2] == 1) {
            shooted++;
            return;
        }
        else return;
    }

    new_xdirect = directionx;
    new_ydirect = directiony;

    if (object == '/') {
        if (directionx == 1) {
            new_xdirect = 0;
            new_ydirect = -1;
        }
        else if (directionx == -1) {
            new_xdirect = 0;
            new_ydirect = 1;
        }
        else if (directiony == 1) {
            new_xdirect = -1;
            new_ydirect = 0;
        }
        else if (directiony == -1) {
            new_xdirect = 1;
            new_ydirect = 0;
        }
    }

    else if (object == '\\') {
        if (directionx == 1) {
            new_xdirect = 0;
            new_ydirect = 1;
        }
        else if (directionx == -1) {
            new_xdirect = 0;
            new_ydirect = -1;
        }
        else if (directiony == 1) {
            new_xdirect = 1;
            new_ydirect = 0;
        }
        else if (directiony == -1) {
            new_xdirect = -1;
            new_ydirect = 0;
        }
    }

    else if (object == '+') {
        engine(startx + directiony, starty + directionx, directiony, directionx, current_color);
        engine(startx - directiony, starty - directionx, -directiony, -directionx, current_color);
        return;
    }
    int next_color = current_color;
    if (object == 'R')next_color = 0;
    else if (object == 'G') next_color = 1;
    else if (object == 'B') next_color = 2;

    engine(startx + new_xdirect, starty + new_ydirect, new_xdirect, new_ydirect, next_color);
}


void light_cleaner() {
    int i, j, k;
    shooted = 0;
    for (i = 0; i < get_size; i++) {
        for (j = 0; j < get_size; j++) {
            light_path[i][j] = 0;
            for (k = 0; k < 3; k++) {
                light_color[i][j][k] = 0;
            }
        }
    }
}



void level_designer() {
    srand(time(NULL));
    int wall_planner, filter_planner, target_planner;
    int red_filter_planner = 0, green_filter_planner = 0, blue_filter_planner = 0, filter_wall;
    int red_target, green_target, blue_target;
    int i, number, x_location, y_location;

    matrix_filler();
    target = 0;
    shooted = 0;
    source_location = get_size / 2;
    starty = source_location;
    matrix[source_location][1] = 'K';

    if (get_size < 10) {
        wall_planner = get_size * get_size * get_size / 400 + 1;
        filter_planner = (get_size + 8) / 8;
        target_planner = (get_size + 8) / 8;
    }
    else {
        wall_planner = get_size * get_size * get_size / 400 + 1;
        filter_planner = (get_size + 8) / 4;
        target_planner = (get_size + 8) / 8;
    }


    if (level > 3) {
        for (i = filter_planner; i > 0; i--) {
            number = (rand() % 3) + 1;
            if (number == 1) red_filter_planner += 1;
            else if (number == 2) green_filter_planner += 1;
            else if (number == 3) blue_filter_planner += 1;
        }
        red_target = red_filter_planner / 2;
        green_target = green_filter_planner / 2;
        blue_target = blue_filter_planner / 2;
        if (red_filter_planner > 0 && red_target < 1) {
            red_target += 1;
        }
        else if (green_filter_planner > 0 && green_target < 1) {
            green_target += 1;
        }
        else if (blue_filter_planner > 0 && blue_target < 1) {
            blue_target += 1;
        }

        for (i = red_target; i > 0; i--) {
            do {
                x_location = (rand() % (get_size - 2)) + 1;
                y_location = (rand() % (get_size - 2)) + 1;
            } while (x_location >= 1 && x_location <= 3 && y_location >= source_location - 2 && y_location <= source_location + 2);

            if (matrix[y_location][x_location] == '.') {
                matrix[y_location][x_location] = 'x';
                target += 1;
            }
        }
        for (i = green_target; i > 0; i--) {
            do {
                x_location = (rand() % (get_size - 2)) + 1;
                y_location = (rand() % (get_size - 2)) + 1;
            } while (x_location >= 1 && x_location <= 3 && y_location >= source_location - 2 && y_location <= source_location + 2);

            if (matrix[y_location][x_location] == '.') {
                matrix[y_location][x_location] = 'y';
                target += 1;
            }
        }
        for (i = blue_target; i > 0; i--) {
            do {
                x_location = (rand() % (get_size - 2)) + 1;
                y_location = (rand() % (get_size - 2)) + 1;
            } while (x_location >= 1 && x_location <= 3 && y_location >= source_location - 2 && y_location <= source_location + 2);

            if (matrix[y_location][x_location] == '.') {
                matrix[y_location][x_location] = 'z';
                target += 1;
            }

        }

        for (i = red_filter_planner; i > 0; i--) {
            do {
                x_location = (rand() % (get_size - 2)) + 1;
                y_location = (rand() % (get_size - 2)) + 1;
            } while (x_location >= 1 && x_location <= 3 && y_location >= source_location - 2 && y_location <= source_location + 2);

            if (matrix[y_location][x_location] == '.') matrix[y_location][x_location] = 'R';
            filter_wall = rand() % 6;
            switch (filter_wall) {
            case 0:
                matrix[y_location + 1][x_location] = '#';
                break;
            case 1:
                matrix[y_location][x_location + 1] = '#';
                break;
            case 2:
                matrix[y_location - 1][x_location] = '#';
                break;
            case 3:
                matrix[y_location][x_location - 1] = '#';
                break;
            case 4:     //In cases 4 and 5, the space was left empty intentionally to allow for the possibility of the filter surroundings being clear.
                break;
            case 5:
                break;
            default: break;
            }
        }
        for (i = green_filter_planner; i > 0; i--) {
            do {
                x_location = (rand() % (get_size - 2)) + 1;
                y_location = (rand() % (get_size - 2)) + 1;
            } while (x_location >= 1 && x_location <= 3 && y_location >= source_location - 2 && y_location <= source_location + 2);

            if (matrix[y_location][x_location] == '.') matrix[y_location][x_location] = 'G';
            filter_wall = rand() % 6;
            switch (filter_wall) {
            case 0:
                matrix[y_location + 1][x_location] = '#';
                break;
            case 1:
                matrix[y_location][x_location + 1] = '#';
                break;
            case 2:
                matrix[y_location - 1][x_location] = '#';
                break;
            case 3:
                matrix[y_location][x_location - 1] = '#';
                break;
            case 4:
                break;
            case 5:
                break;
            default: break;
            }
        }
        for (i = blue_filter_planner; i > 0; i--) {
            do {
                x_location = (rand() % (get_size - 2)) + 1;
                y_location = (rand() % (get_size - 2)) + 1;
            } while (x_location >= 1 && x_location <= 3 && y_location >= source_location - 2 && y_location <= source_location + 2);

            if (matrix[y_location][x_location] == '.') matrix[y_location][x_location] = 'B';
            filter_wall = rand() % 6;
            switch (filter_wall) {
            case 0:
                matrix[y_location + 1][x_location] = '#';
                break;
            case 1:
                matrix[y_location][x_location + 1] = '#';
                break;
            case 2:
                matrix[y_location - 1][x_location] = '#';
                break;
            case 3:
                matrix[y_location][x_location - 1] = '#';
                break;
            case 4:
                break;
            case 5:
                break;
            default: break;
            }
        }
        for (i = wall_planner; i > 0; i--) {
            do {
                x_location = (rand() % (get_size - 2)) + 1;
                y_location = (rand() % (get_size - 2)) + 1;
            } while (x_location >= 1 && x_location <= 3 && y_location >= source_location-2 && y_location <= source_location+2 );
            if (matrix[y_location][x_location] == '.') matrix[y_location][x_location] = '#';
        }



    }
    else if (level == 3) {
        for (i = target_planner; i > 0; i--) {
            do {
                x_location = (rand() % (get_size - 2)) + 1;
                y_location = (rand() % (get_size - 2)) + 1;
            } while (x_location >= 1 && x_location <= 3 && y_location >= source_location - 2 && y_location <= source_location + 2);

            if (matrix[y_location][x_location] == '.') {
                matrix[y_location][x_location] = 'H';
                target += 1;
            }
        }
        for (i = wall_planner * 2; i > 0; i--) {
            do {
                x_location = (rand() % (get_size - 2)) + 1;
                y_location = (rand() % (get_size - 2)) + 1;
            } while (x_location >= 1 && x_location <= 3 && y_location >= source_location - 2 && y_location <= source_location + 2);
            if (matrix[y_location][x_location] == '.') matrix[y_location][x_location] = '#';
        }

    }
    else if (level == 2) {
        do {
            x_location = (rand() % (get_size - 2)) + 1;
            y_location = (rand() % (get_size - 2)) + 1;
        } while (x_location >= 1 && x_location <= 3 && y_location >= source_location - 2 && y_location <= source_location + 2);

        if (matrix[y_location][x_location] == '.') {
            matrix[y_location][x_location] = 'H';
            target += 1;
        }

        for (i = wall_planner * 3; i > 0; i--) {
            do {
                x_location = (rand() % (get_size - 2)) + 1;
                y_location = (rand() % (get_size - 2)) + 1;
            } while (x_location >= 1 && x_location <= 3 && y_location >= source_location - 2 && y_location <= source_location + 2);
            if (matrix[y_location][x_location] == '.') matrix[y_location][x_location] = '#';
        }

    }
    else if (level == 1) {
        do {
            x_location = (rand() % (get_size - 2)) + 1;
            y_location = (rand() % (get_size - 2)) + 1;
        } while (x_location >= 1 && x_location <= 3 && y_location >= source_location - 2 && y_location <= source_location + 2);

        if (matrix[y_location][x_location] == '.') {
            matrix[y_location][x_location] = 'H';
            target += 1;
        }

        for (i = wall_planner; i > 0; i--) {
            do {
                x_location = (rand() % (get_size - 2)) + 1;
                y_location = (rand() % (get_size - 2)) + 1;
            } while (x_location >= 1 && x_location <= 3 && y_location >= source_location - 2 && y_location <= source_location + 2);
            if (matrix[y_location][x_location] == '.') matrix[y_location][x_location] = '#';
        }

    }
}


int main() {
    while (1) {
        printf("The recommended matrix dimensions are 15.\n");
        printf("Enter your matrix size (Max %d):", MAX_SIZE);
        scanf("%d", &get_size);
        if (get_size < 7 || get_size > MAX_SIZE) {
            printf("You have to enter between 7 and %d...\n", MAX_SIZE);
            continue;
        }
        else {
            break;
        }
    }

    int row, c;
    char obj;

    while (level <= 100) {
        level_designer();
        while (1) {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif

            light_cleaner();
            engine(startx, starty, startdirecx, startdirecy, 0);
            matrix_shower();

            if (shooted >= target) {
                printf("\nAwesome! Next level...\n\nPress enter to go to next level...");
                level++;
                getchar();
                getchar();
                break;
            }
            printf("Enter row,column and an object (Exmp: 5 5 /) \nCheck out the README file to learn how to play the game!");
            printf("\nEnter -1 to exit\nEnter -2 to reset\nEnter your position and object: ");
            if (scanf("%d", &row) != 1) {
                while (getchar() != '\n');
                continue;
            }
            if (row == -1) return 0;
            if (row == -2) {
                light_cleaner();
                break;
            }
            if (scanf(" %d", &c) != 1) {
                while (getchar() != '\n');
                continue;
            }
            scanf(" %c", &obj);
            if (obj != '+' && obj != '/' && obj != '.' && obj != '\\') {
                printf("\n\nWARNING: Invalid symbol! You can only use '/' '\\' '.' or '+' \n");
                printf("Press enter to continue.");
                while (getchar() != '\n');
                getchar();
                continue;
            }

            if (row >= 0 && row < get_size && c >= 0 && c < get_size) {
                if (matrix[row][c] != 'K' && matrix[row][c] != 'H' && matrix[row][c] != '#' && matrix[row][c] != 'x' && matrix[row][c] != 'y' && matrix[row][c] != 'z' && matrix[row][c] != 'R' && matrix[row][c] != 'G' && matrix[row][c] != 'B') {
                    matrix[row][c] = obj;
                }
                else {
                    printf("\n\n\nYOU CAN'T PUT OBJECT %dth ROW AND %dth COLUMN\n", row, c);
                    printf("Press enter to continue.");
                    while (getchar() != '\n');
                    getchar();
                }
            }
        }
    }

    if (level == 101) printf("ARE YOU SERIOUS??? \nLEVEL 100!!! \nDON'T YOU HAVE A LIFE? \nGO OUTSIDE AND TOUCH GRASS!!!\n");

    return 0;
}
