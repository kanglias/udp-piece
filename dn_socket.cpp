#include "dn_socket.h"

#define MAX_MSG_SIZE (256*1024)              /*recv缓冲器大小*/

static void recv_data_loop(void *user_data)
{
    dn_socket_t *dn_socket = (dn_socket_t *)user_data;
    int sockfd = dn_socket->sockfd;

    /*客户机的地址信息及长度信息*/
    struct sockaddr_in client;
    int  client_len = sizeof(struct sockaddr_in);
    unsigned char message[MAX_MSG_SIZE];
    int recv_len=0;

    while(!dn_socket->exit_thread)
    {
        // select 超时退出，设置超时为100毫秒
        /********************************接收数据并打印*************************/
        recv_len = recvfrom(sockfd, message,sizeof(message),0,(struct sockaddr *)&client,&client_len); //阻塞式
        if(recv_len <0)
        {
            printf("recvfrom error\n");
            exit(1);
        }
        /*打印客户端地址和端口号*/
        inet_ntop(AF_INET,&client.sin_addr,addr_p,sizeof(addr_p));
        printf("client IP is %s, port is %d\n",addr_p,ntohs(client.sin_port));
        message[recv_len]='\0';
        /*显示消息长度*/
        printf("server received %d:%s\n", recv_len, message);
    }
}

int dn_socket_init(dn_socket_t *dn_socket)
{
    dn_socket->sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&dn_socket->servaddr, sizeof(dn_socket->servaddr));
    dn_socket->servaddr.sin_family = AF_INET;
    dn_socket->servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    dn_socket->servaddr.sin_port = htons(dn_socket->srv_port);
   // setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(timeval))；

            printf("Accepting connections ...\n");
}

int dn_socket_deinit(dn_socket_t *dn_socket)
{

}

int dn_socket_send_data(dn_socket_t *dn_socket, const void *buf, int size)
{
    if(sendto(dn_socket->sockfd, buf, size,0,(struct sockaddr*)&client,client_len)<0)
   {
      printf("sendto error\n");
      exit(1);
   }
}
