#ifndef LIST_H
#define LIST_H
#include "Node.h"
#include "Exception.h"
#include <iostream>
using std::cout;
using std::endl;

template <typename T>
class List
{
private:
	int m_length;

	Node<T>* head;	// must be "Node<T> *head;", not "Node<T>* head;", are these not equivalent?

	Node<T>* tail;

public:
	List();
	List(List<T>& list);
	List(List<T>&& list);
	~List();
	List<T>& operator = (List<T>& rhsList);
	List<T>& operator = (List<T>&& rhslist);

	int getListLength() const;
	Node<T>* findNode(T oldData);				// searchs list till a node's data matches the searched data

	bool isEmpty() const;
	const T& First() const;						// returns first node's data
	const T& Last() const;						// returns last node's data
	void Prepend(T newData);					// Add Node to front of List
	void Append(T newData);						// Add Node to end of List
	void Purge();								// Remove all items from List
	void Extract(T oldData);					// Remove a single item from List
	void InsertAfter(T newData, T oldData);
	void InsertBefore(T newData, T oldData);

	Node<T>* getHead() const;	// For testing only
	Node<T>* getTail() const;
	void PrintForwards() const;
	void PrintBackwards() const;

	// Functions for Lab3 Stacks
	void removeTop();
};

//////////////////////////////////////////////////////////////////////////
// DEFINITIONS
//////////////////////////////////////////////////////////////////////////

template<typename T>
List<T>::List() : head(nullptr), tail(nullptr), m_length(0)
{
}

template<typename T>
List<T>::List(List<T>& list)
{
	if (list.head == nullptr) {				// if list is empty, do the same as the default ctr
		head = nullptr;
		tail = nullptr;
		m_length = 0;
	}
	else {
		Node<T>* newNode = list.head;
		while (newNode) {
			Append(newNode->m_data); // append until at the end of the copy list.
			newNode = newNode->next;
		}
	}
}

template<typename T>
List<T>::List(List<T>&& list)
{
	head = list.head;		// we can just point to the existing data
	tail = list.tail;

	list.head = nullptr;	// and delete the other list's pointers
	list.tail = nullptr;
}

template<typename T>
List<T>::~List()
{
	Node<T>* temp;
	tail = nullptr;
	while (head != nullptr) {
		temp = head;
		head = head->next;
		delete temp;
	}
	head = nullptr;
}

template<typename T>
List<T>& List<T>::operator=(List<T>& rhsList)
{
	if (this != &rhsList) {			// if list is empty, do the same as the default ctr
		Node<T>* newNode = rhsList.head;
		while (newNode) {
			Append(newNode->m_data); // append until at the end of the copy list.
			newNode = newNode->next;
		}
	}
	return *this;
}

template<typename T>
List<T>& List<T>::operator=(List<T>&& rhsList)
{
	if (this != &rhsList) {			// if list is empty, do the same as the default ctr
		head = rhsList.head;
		tail = rhsList.tail;

		rhsList.head = nullptr;
		rhsList.tail = nullptr;
	}
	return *this;
}

template<typename T>
int List<T>::getListLength() const
{
	return m_length;
}

template<typename T>
Node<T>* List<T>::findNode(T oldData) {
	Node<T>* temp = head;		// start from head
	bool dataMatch = false;		// haven't found data

	while (temp && !dataMatch) {		// loop until temp == nullptr and we haven't matched data
		if (temp->m_data == oldData)	// if data matches
			dataMatch = true;			// set match to true
		else
			temp = temp->next;			// otherwise step to next node
	}
	return temp;
}

template<typename T>
bool List<T>::isEmpty() const
{
	if (head == nullptr)
		return true;
	else
		return false;
}

template<typename T>
const T& List<T>::First() const
{
	if (isEmpty())
		throw Exception("ERROR: List is empty.");
	return head->m_data;
}

template<typename T>
const T& List<T>::Last() const
{
	if (isEmpty())
		throw Exception("ERROR: List is empty.");
	return tail->m_data;
}

template<typename T>
void List<T>::Prepend(T newData) // add to the front of the list
{
	if (head == nullptr && tail == nullptr) {			// if list is empty...
		head = new Node<T>(newData, nullptr, nullptr);	// make head a new node
		tail = head;									// make tail the same as head
	}
	else if (head && head == tail) {					// if there is one node...
		head = new Node<T>(newData, tail, nullptr);		// make head a new node with next->tail
		head->next = tail;								// set head next to tail
		tail->prev = head;								// set tail prev to head
	}
	else {
		Node<T>* newNode = new Node<T>(newData, head, nullptr);	// make new temp node with next = head
		head->prev = newNode;									// point head's prev to the new node
		head = newNode;											// make the new node the head
	}
}

template<typename T>
void List<T>::Append(T newData) {
	if (head == nullptr && tail == nullptr) {
		head = new Node<T>(newData, nullptr, nullptr);
		tail = head;
	}
	else if (head && head == tail) {
		tail = new Node<T>(newData, nullptr, head);
		head->next = tail;
		tail->prev = head;
	}
	else {
		Node<T>* newNode = new Node<T>(newData, nullptr, tail);
		tail->next = newNode;
		tail = newNode;
	}
}

template<typename T>
void List<T>::Purge()
{
	Node<T>* temp;
	tail = nullptr;

	while (head != nullptr) {		// traverse list till the next node is nullptr
		temp = head;
		head = head->next;
		delete temp;			// delete the last node object
	}
	head = nullptr;
	m_length = 0;
	return;
}

template<typename T>
void List<T>::Extract(T oldData)
{
	Node<T>* deleteNode = findNode(oldData); // temp node with the node matching the given data

	if (!deleteNode)
		throw Exception("ERROR: No node with data found.");

	if (head == tail) { // if there's only one node
		head = nullptr;
		tail = nullptr;
	}
	else if (deleteNode == head) {	// if we want to delete the head
		head = head->next;			// make head the second node in the list
		head->prev = nullptr;		// delete the first node
	}
	else if (deleteNode == tail) {	// if we want to delete the tail
		tail = tail->prev;			// make tail the second to last in the list
		tail->next = nullptr;		// delete last node.
	}
	else {
		(deleteNode->prev)->next = deleteNode->next;	// make the node before deleteNode point to the node after deleteNode
		(deleteNode->next)->prev = deleteNode->prev;	// make the node after deleteNode point back at the node before deleteNode to bridge gap
	}
}

template<typename T>
void List<T>::InsertAfter(T newData, T oldData)
{
	Node<T>* lookNode = findNode(oldData); // temp node with the node matching the given data

	if (!lookNode)
		throw Exception("ERROR: No node with data found.");

	if (lookNode == tail)
		Append(newData);
	else {
		Node<T>* temp = new Node<T>(newData, lookNode->next, lookNode);
		(temp->next)->prev = temp;
		lookNode->next = temp;
	}
}

template<typename T>
void List<T>::InsertBefore(T newData, T oldData)
{
	Node<T>* lookNode = findNode(oldData); // temp node with the node matching the given data

	if (!lookNode)
		throw Exception("ERROR: No node with data found.");	// throw if node not found

	if (lookNode == head) {		// just prepend if we want to insert before the head
		Prepend(newData);
	}
	else {
		Node<T>* temp = new Node<T>(newData, lookNode, lookNode->prev);	// make a new node that has a next of the found node and a previous of the found node prev
		(temp->prev)->next = temp;	// set the node behind it to point at it
		lookNode->prev = temp;		// set the found node's prev to the new node
	}
}

template<typename T>
Node<T>* List<T>::getHead() const
{
	return head;
}

template<typename T>
Node<T>* List<T>::getTail() const
{
	return tail;
}

template<typename T>
void List<T>::PrintForwards() const
{
	int i = 0;
	cout << "Printing List front to back..." << endl;
	while (head->next != nullptr) {
		cout << "Node " << i << ":" << head->m_data << endl;
	}
}

template<typename T>
void List<T>::PrintBackwards() const
{
	int i = m_length - 1;											// temp var to label nodes
	cout << "Printing List back to front..." << endl;
	while (head->next != nullptr) {								// traverse till at the end of the list
		head = head->next;
	}

	while (head->prev != nullptr) {								// traverse back to the front of the list
		cout << "Node " << i << ":" << head->m_data << endl;
		head = head->prev;										// go from the last node to the second to last node till at the front again
		i--;													// adjust node # for print
	}
}

template<typename T>
inline void List<T>::removeTop()
{
	if (head == tail) { // if there's only one node
		head = nullptr;
		tail = nullptr;
	}
	else {							// if we want to delete the head
		head = head->next;			// make head the second node in the list
		head->prev = nullptr;		// delete the first node
	}
}
#endif LIST_H