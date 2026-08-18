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

class UserManager {
private:
	vector<UserInfo>userlist;
	vector<Friends>friendslist;
	vector<FriendRequest>friendrequestlist;
	vector<Message>messagelist;
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
	int UnreadCount();
	int RequestCount();
};



void chat_start(UserManager& mgr);
void ShowMainPage(UserManager& mgr);
void chat(UserManager& mgr);