#pragma once

template <class T>
class BinaryTree {

	struct Node {
		T data;
		Node* leftChild;
		Node* rightChild;

		Node(const T& _data)
			:data(_data), leftChild(nullptr), rightChild(nullptr) {}
	};

	Node* root;

	void addRecursive(const T& data, Node*& start);

	Node* find(const T& data);
	Node* findRecursive(const T& data, Node* start);

	Node* minRecursive(Node* start);
	Node* maxRecursive(Node* start);

public:
	BinaryTree();
	~BinaryTree();

	void add(const T& data);
	void remove(const T& data);

	const T& min() const;
	const T& max() const;
};


template<class T>
inline BinaryTree<T>::BinaryTree()
	:root(nullptr) {}

template<class T>
inline BinaryTree<T>::~BinaryTree()
{
	while (root)
		remove(root->data);
}

template<class T>
inline void BinaryTree<T>::add(const T& data)
{
	try {
		addRecursive(data, root);
	}
	catch (std::exception& e) {
		std::cout << "BinaryTree: " << e.what();
	}
}

template<class T>
inline void BinaryTree<T>::remove(const T& data)
{
	Node* toRemove = find(data);
	if (!toRemove) return;

	//there are no children
	if (!toRemove->leftChild && !toRemove->rightChild) {
		delete toRemove;
		toRemove = nullptr;
	}
	//there is only one child
	else if (!toRemove->leftChild &&  toRemove->rightChild
		   || toRemove->leftChild && !toRemove->rightChild) {
		Node* child = toRemove->leftChild ? toRemove->leftChild : toRemove->rightChild;

		toRemove->data = child->data;
		tmp = child;
		delete toRemove;
	}
	//there are two children
	else {
		Node* min = minRecursive(toRemove->rightChild);
		toRemove->data = min->data;
		delete min;
	}
}

template<class T>
inline const T& BinaryTree<T>::min() const
{
	return minRecursive(root)->data;
}

template<class T>
inline const T& BinaryTree<T>::max() const
{
	return maxRecursive(root)->data;
}

template<class T>
inline void BinaryTree<T>::addRecursive(const T& data, Node*& start)
{
	if (!start) {
		start = new Node(data);
		return;
	}

	if (data == start->data)
		throw std::logic_error("You tried to insert dublicate elements, that would break the structure!");

	else if (data < start->data)
		return addRecursive(data, start->leftChild);

	else 
		return addRecursive(data, start->rightChild);

}

template<class T>
inline typename BinaryTree<T>::Node* BinaryTree<T>::find(const T& data)
{
	return findRecursive(data, root);
}

template<class T>
inline typename BinaryTree<T>::Node* BinaryTree<T>::findRecursive(const T& data, Node* start)
{
	if (!start) return nullptr;
	if (data == start->data) return start;
	else if (data < start->data) return findRecursive(data, start->leftChild);
	else return findRecursive(data, start->rightChild);
}

template<class T>
inline typename BinaryTree<T>::Node* BinaryTree<T>::minRecursive(Node* start)
{
	if (!start) return start;

	return start->leftChild;
}

template<class T>
inline typename BinaryTree<T>::Node* BinaryTree<T>::maxRecursive(Node* start)
{
	if (!start) return start;

	return start->rightChild;
}

int main() {

	BinaryTree<int> tree;
	tree.add(10);
	tree.add(5);
	tree.add(15);

	tree.add(20);
	tree.remove(15);

	return 0;
}
