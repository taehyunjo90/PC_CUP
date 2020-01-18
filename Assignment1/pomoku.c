#include "pomoku.h"
#include <stdio.h>

const size_t MAX_COL = 20;
const size_t MAX_ROW = 20;
const size_t MIN_COL = 10;
const size_t MIN_ROW = 10;

const int SCORE_INSERT_ROW = 3;
const int SCORE_INSERT_COLUMN = 3;
const int SCORE_REMOVE_ROW = 3;
const int SCORE_REMOVE_COLUMN = 3;
const int SCORE_SWAP_ROW = 2;
const int SCORE_SWAP_COLUMN = 2;
const int SCORE_COPY_ROW = 4;
const int SCORE_COPY_COLUMN = 4;

const int BLANK_PLACE = -1;

size_t g_col_count;
size_t g_row_count;

int g_score[2];
int g_board[20][20];


void init_game(void)
{
    size_t i;
    size_t j;
    
    g_col_count = 15;
    g_row_count = 15;
    g_score[0] = 0;
    g_score[1] = 0;
    
    for (i = 0; i < MAX_ROW; ++i) {
        for (j = 0; j < MAX_COL; ++j) {
            g_board[i][j] = BLANK_PLACE;
        }
    }
}

size_t get_row_count(void)
{
    return g_row_count;
}

size_t get_column_count(void)
{
    return g_col_count;
}

int get_score(const color_t color)
{
    if (color > COLOR_WHITE) {
        return -1;
    } else {
        return g_score[color];
    }
}

int get_color(const size_t row, const size_t col)
{   
    if (row >= get_row_count() || col >= get_column_count() || row == (size_t) - 1 || col == (size_t) - 1) {
        return -1;
    } else {
        return g_board[row][col];
    }
}

int is_placeable(const size_t row, const size_t col)
{
    int not_exist;

    if (row >= get_row_count() || col >= get_column_count()) {
        not_exist = 0;
        return not_exist;
    }

    if (g_board[row][col] == BLANK_PLACE) {
        not_exist = 1;
    } else {
        not_exist = 0;
    }
    
    return not_exist;
}

int place_stone(const color_t color, const size_t row, const size_t col)
{
    if (is_placeable(row, col)) {
        g_board[row][col] = color;
        g_score[color] += get_new_score_by_placed_stone(color, row, col);
        return 1;
    } else {
        return 0;
    }
}

int get_new_score_by_placed_stone(const color_t color, const size_t row, const size_t col)
{
    int new_score = 0;
    
    new_score += get_new_score_by_vector(color, row, col, 1, 0);
    new_score += get_new_score_by_vector(color, row, col, 0, 1);
    new_score += get_new_score_by_vector(color, row, col, 1, 1);
    new_score += get_new_score_by_vector(color, row, col, -1, 1);
    
    
    return new_score;
}

int get_new_score_by_vector(const color_t color, const size_t row, const size_t col, const int x, const int y)
{
    int num_connected_stone = 0;
    int new_score;
    
    int minus_x = x * -1;
    int minus_y = y * -1;
    
    num_connected_stone = get_num_connected_stone(color, row, col, x, y, num_connected_stone);
    num_connected_stone = get_num_connected_stone(color, row, col, minus_x, minus_y, num_connected_stone);
    
    if (num_connected_stone >= 5) {
        new_score = num_connected_stone - 1 - 4;
    } else {
        new_score = 0;
    }
    
    return new_score;
}

int get_num_connected_stone(const color_t color, const size_t row, const size_t col, const int x, const int y, int num_connected_stone)
{
    int target_board_place_stone = g_board[row][col];
    
    if (target_board_place_stone != color || row >= get_row_count() || col >= get_column_count() || row == (size_t) - 1 || col == (size_t) - 1) {
        return num_connected_stone;
    } else {
        num_connected_stone ++;
        return get_num_connected_stone(color, row + x, col + y, x, y, num_connected_stone);
    }    
}

int insert_row(const color_t color, const size_t row)
{
    size_t i;
    size_t j;
    size_t cur_row;
    size_t cur_col;
    size_t reverse_i;
    
    if (get_row_count() >= MAX_ROW || g_score[color] < SCORE_INSERT_ROW || row > get_row_count()) {
        return 0;
    }
    
    g_score[color] -= SCORE_INSERT_ROW;
    
    cur_row = get_row_count();
    cur_col = get_column_count();
    
    for (i = 0; i < cur_row - row; ++i) {
        reverse_i = cur_row - i;
        for (j = 0; j < cur_col; ++j) {
            g_board[reverse_i][j] = g_board[reverse_i - 1][j];
        }
    }
    
    for (j = 0; j < cur_col; ++j) {
        g_board[row][j] = BLANK_PLACE;
    }
    
    g_row_count ++;
    
    return 1;
}

int insert_column(const color_t color, const size_t col)
{
    size_t i;
    size_t j;
    size_t cur_row;
    size_t cur_col;
    size_t reverse_i;
    
    if (get_column_count() >= MAX_COL || g_score[color] < SCORE_INSERT_COLUMN || col > get_column_count()) {
        return 0;
    }

    g_score[color] -= SCORE_INSERT_COLUMN;
    
    cur_row = get_row_count();
    cur_col = get_column_count();
    
    for (i = 0; i < cur_col - col; ++i) {
        reverse_i = cur_col - i;
        for (j = 0; j < cur_row; ++j) {
            g_board[j][reverse_i] = g_board[j][reverse_i - 1];
        }
    }
    
    for (j = 0; j < cur_row; ++j) {
        g_board[j][col] = BLANK_PLACE;
    }
    
    g_col_count ++;
    
    return 1;

}

int remove_row(const color_t color, const size_t row)
{   
    
    size_t i;
    size_t j;
    size_t cur_row;
    size_t cur_col;

    if (get_row_count() <= MIN_ROW || g_score[color] < SCORE_REMOVE_ROW || row > get_row_count() - 1) {
        return 0;
    }
    
    g_score[color] -= SCORE_REMOVE_ROW;
    
    cur_row = get_row_count();
    cur_col = get_column_count();
    
    for (i = row; i < cur_row; ++i) {
        if (i != cur_row - 1) {
            for (j = 0; j < cur_col; ++j) {
                g_board[i][j] = g_board[i + 1][j];
            }
        } else {
            for (j = 0; j < cur_col; ++j) {
                g_board[i][j] = BLANK_PLACE;
            }
        }
    }
    
    g_row_count --;
    
    return 1;   
}

int remove_column(const color_t color, const size_t col)
{
    size_t i;
    size_t j;
    size_t cur_row;
    size_t cur_col;

    if (get_column_count() <= MIN_COL || g_score[color] < SCORE_REMOVE_COLUMN || col > get_column_count() - 1) {
        return 0;
    }
    
    g_score[color] -= SCORE_REMOVE_COLUMN;
    
    cur_row = get_row_count();
    cur_col = get_column_count();
    
    for (i = col; i < cur_col; ++i) {
        if (i != cur_col - 1) {
            for (j = 0; j < cur_row; ++j) {
                g_board[j][i] = g_board[j][i + 1];
            }
        } else {
            for (j = 0; j < cur_row; ++j) {
                g_board[j][i] = BLANK_PLACE;
            }
        }
    }
    
    g_col_count --;
    
    return 1;   
}

int swap_rows(const color_t color, const size_t row0, const size_t row1)
{
    size_t i;
    size_t cur_col;
    int temp_for_swap;
    
    /* 실행 가능 여부 판단 -> row 가능 범위 조건 추가?*/
    if (g_score[color] < SCORE_SWAP_ROW || row0 > get_row_count() - 1 || row1 > get_row_count() - 1) {
        return 0;
    }
    
    cur_col = get_column_count();
    g_score[color] -= SCORE_SWAP_ROW;
    
    for (i = 0; i < cur_col; ++i) {
        temp_for_swap = g_board[row0][i];
        g_board[row0][i] = g_board[row1][i];
        g_board[row1][i] = temp_for_swap;
    }
    
    return 1;
}

int swap_columns(const color_t color, const size_t col0, const size_t col1)
{
    size_t i;
    size_t cur_row;
    int temp_for_swap;
    
    /* 실행 가능 여부 판단 -> row 가능 범위 조건 추가?*/
    if (g_score[color] < SCORE_SWAP_COLUMN || col0 > get_column_count() - 1 || col1 > get_column_count() - 1) {
        return 0;
    }
    
    cur_row = get_row_count();
    g_score[color] -= SCORE_SWAP_COLUMN;
    
    for (i = 0; i < cur_row; ++i) {
        temp_for_swap = g_board[i][col0];
        g_board[i][col0] = g_board[i][col1];
        g_board[i][col1] = temp_for_swap;
    }
    
    return 1;
}

int copy_row(const color_t color, const size_t src, const size_t dst)
{
    size_t i;
    size_t cur_col;
    
    /* 실행 가능 여부 판단 -> row 가능 범위 조건 추가?*/
    if (g_score[color] < SCORE_COPY_ROW || src > get_row_count() - 1 || dst > get_row_count() - 1) {
        return 0;
    }
    
    cur_col = get_column_count();
    g_score[color] -= SCORE_COPY_ROW;
    
    for (i = 0; i < cur_col; ++i) {
        g_board[dst][i] = g_board[src][i];
    }
    
    return 1;
}

int copy_column(const color_t color, const size_t src, const size_t dst)
{
    size_t i;
    size_t cur_row;
    
    if (g_score[color] < SCORE_COPY_COLUMN || src > get_column_count() - 1 || dst > get_column_count() - 1) {
        return 0;
    }
    
    cur_row = get_row_count();
    g_score[color] -= SCORE_COPY_COLUMN;
    
    for (i = 0; i < cur_row; ++i) {
        g_board[i][dst] = g_board[i][src];
    }
    
    return 1;
}


void print_board(void)
{
    int row = get_row_count();
    int col = get_column_count();
    int i;
    int j;
    
    for (i = 0; i < row; ++i) {
        for (j = 0; j < col; ++j) {
            printf("%d/", g_board[i][j]);
        }
        printf("\n");
    }
    /* printf("g_score :: black : %d white : %d", g_score[COLOR_BLACK], g_score[COLOR_WHITE]); */
    printf("\n");
    
}
