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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

const char joint[] = "abcdefghijklmnopqrstuvwxyz-";

#define DICO_SIZE 27 // equivalent to strlen(joint)

int get_equivalence(char letter) {
  int pos = 0;

  if (letter >= 'A' && letter <= 'Z')
    letter += ('a' - 'A');
  while (joint[pos] && joint[pos] != letter)
    ++pos;
  return pos;
}

bool intern_find_word(void *dico, const char *word) {
  char **d = dico;
  int pos = 0;

  if (!dico || !word)
    return false;
  while (word[pos]) {
    int eq = get_equivalence(word[pos]);

    if (!d[eq]) {
      return false;
    }
    d = (char**)d[eq];
    ++pos;
  }
  return (d[get_equivalence(' ')] ? true : false);

}

bool find_word(const dictionary *dico, const char *word) {
  if (!dico || !word || !dico->number)
    return false;
  return intern_find_word(dico->data, word);
}

void intern_free_dico(char **dico) {
  int i = 0;
  char **d = dico;

  while (i < DICO_SIZE) {
    char **x = (char**)d[i];

    if (x) {
      intern_free_dico(x);
      free(x);
    }
    ++i;
  }
}

void free_dictionary(dictionary **dico) {
  if (!dico || !*dico)
    return;
  intern_free_dico(dico[0]->data);
  free(dico[0]->data);
  free(*dico);
  *dico = NULL;
}

bool check_forbidden_character(const char *word) {
  int pos = 0;

  while (word[pos]) {
    int i = 0;

    while (joint[i] && joint[i] != word[pos])
      ++i;
    if (joint[i] != word[pos])
      return false;
    ++pos;
  }
  return true;
}

dictionary *init_dictionary() {
  char **data = 0;
  dictionary *dict = 0;

  if (!(dict = malloc(sizeof(*dict))))
    return dict;
  if (!(data = malloc(sizeof(char**) * (DICO_SIZE + 1)))) {
    free(dict);
    return dict;
  }
  memset(data, 0, (DICO_SIZE + 1) * sizeof(char**));
  dict->data = data;
  dict->number = 0;
  return dict;
}

bool remove_if_possible(char **dico, const char *word, int pos) {
  int i = 0;
  int eq = get_equivalence(word[pos]);
  bool other = false, can_remove = false;

  while (i < DICO_SIZE + 1) {
    if (dico[i]) {
    }
    if (dico[i] && i != eq) {
      other = true;
    }
    if (i == eq && word[pos])
      can_remove = remove_if_possible((char**)dico[eq], word, pos + 1);
    ++i;
  }
  if (can_remove) {
    if (word[pos]) {
      free((char**)dico[eq]);
    }
    dico[eq] = 0;
  }
  // the word doesn't exist anymore so we remove its end limiter
  if (!word[pos])
    dico[eq] = 0;
  return other == false && can_remove == true;
}

DictionaryCodes intern_remove_word(char **dico, const char *word) {
  int pos = 0;

  if (intern_find_word((void*)dico, word) == false)
    return WORD_NOT_FOUND;
  remove_if_possible(dico, word, pos);
  return WORD_REMOVED;
}

DictionaryCodes remove_word(dictionary *dict, const char *word) {
  DictionaryCodes ret;

  if (!dict || !word) {
    return INVALID_ARGUMENT;
  } else if (!word[0]) {
    return WORD_NOT_FOUND;
  }
  ret = intern_remove_word((char**)dict->data, word);
  if (ret == WORD_REMOVED)
    dict->number -= 1;
  return ret;
}

DictionaryCodes intern_add_word(void **dico, const char *word) {
  char **d = (char**)dico;
  int pos = 0;
  int eq;

  while (word[pos]) {
    eq = get_equivalence(word[pos]);

    if (!d[eq]) {
      break;
    }
    d = (char**)d[eq];
    ++pos;
  }
  while (word[pos]) {
    eq = get_equivalence(word[pos]);

    if (!(d[eq] = malloc(sizeof(char**) * (DICO_SIZE + 1)))) {
      return ALLOC_ERROR;
    }
    memset(d[eq], 0, (DICO_SIZE + 1) * sizeof(char**));
    d = (char**)d[eq];
    ++pos;
  }
  d[get_equivalence(' ')] = (void*)1;
  return WORD_ADDED;
}

DictionaryCodes add_word(dictionary *dict, const char *word) {
  DictionaryCodes ret;

  if (dict == NULL || !word || !word[0]) {
    return INVALID_ARGUMENT;
  }
  if (check_forbidden_character(word) == false)
    return INVALID_CHARACTER;
  if (find_word(dict, word)) {
    return WORD_ALREADY_EXISTS;
  }
  ret = intern_add_word((void**)dict->data, word);
  if (ret == WORD_ADDED)
    dict->number += 1;
  return ret;
}

void intern_print_dico(void *dico, char **to_print, int pos, int *actual_size, unsigned int *total) {
  char **d = dico;
  int i = 0;

  if (pos == *actual_size - 1) {
    if (!(*to_print = realloc(*to_print, *actual_size + 128)))
      return;
    *actual_size += 128;
  }
  while (i < DICO_SIZE && *to_print) {
    char **x = (char**)d[i];

    if (x) {
      to_print[0][pos] = joint[i];
      to_print[0][pos + 1] = 0;
      intern_print_dico((void*)x, to_print, pos + 1, actual_size, total);
      if (!*total)
	return;
    }
    ++i;
  }
  if (!*to_print)
    return;
  if (d[i]) {
    to_print[0][pos] = 0;
    printf("%s\n", *to_print);
    *total -= 1;
  }
}

// very slow function !
void print_dictionary(const dictionary *dict) {
  char *to_print;
  int actual_size = 128;
  unsigned int total = dict->number;

  if (!(to_print = malloc(sizeof(*to_print) * actual_size)))
    return;
  intern_print_dico(dict->data, &to_print, 0, &actual_size, &total);
  free(to_print);
}

unsigned int get_words_number(const dictionary *dict) {
  return dict ? dict->number : 0;
}
