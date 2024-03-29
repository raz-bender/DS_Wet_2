#ifndef Tree_Node_H
#define Tree_Node_H

template<class Key, class Data>
class TreeNode
{
public:
	explicit TreeNode(const Key& , const Data&);
	~TreeNode() = default;
	int getBF() const;
	TreeNode* roll();
    Data& getData();
	const Key& getKey()const;
	const int getExtraNumOfWins()const;
	const int getTeamNumOfWins() const;
	const int getSubTreeSize()const;
	const int getSubTreeMaxRank()const;
	void setData(const Data&);
	void setExtraNumOfWins(const int);
	void setTeamNumOfWins(const int teamNumOfWins);
	void setSubTreeSize(const int);
	void setSubTreeMaxRank(const int);
	void setKey(const Key&);
	int getHeight()const;
	void setHeight(int);
	void updateHeight();
	void deleteData();


	TreeNode* m_left;
	TreeNode* m_right;
	TreeNode* m_parent;

private:
	Key m_key;
	Data m_data;
	int m_height;
	int m_teamNumOfWins;
	int m_extraExtraNumOfWins;
	int m_subTreeSize;
	int m_subTreeMaxRank;

	TreeNode* rollLL(TreeNode* node);
	TreeNode* rollLR(TreeNode* node);
	TreeNode* rollRL(TreeNode* node);
	TreeNode* rollRR(TreeNode* node);
};

template<class Key, class Data>
TreeNode<Key, Data>::TreeNode(const Key& key, const Data& data)
{
	m_key = key;
	m_data = data;
	m_right = nullptr;
	m_left = nullptr;
	m_parent = nullptr;
	m_height = 0;
	m_teamNumOfWins = 0;
	m_extraExtraNumOfWins = 0;
	m_subTreeSize = 0;
	m_subTreeMaxRank = 0;
}

template<class Key, class Data>
int TreeNode<Key, Data>::TreeNode::getBF() const
{
	if (!this->m_right && !this->m_left)
		return 0;
	else if(!this->m_right || !this->m_left)
		return this->m_left ? this->m_left->getHeight() + 1 : -this->m_right->getHeight() -1;
	return this->m_left->getHeight() - this->m_right->getHeight();
}

template<class Key, class Data>
 Data& TreeNode<Key, Data>::getData()
{
	return this->m_data;
}

template<class Key, class Data>
const Key& TreeNode<Key, Data>::getKey()const
{
	return this->m_key;
}

template<class Key, class Data>
void TreeNode<Key, Data>::setData(const Data& data)
{
	m_data = data;
}

template<class Key, class Data>
const int TreeNode<Key, Data>::getExtraNumOfWins()const
{
	return this->m_extraExtraNumOfWins;
}

template<class Key, class Data>
const int TreeNode<Key, Data>::getTeamNumOfWins()const
{
	return this->m_teamNumOfWins;
}

template<class Key, class Data>
const int TreeNode<Key, Data>::getSubTreeSize() const
{
	return m_subTreeSize;
}

template<class Key, class Data>
const int TreeNode<Key, Data>::getSubTreeMaxRank() const
{
	return m_subTreeMaxRank;
}

template<class Key, class Data>
void TreeNode<Key, Data>::setExtraNumOfWins(const int ExtraNumOfWins)
{
	m_extraExtraNumOfWins = ExtraNumOfWins;
}

template<class Key, class Data>
void TreeNode<Key, Data>::setTeamNumOfWins(const int teamNumOfWins)
{
	m_teamNumOfWins = teamNumOfWins;
}

template<class Key, class Data>
inline void TreeNode<Key, Data>::setSubTreeSize(const int size)
{
	m_subTreeSize = size;
}

template<class Key, class Data>
void TreeNode<Key, Data>::setSubTreeMaxRank(const int rank)
{
	m_subTreeMaxRank = rank;
}

template<class Key, class Data>
void TreeNode<Key, Data>::setKey(const Key& key)
{
	m_key = key;
}

template<class Key, class Data>
int TreeNode<Key, Data>::getHeight()const
{
	return this->m_height;
}

template<class Key, class Data>
void TreeNode<Key, Data>::setHeight(int height)
{
	this->m_height = height;
}

template<class Key, class Data>
void TreeNode<Key, Data>::deleteData()
{
	delete m_data;
}

//Rolls
template<class Key, class Data>
TreeNode<Key, Data>* TreeNode<Key, Data>::roll()
{
	if (this->getBF() == 2)
		return this->m_left->getBF() > -1 ? rollLL(this) : rollLR(this);
	else
		return  this->m_right->getBF() < 1 ? rollRR(this) : rollRL(this);
}
template<class Key, class Data>
TreeNode<Key, Data>* TreeNode<Key, Data>::rollLL(TreeNode* node)
{
	TreeNode* newRoot = node->m_left;

	//update sub tree size
	int newRootSubSize = (newRoot->m_right ? newRoot->m_right->getSubTreeSize() : 0) + (node->m_right ? node->m_right->getSubTreeSize() : 0) + 1;
	int oldRootSubSize = newRootSubSize + (newRoot->m_left ? newRoot->m_left->getSubTreeSize() : 0) + 1;
	node->setSubTreeSize(newRootSubSize);
	newRoot->setSubTreeSize(oldRootSubSize);

	//update value
	int newRootValue = newRoot->getExtraNumOfWins() + node->getExtraNumOfWins();
	int oldRootValue = node->getExtraNumOfWins() - newRootValue;

	if (newRoot->m_right)
	{
		newRoot->m_right->setExtraNumOfWins(newRoot->m_right->getExtraNumOfWins() + newRoot->getExtraNumOfWins());
		newRoot->m_right->updateHeight();
	}

	node->setExtraNumOfWins(oldRootValue);
	newRoot->setExtraNumOfWins(newRootValue);

	//update max strength
	int oldRooteMaxRank = std::max(std::max((node->m_left ? node->m_left->getSubTreeMaxRank() : 0),
		(newRoot->m_left ? newRoot->m_left->getSubTreeMaxRank() : 0)), (node->m_key > 0 ? (node->m_key + node->m_teamNumOfWins):0)) + oldRootValue;
	int newRooteMaxRank = std::max(std::max((newRoot->m_right ? newRoot->m_right->getSubTreeMaxRank() : 0),
		oldRooteMaxRank), (newRoot->m_key > 0 ? (newRoot->m_key + newRoot->m_teamNumOfWins):0)) + newRootValue;

	node->setSubTreeMaxRank(oldRooteMaxRank);
	newRoot->setSubTreeMaxRank(newRooteMaxRank);

	node->m_left = newRoot->m_right;
	if (newRoot->m_right)
		newRoot->m_right->m_parent = node;
	newRoot->m_right = node;
	newRoot->m_parent = node->m_parent;
	node->m_parent = newRoot;

	if (newRoot->m_parent != nullptr)
	{
		newRoot->m_parent->m_right = newRoot->m_parent->m_right == node ? newRoot : newRoot->m_parent->m_right;
		newRoot->m_parent->m_left = newRoot->m_parent->m_left == node ? newRoot : newRoot->m_parent->m_left;
	}

	node = newRoot;

	if(node->m_left)
		node->m_left->updateHeight();
	if(node->m_right)
		node->m_right->updateHeight();
	if(node)
		node->updateHeight();
	if(node->m_parent)
		node->m_parent->updateHeight();

	return node;

}
template<class Key, class Data>
TreeNode<Key, Data>* TreeNode<Key, Data>::rollLR(TreeNode* node)
{
	node->m_left = rollRR(node->m_left);
	return rollLL(node);
}
template<class Key, class Data>
TreeNode<Key, Data>* TreeNode<Key, Data>::rollRL(TreeNode* node)
{
	node->m_right = rollLL(node->m_right);
	return rollRR(node);
}
template<class Key, class Data>
TreeNode<Key, Data>* TreeNode<Key, Data>::rollRR(TreeNode* node)
{
	TreeNode* newRoot = node->m_right;

	//update sub tree size
	int newRootSubSize = (newRoot->m_left ? newRoot->m_left->getSubTreeSize() : 0) + (node->m_left ? node->m_left->getSubTreeSize() : 0) +  1;
	int oldRootSubSize = newRootSubSize + (newRoot->m_right ? newRoot->m_right->getSubTreeSize() : 0) +  1;
	node->setSubTreeSize(newRootSubSize);
	newRoot->setSubTreeSize(oldRootSubSize);

	//update value
	int newRootValue = newRoot->getExtraNumOfWins() + node->getExtraNumOfWins();
	int oldRootValue = node->getExtraNumOfWins() - newRootValue;

	if (newRoot->m_left)
	{
		newRoot->m_left->setExtraNumOfWins(newRoot->m_left->getExtraNumOfWins() + newRoot->getExtraNumOfWins());
		newRoot->m_left->updateHeight();
	}

	node->setExtraNumOfWins(oldRootValue);
	newRoot->setExtraNumOfWins(newRootValue);

	//update max strength
	int oldRooteMaxRank = std::max(std::max((node->m_right ? node->m_right->getSubTreeMaxRank() : 0),
		(newRoot->m_right ? newRoot->m_right->getSubTreeMaxRank() : 0)), (node->m_key>0?(node->m_key + node->m_teamNumOfWins):0)) + oldRootValue;
	int newRooteMaxRank = std::max(std::max((newRoot->m_left ? newRoot->m_left->getSubTreeMaxRank() : 0),
		oldRooteMaxRank), (newRoot->m_key>0?(newRoot->m_key + newRoot->m_teamNumOfWins):0)) + newRootValue;

	node->setSubTreeMaxRank(oldRooteMaxRank);
	newRoot->setSubTreeMaxRank(newRooteMaxRank);

	node->m_right = newRoot->m_left;
	if (newRoot->m_left)
		newRoot->m_left->m_parent = node;
	newRoot->m_left = node;
	newRoot->m_parent = node->m_parent;
	node->m_parent = newRoot;

	if (newRoot->m_parent != nullptr)
	{
		newRoot->m_parent->m_right = newRoot->m_parent->m_right == node ? newRoot : newRoot->m_parent->m_right;
		newRoot->m_parent->m_left = newRoot->m_parent->m_left == node ? newRoot : newRoot->m_parent->m_left;
	}

	node = newRoot;

	if (node->m_left)
		node->m_left->updateHeight();
	if (node->m_right)
		node->m_right->updateHeight();
	if (node)
		node->updateHeight();
	if (node->m_parent)
		node->m_parent->updateHeight();

	return node;
}

template<class Key, class Data>
void TreeNode<Key, Data>::updateHeight()
{
	if (!this->m_right && !this->m_left)
		this->m_height = 0;
	else if (!this->m_right || !this->m_left)
		this->m_height =  this->m_left ? this->m_left->m_height + 1 : this->m_right->m_height + 1;
	else
		this->m_height = std::max(this->m_right->m_height, this->m_left->m_height) + 1;


	int curNodeRank = (m_right ? m_right->getSubTreeSize() : 0) + (m_left ? m_left->getSubTreeSize() : 0) + 1;
	this->setSubTreeSize(curNodeRank);

	int curNodeMaxRank = std::max(std::max((m_right ? m_right->getSubTreeMaxRank() : 0), (m_left ? m_left->getSubTreeMaxRank() : 0)), (m_key > 0 ?  (m_key + m_teamNumOfWins):0)) + m_extraExtraNumOfWins;
	this->setSubTreeMaxRank(curNodeMaxRank);
}
#endif