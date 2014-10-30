#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "problems.h"

/**
* \brief This is the my homework program on the 03 October of 2014.
*
* Here're 10 solven problems from MIPT test of 2007 year.
* @param There're no parameters
* @return Returns 0 if there's no critical errors.
*/
int main()
{
    int number_of_problem = WRONG_INT;
    printf("Here\'re some programs from MIPT test in 2007\n"
        "What program would you like to execute?\n"
        "1. Transponation of the matrix(2A)\n"
        "2. Finding of n-th simple number(2C)\n"
        "3. Finding a sum of all dividers(5B)\n"
        "4. Symbol filtering(4B)\n"
        "5. Reversing words(4C)\n"
        "6. Sorting a students(5C)\n"
        "7. Finding numbers freed from squares(6C)\n"
        "8. The most farest points(7B)\n" //
        "9. Finding full squares(8B)\n"
        "10. Table of powers(10A)\n");


    scanf("%d", &number_of_problem);
    switch (number_of_problem)
    {
        case TRANSPONATE_MATRIX:    transponate_matrix();   break;
        case Nth_SIMPLE_NUMBER:     nth_simple_number();    break;
        case SUM_OF_ALL_DIVIDERS:   sum_of_all_dividers();    break;
        case SYMBOL_FILTER:         symbol_filter();    break;
        case WORDS_REVERSING:   words_reversing();  break;
        case SORTING_OF_STUDENTS:   sorting_of_students();  break;
        case FREED_FROM_SQUARES:    freed_from_squares();   break;
        case THE_MOST_FARTHEST_POINTS: the_most_farthest_points();    break;
        case FULL_SQUARES:  full_squares();     break;
        case TABLE_OF_POWERS:     table_of_powers();    break;
        default:    printf("Wrong input, sorry!\n");    break;
    }
    return 0;
}

/**
* \brief Function prints some numbers that freed from squares
*
* This function takes from standart input number of numbers that will be checked and
* then these numbers too.
* @param There're no parameters.
* @return Always returns 0, if there's no critical errors.
*/
int freed_from_squares()
{
    int number_of_input_numbers = WRONG_INT;
    scanf ("%i", &number_of_input_numbers);
    long* input_numbers = calloc (number_of_input_numbers, sizeof(*input_numbers));
    assert(input_numbers);
    for (int i = 0; i < number_of_input_numbers; i++)
    {
        scanf("%li", &input_numbers[i]);
    }


    for (int i = 0; i < number_of_input_numbers; i++)
    {
        int this_is_freed_from_squares = TRUE;
        for (long j = 2; j <= input_numbers[i]/2 + 1; j++)
        {
            if (j == input_numbers[i]/2 + 1)
            {
                j = input_numbers[i];
            }

            if (input_numbers[i] % j == 0 && is_square(j))
            {
                this_is_freed_from_squares = FALSE;
                break;
            }
        }
        if (this_is_freed_from_squares)
        {
            printf("%li ", input_numbers[i]);
        }
    }
    printf("\n");

    free(input_numbers);
    input_numbers = 0;
    return 0;
}

/**
* \brief Transponates the matrix
*
* This function transonates the matrix. Functions gets it from standart input (size of square
* matrix at first and the matrix itself then). After it function prints in standart output
* transponated matrix
* @param There're no parameters
* @return Returns 0, if there're no critical errors.
*/
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


    for (int i = 0; i < size; i++)
    {
        free(matrix[i]);
        matrix[i] = 0;
    }
    free(matrix);
    matrix = 0;
    return 0;
}

/**
* \brief This function prints n-th simple number
*
* This functions gets an natural number (n) and then prints n-th simple number in a
* standart output.
* @param There're no parameters.
* @return Returns 0, if there're no critical errors.
*/
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
            int is_simple = TRUE;
            for (int k = 0; k <= i; k++)
            {
                if (j % array_of_simple_numbers[k] == 0)
                {
                    is_simple = FALSE;
                    break;
                }
            }
            if (is_simple)
            {
                array_of_simple_numbers[i+1] = j;
                break;
            }
        }
    }


    printf("%d\n", array_of_simple_numbers[n-1]);


    free(array_of_simple_numbers);
    array_of_simple_numbers = 0;
    return 0;
}

/**
* \brief This function filters all string that it gets.
*
* This function gets from standart input string until it gets EOF symbol. Also it prints
* this strings changed by this rules:
* 1) All digits will be changed to #
* 2) There won't be more than one space between two words
* 3) All big letters get smaller
* 4) All punctuation signs won't be erased
* @param There're no parameters
* @return Returns 0, if there're no critical errors.
*/
int symbol_filter()
{
    char input_symbol = WRONG_CHAR;
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
        else if ( isupper(input_symbol) ) //(BEGIN <= input_symbol && input_symbol <= END)
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

/**
* \brief This function prints reversed string
*
* This function gets from standart input some string (ended with '\n') and prints this string
* reversed.
* @param There're no parameters
* @return Returns 0, if there're no critical errors.
*/
int words_reversing()
{
    char* output_string = calloc(MAX_STRING, sizeof(*output_string));
    assert (output_string);
    getchar();
    scanf("%[^\n]s", output_string);


    for (int i = strlen(output_string) - 1; i >= 0; i--)
    {
        putchar(output_string[i]);
    }


    free(output_string);
    output_string = 0;
    return 0;
}

/**
* \brief This function gets list of students and sorts it by marks and by names.
*
* This function gets number of students from standats output at first, then gets all students
* and their marks and than prints two sortes lists: by marks and by students' names.
* @param There're no parameters
* @return Returns 0, if there're no critical errors.
*/
int sorting_of_students()
{
    int n = WRONG_INT;
    scanf("%d", &n);
    //char** students_list = calloc (n, sizeof(*students_list));
    struct Student* students_list = calloc(n, sizeof(*students_list) );
    assert(students_list);
    for (int i = 0; i < n; i++)
    {
        students_list[i].name = calloc (MAX_STUDENT_NAME, sizeof(*(students_list[i].name)));
        scanf ("%s %d", students_list[i].name, &(students_list[i].mark));
    }


    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if ( strcmp(students_list[i].name, students_list[j].name) > 0)
            {
                char* temp_pointer = students_list[i].name;
                students_list[i].name = students_list[j].name;
                students_list[j].name = temp_pointer;
                temp_pointer = 0;

                int temp_int = students_list[i].mark;
                students_list[i].mark = students_list[j].mark;
                students_list[j].mark = temp_int;
            }
        }
    }


    for (int i = 0; i < n; i++)
    {
        printf("%s %d\n", students_list[i].name, students_list[i].mark);
    }
    printf("\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if ( students_list[i].mark < students_list[j].mark)
            {
                char* temp_pointer = students_list[i].name;
                students_list[i].name = students_list[j].name;
                students_list[j].name = temp_pointer;
                temp_pointer = 0;

                int temp_int = students_list[i].mark;
                students_list[i].mark = students_list[j].mark;
                students_list[j].mark = temp_int;
            }
        }
    }


    for (int i = 0; i < n; i++)
    {
        printf("%s %d\n", students_list[i].name, students_list[i].mark);
    }

    free(students_list);
    students_list = 0;
    return 0;
}

/**
* \brief This function prints sum of all dividers of a number.
*
* This function gets a number from a standart input and then prints a sum of all its
* dividers.
* @param There're no parameters
* @return Returns 0, if there're no critical errors.
*/
int sum_of_all_dividers()
{
    long n = WRONG_INT;
    scanf ("%li", &n);
    double sum = 0;


    for (long i = 1; i < n; i++)
    {
        if (n%i==0)
        {
            sum += i;
        }
    }


    printf("%lg", sum);
    return 0;
}

/**
* \brief This function prints table of powers
*
* This function gets a number (n) from a standart input and then prints table of the
* remainders from dividing a^k by n.
* a is in [1, n-1]
* k is in [0, n-1]
* @param There're no parameters
* @return Returns 0, if there're no critical errors.
*/
int table_of_powers()
{
    int n = WRONG_INT;
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

/**
* \brief This is auxillary function to full_squares()
*
* This function let you know if your number if full square or not.
* @param number is the cheked number
* @return Returns TRUE ( = 1) or FALSE ( = 0)
* @see full_squares()
*/
int is_square(long number)
{
    if (sqrt(number) - (long) sqrt(number) == 0)
    {
        return TRUE;
    }
    return FALSE;
}

/**
* \brief This function prints only full square numbers
*
* This function gets a number of chekable numbers and then prints some of them that are
* not full suqares
* @param There're no parameters
* @return Returns 0, if there're no critical errors.
*/
int full_squares()
{
    int n = WRONG_INT;
    scanf ("%i", &n);
    long* output = calloc(n, sizeof(*output));
    assert(output);
    for (int i = 0; i < n; i++)
    {
        output[i] = WRONG_INT;
    }


    int counter = 0;
    for (int i = 0; i < n; i++)
    {
        long number = WRONG_INT;
        scanf ("%li", &number);
        if (is_square(number))
        {
            output[counter] = number;
            counter++;
        }
    }


    for (int i = 0; i < counter; i++)
    {
        printf("%li ", output[i]);
    }


    free(output);
    output = 0;
    printf("\n");
    return 0;
}

/**
* \brief This function prints the most fared points from list
*
* This function gets the number of points and then these points and
* prints what points are the most fared and how far they are.
* @param There're no parameters
* @return Returns 0, if there're no critical errors.
*/
int the_most_farthest_points()
{
    int number_of_points = WRONG_INT;
    scanf("%i", &number_of_points);
    struct Point* points = calloc (number_of_points, sizeof (*points) );
    assert(points);
    for (int i = 0; i < number_of_points; i++)
    {
        scanf ("%lg %lg", &(points[i].x), &(points[i].y) );
    }


    double maximal_distance = WRONG_INT;
    long two_numbers_of_the_farest_points[2] = {WRONG_INT, WRONG_INT};


    for (int i = 0; i < number_of_points; i++)
    {
        for (int j = i; j < number_of_points; j++)
        {
            if (maximal_distance < hypot(points[i].x - points[j].x, points[i].y - points[j].y) )
            {
                maximal_distance = hypot(points[i].x - points[j].x, points[i].y - points[j].y);
                two_numbers_of_the_farest_points[0] = i;
                two_numbers_of_the_farest_points[1] = j;
            }
        }
    }


    printf("%li %li\n", two_numbers_of_the_farest_points[0] + 1,
        two_numbers_of_the_farest_points[1] + 1);
    printf("%lg\n", maximal_distance);


    free(points);
    points = 0;
    return 0;
}
