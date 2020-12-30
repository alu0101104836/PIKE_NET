#include "../include/file.hpp"

file_::file_(const std::string& filename, bool writeonly)
{
    fichero_ = filename;

    var_ = open(fichero_.c_str(), 0000);
    if (var_ < 0)
    {
        std::cerr << "Abrir el archivo FAIL" << std::endl;
    }

}

std::string file_::read_file()
{
    int lectura;
    do
    {
        char buffer[1024];
        lectura = read(var_, &buffer, 1024);
        std::string buffer_(buffer);

        return buffer_;
    } while (lectura != 0);
    
    return "1";
}

void file_::write_file(const std::string& data)
{

}