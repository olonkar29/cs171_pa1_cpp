#include <iostream>
#include <cstring>
#include <string>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread> 
#define PORT 9000

void client_handler(std::stop_token stoken, int new_socket);

void client_handler(std::stop_token stoken, int new_socket) {
	while(true) {
		// char buffer[1024] = { 0 }; MAYBE CHANGE THIS TO STRING??
		int* recv_flag;
		int valread;
		// std::cout << "a" << std::endl;
		valread = recv(new_socket, recv_flag, sizeof(*(recv_flag)), 0);
		if((*recv_flag) == 0) {
			std::cout << "0" << std::endl;
		} else {
			std::cout << "1" << std::endl;
		}
		
	}
}

int main(int argc, char const* argv[]) {
    // std::cout << "hi" << std::endl;
    int server_fd;
	//Creating socket file descriptor
	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
    //setsockopt
	int opt = 1;
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
    //address
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	//bind
	if(bind(server_fd, (struct sockaddr*)&address, addrlen) < 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	//listen
	if (listen(server_fd, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

    // INSTANTIATE BLOCKCHAIN
	std::cout << "START BLOCKCHAIN" << std::endl;

    // START THREAD FOR USER INPUT
    std::cout << "STARTING USER INPUT THREAD" << std::endl;
    int num_connections = 0;
    int client_sockets[3];

    // FOR EVERY CLIENT START A CLIENT HANDLER THREAD
    while(true) {
        int new_socket;
		if((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
			perror("accept");
			exit(EXIT_FAILURE);
		}
        client_sockets[num_connections] = new_socket;
        std::jthread client(client_handler, new_socket);
        // client.detach();
        num_connections++;
    }

    shutdown(server_fd, SHUT_RDWR);

    return 0;
}