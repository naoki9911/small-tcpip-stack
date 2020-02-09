#include <stdio.h>
#include <sys/socket.h>

#include "my_sock.h"
#include "unix_sock.h"
#include "config.h"

int my_sock_socket(int domain, int type, int protocol){
    if(domain != AF_INET) return -1;
    if(type != SOCK_RAW) return -1;
    if(protocol != 0) return -1;

    int sts_fd = unix_sock_open_client(sts_sock);
    if(sts_fd == -1) return -1;

    struct my_sock_pkt_socket_req pkt_req;
    pkt_req.pkt_type = MY_SOCK_PKT_SOCKET;
    pkt_req.op = MY_SOCK_PKT_OP_REQ;

    switch(type){
        SOCK_RAW:
            pkt_req.sock_type = MY_SOCK_PKT_RECV;
            break;
    }
    send(sts_fd, &pkt_req, sizeof(pkt_req), 0);

    struct my_sock_pkt_socket_res pkt_res;
    int recv_size = recv(sts_fd, &pkt_res, sizeof(pkt_res), 0);

    if(pkt_res.pkt_type != MY_SOCK_PKT_SOCKET) goto err;
    if(pkt_res.op != MY_SOCK_PKT_OP_RES) goto err;
    if(pkt_res.res != MY_SOCK_PKT_RES_OK) goto err;

    return sts_fd;

err:
    close(sts_fd);
    return -1;
}

ssize_t my_sock_recv(int sockfd, void *buf, size_t len, int flags){

}