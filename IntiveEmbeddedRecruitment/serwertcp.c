#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h> 

#define PORT 8080
#define MAXBUFF 4096

int matchIdx (char *query)
{

    char *w2Ptr = query;        /* word 2 - first char pointer */
    int w1Strlen = 0;           /* word 1 length */
    int i = 0;
    int k = 0;

    /* setting the w2Ptr to first char of word 2  */
    for (i = 0; *(query + i) != ' '; i++)
        w2Ptr++;
    
    w1Strlen = i;
    i = 0;
    w2Ptr++; 
    
    /* establish position of word 1 in word 2 (if appear)    */
    while (*(w2Ptr + i) != 0) {
        if (*query == *(w2Ptr + i)) {
           while (k++ < w1Strlen) { 
                if (*(query + k) != *(w2Ptr + i + k))
                    break;
            }
            if (k == w1Strlen) 
               return i;

            i = i + k - 1;
        }
        i++;
        k = 0;
    }

    return -1;
}



void queans(int newSocket) 
{
    char buffer[MAXBUFF];
    
    /* infinite loop for answer to the client queries */
    for(;;) {
        
        memset(buffer, 0, MAXBUFF);
        
        /* recive query from the client and put in buffer */
        recv(newSocket, buffer, MAXBUFF, 0);
        buffer[MAXBUFF - 1] = 0;         
        printf("Query from client: %s\n", buffer);
       
        /* if client type exit - close server connection */
        if (strncmp("exit\n", buffer, 5) == 0 || 
            strncmp("exit\r\n", buffer, 6) == 0 ) {
            
            printf("[+]Server Exit...\n"); 
            break; 

        }
        
        
        /* prepare and send answer to the client */
        printf("Response to the client: %d\n", matchIdx(buffer));
        sprintf(buffer, "%d\n", matchIdx(buffer));
        send(newSocket, buffer, strlen(buffer), 0);
        
        memset(buffer, 0, MAXBUFF);

    }    
}

int main(){

    int sockfd;
    struct sockaddr_in serverAddr;

    int newSocket;
    struct sockaddr_in newAddr;

    socklen_t addr_size;

    /* create socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("[+]Server Socket Creation Failed.\n");
        exit(0);
    } else {
        printf("[+]Server Socket Created Sucessfully.\n");
    }
    
    memset(&serverAddr, '\0', sizeof(serverAddr));

    /* assign ip and port */
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    /* binding socket to the ip */
    if ((bind(sockfd, (struct sockaddr*)&serverAddr, 
        sizeof(serverAddr))) != 0) {
        printf("[+]Server Socket Bind Failed.\n");
        exit(0);
    } else {
        printf("[+]Bind to Port number %d.\n", PORT);
    }   

    /* listening */
    if ((listen(sockfd, 5)) != 0) { 
        printf("[+]Listening failed.\n");
        exit(0);
    } else {
        printf("[+]Listening...\n");
    }
    
    /* accept the data from client */
    newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
    if (newSocket < 0) { 
        printf("[+]Server acccept failed...\n"); 
        exit(0); 
    } else {
        printf("[+]Server acccept the client...\n"); 
    }
        
    /* call fnc responsible for reciving and answering from/to client */
    queans(newSocket);
    
    /* close the socket */
    shutdown(newSocket,2);
    printf("[+]Closing the connection.\n");
    

    return 0;

}