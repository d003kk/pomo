PROG = pomo
CC = /usr/bin/g++
CPPFLAGS = -std=c++14
LDFLAGS = -L/usr/local/lib -lboost_chrono -lboost_system
OBJS = timer.o

$(PROG) : $(OBJS)
	$(CC) $(CPPFLAGS)  -o $(PROG) $(OBJS)

timer.o :
	$(CC) $(CPPFLAGS) $(LDFLAGS) -DBOOST_SYSTEM_NO_DEPRECATED -c timer.cpp

clean:
	rm -f $(PROG) $(OBJS)

