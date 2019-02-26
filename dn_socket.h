#ifndef DN_SOCKET_H
#define DN_SOCKET_H
#include <stdint.h>

#include <string.h>
#include <netinet/in.h>

typedef void (* recv_data_func_t)(void* , int );

/**
 * 封装socket
 */
typedef struct _dn_socket
{
    int socket;                             // 定义socket句柄
    recv_data_func_t recv_func_callback;    // 接收回调
    uint32_t ip;           // 目标IP
    uint16_t srv_port;                      // 服务端口
    uint16_t destPort;                      // 目标端口

    struct sockaddr_in servaddr, cliaddr;
    socklen_t cliaddr_len;
    int sockfd;
    int exit_thread;                        // 初始化为0, 等于1时则退出线程
}dn_socket_t;


/**
 * @brief 初始化socket
 * @param dn_socket
 * @return
 */
int dn_socket_init(dn_socket_t *dn_socket);

/**
 * @brief 退出socket
 * @return
 */
int dn_socket_deinit(dn_socket_t *dn_socket);

int dn_socket_send_data(dn_socket_t *dn_socket, const void* buf, int size);




#endif // DN_SOCKET_H
