/**
    List realization
    Roman Zavodskikh, 412, MIPT, Moscow, Russia, Earth, Solar System
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "list.h"

//#define DEBUG_LIST

#define $(type ,param) type##_ok(param)

#ifdef DEBUG_LIST
#define VALID_LIST(list_p, msg, dump_file) if(!$(List, list_p) ) \
{\
        print_msg_to_dump(msg, dump_file);\
        List_dump(list_p, dump_file);\
        assert(NULL);\
}
#else
#define VALID_LIST(list_p, msg, dump_file)
#endif // DEBUG_LIST

/**
    @brief Constructor of list

    This function makes empty list (in already allocated memory!!!)
    @param list_p Pointer where future list will lie.
    @return 0 always
*/
int List_ctor(struct List_t* list_p)
{
    list_p->head = list_p->tail = NULL;
    list_p->counter = 0;
    return 0;
}

/**
    @brief Validator of list. Writes to List_errno code of state of list

    @param list_p Pointer to list
    @return TRUE if stack is valid
    @return FALSE if stack is not valid
*/
int List_ok(struct List_t* list_p)
{
    if (!list_p)
    {
        List_errno = NULL_LIST_P;
        return FALSE;
    }
    else if(list_p->counter < 0)
    {
        List_errno = NEG_COUNTER;
        return FALSE;
    }
    else
    {
        struct List_elem_t* cur_elem_p = list_p->head;
        for (long i = 0; i < list_p->counter; i++)
        {
            if (cur_elem_p == NULL)
            {
                List_errno = NULL_IN_MID;
                return FALSE;
            }
            cur_elem_p = cur_elem_p->next;
        }
        if (cur_elem_p)
        {
            List_errno = WRONG_LIST_TAIL;
            return FALSE;
        }

        cur_elem_p = list_p->tail;
        for (long i = 0; i < list_p->counter; i++)
        {
            if (cur_elem_p == NULL)
            {
                List_errno = NULL_IN_MID;
                return FALSE;
            }
            cur_elem_p = cur_elem_p->prev;
        }
        if (cur_elem_p)
        {
            List_errno = WRONG_LIST_HEAD;
            return FALSE;
        }

        cur_elem_p = list_p->head;
        while (cur_elem_p)
        {
            if ( (cur_elem_p->prev && cur_elem_p->prev->next != cur_elem_p) ||
                (cur_elem_p->next && cur_elem_p->next->prev != cur_elem_p))
            {
                List_errno = PREV_NEXT_CHAOS;
                return FALSE;
            }
            cur_elem_p = cur_elem_p->next;
        }
    }
    List_errno = GOOD_LIST;
    return TRUE;
}

/**
    @brief This function print to dump file all information about list

    @param list_p Pointer to list
    @param dump_file File that will keep the information
    @return 0 alwys
*/
int List_dump(struct List_t* list_p, FILE* dump_file)
{
    #ifdef DEBUG_LIST
    assert(dump_file);
    fprintf(dump_file, "<div class=\"list_declaration\">\nList [");

    if ($(List, list_p))
    {
        fprintf(dump_file, "ok]");
    }
    else
    {
        fprintf(dump_file, "<font class=\"attention\">BAAAAAAAAAAAD!!!! %s</font>]",
            List_strerror());
    }

    fprintf(dump_file, " [%p], head:[%p], tail:[%p]\n<br/>", (void*)list_p, (void*)list_p->head,
        (void*)list_p->tail);
    fprintf(dump_file, "counter: %li<br/>", list_p->counter);

    struct List_elem_t* cur_elem = list_p->head;
    for (long i = 1; i <= list_p->counter ; i++)
    {
        fprintf(dump_file, "%03li)[%p] data:%s| prev:[%p], next[%p]<br/>", i, (void*)cur_elem,
            cur_elem->data, (void*)cur_elem->prev, (void*)cur_elem->next);
        if (cur_elem->next)
        {
            cur_elem = cur_elem->next;
        }
        else
        {
            break;
        }
    }

    fprintf(dump_file, "</div>");
    #endif // DEBUG_LIST
    return 0;
}

/**
    @brief Prints header to dump file

    @param dump_file Dump file
*/
int write_header_to_html_dump(FILE* dump_file)
{
    assert(dump_file);
    fprintf(dump_file, "<html>\n");
    fprintf(dump_file, "\t<head>\n");
    fprintf(dump_file, "\t\t<meta charset=utf-8>\n");
    fprintf(dump_file, "\t\t<link rel=\"stylesheet\" type=\"text/css\" href=\"./css.css\" />\n");
    fprintf(dump_file, "\t</head>\n");
    fprintf(dump_file, "\t<body>\n");
    return 0;
}

/**
    @brief This function will create (in already allocated memory) some list element (separately
        from list)

    @param elem_p Pointer to memory where element will lie
    @param value Value that element will contain
    @return 0 always
*/
int List_elem_ctor(struct List_elem_t* elem_p, T value)
{
    elem_p->data = value;
    elem_p->next = elem_p->prev = NULL;
    return 0;
}

/**
    @brief Writes end to dump file

    @param dump_file Dump file
*/
int make_ending_of_dump_file(FILE* dump_file)
{
    fprintf(dump_file, "</body>\n</html>");
    return 0;
}

/**
    @brief This function destroys the list

    @param list_p Pointer to list that will be destroyed
    @param dump_file File that will contain dump information (if any)
    @return 0 always
*/
int List_dtor(struct List_t* list_p, FILE* dump_file)
{
    VALID_LIST(list_p, "Invalid list in the beginning of List_dtor", dump_file);

    struct List_elem_t* cur_elem_p = list_p->head;
    for (long i = 0; i < list_p->counter; i++)
    {
        struct List_elem_t* next = cur_elem_p->next;
        List_elem_dtor(cur_elem_p, dump_file);
        cur_elem_p = next;
    }

    list_p->head = list_p->tail = NULL;
    list_p->counter = WRONG_NUM;
    return 0;
}

/**
    @brief Prints some info message in dump file

    @param msg Message that will be printed to dump file
    @param dump_file Dump file
    @return 0 always
*/
int print_msg_to_dump(char* msg, FILE* dump_file)
{
    fprintf(dump_file, "<div class=msg>%s</div><br/>", msg);
    return 0;
}

/**
    @brief This function will destroy some list element (separately from list)

    @param elem_p Pointer to memory where element lies
    @param dump_file Dump file
    @return 0 always
*/
int List_elem_dtor(struct List_elem_t* elem_p, FILE* dump_file)
{
    elem_p->data = NULL;
    elem_p->next = elem_p->prev = NULL;
    free(elem_p);
    return 0;
}

/**
    @brief This function insert some (already created) element to list

    @param list_p Pointer to list
    @param elem_p Pointer to element that will be landmark to insert element
    @param elem_to_ins_p Pointer to insertable element
    @param relevation Some code (FIRST, LAST, BEFORE or AFTER) that tell function where to
        insert element
    @see list.h
    @param dump_file Dump file
    @return 0 always
*/
int List_insert(struct List_t* list_p, struct List_elem_t* elem_p, struct List_elem_t* elem_to_ins_p,
    int relevation, FILE* dump_file)
{
    VALID_LIST(list_p, "Invalid list in the beginning of List_insert", dump_file);

    switch (relevation)
    {
        case FIRST:
            if(list_p->head)
            {
                list_p->head->prev = elem_to_ins_p;
            }
            elem_to_ins_p->next = list_p->head;
            elem_to_ins_p->prev = NULL;
            list_p->head = elem_to_ins_p;
            if(!list_p->tail)
            {
                list_p->tail = list_p->head;
            }
        break;

        case LAST:
            if(list_p->tail)
            {
                list_p->tail->next = elem_to_ins_p;
            }
            elem_to_ins_p->prev = list_p->tail;
            elem_to_ins_p->next = NULL;
            list_p->tail = elem_to_ins_p;
            if (!list_p->head)
            {
                list_p->head = list_p->tail;
            }
        break;

        case BEFORE:
            if(elem_p->prev)
            {
                elem_p->prev->next = elem_to_ins_p;
            }
            else
            {
                list_p->head = elem_to_ins_p;
            }
            elem_to_ins_p->prev = elem_p->prev;
            elem_to_ins_p->next = elem_p;
            elem_p->prev = elem_to_ins_p;
        break;

        case AFTER:
            if(elem_p->next)
            {
                elem_p->next->prev = elem_to_ins_p;
            }
            else
            {
                list_p->tail = elem_to_ins_p;
            }
            elem_to_ins_p->next = elem_p->next;
            elem_to_ins_p->prev = elem_p;
            elem_p->next = elem_to_ins_p;
        break;

        default:
            print_msg_to_dump("Some unexpected relevation in List_insert", dump_file);
            List_errno = UNEXP_RELEV;
        break;
    }

    list_p->counter++;
    VALID_LIST(list_p, "Invalid list in the end of List_insert", dump_file);
    return 0;
}

/**
    @brief This function delete element from list

    @param list_p Pointer to list where is deletable element
    @param elem_p Pointer to element from some list. This element will be deleted
    @param dump_file File that will contain dump information (if any)
    @return 0 always
*/
int List_delete(struct List_t* list_p, struct List_elem_t* elem_p, FILE* dump_file)
{
    VALID_LIST(list_p, "Invalid list in the beginning of List_delete", dump_file);

    if (elem_p->next && elem_p->prev)
    {
        elem_p->next->prev = elem_p->prev;
        elem_p->prev->next = elem_p->next;
    }
    else if (elem_p->next)
    {
        elem_p->next->prev = NULL;
        list_p->head = elem_p->next;
    }
    else if (elem_p->prev)
    {
        elem_p->prev->next = NULL;
        list_p->tail = elem_p->prev;
    }
    else
    {
        list_p->head = list_p->tail = NULL;
    }

    List_elem_dtor(elem_p, dump_file);
    list_p->counter--;
    VALID_LIST(list_p, "Invalid list in the end of List_delete", dump_file);
    return 0;
}

/**
    @return rtr_val A string that tells about state of list (takes info from List_errno)
*/
char* List_strerror()
{
    switch (List_errno)
    {
        case GOOD_LIST:                         return "Good list"; break;
        case NULL_LIST_P:                   return "Null list pointer"; break;
        case WRONG_LIST_HEAD:             return "Wrong list head"; break;
        case WRONG_LIST_TAIL:                return "Wrong list tail"; break;
        case PREV_NEXT_CHAOS:      return "Chaos in prevs and nexts"; break;
        case NULL_IN_MID:      return "Null pointer in the middle of list"; break;
        case NEG_COUNTER:                return "Negative counter"; break;
        case UNEXP_RELEV: return "Some unexpected relevation in insert"; break;
        default:                 return "Some unknown bad situation"; break;
    }
    return "Some unknown bad situation";
}

/**
    @brief Swap two elements in list

    @param list_p Pointer to list
    @param elem_p1 Pointer to 1st element that will be swapped
    @param elem_p2 Pointer to 2nd element that will be swapped
    @param dump_file Dump file
    @return 0 always
*/
int List_swap(struct List_t* list_p, struct List_elem_t* elem_p1, struct List_elem_t* elem_p2,
    FILE* dump_file)
{
    VALID_LIST(list_p, "Invalid list in the beginning of List_swap", dump_file);

    T temp = elem_p1->data;
    elem_p1->data = elem_p2->data;
    elem_p2->data = temp;

    VALID_LIST(list_p, "Invalid list in the end of List_swap", dump_file);
    return 0;
}

int List_find (struct List_t* list_p, T value,FILE* dump_file)
{
    VALID_LIST(list_p, "Invalid list in the beginning of List_find", dump_file);

    struct List_elem_t* cur_elem_p = list_p->head;
    int rtr_val = FALSE;

    for (long i = 0; i < list_p->counter; i++)
    {
        if (strcmp( (char*)cur_elem_p->data, (char*)value) == 0)
        {
            rtr_val = TRUE;
            break;
        }
        cur_elem_p = cur_elem_p->next;
    }

    VALID_LIST(list_p, "Invalid list in the end of List_find", dump_file);
    return rtr_val;
}
