#include "letschat.h"
using namespace std;

/*
函数:Login
功能:查找是否有账号和密码相同的对应的账号，如果有，返回true，没有，返回false
*/
bool UserManager::Login(const string& name, const string& pwd) {
	for (const auto& user : userlist) {
		if (user.Username == name&&user.UserPassword == pwd) {
			return true;
		}
	}
	return false;
}

/*
函数:Sign_up
功能:查找是否有重复的用户名，随后创建新的账号，如果用户名重复，返回false，创建成功，返回true
*/
bool UserManager::Sign_up(const string& name,const string& pwd) {
	for (const auto& user : userlist) {
		if (user.Username == name) {
			return false;
		}
	}
	UserInfo newUser;
	newUser.Username = name;
	newUser.UserPassword = pwd;
	userlist.push_back(newUser);
	return true;
}

/*
函数:LoadInfo
功能:加载账号信息
*/
bool UserManager::LoadInfo() {
	ifstream ifs("info.txt");    //创建ifstream(文本阅读器)类型的对象ifs，读取info.txt
	if (!ifs.is_open()) {
		cout << "File not found";
		Sleep(2000);
		return false;
	}
	userlist.clear();    //先清空，防止重复读入
	string line;       //将数据暂存在line 
	while (getline(ifs, line)) {
		size_t pos = line.find('|');
		if (pos == string::npos) {
			continue;
		}
		UserInfo U;
		U.Username = line.substr(0, pos );
		U.UserPassword = line.substr(pos + 1);
		userlist.push_back(U);
	}
	ifs.close();
	return true;
}

/*
函数:SaveInfo
功能:写入账户信息
*/
bool UserManager::SaveInfo() {
	ofstream ofs("info.txt");
	
	if (!ofs.is_open()) {
		cout << "File not found!";
		Sleep(2000);
		return false;
	}
	for (const auto& user:userlist) {
		ofs << user.Username << "|" << user.UserPassword << "\n";
	}
	ofs.close();
	return true;
}
