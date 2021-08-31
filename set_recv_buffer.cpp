#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define BUFFER_SIZE 512

int main(int argc,char* argv[]){

    if(argc <= 2){
        printf("usage: %s ip_address port_number recv_buffer_size\n",basename(argv[0]));
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);


    struct sockaddr_in server_address;
    bzero(&server_address,sizeof(server_address));
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET,ip,&server_address.sin_addr);
    server_address.sin_port = htons(port);

    int sockfd = socket(PF_INET,SOCK_STREAM,0);
    assert( sockfd >= 0 );

    int recvbuf = atoi(argv[3]);
    int len = sizeof(recvbuf);
    setsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,&recvbuf,sizeof(recvbuf));
    getsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,&recvbuf,(socklen_t*)&len);
    printf("the tcp receive buffer size after setting is %d\n",recvbuf);

    int ret = bind(sockfd,(struct sockaddr*)&server_address,sizeof(server_address));
    assert(ret != -1);

    ret = listen(sockfd,5);
    assert(ret != -1);

    struct sockaddr_in client;
    socklen_t client_addresslength = sizeof(client);
    int connfd = accept(sockfd,(struct sockaddr*)&client,&client_addresslength);

    if(connfd < 0){
        printf("errno is: %d\n",errno);
    }
    else{
        char buffer[BUFFER_SIZE];
        memset(buffer,'\0',BUFFER_SIZE);
        while(recv(connfd,buffer,BUFFER_SIZE-1,0)>0){}
        close(connfd);
    }
    close(sockfd);
    return 0;
}
