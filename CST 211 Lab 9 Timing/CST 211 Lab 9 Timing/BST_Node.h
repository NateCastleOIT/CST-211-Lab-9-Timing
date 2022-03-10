#ifndef BST_NODE_H
#define BST_NODE_H
#include <iostream>
using std::cout;
using std::endl;


template <typename T>
class BSTNode
{
private:
	template<typename T>
	//class BSTree;
	friend class BSTree;// <T>;

	T m_data;
	BSTNode<T>* left;
	BSTNode<T>* right;

	BSTNode();
	BSTNode(T data);
	BSTNode(T data, BSTNode<T>* left, BSTNode<T>* right);
	BSTNode(const BSTNode<T>& rhs);
	BSTNode(BSTNode<T>&& rhs);
	~BSTNode();
	BSTNode<T>& operator = (const BSTNode<T>& rhsNode);
	BSTNode<T>& operator = (BSTNode<T>&& rhsNode);

	T* getNodeData() const;
	void setNodeData(const T newData);
};

//////////////////////////////////////////////////////////////////////////
// DEFINITIONS
//////////////////////////////////////////////////////////////////////////

template<typename T>
BSTNode<T>::BSTNode() : m_data(0), left(nullptr), right(nullptr)
{
}

template<typename T>
BSTNode<T>::BSTNode(T data) : m_data(data), left(nullptr), right(nullptr)
{
}

template<typename T>
BSTNode<T>::BSTNode(T data, BSTNode<T>* left, BSTNode<T>* right) : m_data(data), left(left), right(right)
{
}

template<typename T>
BSTNode<T>::BSTNode(const BSTNode<T>& rhs) : m_data(rhs.m_data), left(rhs.left), right(rhs.right)
{
}

template<typename T>
BSTNode<T>::BSTNode(BSTNode<T>&& rhs) : m_data(rhs.m_data), left(rhs.left), right(rhs.right)
{
	delete rhs.left;
	delete rhs.right;
	rhs.left = nullptr;
	rhs.right = nullptr;
}

template<typename T>
BSTNode<T>::~BSTNode()
{
	left = nullptr;
	right = nullptr;
}

template<typename T>
BSTNode<T>& BSTNode<T>::operator=(const BSTNode<T>& rhsNode)
{
	m_data = rhsNode.m_data;
	left = rhsNode.left;
	right = rhsNode.right;

	return *this;
}

template<typename T>
BSTNode<T>& BSTNode<T>::operator=(BSTNode<T>&& rhsNode)
{
	m_data = rhsNode.m_data;
	left = rhsNode.left;
	right = rhsNode.right;
	rhsNode.left = nullptr;
	rhsNode.right = nullptr;

	return *this;
}

template<typename T>
T* BSTNode<T>::getNodeData() const
{
	return m_data;
}

template<typename T>
void BSTNode<T>::setNodeData(const T newData)
{
	m_data = newData;
}
#endif BST_NODE_H