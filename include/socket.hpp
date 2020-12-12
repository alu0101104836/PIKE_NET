#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <string>
#include <iostream>
#include <cstring>
#include <cerrno>
#include <arpa/inet.h>
#include <array>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

sockaddr_in make_ip_address(int port, const std::string& ip_address = std::string());

struct Message
{
    std::array<char, 1024> text;
};



class Socket
{
    private:
        int fd_;
        sockaddr_in address_;

    public:
        Socket(const sockaddr_in& address);
        ~Socket();

        void send_to(const Message& mensaje, const sockaddr_in& address);
        void receive_from(Message& message, sockaddr_in& address);
};