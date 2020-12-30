#include "../include/file.hpp"

file_::file_(const std::string& filename, bool writeonly)
{
    fichero_ = filename;

    var_ = open(fichero_.c_str(), 0000);
    if (var_ < 0)
    {
        std::cerr << "Abrir el archivo FAIL" << std::endl;
    }

    //sz_ = lseek(var_, 0, SEEK_END);

}

std::string file_::read_file()
{
    int lectura;
    char buffer[sz_];
    lectura = read(var_, &buffer, sz_);
    std::string buffer_(buffer);
    return buffer_;
}

void file_::write_file(const std::string& data)
{

}