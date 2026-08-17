#include"letschat.h"
using namespace std;

int main() {
	UserManager Mgr;
	Mgr.LoadInfo();
	chat_start(Mgr);
	return 0;
}

void chat_start(UserManager &Mgr) {
	cout << "welcome let's chat!" << endl;
	string selected_input;
try_again:
	cout << "Login or Sign up?" << endl;
	cin >> selected_input;
	/*µÇÂ¼*/
	if (selected_input == "login"||selected_input=="Login") {
		string name, pwd;
try_again_login:
		cout << "please enter your UserName:";
		cin >> name;
		cout << "please enter your password:";
		cin >> pwd;
		if (Mgr.Login(name, pwd)) {
			cout << "success!" << endl;
		}
		else {
			cout << "please try again!" << endl;
			goto try_again_login;
		}
	}
	/*×¢²á*/
	else if(selected_input == "signup"||selected_input=="Signup") {
		string name, pwd,pwd2;
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
		cout << "Please try again"<<endl;
		goto try_again;
	}
	
}