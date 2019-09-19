#include "chatuser.h"

ChatUser::ChatUser() : m_socket_fd(-1)
{

}

ChatUser::~ChatUser()
{

}

void ChatUser::Init(int socket_fd)
{
	m_socket_fd = socket_fd;
}
