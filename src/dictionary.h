/*
 * Dictionary - Copyright (c) 2015 Gomez Guillaume.
 *
 * The Original software, FMOD library, is provided by FIRELIGHT TECHNOLOGIES.
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not claim
 *    that you wrote the original software. If you use this software in a product,
 *    an acknowledgment in the product documentation would be appreciated but is
 *    not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 */

#ifndef __DICO_H__
#define __DICO_H__

#include <stdbool.h>

typedef enum {
  WORD_NOT_FOUND = -4,
  INVALID_ARGUMENT = -3,
  INVALID_CHARACTER = -2,
  ALLOC_ERROR = -1,
  WORD_ALREADY_EXISTS = 0,
  WORD_ADDED = 1,
  WORD_REMOVED = 2
} DictionaryCodes;

typedef struct {
  void *data;
  unsigned int number;
} dictionary;

// Returns a null pointer if there is a problem
dictionary *init_dictionary();
// Returns true if the word is in the dictionary.
bool find_word(const dictionary *dict, const char *word);
// Frees the allocated resources.
void free_dictionary(dictionary **dict);
// Return false if there is forbidden character in the given string.
bool check_forbidden_character(const char *word);
// Adds the given string to the dictionary.
// Please refer to the DictionaryCodes enum for for more information about the returned value.
DictionaryCodes add_word(dictionary *dict, const char *word);
// Remove the given string for the dictionary.
DictionaryCodes remove_word(dictionary *dict, const char *word);
// Displays the words contained in the dictionary.
// However, please use this function carefuly, it's very slow !
void print_dictionary(const dictionary *dict);
// Returns the number of words stored in the dictionary.
unsigned int get_words_number(const dictionary *dict);

#endif
