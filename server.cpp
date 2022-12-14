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
    //char* colors[] = ["off", "red", "blue", "green", "orange", "white", "warm"];
    //std::unordered_map<const char*, Color_t> colors = {{"red", Color(255, 0, 0)}, {"blue", Color(0, 0, 255)}, {"green", Color(0, 255, 0)}, {"orange", Color(255, 35, 0)}, {"white", Color(255, 255, 255)}, {"warm", Color(255, 50, 10)}};

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
            if (strstr(client_message, "off")) {
                led_off();
            }
            else {
                led(atoi(client_message));
            }
        }

        if (read_size == 0) {
            puts("Client disconnected");
        } else if (read_size < 0) {
            perror("recv failed");
        }
    } 

    return 0;
}