#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <utility>
#include <iterator>
#include "HashFunctions.h"
#include "Exception.h"


using std::vector;
using std::list;
using std::pair;
using std::make_pair;
using std::string;
using std::iterator;
using std::cout;
using std::endl;

template <typename K, typename V>
class HashTable
{
private:
	const float LOAD_FACTOR = 0.5;
	vector<list<pair<K, V>>> table;// = new vector<list<pair<K, V>>>(_size); 
	int _size;
	int numElement;
	int (*hashFunc)(K key, int size);
	void Rehash();
	vector<list<pair<K, V>>> GETTABLE() const { return table; }

public:
	HashTable();
	HashTable(int size);
	HashTable(HashTable<K, V>& hashtable);
	HashTable(HashTable<K, V>&& hashtable) noexcept;
	~HashTable();
	HashTable<K, V>& operator = (const HashTable<K, V>& rhs);
	HashTable<K, V>& operator = (HashTable<K, V>&& rhs) noexcept;
	V operator [](K key);
	bool operator == (const HashTable<K, V>& rhs);

	void Insert(K key, V value);
	void setHash(int(*func)(K key, int size)); // try with func pointer
	int getHash(K key);
	void Delete(K key);
	void Traverse(V value);
	const void print() const;

	float getLoadFactor() const;
	int getSize() const { return _size; }
	int getNum() const { return numElement; }
	auto getHashFunc() const { return hashFunc; }

	vector<list<pair<K, V>>> getTable() const { return GETTABLE(); }
	bool aboveLoadFactor() { return ((double)numElement / table.size()) > LOAD_FACTOR; }
};

template<typename K, typename V>
inline HashTable<K, V>::HashTable()
{
	_size = 10;
	numElement = 0;
	for (int i = 0; i < _size; i++)
	{
		table.emplace_back(); // fills vector with the correct type, empty lists of pairs
	}
	hashFunc = nullptr;
}

template<typename K, typename V>
inline HashTable<K, V>::HashTable(int size)
{
	_size = size;
	numElement = 0;
	for (int i = 0; i < _size; i++)
	{
		table.emplace_back(); // fills vector with the correct type, empty lists of pairs
	}
	hashFunc = nullptr;
}

template<typename K, typename V>
inline HashTable<K, V>::HashTable(HashTable<K, V>& hashtable)
{
	*this = hashtable;
}

template<typename K, typename V>
inline HashTable<K, V>::HashTable(HashTable<K, V>&& hashtable) noexcept
{
	*this = hashtable;
	hashtable.table.~vector();
}

template<typename K, typename V>
inline HashTable<K, V>::~HashTable()
{
	table.~vector<list<pair<K, V>>>(); // clears the table and frees the memory.
	_size = 0;
	numElement = 0;
}

template<typename K, typename V>
inline HashTable<K, V>& HashTable<K, V>::operator=(const HashTable<K, V>& rhs)
{
	_size = rhs._size;
	numElement = rhs.numElement;
	table = rhs.table;
	setHash(rhs.hashFunc);
	return *this;
}

template<typename K, typename V>
inline HashTable<K, V>& HashTable<K, V>::operator=(HashTable<K, V>&& rhs) noexcept
{
	_size = rhs._size;
	numElement = rhs.numElement;
	table = rhs.table;
	setHash(rhs.hashFunc);
	rhs.table.~vector<list<pair<K, V>>>(); // clears the table and frees the memory.
	rhs._size = 0;
	return *this;
}

template<typename K, typename V>
inline bool HashTable<K, V>::operator==(const HashTable<K, V>& rhs)
{
	return this->table == rhs.table;
}

template<typename K, typename V>
inline void HashTable<K, V>::Insert(K key, V value)
{
	int hashedKey = hashFunc(key, _size);
	table.at(hashedKey).push_back(make_pair(key, value));
	numElement++;
	if (aboveLoadFactor())	// check if adding a new pair will exceed load factor. if so, rehash.
		Rehash();
}

template<typename K, typename V>
inline void HashTable<K, V>::setHash(int(*func)(K key, int size))
{
	hashFunc = func;
}

template<typename K, typename V>
inline int HashTable<K, V>::getHash(K key)
{
	return hashFunc(key, table.size());
}

template<typename K, typename V>
inline V HashTable<K, V>::operator[](K key)
{
	try
	{
		bool found = false;
		int findKey = getHash(key);
		// Pointer to the list in the vector index the hashed key is apart of.
		list<pair<K, V>>* keyList = &table.at(findKey);

		// Go through the list and check each pair by reference
		for (auto& pair : *keyList)
		{
			// If the key matches any pair's first value, return that key's value.
			if (key == pair.first)
			{
				found = true;
				return pair.second;
			}
		}
		if (!found)
			throw Exception("No value found for that key!");
	}
	catch (Exception& e)
	{
		cout << "ERROR: " << e.getMessage() << endl;
	}
}

template<typename K, typename V>
inline void HashTable<K, V>::Delete(K key)
{
	int toRemove = getHash(key);
	// Pointer to the list in the vector index the hashed key is apart of.
	list<pair<K, V>>* keyList = &table.at(toRemove);
	bool found = false;
	// Go through the list and check each pair by reference
	for (auto& pair : *keyList)
	{
		// If the key matches any pair's first value, delete that pair.
		if (key == pair.first)
		{
			(*keyList).remove(pair);
			found = true;
			numElement--;
			break;
		}
	}
	try
	{
		if (!found)
			throw Exception("The given key doesn't exist.");
	}
	catch (Exception& e)
	{
		cout << "ERROR: " << e.getMessage() << endl;
	}
}

template<typename K, typename V>
inline void HashTable<K, V>::Traverse(V value)
{
	try
	{
		bool foundKey = false;
		for (int indx = 0; indx < _size; indx++)
		{
			cout << std::left << std::setw(7) << "Index " << std::right << std::setw(3) << indx << ": ";
			for (const auto pair : table.at(indx))
			{
				if (pair.second == value)
					foundKey = true;
				if (foundKey)
				{
					cout << "(" << pair.first << ", " << pair.second << ")";
					if (pair != table.at(indx).back())
						cout << " -> ";	// print the next pair in the list
				}
			}
			cout << endl;
		}
		if (!foundKey)
			throw Exception("The given value doesn't exist.");
	}
	catch (Exception& e)
	{
		cout << "ERROR: " << e.getMessage() << endl;
	}
}

template<typename K, typename V>
inline const void HashTable<K, V>::print() const
{
	try
	{
		if (numElement == 0)
			throw Exception("This table is empty!");
	}
	catch (Exception& e)
	{
		cout << "ERROR: " << e.getMessage() << endl;
	}

	for (int indx = 0; indx < _size; indx++)
	{
		cout << std::left << std::setw(7) << "Index " << std::right << std::setw(3) << indx << ": ";
		for (const auto pair : table.at(indx))
		{
			cout << "(" << pair.first << ", " << pair.second << ")";
			if (pair != table.at(indx).back())
				cout << " -> ";	// print the next pair in the list
		}
		cout << endl;
	}
}

template<typename K, typename V>
inline float HashTable<K, V>::getLoadFactor() const
{
	return ((double)numElement / table.size());
}

template<typename K, typename V>
inline void HashTable<K, V>::Rehash()
{
	vector<list<pair<K, V>>> tempBucket = table;	// make a new temp vector list pair that's double the size
	for (auto& list : table)	// clear the current table
		list.clear();

	for (int i = 0; i < tempBucket.size(); i++)	// since table is already size n, increase the length by n with new empty lists.
		table.emplace_back();

	_size = table.size();	// should stop the constant rehashing
	numElement = 0;			// set this to 0 so it doesn't continue incrementing from where it was

	for (auto list : tempBucket)		// for each index in the vector
	{
		for (auto pair : list)			// for each list in each vector index
		{
			Insert(pair.first, pair.second);	// insert the pairs that were in the list into the new bucket
		}
	}
}


#endif HASHTABLE_H