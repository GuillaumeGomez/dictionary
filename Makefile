# Dictionary - Copyright (c) 2015 Gomez Guillaume.
#
# This software is provided 'as-is', without any express or implied warranty.
# In no event will the authors be held liable for any damages arising from
# the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not claim
#    that you wrote the original software. If you use this software in a product,
#    an acknowledgment in the product documentation would be appreciated but is
#    not required.
#
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
#
# 3. This notice may not be removed or altered from any source distribution.

STATIC_OPTIONS=	-Wall -c

DYNAMIC_OPTIONS= -Wall -fPIC -c

LIBNAME=	libdictionary

SRCS=		$(wildcard ./src/*.c)

CSRCS=		$(wildcard ./src/*.c) \
		$(wildcard ./example/*.c)

OBJS=		$(SRCS:.c=.o)

COBJS=		$(CSRCS:.c=.o)

RM=		rm -f

dictionary: $(OBJS)
	gcc $(STATIC_OPTIONS) $(SRCS)
	ar rcs $(LIBNAME).a *.o
	gcc $(DYNAMIC_OPTIONS) $(SRCS)
	gcc -shared -o $(LIBNAME).so *.o

example: dictionary
	gcc -Wall example/main.c -L. -ldictionary -o test_dynamic
	gcc -static -Wall -I./src/ example/main.c $(LIBNAME).a -o test_static

all: example

complete:
	gcc $(CSRCS) -o complete

clean:
	$(RM) $(LIBNAME).a
	$(RM) $(LIBNAME).so

re: clean example
