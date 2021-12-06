#include <iostream>
#include <list>
#include <string>
#include <algorithm>

int Operation(int a, int b, int mode) {
	switch (mode) {
	case 0:
		return a + b;

	case 1:
		return a - b;

	case 2:
		return a * b;

	case 3:
		if (b == 0 || a < b) {
			return -1;
		}
		else {
			//only allow a divide by b
			if (a % b != 0) {
				return -1;
			}
			else {
				return a / b;
			}
		}

	default:
		return -1;
	}
}

const int g_max_num = 50;
std::list<std::string> g_answers;

// ((a+b)+c)+d
bool FormA(const int x[], int i, int j, int k) {
	int a = x[0];
	int b = x[1];
	int c = x[2];
	int d = x[3];

	int ret = Operation(a, b, i);
	if (ret < 0) {
		return false;
	}
	
	ret = Operation(ret, c, j);
	if (ret < 0) {
		return false;
	}

	ret = Operation(ret, d, k);
	if (ret == 24) {
		return true;
	}
	else {
		return false;
	}
}

// (a+b) + (c+d)
bool FormB(const int x[], int i, int j, int k) {
	int a = x[0];
	int b = x[1];
	int c = x[2];
	int d = x[3];

	int ret1 = Operation(a, b, i);
	int ret2 = Operation(c, d, k);

	if (ret1 < 0 || ret2 < 0) {
		return false;
	}

	ret1 = Operation(ret1, ret2, j);
	
	if (ret1 == 24) {
		return true;
	}
	else {
		return false;
	}
}

// (a + (b+c)) +d
bool FormC(const int x[], int i, int j, int k) {
	int a = x[0];
	int b = x[1];
	int c = x[2];
	int d = x[3];

	int ret = Operation(b, c, j);

	if (ret < 0) {
		return false;
	}

	ret = Operation(a, ret, i);

	if (ret < 0) {
		return false;
	}

	ret = Operation(ret, d, k);
	if (ret == 24) {
		return true;
	}
	else {
		return false;
	}
}

// a + ((b+c) + d)
bool FormD(const int x[], int i, int j, int k) {
	int a = x[0];
	int b = x[1];
	int c = x[2];
	int d = x[3];

	int ret = Operation(b, c, j);

	if (ret < 0) {
		return false;
	}

	ret = Operation(ret, d, k);

	if (ret < 0) {
		return false;
	}

	ret = Operation(a, ret, i);

	if (ret == 24) {
		return true;
	}
	else {
		return false;
	}
}

// a + (b + (c + d))
bool FormE(const int x[], int i, int j, int k) {
	int a = x[0];
	int b = x[1];
	int c = x[2];
	int d = x[3];

	int ret = Operation(c, d, k);

	if (ret < 0) {
		return false;
	}

	ret = Operation(b, ret, j);

	if (ret < 0) {
		return false;
	}

	ret = Operation(a, ret, i);
	if (ret == 24) {
		return true;
	}
	else {
		return false;
	}
}

void Solve4Num(const int x[]) {
    static const char symbol[4] = {'+' , '-', 'x', '/'};
	const int a = x[0];
	const int b = x[1];
	const int c = x[2];
	const int d = x[3];
	char s_buff[100];
	bool s;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				const char op1 = symbol[i];
				const char op2 = symbol[j];
				const char op3 = symbol[k];

				s = FormA(x, i, j, k);
				if (s) {
					sprintf_s(s_buff, "((%d %c %d) %c %d) %c %d", a, op1, b, op2, c, op3, d);
					g_answers.push_back(s_buff);
				}

				s = FormB(x, i, j, k);
				if (s) {
					sprintf_s(s_buff, "(%d %c %d) %c (%d %c %d)", a, op1, b, op2, c, op3, d);
					g_answers.push_back(s_buff);
				}

				s = FormC(x, i, j, k);
				if (s) {
					sprintf_s(s_buff, "(%d %c (%d %c %d)) %c %d", a, op1, b, op2, c, op3, d);
					g_answers.push_back(s_buff);
				}

				s = FormD(x, i, j, k);
				if (s) {
					sprintf_s(s_buff, "%d %c ((%d %c %d) %c %d)", a, op1, b, op2, c, op3, d);
					g_answers.push_back(s_buff);
				}

				s = FormE(x, i, j, k);
				if (s) {
					sprintf_s(s_buff, "%d %c (%d %c (%d %c %d))", a, op1, b, op2, c, op3, d);
					g_answers.push_back(s_buff);
				}

			}//k
		}//j
	}//i
}


void To24(int x[]) {
	for (int i = 0; i < 4; i++) {
		if (x[i] <= 0 || x[i] >= 14) {
			return;
		}
	}

	std::sort(x, x + 4);

	do {
		Solve4Num(x);

		if (g_answers.size() >= g_max_num) {
			return;
		}

	} while (std::next_permutation(x, x + 4));
}

void Print() {
	for (auto &x : g_answers) {
		std::cout << x << std::endl;
	}
}

int main(int argc, char **argv)
{
	int arr[4] = { 7, 2, 3, 9 };
	To24(arr);
	Print();
	return 0;
}
