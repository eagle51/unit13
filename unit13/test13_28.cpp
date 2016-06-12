#ifndef MYBINSTRTREE_H
#define MYBINSTRTREE_H
#include <string>
using namespace std;
class TreeNode {
public:
	TreeNode():value(""),count(1),left(nullptr),right(nullptr) {}
	TreeNode(const string &s = string(), TreeNode *lchild = nullptr, TreeNode *rchild = nullptr) :
		value(s), count(1), left(lchild), right(rchild) {}
	void CopyTree(void);
	TreeNode(const TreeNode &tn);
	int ReleaseTree(void);
	~TreeNode();
private:
	string value;
	int count;
	TreeNode *left;
	TreeNode *right;
};

class BinStrTree {
	BinStrTree() :root(nullptr) {}
	BinStrTree::BinStrTree(TreeNode *t = nullptr) : root(t) {}
	BinStrTree(const BinStrTree &bst);
	~BinStrTree();
private:
	TreeNode *root;
};

BinStrTree::BinStrTree(const BinStrTree &bst) :root(bst.root)
{
	root->CopyTree();
}

void TreeNode::CopyTree(void)
{
	if (left)
		left->CopyTree();
	if (right)
		right->CopyTree();
	count++;
}

TreeNode::TreeNode(const TreeNode &tn) :value(tn.value), count(1), left(tn.left), right(tn.right)
{
	if (left)
		left->CopyTree();
	if (right)
		left->CopyTree();
}

BinStrTree::~BinStrTree()
{
	if (!root->ReleaseTree())
		delete root;
}

int TreeNode::ReleaseTree(void)
{
	if (left) {
		if (!left->CopyTree())	//ϰ�������һ�д�������������
			delete left;
	}
	if (right) {
		if (!right->CopyTree())
			delete right;
	}
	count--;
	return count;
}

TreeNode::~TreeNode()
{
	if (count)
		ReleaseTree();
}
#endif
//�ȿ������ݽṹ�������������2016��6��12��22:48:43
//ʵ����