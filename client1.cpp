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
	} else {
		std::cout << "CONNECTED 1!!\n";
	}

    int valread;
	char buffer[1024] = { 0 }; //MAYBE CHANGE THIS ONE TO STRING?

    while (true) {

    }

    return 0;
}