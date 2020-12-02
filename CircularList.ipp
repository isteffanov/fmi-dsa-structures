#include "CircularList.hpp"

template<class T>
inline CircularList<T>::CircularList()
	:head(nullptr), tail(nullptr), size(0) {}

template<class T>
inline CircularList<T>::CircularList(const CircularList<T>& other)
	: CircularList<T>()
{
	copy();
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
inline void CircularList<T>::copy()
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