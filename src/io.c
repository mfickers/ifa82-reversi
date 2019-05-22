/**
 * Represents the Input and Output Functions for a Reversi-Game
 *
 * Author: Maximilian Fickers, Julian G�rres, Fabian Heeke
 * Date: 03.04.2019
 **/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include "../include/board.h"
#include "../include/io.h"

#define TCRSS_RGHT 185
#define EDGE_VRTCL 186
#define CRNR_TP_RGHT 187
#define CRNR_BTM_RGHT 188
#define CRNR_BTM_LFT 200
#define CRNR_TP_LFT 201
#define TCRSS_BTM 202
#define TCRSS_TP 203
#define TCRSS_LFT 204
#define EDGE_HRZNTL 205
#define CRSS_CNTR 206

#define EMPTY 32
#define PLR_ONE 177
#define PLR_TWO 219
#define CRSR 220

#define INPT_ESC 27
#define INPT_UP 72
#define INPT_DWN 80
#define INPT_LFT 75
#define INPT_RGHT 77
#define INPT_ENTR 13
#define INPT_PSE 112
#define INPT_ONE 49
#define INPT_TWO 50
#define INPT_THREE 51

char screen[25][51];

void set_console_title()
{
    SetConsoleTitle("Reversi");
}

void render_pass(int player)
{
    printf("Player %d had to pass.\n\n", player);
    fflush(stdin);
    char c;
    scanf("%c", &c);
}

void render_game_over(int score_1, int score_2)
{
    printf("\n\nGAME OVER!\n\n");
    if (score_1 > score_2) {
        printf("Victory: Player One won with %d to %d points!", score_1, score_2);
    } else if (score_1 < score_2) {
        printf("Victory: Player Two won with %d to %d points!", score_2, score_1);
    } else {
        printf("Draw: Both Players are tied with %d points!", score_1);
    }

}
/**
 * Draw the lines of the board into the string array representing the game screen
 **/
void draw_board()
{
    for (int i = 6; i <= 22; i++) {
        for (int j = 6; j <= 38; j++) {
            if (i == 6) {
                // first line
                if (j == 6) {
                    screen[i][j] = CRNR_TP_LFT;
                } else if (j == 38) {
                    screen[i][j] = CRNR_TP_RGHT;
                } else if ((j - 10) % 4 == 0) {
                    screen[i][j] = TCRSS_TP;
                } else {
                    screen[i][j] = EDGE_HRZNTL;
                }
            } else if (i == 22) {
                // last line
                if (j == 6) {
                    screen[i][j] = CRNR_BTM_LFT;
                } else if (j == 38) {
                    screen[i][j] = CRNR_BTM_RGHT;
                } else if ((j - 10) % 4 == 0) {
                    screen[i][j] = TCRSS_BTM;
                } else {
                    screen[i][j] = EDGE_HRZNTL;
                }
            } else if ((i - 7) % 2 == 0) {
                // lines containing the markers
                if ((j - 6) % 4 == 0) {
                    screen[i][j] = EDGE_VRTCL;
                }
            } else {
                // lines between markes
                if (j == 6) {
                    screen[i][j] = TCRSS_LFT;
                } else if (j == 38) {
                    screen[i][j] = TCRSS_RGHT;
                } else if ((j - 10) % 4 == 0) {
                    screen[i][j] = CRSS_CNTR;
                } else {
                    screen[i][j] = EDGE_HRZNTL;
                }
            }
        }
    }
}

/**
 * Prepare the string array representing the game screen
 */
void prepare_screen()
{
    // Line up the strings for readability
    strcpy(screen[0],  "                                                  \0");
    strcpy(screen[1],  "          - - - R E V E R S I - - -               \0");
    strcpy(screen[2],  "                                                  \0");
    strcpy(screen[3],  " Score:  0:0                    Time: 00:00:00    \0");
    strcpy(screen[4],  "                                                  \0");
    strcpy(screen[5],  "        1   2   3   4   5   6   7   8             \0");
    strcpy(screen[6],  "                                                  \0");
    strcpy(screen[7],  "    A                                             \0");
    strcpy(screen[8],  "                                                  \0");
    strcpy(screen[9],  "    B                                             \0");
    strcpy(screen[10], "                                                  \0");
    strcpy(screen[11], "    C                                             \0");
    strcpy(screen[12], "                                                  \0");
    strcpy(screen[13], "    D                                             \0");
    strcpy(screen[14], "                                                  \0");
    strcpy(screen[15], "    E                                             \0");
    strcpy(screen[16], "                                                  \0");
    strcpy(screen[17], "    F                                             \0");
    strcpy(screen[18], "                                                  \0");
    strcpy(screen[19], "    G                                             \0");
    strcpy(screen[20], "                                                  \0");
    strcpy(screen[21], "    H                                             \0");
    strcpy(screen[22], "                                                  \0");
    strcpy(screen[23], "                                                  \0");
}

/**
 * Set the score on the screen array
 *
 * @param struct Board *board: The board
 **/
void draw_score(struct Board *board)
{
    int score_one = count_points(board, 1);
    int score_two = count_points(board, 2);

    char score[5];
    sprintf(score, "%2d:%-2d", score_one, score_two);

    for (int i = 0; i <= 4; i++) {
        screen[3][9 + i] = score[i];
    }
}

/**
 * Draw the game time in the screen array
 *
 * @param int seconds: The game time in seconds
 **/
void draw_time(int seconds)
{
    int minutes = seconds / 60;
    seconds = seconds % 60;
    int hours = minutes / 60;
    minutes = minutes % 60;

    char time[8];
    sprintf(time, "%02d:%02d:%02d", hours, minutes, seconds);


    for (int i = 0; i <= 7; i++) {
        screen[3][38 + i] = time[i];
    }
}

/**
 * Calculate the coord in the screen string array for an x coord
 **/
int x_screen(int x)
{
    return (x * 2) + 7;
}

/**
 * Calculate the coord in the screen string array for a y coord
 **/
int y_screen(int y)
{
    return (y * 4) + 8;
}

/**
 * Set all markers in the screen array
 *
 * @param struct Board *board: The board
 **/
void draw_markers(struct Board *board)
{
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            char field = EMPTY;

            if (board->fields[x][y] == 1) {
                field = PLR_ONE;
            } else if (board->fields[x][y] == 2) {
                field = PLR_TWO;
            }

            screen[x_screen(x)][y_screen(y)] = field;
        }
    }
}

/**
 * Draw the cursor on the given position
 *
 * @param struct Coord cursor: The cursor position
 **/
void draw_cursor(struct Coord cursor)
{
    screen[x_screen(cursor.x)][y_screen(cursor.y)] = CRSR;
}

/**
 * Clear the screen array of menu screens and redraw the board
 **/
void reset_renderer()
{
    prepare_screen();
    draw_board();
}

/**
 * Print the whole screen array to the console
 **/
void render()
{
    system("cls");

    for (int i = 0; i <= 23; i++) {
        printf("%s\n", screen[i]);
    }
}

/**
 * Draw all game elements to the screen array and render it
 *
 * @param struct Board *board: The board
 * @param int seconds: The game time in seconds
 : @param struct Coord cursor: The position of the cursor
 **/
void render_game(struct Board *board, int seconds, struct Coord cursor)
{
    draw_score(board);
    draw_time(seconds);
    draw_markers(board);
    draw_cursor(cursor);

    render();
}

void draw_menu()
{
    for (int i = 11; i <= 20; i++) {
        for (int j = 9; j <= 30; j++) {
            if (i == 11) {
                // first line
                if (j == 9) {
                    screen[i][j] = CRNR_TP_LFT;
                } else if (j == 30) {
                    screen[i][j] = CRNR_TP_RGHT;
                } else {
                    screen[i][j] = EDGE_HRZNTL;
                }
            } else if (i == 20) {
                // last line
                if (j == 9) {
                    screen[i][j] = CRNR_BTM_LFT;
                } else if (j == 30) {
                    screen[i][j] = CRNR_BTM_RGHT;
                } else {
                    screen[i][j] = EDGE_HRZNTL;
                }
            } else {
                if (j == 9 || j == 30) {
                    screen[i][j] = EDGE_VRTCL;
                } else {
                    screen[i][j] = EMPTY;
                }
            }
        }
    }
}

/**
 * Set the menu options in the screen array
 **/
void draw_menu_items(MenuState state)
{
    char item[3][17];

    switch (state) {
    case Select:
        strcpy(item[0], "1: New Game\0");
        strcpy(item[1], "2: Load Game\0");
        strcpy(item[2], "3: Exit\0");
        break;
    case Pause:
        strcpy(item[0], "1: Continue\0");
        strcpy(item[1], "2: Save Game\0");
        strcpy(item[2], "3: Exit\0");
        break;
    case PlayerOne:
    case PlayerTwo:
        strcpy(item[0], "1: Human\0");
        strcpy(item[1], "2: Cpu\0");
        strcpy(item[2], "\0");
        break;
    default:
        strcpy(item[0], "\0");
        strcpy(item[1], "\0");
        strcpy(item[2], "\0");
        break;
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 16 && item[i][j] != '\0'; j++) {
            screen[13 + 2 * i][11 + j] = item[i][j];
        }
    }
}

/**
 * Render the game menu
 **/
void render_menu(MenuState state)
{
    draw_menu();
    draw_menu_items(state);

    render();
}

MenuInput parse_menu_input(MenuState state, int input)
{
    switch (state) {
    case Select:
        switch (input) {
        case 1:
            input = New;
            break;
        case 2:
            input = Load;
            break;
        case 3:
            input = Exit;
            break;
        default:
            input = Invalid;
            break;
        }
        break;
    case Pause:
        switch (input) {
        case 1:
            input = Continue;
            break;
        case 2:
            input = Save;
            break;
        case 3:
            input = Exit;
            break;
        default:
            input = Invalid;
            break;
        }
        break;
    case PlayerOne:
    case PlayerTwo:
        switch (input) {
        case 1:
            input = HumanSelect;
            break;
        case 2:
            input = CpuSelect;
            break;
        default:
            input = Invalid;
            break;
        }
        break;
    default:
        input = Invalid;
        break;
    }

    return input;
}

MenuInput input_menu(MenuState state)
{
    MenuInput input;
    while (1) {
        switch (getch()) {
        case INPT_ONE:
            input = parse_menu_input(state, 1);
            break;
        case INPT_TWO:
            input = parse_menu_input(state, 2);
            break;
        case INPT_THREE:
            input = parse_menu_input(state, 3);
            break;
        default:
            input = Invalid;
        }

        if (input != Invalid) {
            return input;
        }
    }
}

struct Coord input_move(struct Board *board, int seconds, int player, struct Coord cursor)
{
    printf("It's player %d's turn!", player);

    while(1) {
        switch(getch()) {
            case INPT_UP:
                cursor.x--;
                if (cursor.x < 0) {
                    cursor.x = 0;
                }
                break;
            case INPT_DWN:
                cursor.x++;
                if (cursor.x > 7) {
                    cursor.x = 7;
                }
                break;
            case INPT_RGHT:
                cursor.y++;
                if (cursor.y > 7) {
                    cursor.y = 7;
                }
                break;
            case INPT_LFT:
                cursor.y--;
                if (cursor.y < 0) {
                    cursor.y = 0;
                }
                break;
            case INPT_ESC:
            case INPT_PSE:
                printf("paused");
            case INPT_ENTR:
                return cursor;
        }

        render_game(board, seconds, cursor);
    }
}
