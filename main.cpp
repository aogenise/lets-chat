#include"letschat.h"
using namespace std;

int main() {
	UserManager Mgr;
	Mgr.LoadInfo();
	while (1) {
		chat_start(Mgr);
	}
	return 0;
}

