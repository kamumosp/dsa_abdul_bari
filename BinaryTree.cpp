#include <iostream>
#include <cstdint>
#include <stack>
#include <queue>
#include <list>
#include <vector>
#include <array>

using namespace std;

#define	NA (INT_MIN)

typedef enum {_PRE_ORDER_, _POST_ORDER_}eOrder;

struct Node
{
	int data;
	Node *left;
	Node *right;
	
	Node() : data(0), left(NULL), right(NULL) {};
	Node (int _data=0, Node *_left=NULL, Node *_right=NULL)
			: data(_data), left(_left), right(_right) {};
	~Node(){};
};

class BinaryTree
{
	Node *root;
	
public:
	BinaryTree () : root(NULL){};
	BinaryTree (int *arr, int numNodes);
	BinaryTree (int *inorder, int *order, eOrder eOrderTtype, int size);

	~BinaryTree () {
		deleteTree(root);
		root = NULL;
	}
	
	void PreOrder();
	void InOrder();
	void PostOrder();

	void LevelOrder();
	
	void PreOrderIter();
	void InOrderIter();
	void PostOrderIter();
	
	int CountNodes();
	int CountLeafNodes();
	int CountNonLeafNodes();
	int CountDeg1Nodes();
	int CountDeg2Nodes();

	int Height();
	
	int Sum();
	
private:
	
	void deleteTree(Node* p);
	
	void PreOrder(Node* p);
	void InOrder(Node* p);
	void PostOrder(Node* p);

	int CountNodes(Node* p);
	int CountLeafNodes(Node* p);
	int CountNonLeafNodes(Node* p);
	int CountDeg1Nodes(Node* p);
	int CountDeg2Nodes(Node* p);

	int Height(Node* p);
	int Sum(Node* p);
	
	Node* BuildInorderPreorder(int *inorder, int *preorder, 
								int start, int end, int *preIndex);

	Node* BuildInorderPostorder(int *inorder, int *preorder, 
								int start, int end, int *postIndex);
};

BinaryTree::BinaryTree (int *arr, int numNodes)
	: root(NULL)
{
	queue<Node*> mq;
	Node *tmp = NULL;
	
	for (int i = 0; i < numNodes; i++)
	{
		tmp = NULL;
		if (NA == arr[i])
		{
//			Node *p = mq.front();
			if (!(i & 1))	// i is even now
			{
				// clear its parent node from queue
//				if (p)
//					cout << "right node is not present for " << p->data << endl;
				mq.pop();
			}
			else{
//				if (p)
//					cout << "left node is not present for " << p->data << endl;
			}
			
			mq.push(tmp);
			
			continue;	// this node is not present
		}
		
		tmp = new Node(arr[i]);
		if (mq.empty())	// also root is null now
		{
			root = tmp;
//			cout << "root node : " << tmp->data << endl;
		}
		else
		{
			Node *p = mq.front();
			if (!p) {
				// should not happen. check your input. might have missed any NA
				cout << "error..., check input data. might have missed NA's" << endl;
			}
			
			if (i & 1)	//	this is left node
			{
				p->left = tmp;
//				cout << "Adding left node : " << arr[i] << " for " << p->data << endl;
			}
			else {
				p->right = tmp;	//	this is right node
				mq.pop();
//				cout << "Adding right node : " << arr[i] << " for " << p->data << endl;
			}
		}
		
		mq.push(tmp);
	}
}

void BinaryTree::deleteTree(Node* p)
{
	if (!p)	return;
	deleteTree(p->left);
	deleteTree(p->right);
	p->left = p->right = NULL;
	delete p;
}

BinaryTree::BinaryTree (int *inorder, int *order, eOrder eOrderTtype, int size)
	: root(NULL)
{
	if (_PRE_ORDER_ == eOrderTtype) {
		int preorderIndex = 0;
		root = BuildInorderPreorder(inorder, order, 0, (size-1), &preorderIndex);
	}
	else {
		int postorderIndex = (size-1);
		root = BuildInorderPostorder(inorder, order, 0, (size-1), &postorderIndex);
	}
}

int getInorderIndex(int *inorder, int val, int start, int end)
{
	for (int i = start; i <= end; i++)
		if (val == inorder[i])
			return i;
	return -1;
}

Node* BinaryTree::BuildInorderPreorder (int *inorder, int *preorder, 
										int start, int end, int *preorderIndex)
{
	if (start > end)	return NULL;
	
	int val = preorder[*preorderIndex];
	(*preorderIndex)++;

	Node* node = new Node(val);
	if (start == end)	return node;
	
	int inorderIndex = getInorderIndex(inorder, val, start, end);
	
	node->left = BuildInorderPreorder(inorder, preorder, 
										start, (inorderIndex-1), preorderIndex);
	node->right = BuildInorderPreorder(inorder, preorder, 
										(inorderIndex+1), end, preorderIndex);
	
	return node;
}

Node* BinaryTree::BuildInorderPostorder (int *inorder, int *postorder, 
										 int start, int end, int *postorderIndex)
{
	if (start > end)	return NULL;
	
	int val = postorder[*postorderIndex];
	(*postorderIndex)--;
		
	Node* node = new Node(val);
	if (start == end)	return node;
	
	int inorderIndex = getInorderIndex(inorder, val, start, end);
	
	node->right = BuildInorderPostorder(inorder, postorder, 
										(inorderIndex+1), end, postorderIndex);
	node->left = BuildInorderPostorder(inorder, postorder, 
										start, (inorderIndex-1), postorderIndex);
	
	return node;
}

// DF - Depth First traversal methods
void BinaryTree::PreOrder()
{
	cout << "PreOrder   : [";
	PreOrder(root);
	cout << "]" << endl;
}

void BinaryTree::InOrder()
{
	cout << "InOrder    : [";
	InOrder(root);
	cout << "]" << endl;
}

void BinaryTree::PostOrder()
{
	cout << "PostOrder  : [";
	PostOrder(root);
	cout << "]" << endl;
}

// BF - Breadth First traversal method
// Level Order traversal using iterative(non-recursive) method
void BinaryTree::LevelOrder()
{
	cout << "LevelOrder : [";
	
	Node *p = root;
	queue<Node*> mq;
	
	if (!p)	return;
	
	cout << p->data << " ";
	mq.push(p);
	
	while(!mq.empty())
	{
		p = mq.front();
		mq.pop();
		
		if (p->left) {
			cout << p->left->data << " ";
			mq.push(p->left);
		}
		
		if (p->right) {
			cout << p->right->data << " ";
			mq.push(p->right);
		}
	}

	cout << "]" << endl;
}

// BF traversal methods using recursive method
void BinaryTree::PreOrder(Node* p)
{
	if (!p)	return;
	cout << p->data << " ";
	PreOrder(p->left);
	PreOrder(p->right);
}

void BinaryTree::InOrder(Node* p)
{
	if (!p)	return;
	InOrder(p->left);
	cout << p->data << " ";
	InOrder(p->right);
}

void BinaryTree::PostOrder(Node* p)
{
	if (!p)	return;
	PostOrder(p->left);
	PostOrder(p->right);
	cout << p->data << " ";
}

// Counting different nodes
int BinaryTree::CountNodes()
{
	return CountNodes(root);
}
int BinaryTree::CountLeafNodes()
{
	return CountLeafNodes(root);
}
int BinaryTree::CountNonLeafNodes()
{
	return CountNonLeafNodes(root);
}
int BinaryTree::CountDeg1Nodes()
{
	return CountDeg1Nodes(root);
}
int BinaryTree::CountDeg2Nodes()
{
	return CountDeg2Nodes(root);
}

int BinaryTree::CountNodes(Node* p)
{
	if (!p) return 0;
	return CountNodes(p->left) + CountNodes(p->right) + 1;
}
int BinaryTree::CountLeafNodes(Node* p)
{
	if (!p) return 0;
	int l = CountLeafNodes(p->left);
	int r = CountLeafNodes(p->right);
	if (!p->left && !p->right)
		return (l + r + 1);
	return (l + r);
}
int BinaryTree::CountNonLeafNodes(Node* p)
{
	if (!p) return 0;
	int l = CountNonLeafNodes(p->left);
	int r = CountNonLeafNodes(p->right);
	if (p->left || p->right)
		return (l + r + 1);
	return (l + r);
}
int BinaryTree::CountDeg1Nodes(Node* p)
{
	if (!p) return 0;
	int l = CountDeg1Nodes(p->left);
	int r = CountDeg1Nodes(p->right);
	if ( (p->left != NULL) ^ (p->right != NULL) )
		return (l + r + 1);
	
	return (l + r);
}
int BinaryTree::CountDeg2Nodes(Node* p)
{
	if (!p) return 0;
	int l = CountDeg2Nodes(p->left);
	int r = CountDeg2Nodes(p->right);
	if (p->left && p->right)
		return (l + r + 1);
	
	return (l + r);
}

// Tree Height
int BinaryTree::Height()
{
	return Height(root);
}
int BinaryTree::Height(Node* p)
{
	if (!p) return 0;
	int l = Height(p->left);
	int r = Height(p->right);
	
	return (l > r) ? (l + 1) : (r + 1);
}

// Sum of all elements of the Tree
int BinaryTree::Sum()
{
	return Sum(root);
}
int BinaryTree::Sum(Node* p)
{
	if (!p) return 0;
	
	int ls = Sum(p->left);
	int rs = Sum(p->right);
	return (ls + rs + p->data);
}

// DF traversal methods using non-recursive method
// Tree traversal using iterative(non-recursive) method
void BinaryTree::PreOrderIter()
{
	cout << "PreOrderIter  : [";
	
	Node *p = root;
	stack<Node*> st;
	
	while(p || !st.empty())
	{
		if (p) {
			cout << p->data << " ";
			st.push(p);
			p = p->left;
		}
		else{
			p = st.top();
			st.pop();
			p = p->right;
		}
	}
	cout << "]" << endl;
}

void BinaryTree::InOrderIter()
{
	cout << "InOrderIter   : [";
	Node *p = root;
	stack<Node*> st;
	
	while(p || !st.empty())
	{
		if (p) {
			st.push(p);
			p = p->left;
		}
		else{
			p = st.top();
			st.pop();
			cout << p->data << " ";
			p = p->right;
		}
	}
	cout << "]" << endl;
}

void BinaryTree::PostOrderIter()
{
	cout << "PostOrderIter : [";
	Node *p = root;
	Node *pre = NULL;
	stack<Node*> st;
	
	while(p || !st.empty())
	{
		if (p) {
			st.push(p);
			p = p->left;
		}
		else{
			p = st.top();
			if (!p->right || (p->right == pre)) {
				cout << p->data << " ";
				st.pop();
				pre = p;
				p = NULL;
			}
			else
				p = p->right;
		}
	}
	cout << "]" << endl;
}

// data is given in an array.
// format is in level order.
// if any node is null, set its value to NA. set its child also to NA, NA
int32_t main()
{
/*
	int arr[] = {1, 7, 9, 2, 6, NA, 9, NA, NA, 5, 11, NA, NA, 5};
	int size = sizeof(arr) / sizeof(arr[0]);
	
	BinaryTree *bt = new BinaryTree(arr, size);
*/
	int inorder[] = {2, 7, 5, 6, 11, 1, 9, 5, 9};
	int preorder[] = {1, 7, 2, 6, 5, 11, 9, 9, 5};
	int postorder[] = {2, 5, 11, 6, 7, 5, 9, 9, 1};
	int size = sizeof(inorder) / sizeof(inorder[0]);
	
//	BinaryTree *bt = new BinaryTree(inorder, preorder, _PRE_ORDER_, size);
	BinaryTree *bt = new BinaryTree(inorder, postorder, _POST_ORDER_, size);
	
	bt->PreOrder();
	bt->InOrder();
	bt->PostOrder();
	bt->LevelOrder();
	
	bt->PreOrderIter();
	bt->InOrderIter();
	bt->PostOrderIter();
	
	cout << "Num Nodes : " << bt->CountNodes() << endl;
	cout << "Num Leaf Nodes : " << bt->CountLeafNodes() << endl;
	cout << "Num Non-Leaf Nodes : " << bt->CountNonLeafNodes() << endl;
	cout << "Num Deg1 Nodes : " << bt->CountDeg1Nodes() << endl;
	cout << "Num Deg2 Nodes : " << bt->CountDeg2Nodes() << endl;
	cout << "Tree Height : " << bt->Height() << endl;
	cout << "Sum : " << bt->Sum() << endl;
	
	if (bt) delete bt;
	bt = NULL;
	return 0;
}

/*
	// Some examples 
	
	int arr[] = {1, 2, NA};
	PreOrder  : [1 2 ]
	InOrder   : [2 1 ]
	PostOrder : [2 1 ]

	int arr[] = {1, NA, 2};
	PreOrder  : [1 2 ]
	InOrder   : [1 2 ]
	PostOrder : [2 1 ]

	int arr[] = {1, NA, 2, NA, NA, NA, 3};
	PreOrder  : [1 2 3 ]
	InOrder   : [1 2 3 ]
	PostOrder : [3 2 1 ]

	int arr[] = {1, NA, 2, NA, NA, 3, NA};
	PreOrder  : [1 2 3 ]
	InOrder   : [1 3 2 ]
	PostOrder : [3 2 1 ]

	int arr[] = {1, 2, 3, 4, 5, 6, 7};
	PreOrder  : [1 2 4 5 3 6 7 ]
	InOrder   : [4 2 5 1 6 3 7 ]
	PostOrder : [4 5 2 6 7 3 1 ]

	int arr[] = {1, 7, 9, 2, 6, NA, 9, NA, NA, 5, 11, NA, NA, 5};
	PreOrder  : [1 7 2 6 5 11 9 9 5 ]
	InOrder   : [2 7 5 6 11 1 9 5 9 ]
	PostOrder : [2 5 11 6 7 5 9 9 1 ]
	
	int arr[] = {3, 1, 10, 13, 5, 11, 16, NA, NA, 6, NA, NA, NA, 15, 2, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, 9, 4};
	PreOrder  : [3 1 13 5 6 10 11 16 15 9 4 2 ]
	InOrder   : [13 1 6 5 3 11 10 9 15 4 16 2 ]
	PostOrder : [13 6 5 1 11 9 4 15 2 16 10 3 ]

	int arr[] = {8, 3, 10, 1, 6, NA, 14, NA, NA, 4, 7, NA, NA, 13};
	PreOrder  : [8 3 1 6 4 7 10 14 13 ]
	InOrder   : [1 3 4 6 7 8 10 13 14 ]
	PostOrder : [1 4 7 6 3 13 14 10 8 ]

*/
