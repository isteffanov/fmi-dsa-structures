#pragma once

template <class T>
class ForwardList {

	struct Node {
		T data;
		Node* next;

		Node(T data_, Node* next_)
			:data(data_), next(next_) {}
	};

	Node* head;
	Node* tail;

public:
	ForwardList();
	~ForwardList();

	void push_front(const T& thing);
	void pop_front();

	T& front();
	const T& front() const;

	bool empty() const;
	void print();
};

template<class T>
inline ForwardList<T>::ForwardList()
	:head(nullptr), tail(nullptr) {}

template<class T>
inline ForwardList<T>::~ForwardList()
{
	while (!empty())
		pop_front();
}

template<class T>
inline void ForwardList<T>::push_front(const T& thing)
{
	if (empty()) {
		head = new Node(thing, nullptr);
		tail = head;
	}
	else head = new Node(thing, head);
}

template<class T>
inline void ForwardList<T>::pop_front()
{
	if (empty()) throw std::logic_error("You tried to pop from empty list");

	Node* temp = head;
	head = head->next;
	delete temp;
}

template<class T>
inline T& ForwardList<T>::front()
{
	return head->data;
}

template<class T>
inline const T& ForwardList<T>::front() const
{
	return const_cast<T&>(*this).front();
}

template<class T>
inline bool ForwardList<T>::empty() const
{
	return head == nullptr;
}

template<class T>
inline void ForwardList<T>::print()
{
	while (!empty()) {
		std::cout << front() << " ";
		pop_front();
	}
}
