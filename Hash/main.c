#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

//#define DEBUG_HASH

#ifdef DEBUG_HASH
#define VALID_HASH(hash_p, msg, dump_file) \
if(!Hash_ok(hash_p, dump_file))\
{\
    print_msg_to_dump(msg, dump_file);\
    Hash_dump(hash_p, dump_file);\
    assert(NULL);\
}
#else
#define VALID_HASH(hash_p, msg, dump_file)
#endif // DEBUG_HASH

int main(int argc, char** argv)
{
    assert(argc==2);

    FILE* dump_file = fopen("dump.html", "w");
    assert(dump_file);
    write_header_to_html_dump(dump_file);

    struct Hash_t* HASH_P = (struct Hash_t*)calloc(ONE_ELEMENT, sizeof(*HASH_P));
    assert(HASH_P);
    Hash_ctor(HASH_P, dump_file);

    FILE* book_file = fopen(argv[1], "r");
    assert(book_file);

    FILE* csv_file = fopen(get_csv_file_name(argv[1]), "w");
    assert(csv_file);

    unsigned char* book_buffer = create_book_buffer(book_file);
    unsigned char* const begin_of_book_buffer = book_buffer;
    fclose(book_file);
    book_file = NULL;

    unsigned char** book_words = create_book_words_array(book_file);
    for (long i = 0; *book_buffer != '\0'; i++)
    {
        sscanf((char*)book_buffer, "%s", (char*)book_words[i]);
        move_to_next_word(&book_buffer);
    }
    book_buffer = begin_of_book_buffer;
    free(book_buffer);
    book_buffer = NULL;

    Hash_f_t HASH_FUNCS[] =
    {
        HASH_F1,
        HASH_F2,
        HASH_F3,
        HASH_F4,
        HASH_F5
    };

    for (int i = 0; i < NUM_OF_FUNCS; i++)
    {
        Hash_set_function(HASH_P, HASH_FUNCS[i], dump_file);
        for (long j = 0; book_words[j][0] != '\0'; j++)
        {
            if (!Hash_find(HASH_P, book_words[j], dump_file))
            {
                Hash_insert(HASH_P, book_words[j], dump_file);
            }
        }
        Write_hash_data_to_csv(HASH_P, csv_file, dump_file);
        Hash_dump(HASH_P, dump_file);
        Hash_clean(HASH_P, dump_file);
    }

    fclose(csv_file);
    csv_file = NULL;
    Hash_dump(HASH_P, dump_file);
    Hash_dtor(HASH_P, dump_file);
    make_ending_of_dump_file(dump_file);
    free(HASH_P);
    HASH_P = NULL;
    fclose(dump_file);
    dump_file = NULL;
    destroy_book_words_array(book_words);
    book_words = NULL;
    return 0;
}

int HASH_F1 (T* value)
{
    return 1;
}

int HASH_F2 (T* value)
{
    assert(value);
    return (*value)[0];
}

int HASH_F3 (T* value)
{
    return strlen((char*)*value);
}

int HASH_F4 (T* value)
{
    long rtr_val = 0;
    unsigned char* string = *value;
    for (long i = 0; string[i] != '\0'; i++)
    {
        rtr_val += string[i];
    }
    return rtr_val;
}

int HASH_F5 (T* value)
{
    long rtr_val = 0;
    unsigned char* string = *value;
    for (long i = 0; string[i] != '\0'; i++)
    {
        rtr_val = (rtr_val << 1) ^ string[i];
    }
    return rtr_val;
}

int Hash_ctor(struct Hash_t* HASH_P,FILE* dump_file)
{
    HASH_P->hash_f = NULL;
    HASH_P->headers = (struct List_t*)calloc(NUM_OF_HEADERS_IN_HASH,
         sizeof(*(HASH_P->headers)));
    List_ctor(HASH_P->headers);
    HASH_P->num_of_headers = NUM_OF_HEADERS_IN_HASH;
    return 0;
}

int Hash_ok(struct Hash_t* HASH_P,FILE* dump_file)
{
    if (!List_ok(HASH_P->headers))
    {
        Hash_errno = WRONG_HASH_LIST;
        return FALSE;
    }
    Hash_errno = GOOD_HASH;
    return TRUE;
}

int Hash_dtor(struct Hash_t* HASH_P,FILE* dump_file)
{
    VALID_HASH(HASH_P, "Invalid hash in the beginning of Hash_dtor", dump_file);

    HASH_P->hash_f = NULL;

    List_dtor(HASH_P->headers, dump_file);
    free(HASH_P->headers);
    HASH_P->headers = NULL;

    HASH_P->num_of_headers = WRONG_NUM;
    return 0;
}

int Hash_dump(struct Hash_t* HASH_P,FILE* dump_file)
{
    #ifdef DEBUG_HASH
    assert(dump_file);

    fprintf(dump_file, "<div class=hash_declaration>Hash [");
    if(!Hash_ok(HASH_P, dump_file))
    {
        fprintf(dump_file, "ok]");
    }
    else
    {
        fprintf(dump_file, "<font class=\"attention\">BAAAAAAAAAAAD!!!! %s</font>]",
            Hash_strerror());
    }
    fprintf(dump_file, "<br/>Num of headers: %li|", HASH_P->num_of_headers);

    char* buffer = (char*)calloc(MAX_STR_SIZE, sizeof(*buffer));
    for (long i = 0; i < HASH_P->num_of_headers; i++)
    {
        sprintf(buffer, "Header #%li", i);
        print_msg_to_dump(buffer, dump_file);
        List_dump(&(HASH_P->headers[i]), dump_file);
    }

    free(buffer);
    buffer = NULL;
    fprintf(dump_file, "</div>");
    #endif // DEBUG_HASH
    return 0;
}

unsigned char* Hash_strerror()
{
    unsigned char* rtr_val = NULL;
    switch(Hash_errno)
    {
        case GOOD_HASH:                       rtr_val = (unsigned char*)"Good hash"; break;
        case WRONG_HASH_LIST:              rtr_val = (unsigned char*)"Wrong hash list"; break;
        default: rtr_val = (unsigned char*)"Some unexpected situation. Tell developed to fix it"; break;
    }
    return rtr_val;
}

int Hash_set_function(struct Hash_t* HASH_P, int (*hash_f)(T* value), FILE* dump_file)
{
    VALID_HASH(HASH_P, "Invalid hash in the beginning of Hash_set_function", dump_file);

    HASH_P->hash_f = hash_f;

    VALID_HASH(HASH_P, "Invalid hash in the end of Hash_set_function", dump_file);
    return 0;
}

int Hash_insert(struct Hash_t* HASH_P,T value, FILE* dump_file)
{
    VALID_HASH(HASH_P, "Invalid hash in the beginning of Hash_insert", dump_file);

    struct List_elem_t* elem_to_ins_p = (struct List_elem_t*)calloc(ONE_ELEMENT,
         sizeof(*elem_to_ins_p));

    List_elem_ctor(elem_to_ins_p, value);
    long num_of_header = abs( HASH_P->hash_f(&value) ) % HASH_P->num_of_headers;
    List_insert( &(HASH_P->headers[num_of_header] ), NULL, elem_to_ins_p, LAST, dump_file);

    VALID_HASH(HASH_P, "Invalid hash in the end of Hash_insert", dump_file);
    return 0;
}

int Hash_clean(struct Hash_t* HASH_P, FILE* dump_file)
{
    VALID_HASH(HASH_P, "Invalid hash in the beginning of Hash_clean", dump_file);

    for (long i = 0; i < HASH_P->num_of_headers; i++)
    {
        List_dtor(&(HASH_P->headers[i]), dump_file);
        HASH_P->headers[i].counter = 0;
    }

    VALID_HASH(HASH_P, "Invalid hash in the end of Hash_clean", dump_file);
    return 0;
}

int Write_hash_data_to_csv(struct Hash_t* HASH_P, FILE* csv_file, FILE* dump_file)
{
    VALID_HASH(HASH_P, "Invalid hash in the beginning of Write_hash_data_to_csv", dump_file);
    assert(csv_file);
    assert(dump_file);

    for (long i = 0; i < HASH_P->num_of_headers; i++)
    {
        if (i == HASH_P->num_of_headers - 1)
        {
            fprintf (csv_file, "%li\n", HASH_P->headers[i].counter);
        }
        else
        {
            fprintf (csv_file, "%li, ", HASH_P->headers[i].counter);
        }
    }

    VALID_HASH(HASH_P, "Invalid hash in the end of Write_hash_data_to_csv", dump_file);
    return 0;
}

unsigned char* create_book_buffer(FILE* book_file)
{
    assert(book_file);

    long length = 0;
    fseek(book_file, 0, SEEK_END);
    length = ftell(book_file);
    fseek(book_file, 0, SEEK_SET);

    unsigned char* rtr_val = (unsigned char*)calloc(length, sizeof(*rtr_val));
    assert(rtr_val);

    fread (rtr_val, sizeof(*rtr_val), length, book_file);
    fseek(book_file, 0, SEEK_SET);
    return rtr_val;
}

unsigned char** create_book_words_array()
{
    unsigned char** rtr_val = (unsigned char**)calloc(MAX_NUM_OF_WORDS, sizeof(*rtr_val));
    assert(rtr_val);

    for (long i = 0; i < MAX_NUM_OF_WORDS; i++)
    {
        rtr_val[i] = (unsigned char*)calloc(MAX_WORD_SIZE, sizeof(*rtr_val));
        assert(rtr_val[i]);
    }
    return rtr_val;
}

int destroy_book_words_array(unsigned char** book_words)
{
    for (long i = 0; i < MAX_NUM_OF_WORDS; i++)
    {
        free(book_words[i]);
        book_words[i] = NULL;
    }
    free(book_words);
    return 0;
}

int move_to_next_word(unsigned char** string_pointer)
{
    while( (*(*string_pointer) != ' ' ) && ( *(*string_pointer) != '\n' ) && ( *(*string_pointer) != '\t') )
    {
        (*string_pointer)++;
        if (*(*string_pointer) == '\0')
        {
            return 0;
        }
    }
    while( (*(*string_pointer) == ' ' ) || ( *(*string_pointer) == '\n' ) || ( *(*string_pointer) == '\t') )
    {
        (*string_pointer)++;
        if (*(*string_pointer) == '\0')
        {
            return 0;
        }
    }
    return 0;
}

int Hash_find(struct Hash_t* HASH_P,T value, FILE* dump_file)
{
    VALID_HASH(HASH_P, "Invalid hash in the beginning of Hash_find", dump_file);

    long number_of_header = abs( HASH_P->hash_f(&value) ) % HASH_P->num_of_headers;
    int rtr_val = WRONG_NUM;
    if (List_find (&(HASH_P->headers[number_of_header]), value, dump_file) )
    {
        rtr_val = TRUE;
    }
    else
    {
        rtr_val = FALSE;
    }

    VALID_HASH(HASH_P, "Invalid hash in the end of Hash_find", dump_file);
    return rtr_val;
}

char* get_csv_file_name(char* book_file_name)
{
    char* rtr_val = book_file_name;
    int length = strlen(book_file_name);
    //changing ".txt" to ".csv"
    rtr_val[length - 3] = 'c';
    rtr_val[length - 2] = 's';
    rtr_val[length - 1] = 'v';
    return rtr_val;
}
