#include <iostream>
#include <string>
#include <algorithm>

template <class T>
class AVLTree {

	struct Node {
		unsigned key;
		Node* parent;
		T data;
		Node* left;
		Node* right;
		int bf;

		Node(unsigned _key, Node* _parent, T _data, Node* _left = nullptr, Node* _right = nullptr)
			:key(_key), parent(_parent), data(_data), left(_left), right(_right), bf(0) {}

	};

	Node* root;

	//the new key will always be bigger than all others in the structure
	void	insertDirect	(unsigned key,	const T& thing);
	void	removeRecursive	(Node* start,	unsigned key);

	Node*	findRecursive	(Node* start,	unsigned key)	const;

	Node*	rightmostNode	(Node* start)					const;
	Node*	leftmostNode	(Node* start)					const;

	void	LKDHelper		(Node* start)					const;

	//balance methods
	void	updateBalance	(Node* node);
	void	rebalance		(Node* node);
	void	leftRotate		(Node* node);
	void	rightRotate		(Node* node);

	void printRecursive(Node* start, std::string indend, bool last) const ;
public:
	AVLTree()
		:root(nullptr) {}

	void insert(unsigned key, const T& thing)			{ insertDirect(key, thing); }
	void remove(unsigned key)							{ removeRecursive(root, key); }

	void traverseLKD()							const	{ LKDHelper(root); }

	void print()								const	{ printRecursive(root, "", true); }
};

template<class T>
inline void AVLTree<T>::insertDirect(unsigned key, const T& thing)
{
	if (!root) {
		root = new Node(key, nullptr, thing);
		return;
	}

	Node* max = rightmostNode(root);
	Node* newNode = new Node(key, max, thing);

	max->right = newNode;

	updateBalance(newNode);
}

template<class T>
inline void AVLTree<T>::removeRecursive(Node* start, unsigned key)
{
	Node* toRemove = findRecursive(start, key);
	if (!toRemove) throw std::logic_error("You tried to remove item that doesn't exist");

	if (!toRemove->left && !toRemove->right) {
		Node* temp = toRemove->parent;

		//update bf and error proof ourselves
		if (toRemove == temp->left) {
			temp->bf++;
			temp->left = nullptr;
		}
		else {
			temp->bf--;
			temp->right = nullptr;
		}

		delete toRemove;
		toRemove = nullptr;
	}
	else if (!toRemove->left) {
		Node* temp = toRemove;
		toRemove = toRemove->right;

		delete temp;
	}
	else if (!toRemove->right) {
		Node* temp = toRemove;
		toRemove = toRemove->left;

		delete temp;
	}
	else {
		Node* temp = leftmostNode(toRemove->right);
		toRemove->data = temp->data;
		try {
			removeRecursive(toRemove->right, temp->data);
		}
		catch (...) {
			;
		}
	}

	if (toRemove) updateBalance(toRemove);
}

template<class T>
inline typename AVLTree<T>::Node* AVLTree<T>::findRecursive(Node* start, unsigned key) const
{
	if (!start) return nullptr;

	if (key == start->key)		return start;
	else if (key < start->key)	return findRecursive(start->left, key);
	else						return findRecursive(start->right, key);
}

template<class T>
inline typename AVLTree<T>::Node* AVLTree<T>::rightmostNode(Node* start) const
{
	Node* curr = start;
	while (curr->right) {
		curr = curr->right;
	}	

	return curr;
}

template<class T>
inline typename AVLTree<T>::Node* AVLTree<T>::leftmostNode(Node* start) const
{
	Node* curr = start;
	while (curr->left) {
		curr = curr->left;
	}

	return curr;
}

template<class T>
inline void AVLTree<T>::LKDHelper(Node* start) const
{
	if (start) {
		LKDHelper(start->left);
		std::cout << start->data << " - ";
		LKDHelper(start->right);
	}
}

/* Balance methods */

template<class T>
inline void AVLTree<T>::updateBalance(Node* node)
{
	if (node->bf < -1 || node->bf > 1) {
		rebalance(node);
		return;
	}

	if (node->parent) {

		if (node == node->parent->left)		node->parent->bf -= 1;
		if (node == node->parent->right)	node->parent->bf += 1;

		if (node->parent->bf != 0)			updateBalance(node->parent);
	}
}

template<class T>
inline void AVLTree<T>::rebalance(Node* node)
{
	if (node->bf > 0) {

		if (node->right->bf < 0) {
			rightRotate(node->right);
			leftRotate(node);
		}

		else leftRotate(node);
	}
	else if (node->bf < 0) {

		if (node->left->bf > 0) {
			leftRotate(node->left);
			rightRotate(node);
		}

		else rightRotate(node);
	}
}

template<class T>
inline void AVLTree<T>::leftRotate(Node* node)
{
	Node* child = node->right;
	node->right = child->left;

	if (child->left != nullptr)				child->left->parent = node;
	
	child->parent = node->parent;

	if (node->parent == nullptr)			root = child;
	else if (node == node->parent->left)	node->parent->left = child;
	else									node->parent->right = child;

	child->left = node;
	node->parent = child;

	// update the balance factor
	node->bf	= node->bf	- 1 - std::max(0, child->bf);
	child->bf	= child->bf - 1 + std::min(0, node->bf);
}

template<class T>
inline void AVLTree<T>::rightRotate(Node* node)
{
	Node* child = node->left;
	node->left = child->right;

	if (child->right != nullptr)			child->right->parent = node;

	child->parent = node->parent;

	if (node->parent == nullptr)			root = child;
	else if (node == node->parent->right)	node->parent->right = child;
	else									node->parent->left = child;

	child->right = node;
	node->parent = child;

	// update the balance factor
	node->bf	= node->bf	+ 1 - std::min(0, child->bf);
	child->bf	= child->bf + 1 + std::max(0, node->bf);
}

template<class T>
inline void AVLTree<T>::printRecursive(Node* start, std::string indent, bool last) const 
{
	// pretty print
	if (start) {
		std::cout << indent;
		if (last) {
			std::cout << "R----";
			indent += "     ";
		}
		else {
			std::cout << "L----";
			indent += "|    ";
		}

		std::cout << start->data << "( BF = " << start->bf << ")" << std::endl;

		printRecursive(start->left, indent, false);
		printRecursive(start->right, indent, true);
	}
}

