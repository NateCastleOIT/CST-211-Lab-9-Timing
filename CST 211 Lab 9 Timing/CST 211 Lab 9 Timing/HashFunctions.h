#ifndef HASHFUNCTIONS_H
#define HASHFUNCTIONS_H
#include <string>

class Hashes
{
public:
	static int ASCIIHash(std::string key, int size)
	{
		unsigned int i = 0;
		for (int j = 0; j < key[j]; j++)
		{
			i += key[j];
		}
		int newHash = i % size;
		return newHash;
	}
};
#endif HASHFUNCTIONS_H
