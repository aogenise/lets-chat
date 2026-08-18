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

	while (true) {
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
			/*聊天函数chat*/
			break;
		case 2:
			/*通讯录函数Contacts*/
			break;
		case 3:
			/*好友动态函数*/
			break;
		case 4:
			/*好友申请函数*/
			break;
		case 5:
			/*添加好友函数*/
			break;
		case 6:
			/*登出账号函数*/
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

}