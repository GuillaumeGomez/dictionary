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
#include "dico.h"

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

bool find_word(void *dico, const char *word) {
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

void free_dico(void **dico) {
  int i = 0;
  char **d = *dico;

  while (i < DICO_SIZE) {
    char **x = (char**)d[i];

    if (x)
      free_dico((void**)&x);
    ++i;
  }
  free(*dico);
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

void *init_dico() {
  char **dico = 0;

  if (!(dico = malloc(sizeof(char**) * (DICO_SIZE + 1)))) {
    return dico;
  }
  memset(dico, 0, (DICO_SIZE + 1) * sizeof(char**));
  return dico;
}

DictionaryCodes add_word(void **dico, const char *word) {
  if (check_forbidden_character(word) == false)
    return INVALID_CHARACTER;
  if (*dico == NULL) {
    return INVALID_DICO;
  }
  if (find_word(*dico, word)) {
    return WORD_ALREADY_EXISTS;
  }
  char **d = (char**)*dico;
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

void intern_print_dico(void *dico, char **to_print, int pos, int *actual_size) {
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
      intern_print_dico((void*)x, to_print, pos + 1, actual_size);
    }
    ++i;
  }
  if (!*to_print)
    return;
  if (d[i]) {
    to_print[0][pos] = 0;
    printf("%s\n", *to_print);
  }
}

// very slow function !
void print_dico(void *dico) {
  char *to_print;
  int actual_size = 128;

  if (!(to_print = malloc(sizeof(*to_print) * actual_size)))
    return;
  intern_print_dico(dico, &to_print, 0, &actual_size);
  free(to_print);
}