#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

#include "sudoku_cell.h"
#include "sudoku_matrix.h"

static sudoku_matrix_t game_instance;

static bool insert_value_in_cell(unsigned, unsigned, cell_value_t, bool);

static void init_matrix()
{    
    int i,j;

    srand(time(NULL));

    for(i = 0; i < ROW_COUNT; i++)
    {       
        for(j = 0; j < COL_COUNT; j++)
        {            
            game_instance.cells[i][j].is_visible       = false;
            game_instance.cells[i][j].right_value      = CELL_VALUE_NONE;
            game_instance.cells[i][j].inserted_value   = CELL_VALUE_NONE;
            game_instance.cells[i][j].available_values = AVAILABLE_MASK_VALUE_ALL;
        }
    }
}

static bool has_one_value_left(sudoku_cell_t* cell)
{
    unsigned mask = 0x001;
    unsigned occurrence = 0;
    unsigned available_values = cell->available_values;

    for(unsigned i = 0; i < 9; i++)
    {
        if(available_values & mask)
        {
            occurrence++;
            if(occurrence > 1)
               return false;            
        }

        mask = mask << 1;
    }

    return true;    
}

static cell_value_t get_value_left(sudoku_cell_t* cell)
{
    unsigned mask = 0x001;
    unsigned available_values = cell->available_values;
    cell_value_t value = 0;
    for(unsigned i = 0; i < 9; i++)
    {
        if(available_values & mask)
        {
            if(value != 0)
                printf("Errore nell'assuzione che sia rimasto solo un valore");
            value = i + 1;
        }

        mask = mask << 1;
    }

    return value;  

}

static void update_row(unsigned row, cell_value_t cell_val)
{
    unsigned k;
    
    for(k = 0; k < COL_COUNT; k++)
    {
        game_instance.cells[row][k].available_values &= ~(1 << (cell_val - 1));
        if(has_one_value_left(&game_instance.cells[row][k]))
            insert_value_in_cell(row,k,get_value_left(&game_instance.cells[row][k]), false);            
    }
}

static void update_col(unsigned col, cell_value_t cell_val)
{
    unsigned k;
    
    for(k = 0; k < ROW_COUNT; k++)
    {
        game_instance.cells[k][col].available_values &= ~(1 << (cell_val - 1));
        if(has_one_value_left(&game_instance.cells[k][col]))
            insert_value_in_cell(k,col,get_value_left(&game_instance.cells[k][col]), false);
    }    
}

static void update_block(unsigned row, unsigned col, cell_value_t cell_val)
{
    unsigned block_row,block_col;
    unsigned i,j;
    unsigned b_row,b_col;

    if(row < 3)
        block_row = 0;
    else if(row > 5)
        block_row = 2;
    else
        block_row = 1;

    if(col < 3)
        block_col = 0;
    else if(col > 5)
        block_col = 2;
    else
        block_col = 1;
    
    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            b_row = block_row * 3 + i;
            b_col = block_col * 3 + j;
            game_instance.cells[b_row][b_col].available_values &= ~(1 << (cell_val - 1));
            if(has_one_value_left(&game_instance.cells[b_row][b_col]))
                insert_value_in_cell(b_row, b_col, get_value_left(&game_instance.cells[b_row][b_col]), false);
        }
    }
}

void print_available_values(sudoku_cell_t* cell)
{
    unsigned k;
    
    for(k = 1; k <= MAX_CELL_VALUE; k++)
    {
        if(cell->available_values & (1 << (k - 1)))
        {
            printf("%u ", k);
        }
    }   

    printf("\n", k);
}


static bool insert_value_in_cell(unsigned row, unsigned col, cell_value_t val, bool visible)
{
    available_values_mask_t available_values_mask = 1;
    available_values_mask_t available_values;

    if(game_instance.cells[row][col].right_value == CELL_VALUE_NONE)
    {
        printf("Trying inserting [%d][%d] = %d",row+1,col+1,val);

        if(game_instance.cells[row][col].available_values & (available_values_mask << (val - 1)))
        {
            printf(" DONE!!\n");
        
            game_instance.cells[row][col].available_values &= ~(available_values_mask << (val - 1));

            game_instance.cells[row][col].right_value = val;
            game_instance.cells[row][col].is_visible  = visible;

            printf("0x%X\n",game_instance.cells[row][col].available_values);
            
            update_row  (row,val);
            update_col  (col,val);
            update_block(row,col,val);

            game_instance.cells[row][col].available_values = AVAILABLE_MASK_VALUE_NONE;
            print_available_values(&game_instance.cells[row][col]);

            return true;            
        }        
    }
    
    return false;
}

static void insert_random_value_in_cell(bool visible){

    bool done = false;
    unsigned row,col;
    
    cell_value_t val;


    do{
    
        row = (rand() % 9);
        col = (rand() % 9);
        val = (rand() % 9) + 1;

        done = insert_value_in_cell(row, col, val, visible);
        
    }while(!done);

    printf("inserted [%d][%d] = %d\n",row+1,col+1,val);
}


void generate_sudoku_matrix(unsigned solved_cells, unsigned visible_cells){

    unsigned i, cells_left = solved_cells - visible_cells;

    assert(solved_cells >= visible_cells);

    init_matrix();

    insert_value_in_cell(1, 1, 9, true);

    for(i = 0; i < visible_cells; i++){
        insert_random_value_in_cell(CELL_VISIBLE);
    }

    for(i = 0; i < cells_left; i++){
        insert_random_value_in_cell(CELL_NOT_VISIBLE);
    }    
}

sudoku_matrix_t* get_game_instance_ptr()
{
    return &game_instance;
}

