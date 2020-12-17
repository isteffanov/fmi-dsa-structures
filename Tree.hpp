#pragma once
#include <forward_list>

template <class T>
class Tree {

public:
	struct Node {
	private:
		Node* parent;
		T data;
		std::forward_list<Node*> children;

		friend class Tree;
	public:
		Node(Node* _parent, T _data)
			:parent(_parent), data(_data),
			children(std::forward_list<Node*>()) {}
	};

private:
	Node* root;

	const Tree<T>::Node* findWrapper(const T& data, const Node* start) const;
public:
	Tree();
	~Tree();

	Tree<T>::Node* add(const T& data, Node* parent = nullptr);
	void remove(Node* node);
	const Tree<T>::Node* find(const T& data) const;
};

template<class T>
inline Tree<T>::Tree()
	:root(nullptr) {}

template<class T>
inline Tree<T>::~Tree()
{
	if(root) remove(root);
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
	for (Node* child : node->children)
		remove(child);

	delete node;
}

template<class T>
inline typename const Tree<T>::Node* Tree<T>::find(const T& data) const
{
	return this->findWrapper(data, root);
}

template<class T>
inline typename const Tree<T>::Node* Tree<T>::findWrapper(const T& data, const Node* start) const
{
	for (const Node* child : start->children) 
		if (child->data == data) return child;
	
	if (start == root) return nullptr;
}
