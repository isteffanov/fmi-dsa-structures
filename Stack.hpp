#pragma once

template <class T>
class Stack {

	struct Node {
		T data;
		Node* next;

		Node(T data_, Node* next_) 
			: data(data_), next(next_) {}
	};

	Node* topnode;

public:
	Stack();
	Stack(const Stack<T>& other);
	Stack<T> operator=(Stack<T> other);
	~Stack();

	void push(const T thing);
	void pop();

	T& top();
	const T& top() const;

	bool empty() const;
	void print();
};

template<class T>
inline Stack<T>::Stack()
	:topnode(nullptr){}

template<class T>
inline Stack<T>::Stack(const Stack<T>& other)
	:Stack<T>()
{
	topnode = new Node(other.topnode->data, nullptr);
	Node* copied = topnode;
	Node* tocopy = other.topnode->next;

	while (tocopy) {
		copied->next = new Node(tocopy->data, nullptr);
		
		copied = copied->next;
		tocopy = tocopy->next;
	}
}

template<class T>
inline Stack<T> Stack<T>::operator=(Stack<T> other)
{
	std::swap(topnode, other.topnode);
	return *this;
}

template<class T>
inline Stack<T>::~Stack()
{
	while (!empty())
		pop();
}

template<class T>
inline void Stack<T>::push(const T thing)
{
	try {
		topnode = new Node(thing, topnode);
	}
	catch (std::bad_alloc& ba) {
		std::cout << "Stack: " << ba.what() << std::endl;
	}
}

template<class T>
inline void Stack<T>::pop()
{
	Node* next = topnode->next;
	delete topnode;
	topnode = next;
}

template<class T>
inline T& Stack<T>::top()
{
	if (empty()) throw std::logic_error("Stack is empty");

	return topnode->data;
}

template<class T>
inline const T& Stack<T>::top() const
{
	return const_cast<T&>(*this).top();
}

template<class T>
inline bool Stack<T>::empty() const
{
	return topnode == nullptr;
}

template<class T>
inline void Stack<T>::print()
{
	while (!empty()) {
		std::cout << top() << std::endl;
		pop();
	}
}
