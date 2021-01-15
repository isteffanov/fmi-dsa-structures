#pragma once

template <class T>
class BinaryTree {

public:
	struct Node {
		T data;
		Node* left;
		Node* right;

		Node(const T& _data, Node* _left, Node* _right)
			:data(_data), left(_left), right(_right) {}
	};

public:
	BinaryTree();
	BinaryTree(const BinaryTree& other) = delete;
	const BinaryTree& operator=(const BinaryTree& other) = delete;
	~BinaryTree();

	const Node* add(const T& data,	Node* left = nullptr,
									Node* right = nullptr);
	void		remove(const T& data);
	const Node* find(const T& data);

	const T&	min() const;
	const T&	max() const;

	void		print() const;

private:
	Node* root;

	Node* findRecursive(const T& data, Node* start);
	Node* minRecursive(Node* start);
	Node* maxRecursive(Node* start);

	void printInOrder(Node* start);
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
inline typename const BinaryTree<T>::Node*
BinaryTree<T>::add(const T& data, Node* left, Node* right)
{
	return new Node(data, left, right);
}

template<class T>
inline void BinaryTree<T>::remove(const T& data)
{
	//TODO
}

template<class T>
inline typename const BinaryTree<T>::Node*
BinaryTree<T>::find(const T& data)
{
	return findRecursive(data, root);
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
inline void BinaryTree<T>::print() const
{
	printInOrder(root);
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

template<class T>
inline void BinaryTree<T>::printInOrder(Node* start)
{
	if (!start) return;

	printInOrder(start->left);
	std::cout << start->data << " ";
	printInOrder(start->right);
}

int main() {
	using node = BinaryTree<int>::Node;

	BinaryTree<int> tree;
	tree.add(10,
		new node(5,
			nullptr,
			nullptr),
		new node(30,
			new node(7,
				nullptr,
				nullptr),
			new node(200,
				nullptr,
				new node(4,
					nullptr,
					nullptr)
			)
		)
	);



	return 0;
}

