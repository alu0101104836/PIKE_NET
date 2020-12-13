#include "../include/socket.hpp"

int protected_main (void)
{
    sockaddr_in local_address = make_ip_address(3000, "127.0.0.1");
    sockaddr_in remote_address = make_ip_address(3001, "127.0.0.1");
    
    Socket socket_local(local_address);

    Message mensaje;

    while (1)
    {
        socket_local.receive_from(mensaje, remote_address);
        std::cout << mensaje.text.data();
    }

    return 0;
    

}

int main (void)
{
    protected_main();
}