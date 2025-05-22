#include <iostream>
#include <sstream>
using namespace std;

/* Node ���� NumberNode(���� ���), Operation(������ ���), Operation ���� ����, ����, ���� ������ */

struct Node {
	Node* parent;
	virtual int result() const = 0;
	virtual ostream& print(ostream& os) const = 0;
	Node(Node* _parent = nullptr) : parent(_parent) {}
}; /* ��� Node instance���� result �Լ��� ���� ������ ����� ��ȯ�ϵ��� �� */

struct NumberNode : Node {
	int value;
	NumberNode(int v, Node* _parent) : value(v), Node(_parent) {}
	virtual int result() const override {
		return value;
	}
	virtual ostream& print(ostream& os) const override {
		os << value;
	}
}; /* value�� constructor�� ���� assign�ϰ� result �Լ� ��� �� value ��ȯ*/

struct Operation : Node {
	Node* left = nullptr;
	Node* right = nullptr;
	Operation(Node* _parent) : Node(_parent) {}
}; /* �����ڴ� ������ �� ���� �ڽ� ��带 ������ �ϹǷ�, ���� Operation �� ���� ��� Operation���� �� �Ӽ��� �������� �� */

struct Addition : Operation {
	virtual int result() const override {
		return left->result() + right->result();
	}
	virtual ostream& print(ostream& os) const override {
		
	}
	Addition(Node* _parent) : Operation(_parent) {}
}; /* ���� */

struct Subtraction : Operation {
	virtual int result() const override {
		return left->result() - right->result();
	}
	virtual ostream& print(ostream& os) const override {
		if (dynamic_cast<Multiplication*>(parent) != nullptr) {
			os << "("; left->print(os); os << "-"; right->print(os); os << ")";
		}
		else
			left->print(os); os << "-"; right->print(os);
	}
	Subtraction(Node* _parent) : Operation(_parent) {}
}; /* ���� */

struct Multiplication : Operation {
	virtual int result() const override {
		return left->result() * right->result();
	}
	virtual ostream& print(ostream& os) const override{
		left->print(os); os << "*"; right->print(os);
	}
	Multiplication(Node* _parent) : Operation(_parent) {}
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
Node* buildTree(istream& is, Node* _parent) {
	auto s = getToken(is); /* getToken()�� ����Ͽ� ���ڿ��� ���� �ϳ��� ������� �Է� �ޱ� */

	if (isNumber(s)) {
		return new NumberNode(stoi(s), _parent);
	} /* �Է� ���� ���ڰ� 0���� 9 ������ ���� �����̸� ������ convert�Ͽ� NumberNode�� ��ȯ*/

	Operation* op = nullptr;

	if (s[0] == '+') {
		op = new Addition(_parent);
	} /* �Է� ���� ���ڰ� +�̸� ���� ��� ����� op�� assign */

	else if (s[0] == '-') {
		op = new Subtraction(_parent);
	} /* �Է� ���� ���ڰ� -�̸� ���� ��� ����� op�� assign */

	else if (s[0] == '*') {
		op = new Multiplication(_parent);
	} /* �Է� ���� ���ڰ� *�̸� ���� ��� ����� op�� assign */

	if (op == nullptr) {
		cout << "Wrong token";
	} /* �̿��� �����ڳ� ���ڰ� �� ��� �߸��� �Է��̶�� ��� */

	op->left = buildTree(is, op);
	op->right = buildTree(is, op); /* ������ ����� ��� op�� nullptr�� �ƴϹǷ�, recursion�� ���� �� ���� �ڽ� ��� ������ֱ�*/

	return op; /* ���������δ� root ��尡 main �Լ��� ��ȯ�� */

}

int main(void) {

	Node* root = buildTree(cin, root); /* �Է��� ���ڿ��� pre-order traversal��� tree ���� �� root ��� ���� */

	cout << root->result() << endl; /* root ������ leaf ������ traverse�ϸ� result �����. ���������δ� root ��忡 ��� ��� ����� ���̰� ��. */

	return 0;

}