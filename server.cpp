#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "led.h"


int main() {
    int socket_desc, client_desc; //socket file descriptor
    struct sockaddr_in server_info, client_info; //server info
    socklen_t server_info_len = sizeof(server_info);
    socklen_t client_info_len = sizeof(client_info);
    char* message, client_message[2000];
    char msg[200];

    //Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc < 0) {
        perror("socket");
        return -1;
    }

    server_info.sin_family = AF_INET;
    server_info.sin_addr.s_addr = INADDR_ANY; //equal to server_info = {0} (any ips)
    server_info.sin_port = htons ( 80 );

    //Bind
    if (bind(socket_desc, (struct sockaddr*)&server_info, server_info_len) < 0) {
        perror("bind failed");
        return -1;
    }

    //Listen
    listen(socket_desc, 3);

    //Accept incoming connections
    puts("Online...");
    while((client_desc = accept(socket_desc, (struct sockaddr *)&client_info, &client_info_len))) {
        if (client_desc<0) {
		    perror("accept failed");
	    }
        puts("Connection accepted");

        //char* client_ip = inet_ntoa(client_info.sin_addr);      //get ip from client
        // int client_port = ntohs(client_info.sin_port);          //get port from client

        //Send message to client
        message = "Hello Client\n";
        send(client_desc, message, strlen(message), 0);

        //Receive messages from client
        int read_size;
        while ((read_size = recv(client_desc, client_message, strlen(client_message), 0)) > 0) {
            puts(client_message);
            strcpy(msg, client_message);
            puts(msg);
            if (strstr(msg, "off"))
                led_off();
            else
                led(msg);
        }

        if (read_size == 0) {
            puts("Client disconnected");
        } else if (read_size < 0) {
            perror("recv failed");
        }
    } 

    return 0;
}