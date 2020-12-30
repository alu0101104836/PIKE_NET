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

class file_
{
private:
    std::string fichero_;
    int sz_;
    int var_;
public:
    file_(const std::string& filename, bool writeonly = true);
    ~file_(){close(var_);}

    std::string read_file();
    void write_file(const std::string& data);
};
