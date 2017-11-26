CC=g++
CFLAGS=-std=c++14 -g -Wall -Wextra -Wno-deprecated -Werror -pedantic -pedantic-errors
BINDIR=bin
PROGS=\
$(BINDIR)/nasteroids-seq \


all: $(BINDIR) $(PROGS)

$(BINDIR):
	mkdir $(BINDIR)

$(BINDIR)/nasteroids-seq: nasteroids-seq.cpp
	$(CC) $(CFLAGS) -o $(BINDIR)/nasteroids-seq -O3 -DNDEBUG -fopenmp nasteroids-seq.cpp


clean:
	$(RM) $(PROGS)