PROG = pomo
CC = /usr/bin/g++
CPPFLAGS = -std=c++14
LDFLAGS = -L/usr/local/lib -lboost_chrono -lboost_system
OBJS = timer.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS) $(CPPFLAGS) $(LDFLAGS)
timer.o :
	$(CC) -c timer.cpp $(CPPFLAGS)

clean:
	rm -f $(PROG) $(OBJS)

