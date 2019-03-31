.SUFFIXES: .cpp .o

CC=g++

SRCS=qqserver.cpp\
	pub.cpp\
	work.cpp
		
OBJS=$(SRCS:.cpp=.o)

EXE=qqserverd

all: $(OBJS)
	$(CC) -o $(EXE) $(OBJS)
	@echo '^_^ ^_^ ^_^ ^_^ ^_^ ^_^ OK ^_^ ^_^ ^_^ ^_^ ^_^ ^_^'

.cpp.o: 
	$(CC) -Wall -g -o $@ -c $<

clean:
	-rm -f $(OBJS)
	-rm -f core*

