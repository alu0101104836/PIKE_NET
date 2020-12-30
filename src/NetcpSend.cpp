#include "../include/socket.hpp"
#include "../include/file.hpp"

int protected_main (void)
{
    sockaddr_in local_address = make_ip_address(8000, "127.0.0.1");
    sockaddr_in remote_address = make_ip_address(8001, "127.0.0.1");

    Socket socket_local(local_address);

    Message mensaje;
    Message nombre;
    Message tama;

    std::string nombre_archivo;
    std::cout << "Nombre del archivo: ";
    std::cin >> nombre_archivo;
    nombre_archivo.copy(nombre.text.data(), nombre.text.size() - 1, 0);
    socket_local.send_to(nombre, remote_address);

    file_ fichero_send(nombre_archivo);
    std::string a; 
    a = fichero_send.read_file();

    int var = fichero_send.getSize();
    std::string size_of_file = std::to_string(var);
    size_of_file.copy(tama.text.data(), tama.text.size() - 1, 0);
    socket_local.send_to(tama, remote_address);
    std::cout << "Tamaño fichero: " << size_of_file << std::endl;

    std::cout << "Contenido: " << a << std::endl;
    a.copy(mensaje.text.data(), mensaje.text.size() - 1, 0);
    socket_local.send_to(mensaje, remote_address);
    
    return 0;
}

int main (void)
{
    std::cout << "NetCPSend" << std::endl;
    int result = protected_main();
    
    if (result > 0)
    {
        std::cerr << "Falló el Send" << std::endl;
        return 1;
    }
    else
        std::cout << "Exito en el send " << std::endl;

    /*try
    {
        return protected_main();
    }
    catch(const std::bad_alloc& e)
    {
        std::cerr << "NetCPSend: " << e.what() << '\n';
        return 1;
    }
    catch(const std::system_error& e)
    {
        std::cerr << "NetCPSend: " << e.what() << '\n';
        return -1;
    }
    catch(...)
    {
        std::cerr << "NetCPSend ERROR DESCONOCIDO: " << '\n';
        return -99;
    }*/
    //Fin main
}





    /*int doc = open("entrada.txt", 0000);
    if (doc < 0)
    {
        std::cerr << "Abrir el archivo FAIL" << std::endl;
        return 1;
    }*/

    /*int lectura;
    do
    {
        char buffer[1024];
        lectura = read(doc, &buffer, 1024);
        std::string buffer_(buffer);

        if (lectura == 0)
            continue;

        buffer_.copy(mensaje.text.data(), mensaje.text.size() - 1, 0);

        socket_local.send_to(mensaje, remote_address);
        std::cout << "Enviado: " << buffer_ << std::endl;

    } while (lectura != 0);*/