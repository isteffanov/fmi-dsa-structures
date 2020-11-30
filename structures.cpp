#include <iostream>
#include "List.hpp"

int main()
{
	List<int> l;
	for (int i = 1; i <= 10; ++i)
		l.push_back(i);

	l.print();

	for (int i = 1; i <= 10; ++i) {
		l.print();
		l.pop_back();
	}
	return 0;
}

