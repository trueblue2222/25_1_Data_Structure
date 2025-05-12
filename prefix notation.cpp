#include <iostream>
#include <sstream>
using namespace std;

/* Node ���� NumberNode(���� ���), Operation(������ ���), Operation ���� ����, ����, ���� ������ */

struct Node {
	virtual int result() const = 0;
}; /* ��� Node instance���� result �Լ��� ���� ������ ����� ��ȯ�ϵ��� �� */

struct NumberNode : Node {
	int value;
	NumberNode(int v) : value(v) {}
	virtual int result() const override {
		return value;
	}
}; /* value�� constructor�� ���� assign�ϰ� result �Լ� ��� �� value ��ȯ*/

struct Operation : Node {
	Node* left = nullptr;
	Node* right = nullptr;
}; /* �����ڴ� ������ �� ���� �ڽ� ��带 ������ �ϹǷ�, ���� Operation �� ���� ��� Operation���� �� �Ӽ��� �������� �� */

struct Addition : Operation {
	virtual int result() const override {
		return left->result() + right->result();
	}
}; /* ���� */

struct Subtration : Operation {
	virtual int result() const override {
		return left->result() - right->result();
	}
}; /* ���� */

struct Multiplication : Operation {
	virtual int result() const override {
		return left->result() * right->result();
	}
}; /* ���� */

bool isNumber(const string& s) {
	return s[0] >= '0' && s[0] <= '9';
} /* ���� ���·� 0���� 9 ������ �������� �ƴ��� �Ǵ�. ���� s�� stoi �Լ��� ���� numberNode�� ������ ���� */

string getToken(istream& is) {
	string s;
	is >> s;
	return s;
} /* inputstream ��ü�� �Ű������� �޾� s���� prefix notation �Է� �� ��ȯ. recursion �������� ���ڰ� �ϳ��� ������� ��ȯ�Ǹ� ��� ������� */


/* Tree ���� */
Node* buildTree(istream& is) {
	auto s = getToken(is); /* getToken()�� ����Ͽ� ���ڿ��� ���� �ϳ��� ������� �Է� �ޱ� */

	if (isNumber(s)) {
		return new NumberNode(stoi(s));
	} /* �Է� ���� ���ڰ� 0���� 9 ������ ���� �����̸� ������ convert�Ͽ� NumberNode�� ��ȯ*/

	Operation* op = nullptr; 

	if (s[0] == '+') {
		op = new Addition();
	} /* �Է� ���� ���ڰ� +�̸� ���� ��� ����� op�� assign */

	else if (s[0] == '-') {
		op = new Subtration();
	} /* �Է� ���� ���ڰ� -�̸� ���� ��� ����� op�� assign */

	else if (s[0] == '*') {
		op = new Multiplication();
	} /* �Է� ���� ���ڰ� *�̸� ���� ��� ����� op�� assign */

	if (op == nullptr) {
		cout << "Wrong token";
	} /* �̿��� �����ڳ� ���ڰ� �� ��� �߸��� �Է��̶�� ��� */

	op->left = buildTree(is); 
	op->right = buildTree(is); /* ������ ����� ��� op�� nullptr�� �ƴϹǷ�, recursion�� ���� �� ���� �ڽ� ��� ������ֱ�*/

	return op; /* ���������δ� root ��尡 main �Լ��� ��ȯ�� */

}

int main(void) {

	Node* root = buildTree(cin); /* �Է��� ���ڿ��� pre-order traversal��� tree ���� �� root ��� ���� */
	
	cout << root->result() << endl; /* root ������ leaf ������ traverse�ϸ� result �����. ���������δ� root ��忡 ��� ��� ����� ���̰� ��. */

	return 0;
	
}