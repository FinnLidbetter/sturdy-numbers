CC = g++
CFLAGS = -g -Wall

LIBS = -lgmp

SRCS = common.cc main.cc algorithms/dynamic_programming.cc algorithms/automaton.cc algorithms/bfs_01.cc algorithms/order_degree_bfs.cc

OBJS = $(SRCS:.c=.o)

MAIN = sturdy_tester

all:  $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $^


