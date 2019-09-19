#ifndef CHATUSERMANAGER_H
#define CHATUSERMANAGER_H

#include <map>
#include <set>
#include <memory>

#define CHATUSER_MGR ChatUserManager::Instance()

class ChatUser;

class ChatUserManager
{
public:
	static ChatUserManager& Instance();

	void AddChatUser(int socket_fd);
	void RemoveChatUser(int socket_fd);

	void Broadcast(char *buffer, int length, const std::set<int> &exclude);

private:
	ChatUserManager();
	~ChatUserManager();

	std::map<int, std::shared_ptr<ChatUser>> m_chatuser;					// socketfd -> chatuser
};

#endif // CHATUSERMANAGER_H
