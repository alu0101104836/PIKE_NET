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

class file_
{
private:
    std::string fichero_;
    int sz_ = 1024;
    int var_;

    void* p;
public:
    file_(const std::string& filename, bool writeonly = false);
    ~file_()
    {
        close(var_);
        munmap(p, sz_);
    }

    std::string read_file();
    void write_file(const std::string& data);

    int getSize() { return sz_;}
    void setSize(int x) { sz_ = x; }
};
