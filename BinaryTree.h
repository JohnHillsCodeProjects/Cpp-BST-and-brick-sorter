#pragma once
#include <string>

using namespace std;

struct TreeNode
{
	int key;
	string item;
	TreeNode* children[2];
	TreeNode(int, string);
};

class BinaryTree
{
private:
	TreeNode* root = nullptr;
	void displayEntriesWorker(TreeNode*);
	void displayTreeWorker(TreeNode*, int);
	void deleteTreeWorker(TreeNode*);
	void copyTreeWorker(TreeNode*, BinaryTree&);
	void rotateLeft(TreeNode*, TreeNode*);
	void rotateRight(TreeNode*, TreeNode*);
public:
	BinaryTree();
	BinaryTree(BinaryTree&);
	BinaryTree& operator=(BinaryTree&);
	BinaryTree(BinaryTree&&);
	BinaryTree& operator=(BinaryTree&&);
	string* lookup(int);
	bool isTreeEmpty();
	void insert(int, string);
	void displayEntries();
	void displayTree();
	void remove(int);
	TreeNode* getRoot();
	void deleteTree();
};