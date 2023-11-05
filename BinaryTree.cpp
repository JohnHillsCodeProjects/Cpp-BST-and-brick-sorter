#include "BinaryTree.h"
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

TreeNode::TreeNode(int new_key, string new_item)
{
	key = new_key;
	item = new_item;
	children[0] = nullptr;
	children[1] = nullptr;
}

BinaryTree::BinaryTree()
{
	root = nullptr;
}

BinaryTree::BinaryTree(BinaryTree& treeToCopyFrom)
{
	//Called from either "BinaryTree tree1(tree2)" or "BinaryTree tree1 = tree2"
	if (treeToCopyFrom.root == nullptr) return;

	deleteTree();
	copyTreeWorker(treeToCopyFrom.root, treeToCopyFrom);
}

BinaryTree& BinaryTree::operator=(BinaryTree& treeToCopyFrom)
{
	//Called from "tree1 = tree2" where tree1 is already defined
	if (treeToCopyFrom.root == nullptr) return;

	deleteTree();
	copyTreeWorker(treeToCopyFrom.root, treeToCopyFrom);
}

void BinaryTree::copyTreeWorker(TreeNode* node, BinaryTree& treeToCopy)
{
	insert(node->key, node->item);
	if (node->children[0] != nullptr) copyTreeWorker(node->children[0], treeToCopy);
	if (node->children[1] != nullptr) copyTreeWorker(node->children[1], treeToCopy);
}

BinaryTree::BinaryTree(BinaryTree&& oldTree)
{
	//Called with "BinaryTree tree1(std::move(tree2))" or "BinaryTree tree1 = std::move(tree2)"
	if (this->root == oldTree.root) return;
	
	deleteTree();
	root = oldTree.getRoot();
	oldTree.root = nullptr;
}

BinaryTree& BinaryTree::operator=(BinaryTree&& oldTree)
{
	//Called with "tree1 = std::move(tree2)" where tree1 is already defined
	if (this->root == oldTree.root) return;

	deleteTree();
	root = oldTree.getRoot();
	oldTree.root = nullptr;
}

TreeNode* BinaryTree::getRoot() { return this->root; }

bool BinaryTree::isTreeEmpty() { return this->root == nullptr; }

string* BinaryTree::lookup(int key)
{
	if (root == nullptr) return nullptr;
	TreeNode* current = root; bool finding = true;
	while (finding) {
		if (current->key == key) return &current->item; 
		else {
			int side = current->key < key; 
			if (current->children[side] != nullptr) { 
				current = current->children[side]; 
			} else { 
				return nullptr; 
			} 
		}
	}
} 

void BinaryTree::insert(int key, string item)
{
	if (root == nullptr) { 
		TreeNode* new_TreeNode = new TreeNode(key, item);
		root = new_TreeNode;
		return;
	}
	TreeNode* current = root;
	bool finding = true;
	while (finding) {
		if (current->key == key) { 
			current->item = item; 
			return;
		} else {
			int side = current->key < key; 
			if (current->children[side] == nullptr) {
				TreeNode* new_TreeNode = new TreeNode(key, item);
				current->children[side] = new_TreeNode;
				return;
			} else {
				current = current->children[side];
			}
		}
	}
}

void BinaryTree::remove(int key)
{
	TreeNode* current = root; bool finding = true;
	TreeNode* node = nullptr; TreeNode* parentNode = nullptr;
	while (finding) {
		if (current->key == key) { 
			node = current; 
			finding = false; 
		} else {
			int side = current->key < key; 
			if (current->children[side] != nullptr) {
				parentNode = current;
				current = current->children[side];
			} else { 
				return;
			}
		}
	}

	bool condL = node->children[0] == nullptr;
	bool condR = node->children[1] == nullptr;
	if (condL && condR) { //If no children
		if (parentNode == nullptr) { 
			root = nullptr; 
		} else if (parentNode->children[0] == node) { 
			parentNode->children[0] = nullptr; 
		} else { 
			parentNode->children[1] = nullptr; 
		}
	} else if (condL || condR) { //If one child
		if (parentNode == nullptr) {
			int side = condL;
			root = node->children[side];
		} else {
			int side1 = parentNode->children[1] == node;
			int side2 = condL; 
			parentNode->children[side1] = node->children[side2];
		}
	} else { //If 2 children
		TreeNode* newNode = node->children[1]; TreeNode* aboveNewNode = nullptr;
		while (newNode->children[0] != nullptr) { 
			//Tries to find the innermost node on the newNode's left
			aboveNewNode = newNode;  //Original parent of newNode
			newNode = newNode->children[0]; 
		}
		if (aboveNewNode != nullptr) {
			aboveNewNode->children[0] = newNode->children[1];
			newNode->children[1] = node->children[1];
		}
		newNode->children[0] = node->children[0];
		if (node != root) {
			int replaceSide = parentNode->children[1] == node;
			parentNode->children[replaceSide] = newNode;
		} else {
			root = newNode;
		}
	}
	delete node;
}

void BinaryTree::displayEntries()
{
	if (root != nullptr) displayEntriesWorker(root);
}

void BinaryTree::displayEntriesWorker(TreeNode* node)
{
	//This is in-order traversal.
	if (node->children[0] != nullptr) displayEntriesWorker(node->children[0]);
	cout << node->key << " " << node->item << endl;
	if (node->children[0] != nullptr) displayEntriesWorker(node->children[1]);
}

void BinaryTree::displayTree()
{
	if (root != nullptr) displayTreeWorker(root, 0);
}

void BinaryTree::displayTreeWorker(TreeNode* node, int level)
{
	//This is in-order traversal
	if (node->children[0] != nullptr) displayTreeWorker(node->children[0], level + 1);
	int i; for (i = 0; i < level; i++) { cout << "  "; }
	cout << node->key << " " << node->item << endl;
	if (node->children[1] != nullptr) displayTreeWorker(node->children[1], level + 1);
}

void BinaryTree::deleteTree()
{
	if (root != nullptr) deleteTreeWorker(root);
	root = nullptr;
}

void BinaryTree::deleteTreeWorker(TreeNode* node)
{
	//This is post-order traversal
	if (node->children[0] != nullptr) deleteTreeWorker(node->children[0]);
	if (node->children[1] != nullptr) deleteTreeWorker(node->children[1]);
	//cout << "~~Deleting node " << node->key << endl;
	delete node;
}

void BinaryTree::rotateLeft(TreeNode* node, TreeNode* parent)
{
	TreeNode* newRoot = node->children[1];       //Constant

	assert(isTreeEmpty() || newRoot == nullptr); //Constant

	if (parent == nullptr) {                     //Constant
		root = newRoot;                          //Constant
	} else {
		int side = parent->key < node->key;      //Constant
		parent->children[side] = newRoot;        //Constant
	}
	node->children[1] = newRoot->children[0];    //Constant
	newRoot->children[0] = node;                 //Constant
}

void BinaryTree::rotateRight(TreeNode* node, TreeNode* parent)
{
	TreeNode* newRoot = node->children[0];       //Constant

	assert(isTreeEmpty() || newRoot == nullptr); //Constant

	if (parent == nullptr) {                     //Constant
		root = newRoot;                          //Constant
	} else {
		int side = parent->key < node->key;      //Constant
		parent->children[side] = newRoot;        //Constant
	}
	node->children[0] = newRoot->children[1];    //Constant
	newRoot->children[1] = node;                 //Constant
}