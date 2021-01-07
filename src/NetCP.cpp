#include "../include/socket.hpp"
#include "../include/file.hpp"
#include <cstdlib>

int main (int argc, char const *argv[])
{
    int salida = 0;
    std::string var;

    do
    {
        std::cout << std::endl;
        std::cout << "Entrada: ";
        std::cin >> var;
        std::cout << std::endl;

        if (var == "receive")
            std::cout << "Receive" << std::endl;
        else if (var == "send")
            std::cout << "Send" << std::endl;
        else if (var == "abort")
            std::cout << "Abort" << std::endl;
        else if (var == "resume")
            std::cout << "Resume" << std::endl;
        else if (var == "pause")
            std::cout << "Pause" << std::endl;
        else if (var == "quit")
        {
            std::cout << "Quit" << std::endl;
            salida = 1;
        }
        
    }while (salida == 0);
    

    return 0;
}

