#pragma once
#include <iostream>

template <class T>
class CircularList {

	struct Node {
		T data;
		Node* next;

		Node(T data_, Node* next_)
			:data(data_), next(next_) {}
	};

public:
	class iterator {

		friend CircularList;
		Node* ptr;
	public:
		iterator(Node* ptr_ = tail);

		T& operator*();
		const T& operator*() const;
		T* operator->();
		const T* operator->() const;

		bool operator==(const iterator& other) const;
		bool operator!=(const iterator& other) const;
		
		iterator& operator++();
		iterator operator++(int);
	};

private:
	Node* head;
	Node* tail;
	size_t size;

public:
	CircularList();
	CircularList(const CircularList<T>& other);
	CircularList<T> operator=(CircularList other);
	~CircularList();

	void push(const T& thing);
	void pop();

	iterator insert_after(const iterator& it, const T& thing);
	iterator remove_after(iterator& it);

	T& front();
	const T& front() const;

	iterator begin() const;
	iterator end() const;

	void copy(const CircularList<T>& other);
	void clean();

	bool empty() const;
	void print() const;
};


template<class T>
inline CircularList<T>::CircularList()
	:head(nullptr), tail(nullptr), size(0) {}

template<class T>
inline CircularList<T>::CircularList(const CircularList<T>& other)
	: CircularList<T>()
{
	copy(other);
}

template<class T>
inline CircularList<T> CircularList<T>::operator=(CircularList other)
{
	std::swap(size, other.size);
	std::swap(head, other.head);
	std::swap(tail, other.tail);

	return *this;
}

template<class T>
inline CircularList<T>::~CircularList()
{
	clean();
}

template<class T>
inline void CircularList<T>::push(const T& thing)
{
	if (empty()) {
		tail = head = new Node(thing, head);
		tail->next = head;
	}
	else {
		tail->next = new Node(thing, head);
		tail = tail->next;
	}
	++size;
}

template<class T>
inline void CircularList<T>::pop()
{
	if (empty()) throw std::logic_error("Circular List: You tried to pop from an empty list");

	Node* temp = head;
	head = head->next;
	delete temp;

	--size;
	if (empty()) tail = head;
}

template<class T>
inline typename CircularList<T>::iterator CircularList<T>::insert_after(const iterator& it, const T& thing)
{
	Node* next = it.ptr->next;
	Node* newNode = new Node(thing, next);
	it.ptr = newNode;

	++size;
	return iterator(newNode);
}

template<class T>
inline typename CircularList<T>::iterator CircularList<T>::remove_after(iterator& it)
{
	if (empty()) throw std::logic_error("Circular List: You tried to pop from an empty list");

	if (size == 1) {
		delete head;
		tail = head = nullptr;
		--size;
		return iterator(head);
	}

	Node* remove = it.ptr->next;
	if (remove == tail) tail = it.ptr;
	if (remove == head) head = head->next;

	it.ptr->next = remove->next;
	delete remove;

	--size;

	return iterator(it.ptr->next);
}

template<class T>
inline T& CircularList<T>::front()
{
	if (empty()) throw std::logic_error("Circular List: You tried to recieve element from empty list");

	return head->data;
}

template<class T>
inline const T& CircularList<T>::front() const
{
	return const_cast<CircularList&>(*this).front();
}

template<class T>
inline typename CircularList<T>::iterator CircularList<T>::begin() const
{
	return iterator(head);
}

template<class T>
inline typename CircularList<T>::iterator CircularList<T>::end() const
{
	return begin();
}

template<class T>
inline void CircularList<T>::copy(const CircularList<T>& other)
{
	if (other.empty()) return;
	try {
		head = new Node(other.head->data, other.head->next);
		Node* tocopy = other.head->next;
		Node* copied = head;
		++size;

		while (tocopy != other.head) {
			copied->next = new Node(tocopy->data, nullptr);

			tocopy = tocopy->next;
			copied = copied->next;
			++size;
		}

		copied->next = tail = head;							//chaining those together
	}
	catch (...) {
		clean();
		throw;
	}
}

template<class T>
inline void CircularList<T>::clean()
{
	while (!empty())
		pop();
}

template<class T>
inline bool CircularList<T>::empty() const
{
	return size == 0;
}

template<class T>
inline void CircularList<T>::print() const
{
	iterator it = begin();
	do {
		std::cout << *it << " -> ";
		++it;
	} while (it != end());

	std::cout << *begin() << std::endl;
}

/* iterator constructor */

template<class T>
inline CircularList<T>::iterator::iterator(Node* ptr_)
	:ptr(ptr_) {}

/* access operators */

template<class T>
inline T& CircularList<T>::iterator::operator*()
{
	return ptr->data;
}

template<class T>
inline const T& CircularList<T>::iterator::operator*() const
{
	return ptr->data;
}

template<class T>
inline T* CircularList<T>::iterator::operator->()
{
	return &(ptr->data);
}

template<class T>
inline const T* CircularList<T>::iterator::operator->() const
{
	return &(ptr->data);
}


/* comparison operators */

template<class T>
inline bool CircularList<T>::iterator::operator==(const iterator& other) const
{
	return this->ptr == other.ptr;
}

template<class T>
inline bool CircularList<T>::iterator::operator!=(const iterator& other) const
{
	return !(*this == other);
}

/* modifier operators */

template<class T>
inline typename CircularList<T>::iterator& CircularList<T>::iterator::operator++()
{
	if (ptr == nullptr) throw std::out_of_range("Reached the end of list");

	ptr = ptr->next;
	return *this;
}

template<class T>
inline typename CircularList<T>::iterator CircularList<T>::iterator::operator++(int)
{
	if (ptr == nullptr) throw std::out_of_range("Reached the end of list");

	iterator rtrn(*this);
	++(*this);
	return rtrn;
}

int main() {

	CircularList<int> list1;
	for (int i = 1; i <= 10; ++i)
		list1.push(i);

	std::cout << "List 1: ";
	list1.print();

	CircularList<int> list2(list1);

	CircularList<int>::iterator it = list2.begin();
	for (int i = 0; i < 5; ++i) {
		list2.remove_after(it);
	}

	std::cout << "List 1 with removed elements: ";
	list2.print();

	return 0;
}