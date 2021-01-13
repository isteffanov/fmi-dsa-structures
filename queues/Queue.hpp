
template <class T>
class Queue {

	struct Node {
		T data;
		Node* next;

		Node(T data_, Node* next_)
			:data(data_), next(next_){}
	};

	Node* head;
	Node* tail;

public:
	Queue();
	Queue(const Queue<T>& other);
	Queue<T> operator=(Queue<T> other);
	~Queue();

	void enqueue(const T& thing);
	void dequeue();

	T& front();
	const T& front() const;

	void copy(const Queue<T>& other);
	void clean();

	bool empty() const;
	void print();
};

template<class T>
inline Queue<T>::Queue()
	: head(nullptr) {}

template<class T>
inline Queue<T>::Queue(const Queue<T>& other)
	:Queue<T>()
{
	copy(other);
}

template<class T>
inline Queue<T> Queue<T>::operator=(Queue<T> other)
{
	std::swap(head, other.head);

	return *this;
}

template<class T>
inline Queue<T>::~Queue()
{
	clean();
}

template<class T>
inline void Queue<T>::enqueue(const T& thing)
{
	if (empty()) head = tail	   = new Node(thing, head);
	else		 tail = tail->next = new Node(thing, nullptr);
	
}

template<class T>
inline void Queue<T>::dequeue()
{
	if (empty()) throw std::logic_error("Queue: You tried to dequeue from an empty queue");

	Node* remove = head;
	head = head->next;
	delete remove;
}

template<class T>
inline T& Queue<T>::front()
{
	if (empty()) throw std::logic_error("Queue: You tried to access front element in an empty queue");

	return head->data;
}

template<class T>
inline const T& Queue<T>::front() const
{
	return const_cast<Queue<T>&>(*this).front();
}

template<class T>
inline void Queue<T>::copy(const Queue<T>& other)
{
	if (other.empty()) return;
	try {
		head = new Node(other.head->data, nullptr);
		Node* tocopy = other.head->next;
		Node* copied = head;

		while (tocopy != nullptr) {
			copied->next = new Node(tocopy->data, nullptr);

			tocopy = tocopy->next;
			copied = copied->next;
		}

		tail = other.tail;
	}
	catch (...) {
		clean();
		throw;
	}
}

template<class T>
inline void Queue<T>::clean()
{
	while (!empty())
		dequeue();
}

template<class T>
inline bool Queue<T>::empty() const
{
	return head == nullptr;
}

template<class T>
inline void Queue<T>::print()
{
	while (!empty()) {
		std::cout << front();
		dequeue();
		if (!empty()) std::cout << " - ";
	}
}

int main() {

	Queue<int> queue;
	for (int i = 1; i <= 10; ++i)
		queue.enqueue(i);

	queue.print();

	return 0;
}