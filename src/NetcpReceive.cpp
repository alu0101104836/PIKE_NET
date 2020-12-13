#include "../include/socket.hpp"

int protected_main (void)
{
    std::cout << "Creadno las ips" << std::endl;
    sockaddr_in local_address = make_ip_address(8001, "127.0.0.1");
    sockaddr_in remote_address = make_ip_address(8000, "127.0.0.1");


    std::cout << "Creadno socket local" << std::endl;
    Socket socket_local(local_address);

    std::cout << "Creadno mensaje" << std::endl;
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
    std::cout << "NetCPReceive" << std::endl;
    int result = protected_main();

    if (result > 0)
    {
        std::cerr << "Falló el Send" << std::endl;
        return 1;
    }
    std::cout << "Exito en el send " << std::endl;
}