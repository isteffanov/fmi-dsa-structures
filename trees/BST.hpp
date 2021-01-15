#include <iostream>
#include <optional>

template <class T>
class BST {
	struct Node {
		T data;
		Node* left;
		Node* right;

		Node(const T& _data)
			:data(_data), left(nullptr), right(nullptr) {}
	};

	Node* root;

public:
	using type_or_null = std::optional< std::reference_wrapper<const T> >;

	BST();
	BST(const BST& other) = delete;
	const BST& operator=(const BST& other) = delete;
	~BST();

	Node* add(const T& thing);
	void			remove(const T& thing);
	type_or_null	find(const T& thing) const;

	const T& min() const;
	const T& max() const;

	void			print() const;

private:
	Node* addRecursive(const T& thing, Node*& start);
	Node* removeRecursive(const T& thing, Node*& start);
	Node*& findRecursive(const T& thing, Node* start) const;

	Node*& minRecursive(Node* start) const;
	Node*& maxRecursive(Node* start) const;

	void	printInOrder(Node* start) const;
};


template<class T>
inline BST<T>::BST()
	:root(nullptr) {}

template<class T>
inline BST<T>::~BST()
{
	while (root)
		remove(root->data);
}

template<class T>
inline typename BST<T>::Node* BST<T>::add(const T& thing)
{
	try {
		return addRecursive(thing, root);
	}
	catch (std::exception& e) {
		std::cout << "BST: " << e.what() << std::endl;
	}
}

template<class T>
inline void BST<T>::remove(const T& thing)
{
	removeRecursive(thing, root);
}

template<class T>
inline typename BST<T>::type_or_null BST<T>::find(const T& thing) const
{
	Node* found = findRecursive(thing, root);

	if (!found) return std::nullopt;
	else return found->data;
}

template<class T>
inline const T& BST<T>::min() const
{
	if (!root)
		throw std::logic_error("min of empty tree!");

	return minRecursive(root)->data;
}

template<class T>
inline const T& BST<T>::max() const
{
	if (!root)
		throw std::logic_error("max of empty tree!");

	return maxRecursive(root)->data;
}

template<class T>
inline void BST<T>::print() const
{
	printInOrder(root);
	std::cout << std::endl;
}

template<class T>
inline typename BST<T>::Node* BST<T>::addRecursive(const T& thing, Node*& start)
{
	if (!start) {
		start = new Node(thing);
		return start;
	}

	if (thing == start->data)
		throw std::logic_error("Dublicate elements!");
	else if (thing < start->data)
		addRecursive(thing, start->left);
	else
		addRecursive(thing, start->right);
}

template<class T>
inline typename BST<T>::Node* BST<T>::removeRecursive(const T& elem, Node*& node)
{
	if (!node) return node;

	bool isLeaf = !node->left && !node->right;
	bool hasOneChild = (node->left && !node->right) || (!node->left && node->right);

	if (node->data == elem) {

		if (isLeaf) {

			delete node;
			node = nullptr;
			return node;
		}
		else if (hasOneChild) {

			Node* onlyChild = node->left ? node->left : node->right;
			Node* toRemove = node;
			node = onlyChild;
			delete toRemove;
			return node;
		}
		else {

			Node* min = this->minRecursive(node->right);
			node->data = min->data;
			node->right = removeRecursive(min->data, node->right);
		}
	}
	else if (elem < node->data)
		return this->removeRecursive(elem, node->left);

	else
		return this->removeRecursive(elem, node->right);
}

template<class T>
inline typename BST<T>::Node*& BST<T>::findRecursive(const T& thing, Node* start) const
{
	if (!start) return start;

	if (thing == start->data) return start;
	else if (thing < start->data) return findRecursive(thing, start->left);
	else return findRecursive(thing, start->right);
}

template<class T>
inline typename BST<T>::Node*& BST<T>::minRecursive(Node* start) const
{
	if (start) {
		if (start->left)
			return minRecursive(start->left);

		return start;
	}
}

template<class T>
inline typename BST<T>::Node*& BST<T>::maxRecursive(Node* start) const
{
	if (start) {
		if (start->right)
			return maxRecursive(start->right);

		return start;
	}
}

template<class T>
inline void BST<T>::printInOrder(Node* start) const
{
	if (start) {
		printInOrder(start->left);
		std::cout << start->data << " ";
		printInOrder(start->right);
	}
}
