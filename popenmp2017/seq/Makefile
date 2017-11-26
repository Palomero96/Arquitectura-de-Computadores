CC=g++
CFLAGS=-std=c++14 -g -Wall -Wextra -Wno-deprecated -Werror -pedantic -pedantic-errors -O3 -DNDEBUG -fopenmp
BINDIR=bin
PROGS=\
$(BINDIR)/nasteroids-seq \


all: $(BINDIR) $(PROGS)

$(BINDIR):
	mkdir $(BINDIR)

$(BINDIR)/nasteroids-seq: nasteroids-seq.cpp
	$(CC) $(CFLAGS) -o $(BINDIR)/nasteroids-seq nasteroids-seq.cpp


clean:
	$(RM) $(PROGS)