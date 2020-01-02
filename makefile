CC = g++
CFLAGS = -g -Wall

INCLUDES = -I/usr/local/include/boost_1_72_0

LIBS = -lgmp

SRCS = common.cc main.cc algorithms/dynamic_programming.cc algorithms/automaton.cc algorithms/bfs_01.cc algorithms/order_degree_bfs.cc

OBJS = $(SRCS:.c=.o)

MAIN = sturdy_tester

all:  $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^


