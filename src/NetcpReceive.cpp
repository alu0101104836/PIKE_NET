#include "../include/socket.hpp"
#include "../include/file.hpp"

int protected_main (void)
{
    sockaddr_in local_address = make_ip_address(8001, "127.0.0.1");
    sockaddr_in remote_address = make_ip_address(8000, "127.0.0.1");

    Socket socket_local(local_address);

    Message message;
    
    Message nombre;
    socket_local.receive_from(nombre, remote_address);

    std::string nombre_;
    nombre_ = nombre.text.data();
    std::cout << "Nombre: " << nombre_ << std::endl;

    int doc = open("salida.txt", O_RDWR | O_CREAT | O_TRUNC);
    while (1)
    {
        socket_local.receive_from(message, remote_address);
        std::cout << message.text.data() << std::endl;

    }

    write(doc, message.text.data(), message.text.size() - 1);
    close(doc);

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