#ifndef MY_STACK_H
#define MY_STACK_H

#include <stddef.h> //reqired for size_t

enum {FALSE = 0, TRUE = 1};
//This is reqired
typedef struct
{
    double * data;
    double * stack_pointer;
    size_t size;
} my_stack_double;

my_stack_double * my_stack_double_new( size_t size);
int               my_stack_double_delete( my_stack_double * This);

size_t my_stack_double_size( my_stack_double * This);
int my_stack_double_empty( my_stack_double * This);

int my_stack_double_push( my_stack_double * This, double data);
double my_stack_double_pop( my_stack_double * This);
double my_stack_double_top( my_stack_double * This);
double my_stack_double_swap( my_stack_double * This);

void my_stack_double_dump( my_stack_double * This);

//This is an additional task
typedef struct
{
    void * data;
    void * stack_pointer;
    size_t size;
    size_t size_of_elem;
} my_stack;

my_stack * my_stack_new( size_t size);
int        my_stack_delete( my_stack * This, void element_delete());

size_t my_stack_size( my_stack * This);
int my_stack_empty( my_stack * This);

int my_stack_push( my_stack * This, void * data);
void * my_stack_pop( my_stack * This);
void * my_stack_top( my_stack * This);
void * my_stack_swap( my_stack * This);

void my_stack_dump( my_stack * This);

//This is mine
int my_stack_double_ok(my_stack_double* This);
int my_stack_double_perror(char* bgn_of_msg);

enum {ok = 0, stack_overflow = 1, stack_underflow=2, null_stack_pointer=3, null_data_pointer=4};
#endif  //MY_STACK_H
