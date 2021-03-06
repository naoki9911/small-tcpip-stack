#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>

#include "file.h"
#include "unix_sock.h"
#include "dev_tap.h"
#include "netdev.h"
#include "utils.h"
#include "config.h"
#include "socket_manager.h"
#include "arp.h"

const char* sts_dir = "/tmp/sts/";

int main(int argc, char* argv[]){
    signal(SIGPIPE, SIG_IGN);

    if(!file_exist(sts_dir)){
        fprintf(stdout, "STS dir %s does not exist. Creating...\n", sts_dir);
        if(!file_create_dir(sts_dir)){
            fprintf(stderr, "Failed to create STS dir %s\n", sts_dir);
            return -1;
        }
        fprintf(stdout, "Create STS dir %s\n", sts_dir);
    }else{
        fprintf(stdout, "STS dir %s exists\n", sts_dir);
    }

    if(file_exist(sts_sock)){
        fprintf(stdout, "Socket %s exists. Deleting...\n", sts_sock);
        if(file_delete_file(sts_sock)){
            fprintf(stdout, "Delete Socket %s\n", sts_sock);
        }else{
            fprintf(stderr, "Fialed to delete Socket %s\n", sts_sock);
            return -1;
        }
    }


    int tap_fd = dev_tap_open("test");
    /*
    int fd = unix_sock_open_server(sts_sock);
    struct sockaddr_un sun;
    int sock_len = 0;
    int fd_accept = accept(fd, (struct sockaddr *)&sun, &sock_len);
    if(fd_accept == -1){
        fprintf(stderr, "Faild to accept unix domain socket %s\n", sock);
        close(fd);
        return -1;
    }

    uint8_t buf[1500];
    memset(buf, 0, sizeof(buf));

    recv(fd_accept, buf, sizeof(buf), 0);
    printf("RECV:%s\n", buf);
    */
    netdev_add_s("98:FA:9B:4C:09:1D", "192.168.100.1", 1500);
    netdev_add_s("98:FA:9B:4C:09:1E", "192.168.100.2", 1500);
    netdev_list();
    //hw[5] = 0x1e;
    //ip[3] = 2;
    //netdev_add(hw, ip, 1500);
    //netdev_add(hw, ip, 1500);
    //netdev_list();
    //struct netdev_info *netdev = netdev_get_by_ip(ip);
    //if(netdev == NULL){
    //    printf("Not Found\n");
    //}else{
    //    netdev_print(netdev);
    //}
    //hw[5] = 0x1d;
    //netdev = netdev_get_by_hw(hw);
    //if(netdev == NULL){
    //    printf("Not Found\n");
    //}else{
    //    netdev_print(netdev);
    //}

    //hw[5] = 0x1a;
    //netdev = netdev_get_by_hw(hw);
    //if(netdev == NULL){
    //    printf("Not Found\n");
    //}else{
    //    netdev_print(netdev);
    //}
    run_cmd("ip a add 192.168.100.100/24 dev test");

    socket_manager_init();
    arp_init();
    netdev_init("tap_sts");

    while(1){
        //socket_manager_list_raw_socket();
        //const char* str = "Hello World";
        //socket_manager_add_raw_packet(str, strlen(str));
        sleep(1);
    }

    if(file_delete_file(sts_sock)){
        fprintf(stdout, "Delete Socket %s\n", sts_sock);
    }else{
        fprintf(stderr, "Fialed to delete Socket %s\n", sts_sock);
        return -1;
    }
    return 0;
}
