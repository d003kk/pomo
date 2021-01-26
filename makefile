PROG = pomo
CC = /usr/bin/g++
CPPFLAGS = -std=c++14 -I.
LDFLAGS = -L/usr/local/lib -lboost_chrono -lboost_system
OBJS = timer.o main.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS) $(CPPFLAGS) $(LDFLAGS)

main.o :
	$(CC) -c main.cpp $(CPPFLAGS)

timer.o :
	$(CC) -c timer.cpp $(CPPFLAGS)

clean:
	rm -f $(PROG) $(OBJS)

