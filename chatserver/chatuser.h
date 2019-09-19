#ifndef CHATUSER_H
#define CHATUSER_H

class ChatUser
{
public:
	ChatUser();
	~ChatUser();

	void Init(int socket_fd);

private:
	int m_socket_fd;
};

#endif // CHATUSER_H
