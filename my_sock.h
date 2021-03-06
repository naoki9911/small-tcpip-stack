#ifndef _MY_SOCK_H_
#define _MY_SOCK_H_

#include <stdint.h>
#include "config.h"

int my_sock_socket(int domain, int type, int protocol);

ssize_t my_sock_recv(int sockfd, void *buf, size_t len, int flags);
ssize_t my_sock_recvfrom();
ssize_t my_sock_recvmsg();

ssize_t my_sock_send();
ssize_t my_sock_sendto();
ssize_t my_sock_sendmsg();


#define MY_SOCK_PKT_SOCKET (0)
#define MY_SOCK_PKT_DATA (1)

#define MY_SOCK_PKT_OP_REQ (0)
#define MY_SOCK_PKT_OP_RES (1)

#define MY_SOCK_PKT_TYPE_RAW (0)

#define MY_SOCK_PKT_RES_OK (0)
#define MY_SOCK_PKT_RES_ERROR (1)

struct my_sock_pkt_header {
    uint8_t pkt_type;
    uint8_t op;
};

struct my_sock_pkt_socket_req {
    struct my_sock_pkt_header hdr;
    uint8_t sock_type;
};

struct my_sock_pkt_socket_res {
    struct my_sock_pkt_header hdr;
    uint8_t res;
};

struct my_sock_pkt_data {
    uint8_t pkt_type;
    uint32_t size;
    uint8_t data[CONFIG_SOCKET_MANAGER_BUF_SIZE];
};

#endif
