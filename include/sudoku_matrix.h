#ifndef SUDOKU_MATRIX_H
#define SUDOKU_MATRIX_H

#include <stdbool.h>
#include "sudoku_cell.h"

#define ROW_COUNT 9
#define COL_COUNT 9

typedef unsigned char index_t;

typedef struct
{    
    sudoku_cell_t cells[ROW_COUNT][COL_COUNT];

} sudoku_matrix_t;

void print_available_values(sudoku_cell_t* cell);

void generate_sudoku_matrix(unsigned solved_cells, unsigned visible_cells);

/*
void generate_empty_sudoku_matrix();
void generate_solved_sudoku_matrix();
*/

sudoku_matrix_t* get_game_instance_ptr();

cell_value_t sudoku_matrix_get_inserted_value(index_t row, index_t col);

void         sudoku_matrix_set_inserted_value(index_t row, index_t col);


cell_value_t sudoku_matrix_get_right_value(index_t row, index_t col);

void         sudoku_matrix_set_right_value(index_t row, index_t col);



/*
#define CELL_VALUE_NONE             0
#define AVAILABLE_MASK_VALUE_ALL    511
#define AVAILABLE_MASK_VALUE_NONE   0

#define SET_USED_VALUE(value,position)   (value ||  (1 << (position - 1)))
#define UNSET_USED_VALUE(value,position) (value && ~(1 << (position - 1)))

typedef unsigned short available_values_mask_t;
typedef unsigned char  cell_value_t;


typedef struct{
    
    available_values_mask_t available_values;
    cell_value_t            inserted_value;
    cell_value_t            right_value;
    bool                    is_visible;

} Cell;
*/

#endif /* SUDOKU_MATRIX_H */
