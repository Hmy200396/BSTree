#pragma once
template<class K>
struct BSTreeNode
{
	BSTreeNode<K>* _left;
	BSTreeNode<K>* _right;
	K _key;
	BSTreeNode(const K& key)
		:_left(nullptr)
		,_right(nullptr)
		,_key(key)
	{}
};
template<class K>
class BSTree
{
	typedef BSTreeNode<K> Node;
public:
	/*BSTree()
		:_root(nullptr)
	{}*/
	BSTree() = default;//指定强制生成默认构造
	BSTree(const BSTree<K>& t)
	{
		_root = Copy(t._root);
	}
	BSTree& operator=(const BSTree t)
	{
		std::swap(_root, t._root);
		return *this;
	}
	~BSTree();
	bool Insert(const K& key);
	void InOrder();
	void _InOrder(Node* root); 
	bool Find(const K& key);
	bool Erase(const K& key);
	bool FindR(const K& key);
	bool InsertR(const K& key);
	bool EraseR(const K& key);
protected:
	bool _FindR(Node* root, const K& key);
	bool _InsertR(Node*& root, const K& key); 
	bool _EraseR(Node*& root, const K& key);
	void Destroy(Node* root);
	Node* Copy(Node* root);
private:
	Node* _root = nullptr;
};

template<class K>
bool BSTree<K>::Insert(const K& key)
{
	if (_root == nullptr)
	{
		_root = new Node(key);
		return true;
	}
	Node* parent = nullptr;
	Node* cur = _root;
	while (cur)
	{
		if (cur->_key < key)
		{
			parent = cur;
			cur = cur->_right;
		}
		else if (cur->_key > key)
		{
			parent = cur; 
			cur = cur->_left;
		}
		else
		{
			return false;
		}
	}
	cur = new Node(key);
	if (parent->_key < key)
		parent->_right = cur;
	else
		parent->_left = cur;
	return true;
}
template<class K>
void BSTree<K>::InOrder()
{
	_InOrder(_root);
}
template<class K>
void BSTree<K>::_InOrder(Node* root)
{
	if (root == nullptr)
		return;
	_InOrder(root->_left);
	cout << root->_key << " ";
	_InOrder(root->_right);	
}

template<class K>
bool BSTree<K>::Find(const K& key)
{
	Node* cur = _root;
	while (cur)
	{
		if (cur->_key < key)
		{
			cur = cur->_right;
		}
		else if(cur->_key < key)
		{
			cur = cur->_left;
		}
		else
			return true;
	}
	return false;
}

template<class K>
bool BSTree<K>::Erase(const K& key)
{
	Node* parent = nullptr;
	Node* cur = _root;
	while (cur)
	{
		if (cur->_key < key)
		{
			parent = cur;
			cur = cur->_right;
		}
		else if (cur->_key > key)
		{
			parent = cur;
			cur = cur->_left;
		}
		else
		{
			//删除
			//1.左为空
			if (cur->_left == nullptr)
			{
				if (parent == nullptr)
					_root = cur->_right;
				else
				{
					if (parent->_left == cur)
						parent->_left = cur->_right;
					else
						parent->_right = cur->_right;
				}
				delete cur;
			}//2.右为空
			else if (cur->_right == nullptr)
			{
				if (parent == nullptr)
					_root = cur->_left;
				else
				{
					if (parent->_left == cur)
						parent->_left = cur->_left;
					else
						parent->_right = cur->_left;
				}
				delete cur;
			}
			else
			{
				//找右树最小节点替代，也可以是左树最大节点替代
				Node* pminRight = cur;
				Node* minRight = cur->_right;  
				while (minRight->_left != nullptr)
				{
					pminRight = minRight;
					minRight = minRight->_left;
				}
				cur->_key = minRight->_key;
				if(pminRight==cur)
					pminRight->_right = minRight->_right;
				else
					pminRight->_left = minRight->_right;

				delete minRight;
			}
			return true;
		}
	}
	return false;
}
template<class K>
bool BSTree<K>::FindR(const K& key)
{
	return _FindR(_root, key);
}
template<class K>
bool BSTree<K>::_FindR(Node* root, const K& key)
{
	if (root == nullptr)
		return false;
	if (root->_key == key)
		return true;
	if (root->_key < key)
		return _FindR(root->_right, key);
	else
		return _FindR(root->_left, key);
}
template<class K>
bool BSTree<K>::InsertR(const K& key)
{
	return _InsertR(_root, key);
}
template<class K>
bool BSTree<K>::_InsertR(Node*& root, const K& key)
{
	if (root == nullptr)
	{
		root = new Node(key);
		return true;
	}
	if (root->_key < key)
		return _InsertR(root->_right, key);
	else if (root->_key > key)
		return _InsertR(root->_left, key);
	else
		return false;
}
template<class K>
bool BSTree<K>::EraseR(const K& key)
{
	return _EraseR(_root, key);
}
template<class K>
bool BSTree<K>::_EraseR(Node*& root, const K& key)
{
	if (root == nullptr)
		return false;
	if (root->_key < key)
		return _EraseR(root->_right, key);
	else if (root->_key > key)
		return _EraseR(root->_left, key);
	else
	{
		Node* del = root;
		if (root->_left == nullptr)
		{
			root = root->_right;
		}
		else if (root->_right == nullptr)
		{
			root = root->_left;
		}
		else
		{
			Node* maxleft = root->_left;
			while (maxleft->_right != nullptr)
			{
				maxleft = maxleft->_right;
			}
			root->_key = maxleft->_key;
			return _EraseR(root->_left, root->_key);//转换成在子树去删除
		}
		delete del;
		return true;
	}
}
template<class K>
BSTree<K>::~BSTree()
{
	Destroy(_root);
	_root = nullptr;
}
template<class K>
void BSTree<K>::Destroy(Node* root)
{
	if (root == nullptr)
		return;
	Destroy(root->_left);
	Destroy(root->_right);
	delete root;
}
template<class K>
typename BSTree<K>::Node* BSTree<K>::Copy(Node* root)
{
	if (root == nullptr)
		return nullptr;
	Node* newRoot = new Node(root->_key);
	newRoot->_left = Copy(root->_left);
	newRoot->_right = Copy(root->_right);
	return newRoot;
}