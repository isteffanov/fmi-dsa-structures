#pragma once

template <class T>
class ForwardList {

	struct Node {
		T data;
		Node* next;

		Node(T data_, Node* next_)
			:data(data_), next(next_) {}
	};

public:
	class iterator {
		friend ForwardList;

		Node* ptr;

	public:
		iterator(Node* ptr_);

		T&			operator* ();
		const T&	operator* () const;
		T*			operator->();

		bool		operator==(const iterator& other) const;
		bool		operator!=(const iterator& other) const;

		iterator&	operator++();
		iterator	operator++(int);
	};

private:
	Node* head;
	Node* tail;

public:
	ForwardList();
	ForwardList(const std::initializer_list<T>& il);
	ForwardList(const ForwardList<T>& other);
	ForwardList<T> operator=(const ForwardList<T>& other);
	~ForwardList();

	void push_front(const T& thing);
	void pop_front();

	T& front();
	const T& front() const;

	iterator insert_after(iterator& it, const T& thing);
	iterator remove_after(const iterator& it);

	iterator begin() const;
	iterator end()   const;

	void copy(const ForwardList<T>& other);
	void clean();

	bool empty() const;
	void print();
};

#include "ForwardList.ipp"