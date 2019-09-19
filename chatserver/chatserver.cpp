#include <stdio.h>
#include <string.h>
#include <string>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "chatusermanager.h"

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

	// init fd_set
	fd_set master;
	FD_ZERO(&master);

	FD_SET(listenfd, &master);

	char buffer[4096];

	while (true)
	{
		fd_set master_copy = master;

		int sock_count = select(FD_SETSIZE, &master_copy, 0, 0, 0);
		if (sock_count <= 0)
		{
			break;
		}

		int cur_count = 0;
		for (int fd = STDERR_FILENO + 1;; fd++)
		{
			if (!FD_ISSET(fd, &master_copy)) continue;

			if (fd == listenfd)
			{
				// accept a client
				int clientfd = accept(listenfd, 0, 0);
				if (clientfd != -1)
				{
					FD_SET(clientfd, &master);
					CHATUSER_MGR.AddChatUser(clientfd);

					// TODO: broad cast to all client
				}
			}
			else
			{
				// recv a message from client
				memset(buffer, 0, sizeof(buffer));

				int recv_len = recv(fd, buffer, sizeof(buffer), 0);
				if (recv_len <= 0)
				{
					close(fd);
					FD_CLR(fd, &master);
					CHATUSER_MGR.RemoveChatUser(fd);
				}
				else
				{
					// broadcast the message to all client
					CHATUSER_MGR.Broadcast(buffer, recv_len, {fd});
				}
			}

			cur_count++;
			if (cur_count >= sock_count) break;
		}
	}

	// close listening socket
	close(listenfd);

	return 0;
}
