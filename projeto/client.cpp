/*
    C ECHO client example using sockets
*/
#include <stdio.h> //printf
#include <string.h>    //strlen
#include <sys/socket.h>    //socket
#include <arpa/inet.h> //inet_addr
#include <unistd.h>
#include <bits/stdc++.h>


using namespace std;

int main(int argc , char *argv[]) {
    int sock;
    struct sockaddr_in server;
    char cmd[1000] , server_reply[2000];
    string aux;
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1) {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );
 
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0) {
        perror("connect failed. Error");
        return 1;
    }
     
    puts("Connected\n");
     
    //keep communicating with server
    while(1) {
        printf("Enter command : ");
        getline(cin, aux);

        cout << aux << endl;
        strcpy(cmd, aux.c_str());
        
        //Send some data
        if( send(sock , cmd , strlen(cmd) , 0) < 0) {
            puts("Send failed");
            return 1;
        }
        //Receive a reply from the server
        if( recv(sock , server_reply , 2000 , 0) < 0) {
            puts("recv failed");
            break;
        }
         
        puts("Server reply :");
        cout << server_reply << endl;
        memset(server_reply,0,2000);
    }
     
    close(sock);
    return 0;
}