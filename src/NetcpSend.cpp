#include "../include/socket.hpp"

int main (void)
{
    sockaddr_in local_address = make_ip_address(3001, "127.0.0.1");
    sockaddr_in remote_address = make_ip_address(3000, "127.0.0.1");
    
    Socket socket_local(local_address);

    Message mensaje;

    int doc = open("prueba.txt", 0000);

    int lectura;
    do
    {
        std::string buffer;
        lectura = read(doc, &buffer, buffer.size());

        buffer.copy(mensaje.text.data(), mensaje.text.size() - 1, 0);

        socket_local.send_to(mensaje, remote_address);

    } while (lectura != 0);
    
    return 0;
}