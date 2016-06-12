#ifndef MYTREENODE_H
#define MYTREENODE_H
#include <string>
#include <iostream>
using namespace std;
class TreeNode {
public:
	TreeNode(string &s = string()) :value(s), count(1), left(new TreeNode()), right(new TreeNode()) {}
	TreeNode(const TreeNode &);
	TreeNode &operator =(const TreeNode &);
	~TreeNode() { if (--count == 0) { delete left;delete right; } }
private:
	string value;
	int count;
	TreeNode *left;
	TreeNode *right;
};

TreeNode::TreeNode(const TreeNode &rhs)
{
	left = rhs.left;
	right = rhs.right;
	count = rhs.count + 1;
	value = rhs.value;
}

TreeNode &TreeNode::operator= (const TreeNode &rhs)
{
	auto ret1 = rhs.left;
	auto ret2 = rhs.right;
	delete left;
	delete right;
	count = rhs.count + 1;
	value = rhs.value;
}
//自己写的类的实现，什么功能都没有
//2016年6月12日21:48:38
//实验室