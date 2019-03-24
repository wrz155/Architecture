.SUFFIXES: .c .o

CC=gcc
CLIENTSRCS=client.c			
SERVERSRCS=server.c
	
CLIENTOBJS=$(CLIENTSRCS:.c=.o)
SERVEROBJS=$(SERVERSRCS:.c=.o)

CLIENTEXEC=client
SERVEREXEC=server

all:$(CLIENTOBJS) $(SERVEROBJS)
	$(CC) -o $(CLIENTEXEC) $(CLIENTOBJS)
	$(CC) -o $(SERVEREXEC) $(SERVEROBJS)
	@echo '-------------ok--------------'

.c.o:
	$(CC) -Wall -g -o $@ -c $< 

clean:
	rm -f $(CLIENTOBJS)
	rm -f $(SERVEROBJS)
	rm -f core*

