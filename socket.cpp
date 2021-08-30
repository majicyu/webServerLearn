#include <sys/un.h>

struct sockaddr_un{
    sa_family_t sin_family;  /地址族：AF_UNIX/
    char sun_path[108];  /文件路径名/
};

struct sockaddr_in{
    sa_family_t sin_family;  /AF_INET/
    u_int16_t sin_port;  /端口号/
    struct in_addr sin_addr;  /IPv4地址结构体/
};

struct in_addr{
    u_int32_t s_addr;
};

struct sockaddr_in6{
    sa_family_t sin6_family;  /AF_INET6/
    u_int16_t sin6_port;
    u_int32_t sin6_flowinfo;  /流信息/
    struct int6_addr sin6_addr;
    u_int32_t sin6_scope_id;
};
//test
struct in6_addr{
    unsigned char sa_addr[16];
}
