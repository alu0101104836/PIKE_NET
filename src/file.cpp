#include "../include/file.hpp"

file_::file_(const std::string& filename, bool writeonly)
{
    fichero_ = filename;

    var_ = open(fichero_.c_str(), O_RDONLY);
    if (var_ < 0)
    {
        std::cerr << "Abrir el archivo FAIL" << std::endl;
    }

    sz_ = lseek(var_, 0, SEEK_END);

    p = mmap(NULL, sz_, PROT_READ, MAP_SHARED, var_, 0);

}

std::string file_::read_file()
{
    char *buffer;

    buffer = (char *) mmap(NULL, sz_, PROT_READ, MAP_SHARED, var_, 0);

    std::string buffer_(buffer);

    return buffer_;
}

void file_::write_file(const std::string& data)
{

}