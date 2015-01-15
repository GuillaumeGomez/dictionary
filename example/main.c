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
#include "../src/dictionary.h"

void find_and_print_word(void *dico, const char *w) {
  printf("Did we find '%s' ? %s\n", w, find_word(dico, w) == true ? "Yes !" : "No...");
}

int main(int ac, char **av) {
  FILE *fd;
  char *line = NULL;
  dictionary *dict;
  size_t n;

  if (ac < 2) {
    fprintf(stderr, "Missing dictionary file.\n");
    return EXIT_FAILURE;
  }
  if (!(dict = init_dictionary())) {
    fprintf(stderr, "init_dico function failed\n");
    return EXIT_FAILURE;
  }
  if (!(fd = fopen(av[1], "r"))) {
    fprintf(stderr, "%s: No such file or directory.\n", av[1]);
    free_dictionary(&dict);
    return EXIT_FAILURE;
  }
  printf("== Creation of the dictionary. ==\n");
  while (getline(&line, &n, fd) > 0) {
    line[strlen(line) - 1] = 0;
    add_word(dict, line);
  }
  free(line);
  fclose(fd);
  printf("== Dictionary is ready ! ==\n== There is actually %d words in it. ==\n", get_words_number(dict));
  find_and_print_word(dict, "test");
  find_and_print_word(dict, "salut");
  find_and_print_word(dict, "salu");
  find_and_print_word(dict, "bonjour");
  printf("== Let's show the dictionary content: ==\n");
  print_dictionary(dict);
  printf("== Now we remove one word. ==\n");
  printf("removing '%s': %s\n", "salut", remove_word(dict, "salut") == WORD_REMOVED ? "Done" : "Error");
  print_dictionary(dict);
  printf("== Now we remove another word. ==\n");
  printf("removing '%s': %s\n", "test", remove_word(dict, "test") == WORD_REMOVED ? "Done" : "Error");
  print_dictionary(dict);
  printf("== Let's free the dictionary ! ==\n");
  free_dictionary(&dict);
  return EXIT_SUCCESS;
}
