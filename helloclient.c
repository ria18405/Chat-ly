#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/un.h>
#include <sys/types.h>
#define CLIENT_PATH "tpf_unix_sock.client"
#define SERVER_PATH "tpf_unix_sock.server"
char msg[500];

void *recieve(void *my_sock)
{
    int sock = *((int *)my_sock);
    int len;
    while((len = recv(sock,msg,500,0)) > 0) {
        msg[len] = '\0';
        printf(" %s",msg);
    }
}

int main(int argc,char *argv[]){
    pthread_t my_thread;
    int len;
    int sock;
    char newmsg[500];

    struct sockaddr_un server_sockaddr; 
    struct sockaddr_un client_sockaddr;
    memset(&server_sockaddr, 0, sizeof(struct sockaddr_un));
    memset(&client_sockaddr, 0, sizeof(struct sockaddr_un));

    char client_name[100];
    strcpy(client_name, argv[1]);

    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock == -1){
        printf("SOCKET ERROR\n");
    }

    client_sockaddr.sun_family = AF_UNIX;   
    strcpy(client_sockaddr.sun_path, CLIENT_PATH); 
 
    unlink(CLIENT_PATH);
    if (bind(sock,(struct sockaddr *) &client_sockaddr, sizeof(client_sockaddr))==-1)
        printf("BINDING ERROR:\n");
    
    server_sockaddr.sun_family = AF_UNIX;
    strcpy(server_sockaddr.sun_path, SERVER_PATH);
    int length=sizeof(client_sockaddr);
    int connectingvalue=connect(sock,(struct sockaddr *) &server_sockaddr,length );
    if(connectingvalue==-1)
        printf("\n CONNECTION FAILURE \n");
    

    pthread_create(&my_thread,NULL,(void *)recieve,&sock);


    while(1){
        fgets(msg,500,stdin); 
        // printf("%s",msg );
        // if(strcmp(msg,"./ME")==0){
        //     printf("MY DETAILS : Name : %s \n",client_name );
        // }
        // else{
        strcpy(newmsg,client_name);
        strcat(newmsg,"-->");
        strcat(newmsg," ");
        strcat(newmsg,msg);
        len=send(sock,newmsg,strlen(newmsg),0);
        }
    // }

    pthread_join(my_thread,NULL);
    close(sock);
    return 0;
}