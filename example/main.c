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
#include "../src/dico.h"

void find_and_print_word(void *dico, const char *w) {
  printf("Did we find '%s' ? %s\n", w, find_word(dico, w) == true ? "Yes !" : "No...");
}

int main(int ac, char **av) {
  FILE *fd;
  char *line = NULL;
  void *dico;
  size_t n;

  if (ac < 2) {
    fprintf(stderr, "Missing dictionary file.\n");
    return EXIT_FAILURE;
  }
  if (!(dico = init_dico())) {
    fprintf(stderr, "init_dico function failed\n");
    return EXIT_FAILURE;
  }
  if (!(fd = fopen(av[1], "r"))) {
    fprintf(stderr, "%s: No such file or directory.\n", av[1]);
    free_dico(&dico);
    return EXIT_FAILURE;    
  }
  printf("Creation of dico.\n");
  while (getline(&line, &n, fd) > 0) {
    line[strlen(line) - 1] = 0;
    add_word(&dico, line);
  }
  free(line);
  fclose(fd);
  printf("Dico is ready !\n");
  find_and_print_word(dico, "test");
  find_and_print_word(dico, "salut");
  find_and_print_word(dico, "salu");
  find_and_print_word(dico, "bonjour");
  printf("let's show the dico content:\n");
  print_dico(dico);
  printf("let's free the dico !\n");
  free_dico(&dico);
  return EXIT_SUCCESS;
}
