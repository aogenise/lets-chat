#include"letschat.h"
using namespace std;


/*
函数:chat_start
功能:检测登录/注册。成功后进入主界面
*/
void chat_start(UserManager& Mgr) {
	cout << "welcome let's chat!" << endl;
	string selected_input;
try_again:
	cout << "Login or Sign up?" << endl;
	cin >> selected_input;
	/*登录*/
	if (selected_input == "login" || selected_input == "Login") {
		string name, pwd;
	try_again_login:
		cout << "please enter your UserName:";
		cin >> name;
		cout << "please enter your password:";
		cin >> pwd;
		if (Mgr.Login(name, pwd)) {
			cout << "success!" << endl;
			ShowMainPage(Mgr);
		}
		else {
			cout << "please try again!" << endl;
			goto try_again_login;
		}
	}
	/*注册*/
	else if (selected_input == "signup" || selected_input == "Signup") {
		string name, pwd, pwd2;
	try_again_name:
		cout << "please enter your Username:";
		cin >> name;
	try_again_pwd:
		cout << "please enter your password:";
		cin >> pwd;
		cout << "please enter your password again:";
		cin >> pwd2;
		if (pwd == pwd2) {
			if (Mgr.Sign_up(name, pwd)) {
				cout << "success!";
				Mgr.SaveInfo();
				ShowMainPage(Mgr);
			}
			else {
				cout << "Username already exists.";
				goto try_again_name;
			}
		}
		else {
			cout << "password do not match!";
			Sleep(1000);
			system("cls");
			goto try_again_pwd;
		}
	}
	else {
		cout << "Please try again" << endl;
		goto try_again;
	}

}



/*
函数:ShowMainPage
功能:展示主界面
*/
void ShowMainPage(UserManager &mgr){
	while (true) {
		system("cls");
	cout << "let's chat!";
	if (mgr.UnreadCount()!= 0) {
		cout << "(" << mgr.UnreadCount() << " unread)";
	}
	cout << endl;

	cout << "1.Chat" << endl;
	cout << "2.Contacts" << endl;
	cout << "3.Friend Feed" << endl;
	cout << "4.Friend Requests";
	if (mgr.RequestCount() != 0) {
		cout << "(" << mgr.RequestCount() << " pending requests)";
	}
	cout << endl;
	cout << "5.Add Friend" << endl;
	cout << "6.Sign Out" << endl;
	int choose;

	
		cout << "Please select an operation:";
		cin >> choose;
		if (!cin) {
			cin.clear();
			while (cin.get() != '\n');
			cout << "invalid option.please try again" << endl;
			continue;
		}
		switch (choose) {
		case 1:
			chat(mgr);
			break;
		case 2:
			contacts(mgr);
			break;
		case 3:
			friend_feed(mgr);
			break;
		case 4:
			friend_request(mgr);
			break; 
		case 5:
			add_friend(mgr);
			break;
		case 6:
			mgr.SaveInfo();
			return;
			break;
		default:
			cout << "invalid option.please try again"<<endl;
		}
	}
}


/*
函数:chat
功能:遍历用户好友，进行聊天
*/
void chat(UserManager& mgr) {
	while (1) {
		system("cls");
		for (const auto& name : mgr.GetMyFriends()) {
			cout << name;
			int unread = mgr.GetUnreadCount(name);
			if (unread != 0) {
				cout << "(" << unread << "unread)";
			}
			cout << endl;
		}
		vector<string>fri = mgr.GetMyFriends();
		cout << "please select a conversation(0 to exits)";
		int temp;
		cin >> temp;
		cin.ignore();
		if (temp == 0)return;
		system("cls");
		string name = fri[temp - 1];
		while (1) {
			for (const auto m : mgr.GetMassage(name)) {
				cout << m<<endl;
			}
			mgr.Read();
			cout << endl << "please enter...(0 exits):";
			string temp2;
			getline(cin,temp2);
			if (temp2 == "0")break;
			mgr.AddMassage(temp2, name);
			system("cls");
		}
	}
	}

void contacts(UserManager& mgr) {
	system("cls");
	int n = 1;
	for (const auto& m : mgr.GetMyFriends()) {
		cout << n++ <<"." << m << endl;
	}
	Sleep(1000);
}

/*
函数:friend_feed
功能:打印好友动态，给出发表入口
*/
void friend_feed(UserManager& mgr) {
	system("cls");
	if (!mgr.HasFeedPosts()) {
		cout << "No post available."<<endl;
	}
	else {
		vector<string> result = mgr.GetFeed();
		for (const auto m : result) {
			cout << m<<endl;
		}
	}
	cout << "post a status?(y/n):";
	string m;
	cin >> m;
	if (m == "y" || m == "yes"||m=="Y"||m=="Yes") {
		cin.ignore();
		cout << "please enter your post content:";
		string con;
		getline(cin, con);
		mgr.EnterPost(con);
		cout << "successful!";
		Sleep(1000);
	}
	return;
}

/*
函数:friend_request
功能:查看现有的好友申请，并且决定是否同意
*/
void friend_request(UserManager& mgr) {
	system("cls");
	int n=1;
	vector<string>result = mgr.GetRequest();
	for (const auto name : mgr.GetRequest()) {
		cout << n++ << ":" << name << endl;
	}
	cout << "please select a friend request to accept:";
	int m;
	cin >> m;
	string requester = result[m - 1]; //发起申请人的名字
	mgr.AcceptFriendRequest(requester);
	cout << "Added successfuly!";
}



/*
函数:add_friend
功能:添加好友
*/
void add_friend(UserManager& mgr) {
	system("cls");
	cout << "please enter your friend's name:";
	string name;
	cin >> name;
	if (mgr.UserExists(name) == true) {
		cout << "Friend added successfuly!"<<endl;
		Sleep(1000);
		return;
	}
	else {
		cout << "User not found,please exit or try again";
		Sleep(1000);
		return;
	}
}

