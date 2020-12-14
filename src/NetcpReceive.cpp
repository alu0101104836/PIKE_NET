#include "../include/socket.hpp"

int protected_main (void)
{
    std::cout << "Creadno las ips" << std::endl;
    sockaddr_in local_address = make_ip_address(8001, "127.0.0.1");
    sockaddr_in remote_address = make_ip_address(8000, "127.0.0.1");


    std::cout << "Creadno socket local" << std::endl;
    Socket socket_local(local_address);

    std::cout << "Creadno mensaje" << std::endl;
    Message message;

    while (1)
    {
        socket_local.receive_from(message, remote_address);
        std::cout << message.text.data();
    }

    return 0;
    

}

int main (void)
{
    std::cout << "NetCPReceive" << std::endl;
    try
    {
        return protected_main();
    }
    catch(const std::bad_alloc& e)
    {
        std::cerr << "NetCPReceive: " << e.what() << '\n';
        return 1;
    }
    catch(const std::system_error& e)
    {
        std::cerr << "NetCPReceive: " << e.what() << '\n';
        return -1;
    }
    catch(...)
    {
        std::cerr << "NetCPReceive ERROR DESCONOCIDO: " << '\n';
        return -99;
    }
}