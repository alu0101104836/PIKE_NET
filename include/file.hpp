#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <string>
#include <iostream>
#include <cstring>
#include <cerrno>
#include <arpa/inet.h>
#include <array>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/mman.h>
#include <thread>
#include <exception>
#include <atomic>
#include <signal.h>

class file_
{
private:
    size_t sz_;
    int fd_;
    void* mem_mapped;

public:
    file_(const std::string& filename, bool writeonly = false, size_t sz = 0);
    ~file_()
    {
        munmap(mem_mapped, sz_);
        lockf(fd_, F_ULOCK, 0);
        close(fd_);
    }

    std::string read_file();
    void write_file(const std::string& data);
    void escribir(std::string mensaje);
    void* data_();

    size_t getSize() { return sz_; }

};
