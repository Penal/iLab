#ifndef AKINATOR_H_INCLUDED
#define AKINATOR_H_INCLUDED
const int MAX_SIZE_OF_ANS = 10;

enum {NO = 0, YES = 1, DONT_UNDERSTAND = 2};

int akinator_create_new_person(Node_t* akinator_dtbase, FILE* dump_file);
int akinator_play(Node_t* akinator_dtbase,FILE* dump_file);
int get_yes_or_no_answer(char* msg);
int get_string(char* str_ptr);

#endif // AKINATOR_H_INCLUDED
