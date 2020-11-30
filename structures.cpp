#include <iostream>
#include "List.hpp"

int main()
{
	List<int> l;
	for (int i = 1; i <= 10; ++i)
		l.push_back(i);

	List<int> k(l);
	k.print();

	
	return 0;
}

