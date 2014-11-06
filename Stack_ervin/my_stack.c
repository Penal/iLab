#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "stdint.h"
#include "my_stack.h"
#define $(param) my_stack_double_ok(param)

int My_stack_double_errno = 0;

my_stack_double* my_stack_double_new( size_t size)
{
    my_stack_double* rtr_p = (my_stack_double *) calloc (1, sizeof(*rtr_p));
    rtr_p->stack_pointer = (double*) calloc (size, sizeof(*(rtr_p->data)));
    assert(rtr_p->stack_pointer);
    rtr_p->size = size;
    rtr_p->data = rtr_p->stack_pointer;
    return rtr_p;
}

int my_stack_double_delete( my_stack_double * This)
{
    free (This->stack_pointer);
    free (This);
    return 0;
}

size_t my_stack_double_size( my_stack_double * This)
{
    size_t Size = (This->data - This->stack_pointer);
    return Size;
}

int my_stack_double_empty( my_stack_double * This)
{
    if(my_stack_double_size(This) == 0)
    {
        return TRUE;
    }
    return FALSE;
}

int my_stack_double_ok(my_stack_double* This)
{
    if (!This)
    {
        My_stack_double_errno = null_stack_pointer;
        return 0;
    }
    else if (!This->stack_pointer)
    {
        My_stack_double_errno = null_data_pointer;
        return 0;
    }
    else if (my_stack_double_size(This) > SIZE_MAX/2) //not <0 because size_t is unsigned
    {
        My_stack_double_errno = stack_underflow;
        return 0;
    }
    else if (my_stack_double_size(This) > This->size)
    {
        My_stack_double_errno = stack_overflow;
        return 0;
    }
    return 1;
}

int my_stack_double_push( my_stack_double * This, double data)
{
    if (!$(This))
    {
        my_stack_double_dump(This);
        printf("INVALID STACK IN THE BEGINNING OF STACK_PUSH\n");
        assert(NULL);
    }
    if(my_stack_double_full(This))
    {
        double* old_stack_pointer = This->stack_pointer;
        This->size *= 2;
        This->stack_pointer = (double*)realloc(This->stack_pointer, This->size
                *sizeof(*This->stack_pointer));
        assert(This->stack_pointer);
        long delta = This->stack_pointer - old_stack_pointer;
        This->data += delta;
    }
    *(This->data) = data;
    This->data++;
    if (!$(This))
    {
        my_stack_double_dump(This);
        printf("INVALID STACK IN THE END OF STACK_PUSH\n");
        assert(NULL);
    }
    return 0;
}

double my_stack_double_pop( my_stack_double * This)
{
    if (!$(This))
    {
        my_stack_double_dump(This);
        printf("INVALID STACK IN THE BEGINNING OF STACK_POP\n");
        assert(NULL);
    }
    double rtr_val = *(This->data-1);
    This->data--;
    if (my_stack_double_size(This) < This->size/2)
    {
        double* old_stack_pointer = This->stack_pointer;
        This->size /= 2;
        This->stack_pointer = (double*)realloc(This->stack_pointer, This->size
                *sizeof(*This->stack_pointer));
        assert(This->stack_pointer);
        long delta = This->stack_pointer - old_stack_pointer;
        This->data += delta;
    }
    if (!$(This))
    {
        my_stack_double_dump(This);
        printf("INVALID STACK IN THE END OF STACK_POP\n");
        assert(NULL);
    }
    return rtr_val;
}

void my_stack_double_dump( my_stack_double * This)
{
    my_stack_double_perror("Such situation occured");
    printf("Stack [");
    if ($(This))
    {
        printf("ok]");
    }
    else
    {
        printf("BAD!!!]");
    }
    printf(" [0x%lx] |||(GBG means GARBAGE)\n", (unsigned long)This);
    printf(" counter = %40li|\nmax_size = %40li|\n", my_stack_double_size(This), This->size);
    printf("DATA [0x%lx]:\n", (unsigned long)This->stack_pointer);
    if (This->stack_pointer)
    {
        for (long i = 0; i < This->size;i++)
        {
            printf("\tdata[%07li]=%30.10lg|",i,This->stack_pointer[i]);
            if (i >= my_stack_double_size(This) || My_stack_double_errno == stack_underflow)
            {
                printf("(GBG)");
            }
            printf("\n");
        }
    }
    printf("END OF DATA\n");
}

int my_stack_double_perror(char* bgn_of_msg)
{
    assert(bgn_of_msg);
    char* error_msg = ""; //I don't know why, but using allocation and free I get error messages
    assert (error_msg);
    switch (My_stack_double_errno)
    {
        case ok:    error_msg = "Everithing is ok :-)"; break;
        case stack_overflow:    error_msg = "Stack overflow"; break;
        case stack_underflow:   error_msg = "Stack underflow"; break;
        case null_stack_pointer:    error_msg = "Null stack pointer"; break;
        case null_data_pointer: error_msg = "Null data pointer"; break;
        default: sprintf(error_msg, "Unknown error #%i\n", (int)My_stack_double_errno); break;
    }
    printf("%s:%s\n", bgn_of_msg, error_msg);
    error_msg = NULL;
    return 0;
}

double my_stack_double_top( my_stack_double * This)
{
    if (!$(This))
    {
        my_stack_double_dump(This);
        printf("INVALID STACK IN THE BEGINNING OF STACK_TOP\n");
        assert(NULL);
    }
    return *(This->data-1);
    if (!$(This))
    {
        my_stack_double_dump(This);
        printf("INVALID STACK IN THE END OF STACK_TOP\n");
        assert(NULL);
    }
}

double my_stack_double_swap( my_stack_double * This)
{
    if (!$(This))
    {
        my_stack_double_dump(This);
        printf("INVALID STACK IN THE BEGINNING OF STACK_SWAP\n");
        assert(NULL);
    }
    double temp1 = my_stack_double_pop(This);
    double temp2 = my_stack_double_pop(This);
    my_stack_double_push(This, temp1);
    my_stack_double_push(This, temp2);
    if (!$(This))
    {
        my_stack_double_dump(This);
        printf("INVALID STACK IN THE END OF STACK_SWuAP\n");
        assert(NULL);
    }
    return 0;
}

int my_stack_double_full( my_stack_double* This)
{
    if(my_stack_double_size(This) >= This->size)
    {
        return TRUE;
    }
    return FALSE;
}

