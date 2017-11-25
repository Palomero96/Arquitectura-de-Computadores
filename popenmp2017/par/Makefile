CC=g++
CFLAGS=-std=c++14 -g -Wall -Wextra -Wno-deprecated -Werror -pedantic -pedantic-errors -O3 -DNDEBUG 
BINDIR=bin
PROGS=\
$(BINDIR)/nasteroids-par \


all: $(BINDIR) $(PROGS)

$(BINDIR):
	mkdir $(BINDIR)

$(BINDIR)/nasteroids-par: nasteroids-par.cpp
	$(CC) $(CFLAGS) -o $(BINDIR)/nasteroids-par -fopenmp nasteroids-par.cpp 


clean:
	$(RM) $(PROGS)