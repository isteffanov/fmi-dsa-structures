#pragma once
#include <iostream>

template <class T>
class List
{
	struct Node {
		Node* prev;
		T data;
		Node* next;

		Node(Node* prev_, T data_, Node* next_ = nullptr)
			: prev(prev_), data(data_), next(next_) {}
	};

public:
	class iterator {
		friend List;

		Node* ptr;

	public:
		iterator(Node* ptr_);

		T&			operator*();
		const T&	operator*() const;
		T*			operator->();

		bool operator==(const iterator& other) const;
		bool operator!=(const iterator& other) const;

		iterator& operator++();
		iterator  operator++(int);
		iterator& operator--();
		iterator  operator--(int);
	};
private:

	Node* head;
	Node* tail;

public:
	List();
	List(const std::initializer_list<T>& il);
	List(const List<T>& other);
	List<T>& operator=(const List<T>& other);
	~List<T>();

	void push_front(const T thing);
	void push_back(const T thing);
	void pop_front();
	void pop_back();

	iterator begin() const;
	iterator end() const;

	iterator insert(const iterator& it, const T& thing);
	iterator remove(const iterator& it);

	inline T& front();
	inline T& back();
	inline const T& front() const;
	inline const T& back()	const;

	void reverse();

	void copy(const List<T>& other);
	void clean();

	bool empty() const;
	void print() const;
};

template<class T>
inline List<T>::List()
	:head(nullptr), tail(nullptr) {}

template<class T>
inline List<T>::List(const std::initializer_list<T>& il)
	: List<T>()
{
	for (const T& el : il)
		push_back(el);
}

template<class T>
inline List<T>::List(const List<T>& other)
	:List<T>()
{
	copy(other);
}

template<class T>
inline List<T>& List<T>::operator=(const List<T>& other)
{
	if (this != &other) {
		clean();
		copy(other);
	}

	return *this;
}


template<class T>
inline List<T>::~List()
{
	clean();
}

/* push / pop methods */

template<class T>
inline void List<T>::push_front(const T thing)
{
	if (head == nullptr) head = new Node(nullptr, thing, head);
	else {
		head->prev = new Node(nullptr, thing, head);
		head = head->prev;
	}

	if (tail == nullptr) tail = head;
}

template<class T>
inline void List<T>::push_back(const T thing)
{
	if (tail == nullptr) {								//there are no elements in the list
		tail = new Node(nullptr, thing, nullptr);
		head = tail;
	}
	else {
		tail->next = new Node(tail, thing, nullptr);
		tail = tail->next;
	}
}

template<class T>
inline void List<T>::pop_front()
{
	if (empty())										//there are no elements in the list
		throw std::logic_error("Empty list");

	if (head == tail) {									//there is 1 element in the list
		delete tail;
		head = tail = nullptr;
	}
	else {
		head = head->next;
		delete head->prev;
		head->prev = nullptr;
	}
}

template<class T>
inline void List<T>::pop_back()
{
	if (empty())
		throw std::logic_error("Empty list");

	if (head == tail) {									//there is 1 element in the list
		delete tail;
		head = tail = nullptr;
	}
	else {
		tail = tail->prev;
		delete tail->next;
		tail->next = nullptr;
	}
}

/* iterator methods */

template<class T>
inline typename List<T>::iterator List<T>::begin() const
{
	return iterator(head);
}

template<class T>
inline typename List<T>::iterator List<T>::end() const
{
	if (tail == nullptr) throw std::logic_error("Empty list");
	return iterator(tail->next);
}

template<class T>
inline typename List<T>::iterator List<T>::insert(const iterator& it, const T& thing)
{
	if (it == begin() || empty()) {
		push_front(thing);
		return iterator(head);
	}

	Node* prev = it.ptr->prev;
	Node* newNode = new Node(prev, thing, it.ptr);

	prev->next = newNode;
	it.ptr->prev = newNode;

	return iterator(newNode);
}

template<class T>
inline typename  List<T>::iterator List<T>::remove(const iterator& it)
{
	if (empty()) throw std::logic_error("Empty list");
	if (it == end()) return end();

	if (it.ptr == head) {
		pop_front();
		return iterator(head);
	}

	if (it.ptr == tail) {
		pop_back();
		return iterator(tail);
	}

	Node* prev = it.ptr->prev;
	Node* next = it.ptr->next;

	prev->next = next;
	next->prev = prev;

	delete it.ptr;

	return iterator(next);

}

/* front / back methods */

template<class T>
inline T& List<T>::front()
{
	return head->data;
}

template<class T>
inline T& List<T>::back()
{
	return tail->data;
}

template<class T>
inline const T& List<T>::front() const
{
	return head->data;
}

template<class T>
inline const T& List<T>::back() const
{
	return tail->data;
}

template<class T>
inline void List<T>::reverse()
{
	Node* toBePrev = head->next;
	Node* curr = head;

	while (toBePrev) {
		curr->next = curr->prev;
		curr->prev = toBePrev;

		toBePrev = toBePrev->next;
		curr = curr->prev;
	}

	tail = head;
	head = curr;

	head->next = head->prev;
	head->prev = nullptr;
}

/* constructor helper methods */

template<class T>
inline void List<T>::copy(const List<T>& other)
{
	if (other.empty()) return;

	try {
		head = new Node(nullptr, other.head->data, nullptr);
		Node* tocopy = other.head;
		Node* copied = head;

		do {
			tocopy = tocopy->next;

			copied->next = new Node(copied, tocopy->data, nullptr);
			copied = copied->next;
		} while (tocopy->next != nullptr);

		tail = copied;
	}
	catch (...) {
		clean();
		throw;
	}
}

template<class T>
inline void List<T>::clean()
{
	while (!empty())
		pop_front();
}

/* other methods */

template<class T>
inline bool List<T>::empty() const
{
	return head == nullptr;
}

template<class T>
inline void List<T>::print() const
{
	std::cout << "[ ";

	if (!empty()) {
		for (iterator it = begin(); it != end(); ++it)
			std::cout << *it << (it.ptr != tail ? " <-> " : "");
	}

	std::cout << " ]" << std::endl;
}

/* iterator constructor */

template<class T>
inline List<T>::iterator::iterator(Node* ptr_)
	:ptr(ptr_) {}

/* access operators */

template<class T>
inline T& List<T>::iterator::operator*()
{
	return ptr->data;
}

template<class T>
inline const T& List<T>::iterator::operator*() const
{
	return ptr->data;
}

template<class T>
inline T* List<T>::iterator::operator->()
{
	return &(ptr->data);
}

/* comparison operators */

template<class T>
inline bool List<T>::iterator::operator==(const iterator& other) const
{
	return this->ptr == other.ptr;
}

template<class T>
inline bool List<T>::iterator::operator!=(const iterator& other) const
{
	return !(*this == other);
}

/* modifier operators */

template<class T>
inline typename List<T>::iterator& List<T>::iterator::operator++()
{
	if (ptr == nullptr) throw std::out_of_range("Reached the end of list");

	ptr = ptr->next;
	return *this;
}

template<class T>
inline typename List<T>::iterator List<T>::iterator::operator++(int)
{
	if (ptr == nullptr) throw std::out_of_range("Reached the end of list");

	iterator rtrn(*this);
	++(*this);
	return rtrn;
}

template<class T>
inline typename List<T>::iterator& List<T>::iterator::operator--()
{
	if (ptr == nullptr) throw std::out_of_range("Reached the beginning of list");

	ptr = ptr->prev;
	return *this;
}

template<class T>
inline typename List<T>::iterator List<T>::iterator::operator--(int)
{
	if (ptr == nullptr) throw std::out_of_range("Reached the beginning of list");

	iterator rtrn(*this);
	--(*this);
	return rtrn;
}

int main() {

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

	return 0;
}