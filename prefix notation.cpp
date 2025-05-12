#include <iostream>
#include <sstream>
using namespace std;

/* Node �ؿ� NumberNode�� Operation, Operation �ؿ� ���ϱ�, ����, ���ϱ� */

struct Node {
	virtual int result() const = 0;
};

struct NumberNode : Node {
	int value;
	NumberNode(int v) : value(v) {}
	virtual int result() const override {
		return value;
	}
};

struct Operation : Node {
	Node* left = nullptr;
	Node* right = nullptr;
};

struct Addition : Operation {
	virtual int result() const override {
		return left->result() + right->result();
	}
};

struct Subtration : Operation {
	virtual int result() const override {
		return left->result() - right->result();
	}
};

struct Multiplication : Operation {
	virtual int result() const override {
		return left->result() * right->result();
	}
};

/* �Է¹��� ���� �������� ���������� �Ǵ��ϴ� �Լ� : IsNumber, getToken */

bool isNumber(const string& s) {
	return s[0] >= '0' && s[0] <= '9';
}

string getToken(istream& is) {
	string s;
	is >> s;
	return s;
}



Node* buildTree(istream& is) {
	auto s = getToken(is);

	if (isNumber(s)) {
		return new NumberNode(stoi(s));
	}

	Operation* op = nullptr;

	if (s[0] == '+') {
		op = new Addition();
	}

	else if (s[0] == '-') {
		op = new Subtration();
	}

	else if (s[0] == '*') {
		op = new Multiplication();
	}

	if (op == nullptr) {
		cout << "Wrong token";
	}

	op->left = buildTree(is);
	op->right = buildTree(is);

	return op;

}

int main(void) {

	Node* root = buildTree(cin);
	
	cout << root->result() << endl;

	return 0;
	
}