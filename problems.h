enum {TRANSPONATE_MATRIX = 1, Nth_SIMPLE_NUMBER, SUM_OF_ALL_DIVIDERS,
    SYMBOL_FILTER, WORDS_REVERSING, SORTING_OF_STUDENTS,
        FREED_FROM_SQUARES, THE_MOST_FARED_POINTS, FULL_SQUARES,
        TABLE_OF_POWERS};

#define COORDINATES_NUMBER 2
#define X 0
#define Y 1

#define MAX_STRING 10000
#define MAX_STUDENT_NAME 30

#define WRONG_INT  -2048
#define WRONG_CHAR -1

#define TRUE 1
#define FALSE 0

#define SPACE_BETWEEN_a_AND_A ('a'-'A')
#define BEGIN 'A'
#define END 'Z'

int transponate_matrix();
int nth_simple_number();
int sum_of_all_dividers();
int symbol_filter();
int words_reversing();
int sorting_of_students();
int freed_from_squares();
int the_most_fared_points();
int full_squares();
int table_of_powers();
int is_square(long number);
double distance_between_two_points(double* first_point, double* second_point);
