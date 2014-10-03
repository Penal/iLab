enum {TRANSPONATE_MATRIX = 1, Nth_SIMPLE_NUMBER = 2, SUM_OF_ALL_DIVIDERS = 3,
    SYMBOL_FILTER = 4, WORDS_REVERSING = 5, SORTING_OF_STUDENTS = 6,
        FREED_FROM_SQUARES = 7, THE_MOST_FARTHEST_POINTS = 8, FULL_SQUARES = 9,
        TABLE_OF_POWERS = 10};

#define MAX_STRING 10000
#define MAX_STUDENT_NAME 30

#define WRONG_INT  -2048
#define WRONG_CHAR -1

#define TRUE 1
#define FALSE 0

#define SPACE_BETWEEN_a_AND_A ('a'-'A')
#define BEGIN 'A'
#define END 'Z'


struct Student
{
    int mark;
    char* name;
};

struct Point
{
    double x;
    double y;
};


int transponate_matrix();
int nth_simple_number();
int sum_of_all_dividers();
int symbol_filter();
int words_reversing();
int sorting_of_students();
int freed_from_squares();
int the_most_farthest_points();
int full_squares();
int table_of_powers();
int is_square(long number);
