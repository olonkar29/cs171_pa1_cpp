#include <iostream>
#include <cstring>
#include <string>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread> 
#define PORT 9000

void reply_client(std::stop_token stoken, int new_socket, int* recv_flag);
void reply_client(std::stop_token stoken, int new_socket, int* recv_flag) {
	if((*recv_flag) == 0) {
		std::cout << "0" << std::endl;
		//CLIENT TRANSFER
		int trans_flag = 0;
		// Make transaction
		if(trans_flag == 0) {
			// Successful transaction
			send(new_socket, & trans_flag, sizeof(trans_flag), 0);
		} else {
			// Failed transaction
			send(new_socket, & trans_flag, sizeof(trans_flag), 0);
		}
		
	} else {
		std::cout << "1" << std::endl;
		//CLIENT EXIT
	}
}

void client_handler(std::stop_token stoken, int new_socket);
void client_handler(std::stop_token stoken, int new_socket) {
	while(true) {
		int* recv_flag;
		int valread;
		valread = recv(new_socket, recv_flag, sizeof(*(recv_flag)), 0);
		if(valread>=1) {
			// std::cout << std::to_string((*recv_flag)) << std::endl;
			std::jthread client_replier(reply_client, new_socket, recv_flag);
		}
		
		// std::jthread client_replier(reply_client, new_socket, recv_flag);
	}
}

void get_user_input(std::stop_token stoken);
void get_user_input(std::stop_token stoken){
	std::string in;
	while(true){
		std::cin >> in;
		std::cout << in << std::endl;
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
	std::jthread user_input(get_user_input);
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