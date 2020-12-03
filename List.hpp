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

#include "List.ipp"
