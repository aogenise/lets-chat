#pragma once
#include<iostream>
#include<Windows.h>
#include<vector>
#include<string>
#include<fstream>
#include <limits>
using namespace std;

struct UserInfo {
	string Username;
	string UserPassword;
};

struct Friends {
	string from;   //谁加
	string to;   //加谁
};

struct Message {
	string from;
	string to;
	string contents;
	bool is_read;
};

struct FriendRequest {
	string from;
	string to;
};

struct FriendFeed {
	string contents;
	string name;
};
class UserManager {
private:
	vector<UserInfo>userlist;
	vector<Friends>friendslist;
	vector<FriendRequest>friendrequestlist;
	vector<Message>messagelist;
	vector<FriendFeed>Feedlist;
	string currentUser;
public:
	//写入信息
	bool SaveInfo();
	//读取信息
	bool LoadInfo();
	//登录界面
	bool Login(const string &name,const string &pwd);
	//注册界面
	bool Sign_up(const string &name,const string &pwd);
	//检测用户是否存在并且书写发送信息
	bool UserExists(const string &name);
	//同意好友申请，将该数据从申请队列转移到好友队列
	bool AcceptFriendRequest(const string& requester);
	//返回动态存在情况
	bool HasFeedPosts();
	//判断是否是我的好友
	bool IsFriend(const string& name);
	//统计未读消息总数
	int UnreadCount();
	//统计请求总数
	int RequestCount();
	//统计单个好友的未读消息总数
	int GetUnreadCount(const string &friendname);
	//将动态加入动态流
	void EnterPost(const string& content);
	//返回动态信息
	vector<string> GetFeed();
	//返回好友列表
	vector<string>GetMyFriends();
	//返回好友申请列表
	vector<string>GetRequest();
};



void chat_start(UserManager& mgr);
void ShowMainPage(UserManager& mgr);
void chat(UserManager& mgr);
void contacts(UserManager& mgr);
void friend_feed(UserManager& mgr);
void friend_request(UserManager& mgr);
void add_friend(UserManager& mgr);