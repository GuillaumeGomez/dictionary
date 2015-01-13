#ifndef __DICO_H__
#define __DICO_H__

#include <stdbool.h>

typedef enum {
  INVALID_DICO = -3,
  INVALID_CHARACTER = -2,
  ALLOC_ERROR = -1,
  WORD_ALREADY_EXISTS = 0,
  WORD_ADDED = 1
} DictionaryCodes;


// Returns a null pointer if there is a problem
void *init_dico();
// Returns true if the word is in the dictionary.
bool find_word(void *dictionary, const char *word);
// Frees the allocated resources.
void free_dico(void **dictionary);
// Return false if there is forbidden character in the given string.
bool check_forbidden_character(const char *word);
// Adds the given string to the dictionary.
// Please refer to the DictionaryCodes enum for for more information about the returned value.
DictionaryCodes add_word(void **dictionary, const char *word);
// Displays the words contained in the dictionary
// However, please use this function carefuly, it's very slow !
void print_dico(void *dictionary);

#endif
