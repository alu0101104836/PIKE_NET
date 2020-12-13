#include "../include/socket.hpp"

sockaddr_in make_ip_address(int port, const std::string& ip_address)
{
    
    sockaddr_in local_address {};
    
    local_address.sin_family = AF_INET;

    if (ip_address == std::string())
        local_address.sin_addr.s_addr = htonl(INADDR_ANY);
    else
        inet_aton(ip_address.c_str(), &local_address.sin_addr);

    local_address.sin_port = htons(port);

    return local_address;
}



Socket::Socket(const sockaddr_in& address)
{
    fd_ = socket(AF_INET, SOCK_DGRAM, 0);

    if ( fd_ < 0)
        std::cerr << "No se pudo crear el socket: " << std::strerror(errno) << std::endl; //Error si no se puede crear el socket

    int result = bind(fd_, reinterpret_cast<const sockaddr*>(&address), sizeof(address));

    if (result < 0)
        std::cerr << "Falló el bind: "<< std::endl;

    address_ = address;
}

void Socket::send_to(const Message& mensaje, const sockaddr_in& address)
{
    int result = sendto(fd_, &mensaje, sizeof(mensaje), 0, reinterpret_cast<const sockaddr*>(&address), sizeof(address));
    if (result < 0)
        std::cerr << "Falló sendto: " << std::strerror(errno) << std::endl;
}

void Socket::receive_from(Message& message, sockaddr_in& address)
{
    socklen_t src_len = sizeof(address);
    int result = recvfrom(fd_, &message, sizeof(message), 0,
	reinterpret_cast<sockaddr*>(&address), &src_len);

    if (result < 0) 
        std::cerr << "falló recvfrom: " << std::strerror(errno) << std::endl;
}