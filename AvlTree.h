#ifndef Avl_Tree_H
#define Avl_Tree_H
#include <math.h>
#include <iostream>
#include "TreeNode.h"

using namespace std;

template <class Key, class Data>
class AvlTree
{
	typedef TreeNode<Key, Data> Node;

public:
	AvlTree();
	~AvlTree();

	Node* find(const Key& key, const Data& data = NULL);
	//Node* findWithData(const Key& key, const Data & data);
    bool insert(const Key& key, const Data& data, bool enableDulications = false);
	void remove(const Key& key, const Data& data = NULL);
	//void removeWithData(const Key& key, const Data& data);
	int getSize();
    void setSize(int size);
    void setValueToNodes(Node* startNode, Node* endNode, int value);//in order to add value to the nodes between start and end (inclueded)
    void setValueToNodesAux(Node* node, Node* curNode, int value, bool goRight);
    void deleteTreeData(Node* node);

    Node* getRoot(){
        return this->m_root;
    }

	Node* getMaxNode();
	Node* getMinNode();
	void printBinaryTree(int depth = 0, char prefix = '-');
	void printBinaryTreeAux(Node* root, int depth = 0, char prefix = '-');


	Node* getNextNode(Node* node, Node* prevNode = nullptr, bool goRight = true);
	Node* getPrevNode(Node* node, Node* prevNode = nullptr, bool goLeft = true);

	int getNodeRank(Node* node);
	int getNodeCalculatedValue(Node* node);

private:
	Node* m_root;
	int m_size;

	void deleteTree(Node* node);
	Node* findAux(Node* root, const Key& key, const Data& data = NULL) ;
	//Node* findAuxWithData(Node* root, const Key& key, const Data& data) ;
	Node* insertAux(const Key& key, const Data& data, Node* curNode, Node* parent, Node* newNode, bool enableDuplications = false, int reduceValue =0);
	Node* removeAux(Node* curNode);

};

template<class Key, class Data>
void AvlTree<Key, Data>::setSize(int size) {
    this->m_size = size;
}

template<class Key, class Data>
void AvlTree<Key, Data>::setValueToNodes(Node* startNode, Node* endNode, int value)
{
	setValueToNodesAux(startNode, m_root, value, false);
	if(Node* prev = getPrevNode(endNode))
		setValueToNodesAux(prev, m_root, -value, false);	
}

template<class Key, class Data>
void AvlTree<Key, Data>::setValueToNodesAux(Node* node, Node* curNode, int value, bool prevRight)
{
	if (curNode == node)
	{
		if (!prevRight)
			curNode->setValue(curNode->getValue() + value);
		if(curNode->m_right)
			curNode->m_right->setValue(curNode->m_right->getValue() - value);
	}
	//go left 
	else if (curNode->getKey() > node->getKey() || (curNode->getKey() == node->getKey() && curNode->getData() > node->getData()))
	{
		if(prevRight)
			curNode->setValue(curNode->getValue() - value);

		setValueToNodesAux(node, curNode->m_left, value, false);
	}
	//go right
	else
	{
		if(!prevRight)
			curNode->setValue(curNode->getValue() + value);
		setValueToNodesAux(node, curNode->m_right, value, true);
	}
}

template <class Key, class Data>
AvlTree<Key, Data>::AvlTree(){
	m_size = 0;
	m_root = nullptr;
}

template <class Key, class Data>
AvlTree<Key, Data>::~AvlTree() { deleteTree(m_root); }

template <class Key, class Data>
void AvlTree<Key, Data>::deleteTree(Node* node)
{
	if (node == nullptr)
		return ;
	deleteTree(node->m_left);
	deleteTree(node->m_right);
	delete node;
}

template <class Key, class Data>
void AvlTree<Key, Data>::deleteTreeData(Node* node)
{
	if (node == nullptr)
		return;

	deleteTreeData(node->m_left);
	deleteTreeData(node->m_right);
	node->deleteData();
}


template <class Key, class Data>
int AvlTree<Key, Data>::getSize()
{
	return m_size;
}

template <class Key, class Data>
typename AvlTree<Key, Data>::Node* AvlTree<Key, Data>::find(const Key& key, const Data& data)
{
	//Use data in case you allow key duplications and then you need to check that data is equal as well
	return findAux(m_root, key, data);
}

//template <class Key, class Data>
//typename AvlTree<Key, Data>::Node* AvlTree<Key, Data>::findWithData(const Key& key, const Data& data)
//{
//	//Use data in case you allow key duplications and then you need to check that data is equal as well
//	return findAuxWithData(m_root, key, data);
//}

template <class Key, class Data>
typename AvlTree<Key, Data>::Node* AvlTree<Key, Data>::findAux(Node* root, const Key& key, const Data& data)
{
	if (root == nullptr)
		return nullptr;
	if (root->getKey() == key)
	{
		if(data==NULL || root->getData() == data)
			return root;
		else
			return root->getData() > data ? findAux(root->m_left, key, data) : findAux(root->m_right, key, data);
	}
	else
		return root->getKey() > key ? findAux(root->m_left, key, data) : findAux(root->m_right, key, data);
}

//template <class Key, class Data>
//typename AvlTree<Key, Data>::Node* AvlTree<Key, Data>::findAuxWithData(Node* root, const Key& key, const Data& data)
//{
//	if (root == nullptr)
//		return nullptr;
//	if (root->getKey() == key &&  root->getData() == data)//checkData is NULL by default
//		return root;
//	if (root->getKey() == key)
//		return root->getData() > data ? findAuxWithData(root->m_left, key, data) : findAuxWithData(root->m_right, key, data);
//	else
//		return root->getKey() > key ? findAuxWithData(root->m_left, key, data) : findAuxWithData(root->m_right, key, data);
//}

template <class Key, class Data>
bool AvlTree<Key, Data>::insert(const Key& key, const Data& data, bool enableDuplications)//put this function under try catch
{
	if (!enableDuplications && find(key, data))
		return false;

	Node* newNode = new Node(key, data);
	m_root = insertAux(key, data, m_root, nullptr, newNode, enableDuplications);
	m_size++;
	return true;;
}

template <class Key, class Data>
typename AvlTree<Key, Data>::Node* AvlTree<Key, Data>::insertAux(const Key& key, const Data& data, Node* curNode, Node* parent, Node* newNode, bool enableDuplications, int reduceValue)
{
	if (!curNode)
	{
		curNode = newNode;
		curNode->m_parent = parent;
		curNode->setSubTreeSize(1);
		curNode->setValue(-reduceValue);
	}
	else
	{
		reduceValue += curNode->getValue();

		if (curNode->getKey() == key)
		{
			if (curNode->getData() > data)
				curNode->m_left = insertAux(key, data, curNode->m_left, curNode, newNode, enableDuplications, reduceValue);
			else
				curNode->m_right = insertAux(key, data, curNode->m_right, curNode, newNode, enableDuplications, reduceValue);

		}
		else if (curNode->getKey() > key)
			curNode->m_left = insertAux(key, data, curNode->m_left, curNode, newNode, enableDuplications, reduceValue);
		else
			curNode->m_right = insertAux(key, data, curNode->m_right, curNode, newNode, enableDuplications, reduceValue);


		int curNodeRank = (curNode->m_right ? curNode->m_right->getSubTreeSize() : 0) + (curNode->m_left ? curNode->m_left->getSubTreeSize() : 0) + 1;
		curNode->setSubTreeSize(curNodeRank);
		

		if (abs(curNode->getBF()) > 1)
		{
			curNode = curNode->roll();
		}
	}

	curNode->updateHeight();
	return curNode;
}

template <class Key, class Data>
void AvlTree<Key, Data>::remove(const Key& key, const Data& data)
{
	Node* node = find(key, data);
	if (!node)
		return;

	node = removeAux(node);
	if (node)
	{
		node->updateHeight();
		while (node)
		{
			node->updateHeight();
			if (abs(node->getBF()) > 1)
				node = node->roll();
			if (!node->m_parent)
				m_root = node;
			node = node->m_parent;
		}
	}
	m_size--;
}

//template <class Key, class Data>
//void AvlTree<Key, Data>::removeWithData(const Key& key, const Data& data)
//{
//	Node* node = findWithData(key, data);
//	if (!node)
//		return;
//
//	node = removeAux(node);
//	if (node)
//	{
//		node->updateHeight();
//		while (node)
//		{
//			node->updateHeight();
//			if (abs(node->getBF()) > 1)
//				node = node->roll();
//			if (!node->m_parent)
//				m_root = node;
//			node = node->m_parent;
//		}
//	}
//	m_size--;
//}

template <class Key, class Data>
typename AvlTree<Key, Data>::Node* AvlTree<Key, Data>::removeAux(Node* curNode)
{
	//removal from binary tree
	if (!curNode)
		return curNode;

	//if the node has maximum one child
	if ((curNode->m_left == nullptr) || (curNode->m_right == nullptr))
	{
		Node* child = curNode->m_left ? curNode->m_left : curNode->m_right;


		if (curNode == m_root)
		{
			m_root = child;
			if(child)
				child->m_parent = nullptr;
		}

		else if (curNode->m_parent)//if the node to be deleted is a child
		{
			if (curNode->m_parent->m_left == curNode)
			{
				if (child)
					child->m_parent = curNode->m_parent;
				curNode->m_parent->m_left = child;
			}
			else
			{
				if (child)
					child->m_parent = curNode->m_parent;
				curNode->m_parent->m_right = child;
			}

		}
		Node* parent = curNode->m_parent;
		delete curNode;
		return parent;
	}
	else
	{
		// node with two children: Get the inorder 
		// successor (smallest in the right subtree) 
		Node* nextNode = getNextNode(curNode, curNode, true);

		// Copy the inorder successor's 
		// data to this node 
		curNode->setKey(nextNode->getKey());
		curNode->setData(nextNode->getData());

		// Delete the inorder successor 
		return removeAux(nextNode);
	}

}

template <class Key, class Data>
typename AvlTree<Key, Data>::Node* AvlTree<Key, Data>::getNextNode(Node* node, Node* prevNode, bool goRight)
{
	//has right son
	if (goRight && node->m_right && node->m_right != prevNode)
	{
		return getNextNode(node->m_right, node, false);
	}
	else if (!goRight)
	{
		while (node->m_left)
		{
			node = node->m_left;
		}
		return node;
	}
	//in case of a root
	else if (node == m_root)
		return nullptr;
	//is a left son
	else if (node && node->m_parent->m_left == node)
		return node->m_parent;

	//is a right son
	else if (node && node->m_parent->m_right == node)
		return getNextNode(node->m_parent, node, goRight);

	else
		return nullptr;
}

template <class Key, class Data>
typename AvlTree<Key, Data>::Node* AvlTree<Key, Data>::getPrevNode(Node* node, Node* prevNode , bool goLeft)
{
	//has left son
	if (goLeft && node->m_left && node->m_left != prevNode)
	{
		return getPrevNode(node->m_left, node, false);
	}
	else if (!goLeft)
	{
		while (node->m_right)
		{
			node = node->m_right;
		}
		return node;
	}
	//in case of a root
	else if (node == m_root)
		return nullptr;
	//is a left son
	else if (node && node->m_parent->m_right == node)
		return node->m_parent;

	//is a right son
	else if (node && node->m_parent->m_left == node)
		return getPrevNode(node->m_parent, node, goLeft);

	else
		return nullptr;
}

template<class Key, class Data>
int AvlTree<Key, Data>::getNodeRank(Node* node)
{
	Node* temp = m_root;
	int counter = 0;
	while (temp != node)
	{
		//go left 
		if (temp->getKey() > node->getKey() || (temp->getKey() == node->getKey() && temp->getData() > node->getData()))
		{
			temp =   temp->m_left;
		}
		//go right
		else
		{
			counter += temp->m_left ? (temp->m_left->getSubTreeSize() + 1) : 1;
			temp = temp->m_right;
		}
	} 
	
	counter += node->m_left ? (node->m_left->getSubTreeSize() + 1) : 1;
	return counter;
}

template<class Key, class Data>
int AvlTree<Key, Data>::getNodeCalculatedValue(Node* node)
{
	Node* temp = m_root;
	int counter = 0;
	while (temp != node)
	{
		counter += temp->getValue();

		//go left 
		if (temp->getKey() > node->getKey() || (temp->getKey() == node->getKey() && temp->getData() > node->getData()))
		{
			temp = temp->m_left;
		}
		//go right
		else
		{
			temp = temp->m_right;
		}
	}

	counter += temp->getValue();
	return counter;
}

template <class Key, class Data>
typename AvlTree<Key, Data>::Node* AvlTree<Key, Data>::getMaxNode()
{
	Node* temp = m_root;
	if (!temp)
		return nullptr;
	while (temp->m_right)
		temp = temp->m_right;
	return temp;
}

template <class Key, class Data>
typename AvlTree<Key, Data>::Node* AvlTree<Key, Data>::getMinNode()
{
	Node* temp = m_root;
	if (!temp)
		return nullptr;
	while (temp->m_left)
		temp = temp->m_left;
	return temp;
}

template <class Key, class Data>
void AvlTree<Key, Data>::printBinaryTree(int depth , char prefix ) {
	printBinaryTreeAux(this->m_root, depth, prefix);
    cout << "\n ------------------ \n";
}

template <class Key, class Data>
void AvlTree<Key, Data>::printBinaryTreeAux(Node* root, int depth, char prefix) {
	if (root == nullptr)
		return;

	printBinaryTreeAux(root->m_right, depth + 1, '+');

	for (int i = 0; i < depth; i++) {
		std::cout << "   ";
	}

	std::cout << prefix << root->getKey() << std::endl;

	printBinaryTreeAux(root->m_left, depth + 1, '|');
}



#endif