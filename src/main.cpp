#include <stdio.h>
#include <string.h>
#include <string>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define LISTEN_PORT 6789

int main()
{
	// create listen socket
	int listenfd  = socket(AF_INET, SOCK_STREAM, 0);

	// bind the listen socket
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(LISTEN_PORT);

	if (bind(listenfd, (sockaddr*)&addr, sizeof(addr)) == -1)
	{
		fprintf(stderr, "bind failed on port %u\n", LISTEN_PORT);
		return -1;
	}

	// start listening
	if (listen(listenfd, SOMAXCONN) == -1)
	{
		fprintf(stderr, "listen failed on port %u\n",  LISTEN_PORT);
		return -2;
	}
	fprintf(stdout, "listen succ on port %u\n", LISTEN_PORT);

	// accept client
	sockaddr_in clientaddr;
	socklen_t clientaddr_len = sizeof(clientaddr);
	int clientfd = accept(listenfd, (sockaddr*)&clientaddr, &clientaddr_len);
	if (clientfd == -1)
	{
		fprintf(stderr, "accpet failed\n");
		return -3;
	}
	fprintf(stdout, "accpet a client from %s:%u\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

	// close listen socket
	close(listenfd);

	// recv message from client
	char buffer[1024];
	while (true)
	{
		memset(buffer, 0, sizeof(buffer));
		int recv_len = recv(clientfd, buffer, sizeof(buffer), 0);
		if (recv_len < 0)
		{
			fprintf(stderr, "recv failed!\n");
			break;
		}
		else if (recv_len == 0)
		{
			fprintf(stdout, "client closed\n");
			break;
		}
		else
		{
			std::string message(buffer, 0, recv_len);
			fprintf(stdout, "recv message: %s\n", message.c_str());

			// send back
			send(clientfd, buffer, recv_len, 0);
		}
	}

	// close client socket
	close(clientfd);

	return 0;
}
