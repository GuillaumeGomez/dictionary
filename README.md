# Dictionary
A new way to handle dictionary !

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

 * init_dico
 * find_word
 * free_dico
 * check_forbidden_character
 * add_word
 * print_dico

You have to call `init_dico` first and `free_dico` in last.

# License

For more information, please read the license file.
