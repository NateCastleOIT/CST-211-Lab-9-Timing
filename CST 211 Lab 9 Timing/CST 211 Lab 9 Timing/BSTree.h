#ifndef BSTREE_H
#define BSTREE_H
#include "BST_Node.h"
#include "Exception.h"
#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;

template <typename T>
class BSTree
{
private:
	BSTNode<T>* root;

	void Insert(T data, BSTNode<T>* node);
	BSTNode<T>* Delete(T data, BSTNode<T>* node);
	BSTNode<T>* Purge(BSTNode<T>* node);	// takes in root for recursion
	BSTNode<T>* findMin(BSTNode<T>* node);
	BSTNode<T>* findMax(BSTNode<T>* node);

	void InOrderTraversal(BSTNode<T>* root/*, void (*visit) (T data)*/);	// Function Pointer
	void PreOrderTraversal(BSTNode<T>* root/*, void (*visit) (T data)*/);
	void PostOrderTraversal(BSTNode<T>* root/*, void (*visit) (T data)*/);
	void BreadthFirstTraversal(BSTNode<T>* root/*, void (*visit) (T data)*/);


public:
	BSTree() : root(nullptr) {}
	BSTree(BSTree<T>& bstree) : root(CopyTree(bstree.root)) {}
	BSTree(BSTree<T>&& bstree) noexcept;
	~BSTree();
	BSTree<T>& operator = (BSTree<T>& rhs);
	BSTree<T>& operator = (BSTree<T>&& rhs) noexcept;

	void insert(T data) { Insert(data, root); }
	void delete_(T data) { Delete(data, root); }
	int getHeight(BSTNode<T>* node) const;
	void purgeBST() { Purge(root); }
	BSTNode<T>* CopyTree(BSTNode<T>* node);

	void inOrder(/*void (*funcptr)(T data)*/) { InOrderTraversal(root/*, funcptr*/); }
	void preOrder() { PreOrderTraversal(root); }
	void postOrder() { PostOrderTraversal(root); }
	void breadthFirst() { BreadthFirstTraversal(root); }

	bool isEmpty() const;
	void PrintForwards(T data) const;
	//BSTNode<T>* findNode(T oldData);				// searchs bstree till a root's data matches the searched data
	void currentLevel(BSTNode<T>* root, int data);
	BSTNode<T>* getRoot() const { return root; }
	T getRootData() const { return root->m_data; }
	BSTNode<T>* getLeft(BSTNode<T>* node) const { return node->left; }
	BSTNode<T>* getRight(BSTNode<T>* node) const { return node->right; }
	T getData(BSTNode<T>* node) const { return node->m_data; }
};

//////////////////////////////////////////////////////////////////////////
// DEFINITIONS
//////////////////////////////////////////////////////////////////////////

template<typename T>
BSTree<T>::BSTree(BSTree<T>&& bstree) noexcept
{
	root = bstree.root;		// we can just point to the existing data

	bstree.root = nullptr;	// and delete the other bstree's pointers
}

template<typename T>
BSTree<T>::~BSTree()
{
	root = Purge(root);
}

template<typename T>
BSTree<T>& BSTree<T>::operator=(BSTree<T>& rhs)
{
	if (!rhs.root || this == &rhs)	// if rhs root is not null or if self assignment
		return this;
	root = CopyTree(rhs.root);
	return root;
}

template<typename T>
BSTree<T>& BSTree<T>::operator=(BSTree<T>&& rhs) noexcept
{
	if (this != &rhs) {
		root = rhs.root;

		rhs.root = nullptr;
	}
	return *this;
}

template<typename T>
void BSTree<T>::currentLevel(BSTNode<T>* root, int data)
{
	if (root == nullptr)
		return;
	if (data == 1)
		cout << root->m_data << "\t";
	else if (data > 1) {
		currentLevel(root->left, data - 1);
		currentLevel(root->right, data - 1);
	}
}

template<typename T>
bool BSTree<T>::isEmpty() const
{
	return (root == nullptr);
}

template<typename T>
void BSTree<T>::Insert(T data, BSTNode<T>* node)
{
	if (!node)
	{
		node = new BSTNode<T>(data);	// Tree is empty, make root a new root
		root = node;
	}
	else
	{
		if (data < node->m_data)
		{	// New data is less than current root data
			if (!node->left)
			{		// if left child is empty
				BSTNode<T>* temp = new BSTNode<T>(data);
				node->left = temp;	// set left child root to new root with new data
			}
			else
				Insert(data, node->left);	// otherwise keep going down the left branch
		}
		else if (data > node->m_data)
		{	// New data is more than the current root data
			if (!node->right)
			{	// if the right child root is empty
				BSTNode<T>* temp = new BSTNode<T>(data);
				node->right = temp;	// make the right child root a new root with the new data
			}
			else
				Insert(data, node->right);	// otherwise keep going down the right branch
		}
	}
}

template<typename T>
BSTNode<T>* BSTree<T>::Delete(T data, BSTNode<T>* node)
{
	BSTNode<T>* temp;
	try {
		if (isEmpty())
			throw Exception("Tree is empty.");
	}
	catch (Exception& e) { cout << e.getMessage(); }

	if (data < node->m_data)	// if the searched data is less than the left child, re-search at that child root
		node->left = Delete(data, node->left);
	else if (data > node->m_data)	// if the searched data is more than the right child, re-search at that child root
		node->right = Delete(data, node->right);
	else
	{
		// No child
		if (node->right == nullptr && node->left == nullptr)
		{
			node = nullptr;
			delete node;
		}
		// One Child
		else if (node->right == nullptr)
		{
			BSTNode<T>* temp = node;
			node = node->left;
			temp = nullptr;
			delete temp;
		}
		else if (node->left == nullptr)
		{
			BSTNode<T>* temp = node;
			node = node->right;
			temp = nullptr;
			delete temp;
		}
		// Two Child
		else
		{
			BSTNode<T>* temp = findMax(node->left);
			node->m_data = temp->m_data;
			node->left = Delete(temp->m_data, node->left);
		}
	}
	return node;
}

template<typename T>
BSTNode<T>* BSTree<T>::Purge(BSTNode<T>* node)
{
	try {
		if (isEmpty())
			throw Exception("\nPurging empty Tree...");
	}
	catch (Exception& e)
	{
		cout << e.getMessage();
		return nullptr;
	}

	while (root->left != nullptr)
	{
		BSTNode<T>* temp = findMin(node);
		delete_(temp->m_data);
	}
	while (root->right != nullptr)
	{
		BSTNode<T>* temp = findMax(node);
		delete_(temp->m_data);

	}

	root = nullptr;
	delete root;

	return nullptr;
}

template<typename T>
BSTNode<T>* BSTree<T>::findMin(BSTNode<T>* node)
{
	if (node == nullptr)	// if the root is empty return nullptr
		return nullptr;
	else if (node->left == nullptr)	// if the left child is empty return this root
		return node;
	else
		return findMin(node->left);	// otherwise, continue looking for the minimum down the left branch
}

template<typename T>
BSTNode<T>* BSTree<T>::findMax(BSTNode<T>* node)
{
	if (node == nullptr)	// if the root is empty return nullptr
		return nullptr;
	else if (node->right == nullptr)	// if the right child is empty return this root
		return node;
	else
		return findMin(node->right);	// otherwise, continue looking for the maximum down the right branch
}

template<typename T>
int BSTree<T>::getHeight(BSTNode<T>* node) const
{
	if (!node)
		return 0;
	return 1 + std::max(getHeight(node->left), getHeight(node->right));
}

template<typename T>
BSTNode<T>* BSTree<T>::CopyTree(BSTNode<T>* node)
{
	if (!node)
		return nullptr;
	BSTNode<T>* newNode = new BSTNode<T>(node->m_data);
	newNode->left = CopyTree(node->left);
	newNode->right = CopyTree(node->right);
	return newNode;
}

template<typename T>
void BSTree<T>::InOrderTraversal(BSTNode<T>* root/*, void (*visit)(T data)*/)
{

	try {
		if (isEmpty())
			throw Exception("\nCan't Print empty Tree.");
	}
	catch (Exception& e)
	{
		cout << e.getMessage();
		return;
	}
	if (!root)
		return;
	InOrderTraversal(root->left);
	//visit(root->m_data);
	cout << root->m_data << endl;
	InOrderTraversal(root->right);
}

template<typename T>
void BSTree<T>::PreOrderTraversal(BSTNode<T>* root/*, void(*visit)(T data)*/)
{
	try {
		if (isEmpty())
			throw Exception("\nCan't Print empty Tree.");
	}
	catch (Exception& e)
	{
		cout << e.getMessage();
		return;
	}
	//visit(data);
	if (!root)
		return;
	cout << root->m_data << endl;
	PreOrderTraversal(root->left);
	PreOrderTraversal(root->right);
}

template<typename T>
void BSTree<T>::PostOrderTraversal(BSTNode<T>* root/*, void(*visit)(T data)*/)
{
	try {
		if (isEmpty())
			throw Exception("\nCan't Print empty Tree.");
	}
	catch (Exception& e)
	{
		cout << e.getMessage();
		return;
	}
	PostOrderTraversal(root->left);
	PostOrderTraversal(root->right);
	cout << root->m_data << endl;
	//visit(data);
}

template<typename T>
void BSTree<T>::BreadthFirstTraversal(BSTNode<T>* root/*, void(*visit)(T data)*/)
{

	try {
		if (isEmpty())
			throw Exception("\nCan't Print empty Tree.");
	}
	catch (Exception& e)
	{
		cout << e.getMessage();
		return;
	}
	for (int i = 1; i <= getHeight(root); i++) {
		currentLevel(root, i);
		cout << endl;
	}
}

template<typename T>
void BSTree<T>::PrintForwards(T data) const
{
	cout << data << endl;
}
#endif BSTREE_H