#pragma once
#include<iostream>
#include<Windows.h>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

struct UserInfo {
	string Username;
	string UserPassword;
};

class UserManager {
private:
	vector<UserInfo>userlist;
public:
	//写入信息
	bool SaveInfo();
	//读取信息
	bool LoadInfo();
	//登录界面
	bool Login(const string &name,const string &pwd);
	//注册界面
	bool Sign_up(const string &name,const string &pwd);
};


void chat_start(UserManager& mgr);
