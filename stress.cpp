#include <bits/stdc++.h>
using namespace std;
const string name = "a";
bool check() {
	return system(("fc out ans")) != 0;
}
int main() {
	int iTest = 1;
	while(1) {

	 system((name + "_gen.exe > in").c_str());
	 system((name + ".exe < in > out").c_str());
	 system((name + "_slow.exe < in > ans").c_str());

	if (check()) {
			cout << "Test " << iTest << ": WRONG!\n";
			return 0;
	}
		 cout << "Test " << iTest << ": CORRECT!\n";
		 ++iTest;
	}
	return 0;
}
