#ifndef NODE_H
#define NODE_H
#include <iostream>
using std::cout;
using std::endl;


template <typename T>
class Node
{
private:
	template<typename T>
	//class List;
	friend class List;// <T>;

	T m_data;
	Node<T>* prev;
	Node<T>* next;

	Node();
	Node(T data, Node<T>* next, Node<T>* prev);
	Node(const Node<T>& rhs);
	Node(Node<T>&& rhs);
	~Node();
	Node<T>& operator = (const Node<T>& rhsNode);
	Node<T>& operator = (Node<T>&& rhsNode);

	T* getNodeData() const;
	void setNodeData(const T newData);
};

//////////////////////////////////////////////////////////////////////////
// DEFINITIONS
//////////////////////////////////////////////////////////////////////////

template<typename T>
Node<T>::Node() : m_data(0), next(nullptr), prev(nullptr)
{
}

template<typename T>
Node<T>::Node(T data, Node<T>* next, Node<T>* prev) : m_data(data), next(next), prev(prev)
{
}

template<typename T>
Node<T>::Node(const Node<T>& rhs) : m_data(rhs.m_data), next(rhs.next), prev(rhs.prev)
{
}

template<typename T>
Node<T>::Node(Node<T>&& rhs) : m_data(rhs.m_data), next(rhs.next), prev(rhs.prev)
{
	delete rhs.prev;
	delete rhs.next;
	rhs.next = nullptr;
	rhs.prev = nullptr;
}

template<typename T>
Node<T>::~Node()
{
	next = nullptr;
	prev = nullptr;
}

template<typename T>
Node<T>& Node<T>::operator=(const Node<T>& rhsNode)
{
	m_data = rhsNode.m_data;
	next = rhsNode.next;
	prev = rhsNode.prev;

	return *this;
}

template<typename T>
Node<T>& Node<T>::operator=(Node<T>&& rhsNode)
{
	m_data = rhsNode.m_data;
	next = rhsNode.next;
	prev = rhsNode.prev;
	rhsNode.next = nullptr;
	rhsNode.prev = nullptr;

	return *this;
}

template<typename T>
T* Node<T>::getNodeData() const
{
	return m_data;
}

template<typename T>
void Node<T>::setNodeData(const T newData)
{
	m_data = newData;
}
#endif NODE_H