#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED
#include "../List/main.c"
typedef int (*Hash_f_t) (T* value);

struct Hash_t
{
    struct List_t* headers;
    long num_of_headers;
    Hash_f_t hash_f;
};

const int MAX_NUM_OF_WORDS = 340000;
const int MAX_STR_SIZE = 50;
const int MAX_WORD_SIZE = 25;
const int NUM_OF_HEADERS_IN_HASH = 761;

const int NUM_OF_FUNCS = 5;
int HASH_F1 (T* value);
int HASH_F2 (T* value);
int HASH_F3 (T* value);
int HASH_F4 (T* value);
int HASH_F5 (T* value);

enum {GOOD_HASH, WRONG_HASH_LIST};
int Hash_errno = GOOD_HASH;

int Hash_ctor(struct Hash_t* HASH_P,FILE* dump_file);
int Hash_dtor(struct Hash_t* HASH_P,FILE* dump_file);
int Hash_ok(struct Hash_t* HASH_P,FILE* dump_file);
int Hash_dump(struct Hash_t* HASH_P,FILE* dump_file);
int Hash_set_function(struct Hash_t* HASH_P, int (*hash_f)(T* value), FILE* dump_file);
int Hash_insert(struct Hash_t* HASH_P,T value, FILE* dump_file);
int Hash_clean(struct Hash_t* HASH_P, FILE* dump_file);
int Hash_find(struct Hash_t* HASH_P,T value, FILE* dump_file);

int Write_hash_data_to_csv(struct Hash_t* HASH_P, FILE* csv_file, FILE* dump_file);
unsigned char* Hash_strerror();
unsigned char* create_book_buffer(FILE* book_file);
unsigned char** create_book_words_array();
int destroy_book_words_array(unsigned char **book_words);
int move_to_next_word(unsigned char** string_pointer);
char* get_csv_file_name(char* book_file_name);
#endif // HASH_H_INCLUDED
