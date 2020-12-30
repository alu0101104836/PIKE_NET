#include "../include/file.hpp"
#include "../include/socket.hpp"

file_::file_(const std::string& filename, bool writeonly)
{
    fichero_ = filename;

    if (writeonly == false)
        var_ = open(fichero_.c_str(), O_RDONLY);
    else
        var_ = open(fichero_.c_str(), O_RDWR | O_CREAT );
    
    if (var_ < 0)
    {
        std::cerr << "Abrir el archivo FAIL" << std::endl;
    }

}

std::string file_::read_file()
{
    char *buffer;
    
    sz_ = lseek(var_, 0, SEEK_END);

    buffer = (char *) mmap(NULL, sz_, PROT_READ, MAP_SHARED, var_, 0);

    std::string buffer_(buffer);

    return buffer_;
}

void file_::write_file(const std::string& data)
{
    /*Message message;
    
    data.copy(message.text.data(), message.text.size() - 1, 0);*/

    char *buffer;

    lseek(var_, data.size(), SEEK_SET);

    write(var_, "", 1);

    buffer = (char *) mmap(0, data.size() + 1, PROT_READ | PROT_WRITE, MAP_SHARED, var_, 0);

    memcpy(buffer, &data, data.size());

    msync(buffer, data.size() + 1, MS_SYNC);

}