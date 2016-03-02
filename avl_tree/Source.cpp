#include <iostream>

using namespace std;

struct Node
{
	int key;
	unsigned char height;
	Node *left;
	Node *right;

	Node(int k) :	key(k), 
					left(nullptr), 
					right(nullptr), 
					height(1)
	{}
};

unsigned char height(Node *tmp)
{
	return tmp ? tmp->height : 0;
}

int bfactor(Node *tmp)
{
	return height(tmp->right) - height(tmp->left);
}

void fixHeight(Node *p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}

Node* rotateRight(Node *p)
{
	Node *q = p->left;
	p->left = q->right;
	q->right = p;
	fixHeight(p);
	fixHeight(q);
	
	return q;
}

Node* rotateLeft(Node *q)
{
	Node *p = q->right;
	q->right = p->left;
	p->left = q;
	fixHeight(q);
	fixHeight(p);

	return p;
}

Node* balance(Node *p)
{
	fixHeight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateRight(p->right);

		return rotateLeft(p);
	}

	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)		
			p->left = rotateLeft(p->left);
		return rotateRight(p);	
	}

	return p;
}

Node* insert(Node *p, int& k)
{
	if (!p)
		return new Node(k);
	if (k < p->key)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	return balance(p);
}

int main()
{
	const int n = 14;
	int ms[n] = { 50, 48, 49, 43, 44, 20, 3, 23, 24, 59, 63, 61, 68, 25 };

	Node *tree = nullptr;

	for (int i = 0; i < n; ++i)
	{
		tree = insert(tree, ms[i]);
	}

	return 0;
}