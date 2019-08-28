#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include "quote.h"

#define PORT 6789

int main()
{
    Quote quote;
    if (!quote.Init("quote.txt"))
    {
        return -1;
    }

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);

    // bind socket
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(PORT);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
    if (bind(listenfd, (sockaddr*)&hint, sizeof(hint)) == -1)
    {
        perror("bind");
        return -2;
    }

    // listen
    if (listen(listenfd, SOMAXCONN) == -1)
    {
        perror("listen");
        return -3;
    }

    // accept
    while (true)
    {
        int clientfd = accept(listenfd, NULL, NULL);
        if (clientfd == -1)
        {
            perror("accept");
            return -4;
        }

        // recv send
        while (true)
        {
            char buffer[1024];
            memset(buffer, 0, sizeof(buffer));

            int recvlen = recv(clientfd, buffer, sizeof(buffer), 0);
            if (recvlen <= 0)
            {
                break;
            }
            else
            {
                std::string msg = std::string(buffer, 0, recvlen);
                std::string back_msg = "";
                if (msg.find("QUOTE") != std::string::npos)
                {
                    back_msg = quote.GetRandomQuote();
                }

                send(clientfd, back_msg.c_str(), back_msg.size() + 1, 0);
            }
        }
    }
    return 0;
}
