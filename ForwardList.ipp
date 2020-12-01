#include "ForwardList.hpp"

template<class T>
inline ForwardList<T>::ForwardList()
	:head(nullptr), tail(nullptr) {}

template<class T>
inline ForwardList<T>::ForwardList(const std::initializer_list<T>& il)
	: ForwardList<T>()
{
	typename std::initializer_list<T>::iterator it = il.end() - 1;
	for (; it >= il.begin(); --it)
		push_front(*it);
}

template<class T>
inline ForwardList<T>::ForwardList(const ForwardList<T>& other)
{
	copy(other);
}

template<class T>
inline ForwardList<T> ForwardList<T>::operator=(const ForwardList<T>& other)
{
	if (this != &other) {
		clean();
		copy(other);
	}

	return *this;
}


template<class T>
inline ForwardList<T>::~ForwardList()
{
	clean();
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
inline typename ForwardList<T>::iterator ForwardList<T>::insert_after(iterator& it, const T& thing)
{
	if (it == end())
		throw std::logic_error("Forward List: You tried to insert element after the end");

	Node* next = it.ptr->next;
	Node* newNode = new Node(thing, next);
	it.ptr->next = newNode;

	if (it.ptr->next == nullptr) tail = newNode;

	return iterator(next);
}

template<class T>
inline typename ForwardList<T>::iterator ForwardList<T>::remove_after(const iterator& it)
{
	if (it == end() || it.ptr->next == nullptr)
		throw std::logic_error("Forward List: You tried to remove element after the end");

	Node* remove = it.ptr->next;
	it.ptr->next = remove->next;
	delete remove;

	return iterator(it.ptr->next);
}

template<class T>
inline typename ForwardList<T>::iterator ForwardList<T>::begin() const
{
	return iterator(head);
}

template<class T>
inline typename ForwardList<T>::iterator ForwardList<T>::end() const
{
	return iterator(tail->next);
}

template<class T>
inline void ForwardList<T>::copy(const ForwardList<T>& other)
{
	head = new Node(other.head->data, nullptr);
	Node* tocopy = other.head->next;
	Node* copied = head;

	while (tocopy != nullptr) {
		copied->next = new Node(tocopy->data, nullptr);

		copied = copied->next;
		tocopy = tocopy->next;
	}
}

template<class T>
inline void ForwardList<T>::clean()
{
	while (!empty())
		pop_front();
}

template<class T>
inline bool ForwardList<T>::empty() const
{
	return head == nullptr;
}

template<class T>
inline void ForwardList<T>::print()
{
	std::cout << "[ ";

	for (iterator it = begin(); it != end(); ++it)
		std::cout << *it << (it.ptr != tail ? " -> " : "");

	std::cout << " ]" << std::endl;
}

/* iterator constructor */

template <class T>
inline ForwardList<T>::iterator::iterator(Node* ptr_)
	:ptr(ptr_) {}

/* access operators */

template<class T>
inline T& ForwardList<T>::iterator::operator*()
{
	return ptr->data;
}

template<class T>
inline const T& ForwardList<T>::iterator::operator*() const
{
	return ptr->data;
}

template<class T>
inline T* ForwardList<T>::iterator::operator->()
{
	return *ptr;
}

/* comparison operators */

template<class T>
inline bool ForwardList<T>::iterator::operator==(const iterator& other) const
{
	return this->ptr == other.ptr;
}

template<class T>
inline bool ForwardList<T>::iterator::operator!=(const iterator& other) const
{
	return !(*this == other);
}

/* modifier operators */

template<class T>
inline typename ForwardList<T>::iterator& ForwardList<T>::iterator::operator++()
{
	if (ptr == nullptr) throw std::out_of_range("Reached the end of list");

	ptr = ptr->next;
	return *this;
}

template<class T>
inline typename ForwardList<T>::iterator ForwardList<T>::iterator::operator++(int)
{
	if (ptr == nullptr) throw std::out_of_range("Reached the end of list");

	iterator rtrn(*this);
	++(*this);
	return rtrn;
}
