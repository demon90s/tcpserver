#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "chatusermanager.h"
#include "chatuser.h"

ChatUserManager &ChatUserManager::Instance()
{
	static ChatUserManager inst;
	return inst;
}

void ChatUserManager::AddChatUser(int socket_fd)
{
	if (m_chatuser.find(socket_fd) != m_chatuser.end())
	{
		return;
	}

	std::shared_ptr<ChatUser> chat_user(new ChatUser());
	chat_user->Init(socket_fd);
	m_chatuser.insert(std::make_pair(socket_fd, chat_user));
}

void ChatUserManager::RemoveChatUser(int socket_fd)
{
	m_chatuser.erase(socket_fd);
}

void ChatUserManager::Broadcast(char *buffer, int length, const std::set<int> &exclude)
{
	for (auto p : m_chatuser)
	{
		if (exclude.find(p.first) == exclude.end())
		{
			send(p.first, buffer, length, 0);
		}
	}
}

ChatUserManager::ChatUserManager()
{

}

ChatUserManager::~ChatUserManager()
{
}
