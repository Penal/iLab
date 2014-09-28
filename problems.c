#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "problems.h"

int main()
{
    int number_of_problem = WRONG_INT;
    printf("Here\'re some programs from MIPT test in 2007\n"
        "What program would you like to execute?\n"
        "1. Transponation of the matrix(2A)\n"
        "2. Finding of n-th simple number(2C)\n"
        "3. Finding a sum of all dividers(5B)\n"
        "4. Symbol filtering(4B)\n"
        "5. Reversing words(4C)\n" //Hadn't finished
        "6. Sorting a students(5C)\n"
        "7. Finding numbers freed from squares(6C)\n" //Hadn't finished
        "8. Finding number of expansion(6D)\n" //Hadn't finished
        "9. Finding full squares(8B)\n" //Wrong work
        "10. Table of powers(10A)\n");
    scanf("%d", &number_of_problem);
    switch (number_of_problem)
    {
        case TRANSPONATE_MATRIX:
            transponate_matrix();
        break;
        case Nth_SIMPLE_NUMBER:
            nth_simple_number();
        break;
        case SUM_OF_ALL_DIVIDERS:
            sum_of_all_dividers();
        break;
        case SYMBOL_FILTER:
            symbol_filter();
        break;
        case WORDS_REVERSING:
        break;
        case SORTING_OF_STUDENTS:
            sorting_of_students();
        break;
        case FREED_FROM_SQUARES:
        break;
        case NUMBER_OF_EXPANSION:
        break;
        case FULL_SQUARES:
            full_squares();
        break;
        case TABLE_OF_POWERS:
            table_of_powers();
        break;
        default:
        break;
    }
    return 0;
}

int transponate_matrix ()
{
    int size = WRONG_INT;
    scanf ("%d", &size);
    if (size == WRONG_INT)
    {
        return WRONG_INT;
    }
    long** matrix = calloc(size, sizeof(*matrix));
    assert (matrix);
    for (int i = 0; i < size; i++)
    {
        matrix[i] = calloc(size, sizeof(**matrix));
        assert(matrix[i]);
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            scanf("%li", &matrix[i][j]);
        }
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            long temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%li ", matrix[i][j]);
        }
        printf("\n");
    }
    free(matrix);
    return 0;
}

int nth_simple_number()
{
    int n = WRONG_INT;
    scanf("%d", &n);
    if (n == WRONG_INT)
    {
        return WRONG_INT;
    }
    int* array_of_simple_numbers = calloc (n, sizeof(*array_of_simple_numbers));
    assert (array_of_simple_numbers);
    array_of_simple_numbers[0] = 2;
    for (int i = 1; i < n; i++)
    {
        array_of_simple_numbers[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = array_of_simple_numbers[i]+1;;j++)
        {
            int simplisity = SIMPLE;
            for (int k = 0; k <= i; k++)
            {
                if (j % array_of_simple_numbers[k] == 0)
                {
                    simplisity = NOT_SIMPLE;
                    break;
                }
            }
            if (simplisity)
            {
                array_of_simple_numbers[i+1] = j;
                break;
            }
        }
    }
    printf("%d\n", array_of_simple_numbers[n-1]);
    free(array_of_simple_numbers);
    return 0;
}

int symbol_filter()
{
    char input_symbol;
    int previous_is_space = FALSE;
    while ( (input_symbol = getchar()) != EOF)
    {
        if (input_symbol == '.' || input_symbol == ',' || input_symbol == '!'
            || input_symbol == '?')
        {
            previous_is_space = FALSE;
        }
        else if (input_symbol == ' ' || input_symbol == '\t')
        {
            if (!previous_is_space)
            {
                putchar(' ');
            }
            previous_is_space = TRUE;
        }
        else if (input_symbol >= 'A' && input_symbol <= 'Z')
        {
            putchar(input_symbol+SPACE_BETWEEN_a_AND_A);
            previous_is_space = FALSE;
        }
        else if (input_symbol >= '0' && input_symbol <= '9')
        {
            putchar('#');
            previous_is_space = FALSE;
        }
        else
        {
            putchar(input_symbol);
            previous_is_space = FALSE;
        }
    }
    return 0;
}


int words_reversing()
{
    char* output_string = calloc(MAX_STRING, sizeof(*output_string));
    char* begin_adress = output_string;
    char input_symbol;
    assert (output_string);
    while ( (input_symbol = getchar()) && (input_symbol != '\n'))
    {
        *output_string = input_symbol;
        output_string++;
    }
    output_string = begin_adress;
    free(begin_adress);
    for (int i = 0, j = strlen(output_string); i < strlen(output_string)/2; i++, j--)
    {
        char temp = output_string[i];
        output_string[i] = output_string[j];
        output_string[j] = temp;
    }
    printf("%s", output_string);
    free(output_string);
    return 0;
}

int sorting_of_students()
{
    int n = WRONG_INT;
    scanf("%d", &n);
    char** students_list = calloc (n, sizeof(*students_list));
    assert(students_list);
    int* students_marks = calloc (n, sizeof(*students_marks));
    assert(students_marks);
    for (int i = 0; i < n; i++)
    {
        students_list[i] = calloc(MAX_STUDENT_NAME, sizeof(**students_list));
        scanf ("%s %d", students_list[i], &students_marks[i]);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if ( strcmp(students_list[i], students_list[j]) > 0)
            {
                char* temp_string = calloc (MAX_STUDENT_NAME, sizeof(*temp_string));
                int temp_int;
                assert(temp_string);
                strcpy(temp_string,students_list[i]);
                temp_int = students_marks[i];
                strcpy(students_list[i],students_list[j]);
                students_marks[i] = students_marks[j];
                strcpy(students_list[j],temp_string);
                students_marks[j] = temp_int;
                free(temp_string);
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf("%s %d\n", students_list[i], students_marks[i]);
    }
    printf("\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if ( students_marks[i] < students_marks[j])
            {
                char* temp_string = calloc (MAX_STUDENT_NAME, sizeof(*temp_string));
                int temp_int;
                assert(temp_string);
                strcpy(temp_string,students_list[i]);
                temp_int = students_marks[i];
                strcpy(students_list[i],students_list[j]);
                students_marks[i] = students_marks[j];
                strcpy(students_list[j],temp_string);
                students_marks[j] = temp_int;
                free(temp_string);
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf("%s %d\n", students_list[i], students_marks[i]);
    }

    free(students_list);
    free(students_marks);
    return 0;
}

int sum_of_all_dividers()
{
    long n;
    scanf ("%li", &n);
    double sum = 0;
    for (long i = 1; i < n; i++)
    {
        if (n%i==0)
        {
            sum += (double) i;
        }
    }
    printf("%lg", sum);
    return 0;
}

int table_of_powers()
{
    int n;
    scanf ("%i", &n);
    for (int k = 0; k < n; k++)
    {
        for (int a = 1; a < n; a++)
        {
            printf("%li ", ((long) pow(a, k)) % n);
        }
        printf("\n");
    }
    return 0;
}

int is_square(long number)
{
    if (sqrt(number) - (long) number == 0)
    {
        return TRUE;
    }
    return FALSE;
}

int full_squares()
{
    int n;
    scanf ("%i", &n);
    long* output = calloc(n, sizeof(*output));
    assert(output);
    int counter = 0;
    for (int i = 0; i < n; i++)
    {
        long number;
        scanf ("%li", &number);
        if (is_square(number))
        {
            output[counter] = number;
            counter++;
        }
    }
    for (int i = 0; i <= counter; i++)
    {
        printf("%li ", output[counter]);
    }
    free(output);
    printf("\n");
    return 0;
}
