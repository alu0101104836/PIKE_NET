CC = g++
CFLAGS  = -g -Wall -std=c++11 -pthread

#Se debe ejecutar por separada para conseguir los dos ejecutables,
#tanto NetR para el receive, como NetS para el Send
# make NetR 
# make NetS
# make NetCP

NetR: NetcpReceive.o socket.o file.o
	$(CC) $(CFLAGS) -o NetR NetcpReceive.o socket.o file.o

NetS: NetcpSend.o socket.o file.o
	$(CC) $(CFLAGS) -o NetS NetcpSend.o socket.o file.o

Net: NetCP.o socket.o file.o
	$(CC) $(CFLAGS) -o Net NetCP.o socket.o file.o


NetCP.o: src/NetCP.cpp
	$(CC) $(CFLAGS) -c src/NetCP.cpp

socket.o: src/socket.cpp
	$(CC) $(CFLAGS) -c include/socket.hpp src/socket.cpp

file.o: src/file.cpp
	$(CC) $(CFLAGS) -c include/file.hpp src/file.cpp

NetcpReceive.o: src/NetcpReceive.cpp
	$(CC) $(CFLAGS) -c src/NetcpReceive.cpp

NetcpSend.o: src/NetcpSend.cpp
	$(CC) $(CFLAGS) -c src/NetcpSend.cpp

clean:
	rm *.o NetR NetS NetCP

