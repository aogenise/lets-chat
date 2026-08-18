#include "letschat.h"
using namespace std;

/*
函数:Login
功能:查找是否有账号和密码相同的对应的账号，如果有，返回true，没有，返回false
*/
bool UserManager::Login(const string& name, const string& pwd) {
	for (const auto& user : userlist) {
		if (user.Username == name&&user.UserPassword == pwd) {
			currentUser = name;
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
	currentUser = name;
	return true;
}

/*
函数:LoadInfo
功能:加载账号信息
*/
bool UserManager::LoadInfo() {
	ifstream ifs("info.txt");    //创建ifstream(文本阅读器)类型的对象ifs，读取info.txt
	if (!ifs.is_open()) {
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
		return false;
	}
	for (const auto& user:userlist) {
		ofs << user.Username << "|" << user.UserPassword << "\n";
	}
	ofs.close();
	return true;
}


/*
函数:UnreadCount
功能:记录没有看过的信息数。如果说这条信息是我的，并且我并没有看过，那么就加一
*/

int UserManager::UnreadCount() {
	int n=0;
	for(auto m:messagelist) {
		if (m.to == currentUser && !m.is_read) {
			n++;
		}
	}
	return n;
}


/*
函数:RequestCount
功能:统计请求总数
*/
int UserManager::RequestCount() {
	int n=0;
	for (auto m : friendrequestlist) {
		if (m.to == currentUser) {
			n++;
		}
	}
	return n;
}

/*
函数:GetUnreadCount
功能:统计单个好友的未读信息总数
*/
int UserManager::GetUnreadCount(const string &friendname) {
	int n = 0;
	for (auto m : messagelist) {
		if ((m.to == currentUser && m.from == friendname && !m.is_read )||(m.from==currentUser&&m.to==friendname && !m.is_read)) {
			n++;
		}
	}
	return n;
}

/*
函数:GetMyFriends
功能:返回好友列表
*/
vector<string>UserManager::GetMyFriends() {
	vector<string>result;
	for (const auto& f : friendslist) {
		if (f.from == currentUser)result.push_back(f.to);
		if (f.to == currentUser)result.push_back(f.from);
	}
	return result;
}


/*
函数:UserExists
功能:检测用户是否存在
*/
bool UserManager::UserExists(const string& name) {
	for (const auto& m : userlist) {
		if (m.Username == name) {
			struct FriendRequest request;
			request.from = currentUser;
			request.to = name;
			friendrequestlist.push_back(request);
			return true;
		}
	}
	return false;
}


/*
函数:GetRequest
功能:返回好友申请列表
*/
vector<string>UserManager::GetRequest() {
	vector<string>result;
	for (const auto m : friendrequestlist) {
		if (m.to == currentUser) {
			result.push_back(m.from);
		}
	}
	return result;
}


/*
函数:AcceptFriendRequset
功能:同意好友请求
*/
bool UserManager::AcceptFriendRequest(const string&requester) {
	for (auto it = friendrequestlist.begin(); it != friendrequestlist.end();) {
		if (it->from == requester&&it->to==currentUser) {
			Friends f;
			f.to = currentUser;
			f.from = requester;
			friendslist.push_back(f);
			friendrequestlist.erase(it);
			return true;
		}
		else {
			++it;
		}
	}
	return false;
}


/*
函数:HasFeedPosts
功能:检测有无动态
*/
bool UserManager::HasFeedPosts() {
	if (Feedlist.size() != 0)return true;
	else return false;
}


/*
函数:GetFeed
功能:输出好友动态
*/
vector<string>UserManager::GetFeed() {
	vector<string>result;
	for (const auto& m : Feedlist) {
		if (IsFriend(m.name)) {
			result.push_back(m.name+":\n     "+m.contents);
		}
	}
	return result;
}



/*
函数:EnterPost
功能:将内容加入动态流
*/
void UserManager::EnterPost(const string& content) {
	FriendFeed F;
	F.name = currentUser;
	F.contents = content;
	Feedlist.push_back(F);
}



/*
函数:IsFriend
作用:判断是否为我的好友
*/
bool UserManager::IsFriend(const string& name) {
	for (const auto m : friendslist) {
		if (m.from == name && m.to == currentUser); return true;
		if (m.to == name && m.from == currentUser); return true;
	}
	return false;
}