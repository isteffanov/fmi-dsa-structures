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


	Node* head;
	Node* tail;

public:
	List();
	~List<T>();

	void push_front(const T thing);
	void push_back(const T thing);
	void pop_front();
	void pop_back();

	bool empty() const;
	void print() const;
};

template<class T>
inline List<T>::List()
	:head(nullptr), tail(nullptr){}

template<class T>
inline List<T>::~List()
{
	while (!empty())
		pop_front();
}

/* push / pop methods */

template<class T>
inline void List<T>::push_front(const T thing)
{
	head = new Node(nullptr, thing, head);
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
		throw "Empty list";

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
		throw "Empty list";

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


template<class T>
inline bool List<T>::empty() const
{
	return head == nullptr;
}

template<class T>
inline void List<T>::print() const
{	

	//TODO iterator
	Node* it = head;
	while (it != tail) {
		std::cout << it->data << " -> ";
		it = it->next;
	}

	std::cout << it->data << '\n';
	
}


