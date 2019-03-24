.SUFFIXES: .c .o

CC=gcc

SRCS1=udp_client.c
SRCS2=udp_server.c	
OBJS1=$(SRCS1:.c=.o)
OBJS2=$(SRCS2:.c=.o)

EXE1=udp_client
EXE2=udp_server

all: $(OBJS1) $(OBJS2)
	$(CC) -o $(EXE1) $(OBJS1) -lpthread
	$(CC) -o $(EXE2) $(OBJS2) -lpthread
	@echo '^_^ ^_^ ^_^ ^_^ ^_^ ^_^ OK ^_^ ^_^ ^_^ ^_^ ^_^ ^_^'

.c.o: 
	$(CC) -Wall -g -o $@ -c $<

clean:
	-rm -f $(OBJS1) $(OBJS2)
	-rm -f core*

