CC = g++
CFLAGS  = -g -Wall

netcp_pike: main.o socket.o
	$(CC) $(CFLAGS) -o netcp_pike main.o socket.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c src/main.cpp

socket.o: socket.hpp
	$(CC) $(CFLAGS) -c src/socket.hpp

clean:
	rm *.o