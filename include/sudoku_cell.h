#ifndef SUDOKU_CELL_H
#define SUDOKU_CELL_H

#include <stdbool.h>

#define CELL_VISIBLE     true
#define CELL_NOT_VISIBLE  false

#define MAX_CELL_VALUE              9

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

} sudoku_cell_t;


#endif /* SUDOKU_CELL_H */
