#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <string>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <unistd.h>

#define PORT 9000

void get_user_input(std::stop_token stoken, int client_fd);
void get_user_input(std::stop_token stoken, int client_fd){
	std::string in;
	int send_flag;
    while (true) {
		std::cin >> in;
		/*
		if (in.at(0) == 'T') {
			send_flag = 0;
			send(client_fd, &send_flag, sizeof(send_flag), 0);
		} else if (in.at(0) == 'E') {
			send_flag = 1;
			send(client_fd, &send_flag, sizeof(send_flag), 0);
		} else if (in.at(0) == 'W') {
			sleep(5);
		} else {
			std::cout << "Invalid command. Try again." << std::endl;
		}
		*/
		send_flag = 0;
		send(client_fd, &send_flag, sizeof(send_flag), 0);
    }
}

void handle_message(std::stop_token stoken, int* serv_flag);
void handle_message(std::stop_token stoken, int* serv_flag) {
	if((*serv_flag) == 0) {
		std::cout << "Success" << std::endl;
	} else {
		std::cout << "Insufficient Balance" << std::endl;
	}
}

int main(int argc, char const* argv[]) {
    sleep(1);
    int client_fd;
	if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		std::cout << "\n Socket creation error \n";
		return -1;
	}
    struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
		std::cout << "\n Invalid address / Address not supported \n";
		return -1;
	}
    int status;
	
    if((status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
		std::cout << "\n Connection Failed \n";
		return -1;
	}

	std::jthread user_input(get_user_input, client_fd);
	
	while(true){
		int valread;
		int* serv_flag;
		valread = recv(client_fd, serv_flag, sizeof(*(serv_flag)), 0);
		if (valread>=1) {
			std::jthread msg_handler(handle_message, serv_flag);
		}
	}
	
    return 0;
}