#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>
#include "Exception.h"
using std::cout;
using std::endl;

template <typename T>
class Array {
private:
	T* m_array;
	int m_start_index;
	int m_length;

public:
	Array();
	Array(int length, int start_index = 0);
	Array(const Array<T>& copy);
	Array(Array<T>&& copy);
	Array& operator = (const Array<T>& rhs);
	Array& operator = (Array<T>&& rhs);
	~Array();
	T& operator [](int index);
	int getStartIndex() const;
	int getLength() const;

	void setStartIndex(const int start_index);
	void setLength(const int length);
};


template<typename T>
Array<T>::Array() : m_array(nullptr), m_length(0), m_start_index(0)
{
}

template<typename T>
Array<T>::Array(int length, int start_index) : m_array(nullptr), m_length(0), m_start_index(start_index)
{
	if (length < 0)
		throw Exception("Invalid negative length passed."); // check for valid length

	m_length = length;			// set length if valid
	m_array = new T[m_length];	// create new array of <T> with new length
}

template<typename T>
Array<T>::Array(const Array<T>& copy) : m_array(nullptr), m_start_index(copy.m_start_index), m_length(copy.m_length)
{
	if (copy.m_length >= 0) {									// make sure copy length is valid
		m_array = new T[copy.m_length];							// make new array of new length if valids

		if (copy.m_array != nullptr)							// make sure copy isn't empty
			for (int i = 0; i < m_length; i++)
				m_array[i] = copy.m_array[i];					// copy copy into new array
	}
	else {
		throw(Exception("Copy's length is invalid."));
	}

	//m_array = copy.m_array;
	////*this = Array(copy.m_length, copy.m_start_index);
	//m_length = copy.m_length;
	//m_start_index = copy.m_start_index;

	//for (int i = m_start_index; i < m_length; i++) {
	//	this->m_array[i] = copy.m_array[i];
	//}
}

template<typename T>
Array<T>::Array(Array<T>&& copy) : m_array(copy.m_array), m_length(copy.m_length), m_start_index(copy.m_start_index) //move copy
{

	copy.m_array = nullptr;

	//m_array = copy.m_array;
	//m_length = copy.m_length;
	//m_start_index = copy.m_start_index;

	//for (int i = this.m_start_index; i < this.m_length; i++) {
	//	this[i] = copy[i];
	//}

	//delete[] copy;
	//copy.m_array = nullptr;
}

template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& rhs)
{
	if (this != &rhs) {										// checks if this == &rhs
		delete[] m_array;									// deletes current array
		m_array = nullptr;
		m_length = rhs.m_length;
		m_start_index = rhs.m_start_index;						// makes a new array with new values
		if (rhs.m_array != nullptr) {							// make sure that rhs isn't empty
			m_array = new T[rhs.m_length];
			for (int i = m_start_index; i < m_length; i++) {	// replaces new empty array with the values from rhs.m_array
				m_array[i] = rhs.m_array[i];
			}
		}
		return *this;										// returns the new array object
	}
}


template<typename T>
Array<T>& Array<T>::operator=(Array<T>&& rhs)	// don't know if this is right at all
{												// never learned about &&, google helps but don't know what the purpose is here.
	if (this != &rhs) {							// checks if this == &rhs
		delete[] m_array;						// deletes current array
		m_array = rhs.m_array;
		m_length = rhs.m_length;
		m_start_index = rhs.m_start_index;		// makes a new array with new values
		rhs.m_array = nullptr;

	}
	return *this;								// returns the new array object
}

template<typename T>
Array<T>::~Array()
{
	delete[] m_array;		// delete memory in array
	m_array = nullptr;		// set empty array to nullptr
	m_length = 0;
	m_start_index = 0;

	/*
	I'm using the examples from the error code and it's basically the same as what I was
	doing so I'm not really sure what I was having a problem with before. Maybe it didn't like
	that I wasn't setting length and index to 0? I don't think it was the use of "this->" since I
	tried it without it as well.
	*/

	//delete[] this->m_array;	// Causes heap corruption
	//this->m_array = nullptr;	// If I use the default destructor the corruption stops but I then get an
								// Debug Assertion error. I think if I get this right it should hopefully
								// be able to run the rest of the test.

	//delete[] m_array;			// Causes Heap corruption
	//m_array = nullptr;		// I don't know how to fix this
}

template<typename T>
T& Array<T>::operator[](int index)
{
	if (index < m_start_index || index > m_length)	//checks if index is out of bounds
		throw Exception("Out of bounds.");

	return m_array[index - m_start_index];
}

template<typename T>
int Array<T>::getStartIndex() const
{
	return m_start_index;
}

template<typename T>
int Array<T>::getLength() const
{
	return m_length;
}

template<typename T>
void Array<T>::setStartIndex(const int start_index)
{
	m_start_index = start_index;
}

template<typename T>
void Array<T>::setLength(const int length)
{

	if (length < 0)
		throw Exception("Length cannot be negative.");			// if length is negative throw and exception
	T* newArray = new T[length];								// Make a new array of the new length
	int shorter = (m_length < length ? m_length : length);		// Determine which length is shorter
	for (int i = m_start_index; i < shorter; i++) {				// from the beginning of the array until whichever was shorter, fill in with the old data
		newArray[i] = m_array[i];								// filling in
	}
	m_array = newArray;											// set new values in/replace array
	m_length = length;											// set new length
}
#endif
