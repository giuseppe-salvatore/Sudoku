#include <stdio.h>
#include <stdlib.h>
#include "sudoku_cell.h"
#include "sudoku_matrix.h"

#include <stdbool.h>

int main(int argc, char* argv[])
{
    int i,j,initial_values;
    sudoku_matrix_t* game;
    unsigned occurrence[9];

    if(argc != 2)
    {
        printf("Define a start number\n");
        exit(-1);
    }

    sscanf(argv[1],"%d",&initial_values);        

    generate_sudoku_matrix(initial_values, initial_values);
    printf("Instance generated\n");
    game = get_game_instance_ptr();

    for(i = 0; i < ROW_COUNT; i++)
    {       
        occurrence[i] = 0;
        for(j = 0; j < COL_COUNT; j++)
        {        
            printf("\ncell[%d][%d] = %d\n\t",i+1,j+1,game->cells[i][j].right_value);    
            print_available_values(&game->cells[i][j]);
        }
    }


    for(i = 0; i < 1000; i++)
    {        
        j = rand() % 9;
        occurrence[j]++;            
    }


    for(i = 0; i < ROW_COUNT; i++)
    {       
        printf("Occurrence[%d] = %d\n",i,occurrence[i]);        
    }

    return 0; 
    
}
