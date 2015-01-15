# Dictionary
A new way to handle dictionaries !

# Build
To build the library:

```Shell
> make
```

It will generate a dynamic and a static libraries : `libdictionary.so` and `libdictionary.a`.

A little example is given inside the example folder. To build it, just do:

```Shell
> make example
```

It will generate two files: `test_static` and `test_dynamic`. The first one has been compiled with "statically", not the second. To run one of them:

```Shell
> ./test_static dico.txt
```

# Functions available

For the moment, here are the available functions:

 * init_dictionary : Returns the dictionary object or NULL.
 * find_word : Returns true if the word is in the dictionary.
 * free_dictionary : Frees the dictionary object.
 * check_forbidden_character : Returns false if there is not supported character in the given string.
 * add_word : Adds a word to the dictionary.
 * print_dictionary : Displays all the words stored in the dictionary.
 * remove_word : Deletes a word stored in the dictionary.
 * get_words_count : Returns the number of words stored in the dictionary.

You have to call `init_dictionary` first and `free_dictionary` last.

# Example
An example is available in the example folder. However, here's another one:

```C
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"

int main(int ac, char **av) {
    if (ac < 3) {
      fprintf(stderr, "USAGE: ./example [string1, string2, ...]\n");
      return EXIT_FAILURE;
    }
    dictionary *dict = init_dictionary();

    if (!dict) {
        fprintf(stderr, "init_dictionary function failed\n");
	return EXIT_FAILURE;
    }
    while (--ac > 1) {
        add_word(dict, av[ac]);
    }
    print_dictionary(dict);
    printf("Can we find '%s' ? %s\n", find_word(dict, av[2]) == true ? "Yes !" : "No...");
    free_dictionary(&dict);
    return EXIT_SUCCESS;
}
```

# License

For more information, please read the license file.
