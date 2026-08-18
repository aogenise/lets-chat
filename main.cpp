#include"letschat.h"
using namespace std;

int main() {
	UserManager Mgr;
	Mgr.LoadInfo();
	chat_start(Mgr);
	return 0;
}

