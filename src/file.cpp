#include "../include/file.hpp"
#include "../include/socket.hpp"

file_::file_(const std::string& filename, bool writeonly, size_t sz)
{
    if (writeonly == false)
    {
        fd_ = open(filename.c_str(), O_RDONLY, (mode_t)0600);
        if (fd_ < 0)
            std::cerr << "Abrir el archivo FAIL" << std::endl;
        
        lockf(fd_, F_LOCK, 0);
        sz_ = lseek(fd_, 0, SEEK_END);

        mem_mapped = mmap(NULL, sz_, PROT_READ, MAP_SHARED, fd_, 0);
        
    }
    else
    {
        fd_ = open(filename.c_str(), O_RDWR | O_CREAT | O_TRUNC , (mode_t)0600);
        if (fd_ < 0)
            std::cerr << "Abrir el archivo FAIL" << std::endl;        
        
        lockf(fd_, F_LOCK, 0);
        
        ftruncate(fd_, sz);
        sz_ = sz;
        
        write(fd_, "", 1);

        mem_mapped = mmap(0, sz, PROT_READ | PROT_WRITE, MAP_SHARED, fd_, 0);
    }
    
    /*char * buffer;
    buffer = (char *) mem_mapped;
    std::cout << "MEM: " << &mem_mapped << std::endl;
    if (writeonly == false)
        std::cout << "MEMC: " << buffer << std::endl;*/
}


void* file_::data_()
{
    return mem_mapped;
}

std::string file_::read_file()
{
    int lectura;
    do
    {
        char buffer[1024];
        lectura = read(fd_, &buffer, 1024);
        std::string buffer_(buffer);

        return buffer_;
    } while (lectura != 0);

    return "1";
}

void file_::write_file(const std::string& data)
{
    Message message;
    
    data.copy(message.text.data(), message.text.size() - 1, 0);

    write(fd_, message.text.data(), message.text.size() - 1);

}

void file_::escribir(std::string mensaje)
{
    mem_mapped = reinterpret_cast<void*> (&mensaje);

    msync(mem_mapped, sz_, MS_SYNC);
}

    /*char *buffer;

    buffer = (char *) mmap(NULL, sz_, PROT_READ, MAP_SHARED, var_, 0);

    std::string buffer_(buffer);*/

    /*char *buffer;

    lseek(var_, data.size(), SEEK_SET);

    write(var_, "", 1);

    buffer = (char *) mmap(0, data.size() + 1, PROT_READ | PROT_WRITE, MAP_SHARED, var_, 0);

    memcpy(buffer, &data, data.size());

    msync(buffer, data.size() + 1, MS_SYNC);*/