#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/un.h>
#include <stdlib.h>
#include <errno.h>
#define PATH  "tpf_unix_sock.server"

int clients[100];
int clientcount=0;    

void send_all(char *msg,int curr){
    int i=0;

    while(i<clientcount){
        if(clients[i]!=curr){
            send(clients[i],msg,strlen(msg),0);
        }
        i++;
    }

}
void send_pm(char *msg,int tosocket,int curr){
 // pthread_mutex_lock(&mutex);
 // if(tosocket >=n){
 //    printf("Trying to send messages to an undefined client. Try again \n");
 // }
 // else if(clients[tosocket]==curr){
 //    char *send_msg="You are trying to send a message to yourself. Try again ";
 //    printf("You are trying to send a message to yourself. Try again \n");
 //    // strcat(send_msg,"You are trying to send a message to yourself. Try again ");
 //    // int len = write(clients[tosocket],send_msg,strlen(send_msg));
 //    send(curr,send_msg,strlen(send_msg),0);
 // }
 // else{
send(clients[tosocket],msg,strlen(msg),0);
// }
 // pthread_mutex_unlock(&mutex);
}
void send_error(char *msg, int curr){
    printf("This is msg : %s\n",msg);
    send(curr,msg,strlen(msg),0);
}
void *recieve(void *client_sock){
    int sock = *((int *)client_sock);
    char msg[500];
    int len;
    while((len = recv(sock,msg,500,0)) > 0) {
        msg[len] = '\0';
        // printf("this is the msg%s\n",msg );
        char * token=strtok(msg," ");
        // send_all(token,sock);
        token=strtok(NULL," ");      //all/send
        if(strcmp(token,"SEND")==0){
            printf("identified SEND\n");
            token=strtok(NULL," "); //number
            int tosocket= atoi(token);

            if(tosocket<=0){
                char*msg="Invalid/ Missing argument. Input only available clients\n";
                send_error(msg,sock);
            }
            // printf("socket number %d , AND current sock no.%d AND arayval %d n %d \n",tosocket-1,sock,clients[tosocket-1],n);

            if(tosocket-1>=clientcount){
                // printf("wtfff");
                char *msg1="Trying to send messages to an undefined client. Try again\n";
                send_error(msg1,sock);
            }
            else if(clients[tosocket-1]==sock){
                char *msg2="You are trying to send a message to yourself. Try again\n";
                send_error(msg2,sock);
            }
            
            else{
                char *newmsg="Personal message from ";
                // printf("%s\n",newmsg);
                send_pm(newmsg,tosocket-1,sock);    //sending above string
                send_pm(msg,tosocket-1,sock);      //SENDING NAME

                /*
                token=strtok(NULL," ");     //real msg
                
                while(token!=NULL){
                    send_pm(token,tosocket-1,sock);
                    token=strtok(NULL," ");
                }
                */
                char bigstring[500];
                token=strtok(NULL," ");     //real msg   
                while(token!=NULL){
                    strcat(bigstring,token);
                    strcat(bigstring," ");
                    token=strtok(NULL," ");
                }
                send_pm(bigstring,tosocket-1,sock);
                memset(bigstring,0,strlen(bigstring));
                }
        }
        else if(strcmp(token,"ALL")==0){
            printf("identified ALL \n");
            // printf("This is the msg %s\n",msg);
            char *newmsg="Global message from ";
            send_all(newmsg,sock);
            send_all(msg,sock);        //SENDING NAME


            char bigstring[500];
            token=strtok(NULL," ");     //real msg   
            while(token!=NULL){
                strcat(bigstring,token);
                strcat(bigstring," ");
                token=strtok(NULL," ");
            }
            send_all(bigstring,sock);
            memset(bigstring,0,strlen(bigstring));
        }
        // else if(strcmp(token,"/ME")==0){
        //     char *msg = "My details.\n client no ";
        //      // strcat(msg,clientcount+1);
        //      strcat(msg," ");
        //      // strcat(msg,Client_sock);
        //     printf("%s\n",msg);
        //     // strcat(msg,)
            
        // }
        else{
            // printf("%s",token);
            char *msg = "Please check documentation; Use SEND/ALL only.\n";
            // printf("%s\n", msg);
            send_error(msg,sock);
        }
    }

}

int main(){

    pthread_t my_thread;
    int sock=0 , Client_sock=0;
    struct sockaddr_un server_sockaddr; 
    memset(&server_sockaddr, 0, sizeof(struct sockaddr_un));
                     
    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock == -1){
        printf("SOCKET ERROR:\n");
    }
    server_sockaddr.sun_family = AF_UNIX;   
    strcpy(server_sockaddr.sun_path, PATH); 
    int length=sizeof(server_sockaddr);
    unlink(PATH);

    int bindingvalue=bind(sock,(struct sockaddr *)&server_sockaddr, length);
        if(bindingvalue==-1)
            printf("BINDING ERROR  \n");
    else
        printf("Server is up!\n");

    int listeningvalue=listen(sock ,100);
    if(listeningvalue==-1)
        printf("LISTENING FAILURE \n");
    else{
        printf("Listening has started \n");
    }

    while(1){
        Client_sock = accept(sock, (struct sockaddr *)NULL,NULL);
        
        if(Client_sock<0)
            printf("Accept failed  \n");
        else 
            printf("Client no %d connected at port %d\n",clientcount+1,Client_sock);
        

        
        clients[clientcount]= Client_sock;
        clientcount++;
 
        pthread_create(&my_thread,NULL,(void *)recieve,&Client_sock);

    }
    return 0; 

}