#include <iostream>
#include "List.hpp"

void ListTest() {
	List<int> list1;
	for (int i = 1; i <= 10; ++i)
		list1.push_back(i);

	std::cout << "Filled via for loop: ";
	list1.print();

	List<int> list2 = { 11, 12, 13, 14, 15 };
	std::cout << "Filled via initializer list: ";
	list2.print();


	List<int>::iterator it = list2.begin();
	for (int i = 0; i < 2; ++i)
		++it;
	list2.insert(it, 20);
	std::cout << "Inserted '20' in third place: ";
	list2.print();

	List<int>::iterator it1 = list1.begin();
	for (int i = 1; i < 7; ++i)
		++it1;
	list1.remove(it1);
	std::cout << "Removed the seventh item: ";
	list1.print();
}

int main()
{
	ListTest();

	
	return 0;
}

