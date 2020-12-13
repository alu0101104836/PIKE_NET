CC = g++
CFLAGS  = -g -Wall -std=c++11 -pthread

NetS: NetcpSend.o socket.o
	$(CC) $(CFLAGS) -o NetS src/NetcpSend.o src/socket.o

NetR: NetcpReceive.o socket.o
	$(CC) $(CFLAGS) -o NetR src/NetcpReceive.o src/socket.o

netcp_pike: main.o socket.o
	$(CC) $(CFLAGS) -o netcp_pike src/main.o src/socket.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c src/main.cpp

socket.o: socket.hpp
	$(CC) $(CFLAGS) -c include/socket.hpp

NetcpReceive.o: NetcpReceive.cpp
	$(CC) $(CFLAGS) -c src/NetcpReceive.cpp

NetcpReceive.o: NetcpSend.cpp
	$(CC) $(CFLAGS) -c src/NetcpSend.cpp

clean:
	rm *.o NetR NetS