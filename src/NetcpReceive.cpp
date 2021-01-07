#include "../include/socket.hpp"
#include "../include/file.hpp"

int protected_main (void)
{
    sockaddr_in local_address = make_ip_address(8001, "127.0.0.1");
    sockaddr_in remote_address = make_ip_address(8000, "127.0.0.1");

    Socket socket_local(local_address);
    
    Message nombre;
    socket_local.receive_from(nombre, remote_address);
    std::string nombre_;
    nombre_ = nombre.text.data();
    nombre_.resize(nombre_.size() - 3);
    std::cout << "Nombre: " << nombre_ << std::endl;

    Message size;
    socket_local.receive_from(size, remote_address);
    int size_f;
    size_f = std::atoi((char*) size.text.data());
    std::cout << "Tamaño del fichero del send: " << size_f << std::endl;

    Message mensaje;
    socket_local.receive_from(mensaje, remote_address);
    std::string aux = mensaje.text.data();
    std::cout << "Mensaje: " << aux << std::endl;

    file_ fichero_send("send/" + nombre_, true, size_f);

    fichero_send.write_file(aux);


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