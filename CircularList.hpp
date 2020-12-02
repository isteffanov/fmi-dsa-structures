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

	void copy();
	void clean();

	bool empty() const;
	void print() const;
};

#include "CircularList.ipp"