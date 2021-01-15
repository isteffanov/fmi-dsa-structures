#pragma once
#include <list>
#include <queue>
#include <stack>

template <class T>
class Tree {

public:
	struct Node {
		Node* parent;
		T data;
		std::list<Node*> children;

		bool visited;

	public:
		Node(Node* _parent, T _data)
			:parent(_parent), data(_data), visited(false) {}
	};

public:
	Tree();
	Tree(const Tree& other) = delete;
	const Tree& operator=(const Tree& other) = delete;
	~Tree();

	Node* add(const T& data, Node* parent = nullptr);
	void		remove(Node* node);
	const Node* find(const T& data) const;

	size_t		height() const;
	size_t		width() const;
	bool		balanced() const;
	size_t		weight() const;

	void		print() const;
	void		printLevel(size_t level) const;

private:
	Node* root;

	void	removeRecursive(Node* node);
	void	removeConnecting(Node* node);
	Node* findWrapper(const T& data, Node* start) const;

	size_t	heightRecursive(Node* node) const;
	size_t	widthRecursive(Node* node) const;
	bool	balancedRecursive(Node* node) const;
	size_t	weightRecursive(Node* node) const;
	void	printLevelRecursive(size_t level, Node* node) const;

	Node* bfs(const T& data, Node* start) const;
	Node* dfs(const T& data, Node* start) const;
};

template<class T>
inline Tree<T>::Tree()
	:root(nullptr) {}

template<class T>
inline Tree<T>::~Tree()
{
	if (root) removeRecursive(root);
}

template<class T>
inline typename Tree<T>::Node* Tree<T>::add(const T& data, Tree<T>::Node* parent)
{
	if (!parent) {
		root = new Node(nullptr, data);
		return root;
	}

	Node* newNode = new Node(parent, data);
	parent->children.push_front(newNode);
	return newNode;
}

template<class T>
inline void Tree<T>::remove(Node* node)
{
	removeConnecting(node);
}

template<class T>
inline void Tree<T>::removeRecursive(Node* node)
{
	if (!node) return;

	for (Node* child : node->children)
		removeRecursive(child);

	delete node;
}

template<class T>
inline void Tree<T>::removeConnecting(Node* node)
{
	if (!node) return;

	Node* parent = node->parent;
	parent->children.remove(node);

	//connecting node's parent to node's children
	for (Node* child : node->children) {
		child->parent = parent;
		parent->children.push_front(child);
	}

	delete node;
}

template<class T>
inline typename const Tree<T>::Node* Tree<T>::find(const T& data) const
{
	if (root) return findWrapper(data, root);
	throw std::logic_error("Tree: Tree is empty!");
}

template<class T>
inline typename Tree<T>::Node* Tree<T>::findWrapper(const T& data, Node* start) const
{
	return dfs(data, start);
}

template<class T>
inline size_t Tree<T>::height() const
{
	if (root) return heightRecursive(root);
	throw std::logic_error("Tree: Tree is empty!");
}

template<class T>
inline size_t Tree<T>::heightRecursive(Node* node) const
{
	size_t maxHeight = 0;
	for (Node* child : node->children) {
		size_t heightChild = heightRecursive(child);
		if (heightChild > maxHeight) maxHeight = heightChild;
	}

	return maxHeight + 1;
}

template<class T>
inline size_t Tree<T>::width() const
{
	if (root) return widthRecursive(root);
	throw std::logic_error("Tree: Tree is empty!");
}

template<class T>
inline size_t Tree<T>::widthRecursive(Node* node) const
{
	size_t curWidth = node->children.size();
	size_t childWidth = 0;

	for (Node* child : node->children)
		childWidth += widthRecursive(child);

	if (childWidth > curWidth) curWidth = childWidth;

	return curWidth;

}

template<class T>
inline void Tree<T>::print() const
{
	size_t treeHeight = height();
	for (int i = 0; i < treeHeight; ++i) {
		printLevel(i);
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

template<class T>
inline void Tree<T>::printLevel(size_t level) const
{
	if (root) printLevelRecursive(level, root);
	else throw std::logic_error("Tree: Tree is empty!");
}

template<class T>
inline void Tree<T>::printLevelRecursive(size_t level, Node* node) const
{
	if (level == 0) {
		std::cout << node->data << " ";
		return;
	}

	for (Node* child : node->children)
		printLevelRecursive(level - 1, child);
}

template<class T>
inline bool Tree<T>::balanced() const
{
	if (root) return balancedRecursive(root);
	throw std::logic_error("Tree: Tree is empty!");
}

template<class T>
inline bool Tree<T>::balancedRecursive(Node* node) const
{
	for (Node* child1 : node->children)
		for (Node* child2 : node->children)
			if (std::abs((int)(heightRecursive(child1) - heightRecursive(child2))) > 1)
				return false;

	return true;
}

template<class T>
inline size_t Tree<T>::weight() const
{
	if (root) return weightRecursive(root);
	throw std::logic_error("Tree: Tree is empty!");
}

template<class T>
inline size_t Tree<T>::weightRecursive(Node* node) const
{
	size_t sum = 0;
	for (Node* child : node->children)
		sum += weightRecursive(child);

	return sum + 1;
}

template<class T>
inline typename Tree<T>::Node* Tree<T>::bfs(const T& data, Node* start) const
{
	std::queue<Node*> wave;

	wave.push(start);

	while (!wave.empty()) {
		Node* cur = wave.front();
		wave.pop();

		if (cur->data == data) return cur;

		cur->visited = true;

		for (Node* child : cur->children)
			if (!child->visited) wave.push(child);
	}
}

template<class T>
inline typename Tree<T>::Node* Tree<T>::dfs(const T& data, Node* start) const
{
	if (start->data == data) return start;

	start->visited = true;
	for (Node* child : start->children) {
		if (!child->visited) {
			Node* depth = dfs(data, child);
			if (depth) return depth;
		}
	}

	return nullptr;
}

int main() {

	Tree<int> tree;
	Tree<int>::Node* root = tree.add(10);
	Tree<int>::Node* node5 = tree.add(5, root);
	Tree<int>::Node* node15 = tree.add(15, root);
	Tree<int>::Node* node20 = tree.add(20, root);

	tree.add(1, node5);
	tree.add(2, node5);
	tree.add(30, node5);
	tree.add(4, node5);
	tree.add(6, node20);
	tree.add(7, node20);
	tree.add(6, node15);
	
	tree.print();
	std::cout << "Height:	" << tree.height() << std::endl;
	std::cout << "Width:	" << tree.width() << std::endl;
	std::cout << "Balanced: " << std::boolalpha << tree.balanced() << std::endl;
	std::cout << "Weigth:	" << tree.weight() << std::endl;

	return 0;
}
