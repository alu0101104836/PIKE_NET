CC = g++
CFLAGS  = -g -Wall -std=c++11 -pthread

#Se debe ejecutar por separada para conseguir los dos ejecutables,
#tanto NetR para el receive, como NetS para el Send
# make NetR 
# make NetS

NetR: NetcpReceive.o socket.o
	$(CC) $(CFLAGS) -o NetR NetcpReceive.o socket.o

NetS: NetcpSend.o socket.o
	$(CC) $(CFLAGS) -o NetS NetcpSend.o socket.o

netcp_pike: main.o socket.o
	$(CC) $(CFLAGS) -o netcp_pike main.o socket.o




main.o: src/main.cpp
	$(CC) $(CFLAGS) -c src/main.cpp

socket.o: src/socket.cpp
	$(CC) $(CFLAGS) -c include/socket.hpp src/socket.cpp

NetcpReceive.o: src/NetcpReceive.cpp
	$(CC) $(CFLAGS) -c src/NetcpReceive.cpp

NetcpSend.o: src/NetcpSend.cpp
	$(CC) $(CFLAGS) -c src/NetcpSend.cpp

clean:
	rm *.o NetR NetS

