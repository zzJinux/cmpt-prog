#include <cstdio>
using namespace std;

struct AVLTree {
	struct Node {
		int key;
		AVLTree *left, *right;
	};

	Node *root = nullptr;
	int height = 0;

	void insert(int key, int level = 1) {
		if(root == nullptr) {
			root = new Node {key, new AVLTree(), new AVLTree() };
			height = 1;
			return;
		}

		if(key < root->key) {
			root->left->insert(key);
		}
		else if(key > root->key) {
			root->right->insert(key);
		}
		else { /* TODO: duplicate key handling */ }

		int balance = getBalance(true);
		rebalance(balance);
	}
	
	void rebalance(int balance) {
		if(balance < -1) {
			if(root->left->getBalance() > 0) {
				root->left->lrotate();
			}
			rrotate();
		}
		else if(balance > 1) {
			if(root->right->getBalance() < 0) {
				root->right->rrotate();
			}
			lrotate();
		}
	}

	void lrotate() {
		auto A = root->right->root; // new-root
		*root->right = *A->left;
		A->left->root = root;

		root = A;
		root->left->getBalance(true);
		getBalance(true);
	}

	void rrotate() {
		auto A = root->left->root; // new-root
		*root->left = *A->right;
		A->right->root = root;

		root = A;
		root->right->getBalance(true);
		getBalance(true);
	}

	int getBalance(bool heightUpdate = false) {
		int lh, rh;
		lh = root->left->height;
		rh = root->right->height;
		if(heightUpdate) {
			height = 1 + (lh > rh ? lh : rh);
		}
		return rh - lh;
	}

	void display() {
		if(root == nullptr) return;
		putchar('(');
		root->left->display();
		printf("%d", root->key);
		root->right->display();
		putchar(')');
	}

	~AVLTree() {
		if(root != nullptr) {
			delete root->left;
			delete root->right;
			delete root;
		}
	}
};

int main() {
	auto avlTree = new AVLTree();
	for(int k; scanf("%d", &k) == 1;) {
		avlTree->insert(k, 0);
	}
	avlTree->display();
}
