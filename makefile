# This Makefile is set up for CS201 A1
# copy to your MCECS account with:
# cp ~markem/public_html/CS201/homework/Makefile .
# NOTE: All indented lines are indented with a tab character.
#       This is required.

CC=g++
# flag all warnings. default optimization level.
CFLAGS=-Wall -Og
# set up for use in gdb
DFLAGS=-g
# For additional libraries, e.g. -lm
LDFLAGS=
PROGS=connect_four

all: $(PROGS)

#%: %.c
connect_four: main.cpp agent.cpp environment.cpp
	$(CC) $(CFLAGS) $(DFLAGS) $ main.cpp agent.cpp environment.cpp $(LDFLAGS) -o connect_four

clean:
	rm -f $(PROGS) *.o ~*

