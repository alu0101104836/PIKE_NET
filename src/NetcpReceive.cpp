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

    Message size_of_file_;
    socket_local.receive_from(size_of_file_, remote_address);
    std::string size_;
    size_ = size_of_file_.text.data();
    int val = std::stoi(size_);
    std::cout << "Size: " << size_ << std::endl;

    std::string nombre_fichero;
    std::cout << "Nombre del fichero a guardar: ";
    std::cin >> nombre_fichero;

    file_ fichero_receive(nombre_fichero,true);

    socket_local.receive_from(message, remote_address);
    std::cout << message.text.data() << std::endl;
    std::string aux = message.text.data();

    fichero_receive.setSize(val);
    fichero_receive.write_file(aux);

    

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