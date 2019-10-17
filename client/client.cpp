#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(-1);
	}

	// create client socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	// connect to server
	sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(atoi(argv[1]));
	inet_pton(AF_INET, "127.0.0.1", &serveraddr.sin_addr);
	int res = connect(sockfd, (sockaddr*)&serveraddr, sizeof(serveraddr));
	if (res == -1)
	{
		perror("connect");
		exit(-2);
	}

	// handle loop
	std::string msg;
	char buffer[1024];
	while (true)
	{
		// read from keyboard
		if (!getline(std::cin, msg))
		{
			break;
		}

		// send to server
		send(sockfd, msg.c_str(), msg.size() + 1, 0);

		// receive from server
		int recv_len = recv(sockfd, buffer, sizeof(buffer), 0);
		if (recv_len > 0)
		{
			std::cout << buffer << std::endl;
		}
	}

	close(sockfd);

	return 0;
}
