#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
typedef unsigned char* T;

struct List_elem_t
{
    T data;
    struct List_elem_t *next;
    struct List_elem_t *prev;
};

struct List_t
{
    struct List_elem_t* head;
    struct List_elem_t* tail;
    long counter;
};

enum {FALSE = 0, TRUE = 1};
enum {FIRST=0, LAST = 1, BEFORE = 4, AFTER = 5};

enum
{
    GOOD_LIST = 0,
    NULL_LIST_P = 1,
    WRONG_LIST_HEAD,
    WRONG_LIST_TAIL,
    PREV_NEXT_CHAOS,
    NULL_IN_MID,
    NEG_COUNTER,
    UNEXP_RELEV
};

int List_errno = GOOD_LIST;

const int ONE_ELEMENT = 1;
const int WRONG_NUM = -13;
const int MAX_NUM_OF_SECOND = 2;

int List_ctor(struct List_t* list_p);
int List_dtor(struct List_t* list_p, FILE* dump_file);
int List_ok(struct List_t* list_p);
int List_dump(struct List_t* list_p, FILE* dump_file);
int List_insert(struct List_t* list_p, struct List_elem_t* elem_p, struct List_elem_t* elem_to_ins_p,
    int relevation, FILE* dump_file);
int List_delete(struct List_t* list_p, struct List_elem_t* elem_p, FILE* dump_file);
int List_swap(struct List_t* list_p, struct List_elem_t* elem_p1, struct List_elem_t* elem_p2,
    FILE* dump_file);
int List_find (struct List_t* list_p, T value,FILE* dump_file);

int List_elem_ctor(struct List_elem_t* elem_p, T value);
int List_elem_dtor(struct List_elem_t* elem_p, FILE* dump_file);

int write_header_to_html_dump(FILE* dump_file);
int print_msg_to_dump(char* msg, FILE* dump_file);
int make_ending_of_dump_file(FILE* dump_file);
char* List_strerror();
#endif // LIST_H_INCLUDED
