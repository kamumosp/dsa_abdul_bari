#include <iostream>
#include <cstdint>

using namespace std;

struct Node
{
	int data;
	Node *prev;
	Node *next;
//	Node():data(0), prev(NULL), next(NULL){};
//	Node(int x):data(x), prev(NULL), next(NULL){};
//	Node(int x, Node *bef):data(x), prev(bef), next(NULL){};
	Node(int x=0, Node *bef=NULL, Node *aft=NULL):data(x), prev(bef), next(aft){};
};

Node *createLL(int arr[], int size)
{
	Node *head = NULL;
	Node *temp = NULL;
	
	for (int i = 0; i < size; i++)
	{
		if (!head)
		{
			temp = new Node(arr[i]);
			head = temp;
		}
		else{
			temp->next = new Node(arr[i], temp);
			temp = temp->next;
		}
	}
	return head;
}

void printLL(Node *head)
{
	cout << "[";
	while (head)
	{
		cout << head->data;
		if (head->next)
			cout << ", ";
		
		head = head->next;
	}
	cout << "]" << endl;
}

void printLLRec(Node *head)
{
	static bool first = true;
	
	if (first)
	{
		first = false;
		cout << "[";
	}
	if (!head) {
		cout << "]" << endl;
		return;
	}
	
	cout << head->data;
	if (head->next)
		cout << ", ";
	
	printLLRec(head->next);
}

void printCircularLL(Node *head)
{
	Node *p = head;
	cout << "[";
	do
	{
		cout << p->data;
		
		cout << ", ";
		
		p = p->next;
		
	} while (p != head);
	
	cout << "]" << endl;
}
void printCircularLLRec(Node *head, Node *p = NULL)
{
	if (p == head) {
		cout << "]" << endl;
		return;
	}
	
	if (!p)	{
		p = head;
		cout << "[";
	}

	cout << p->data;
	
	cout << ", ";
	
	printCircularLLRec(head, p->next);
}

void deleteLL(Node *head)
{
	Node *temp;
	
	while (head)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
}

void deleteCircularLL(Node *head)
{
	if (!head)	return;
	Node *p = head->next;
	Node *temp;
	
	while (p != head)
	{
		temp = p;
		p = p->next;
		delete temp;
	}
	delete p;
}

int count (Node *head)
{
	int cnt = 0;
	
	while (head)
	{
		cnt++;
		head = head->next;
	}
	return cnt;
}

int countCircular (Node *head)
{
	if (!head) return 0;
	Node *p = head->next;
	int cnt = 1;
	
	while(p != head)
	{
		cnt++;
		p = p->next;
	};
	
	return cnt;
}

int countRec(Node *head)
{
	if (!head)
		return 0;
	
	return countRec(head->next) + 1;
}

int sum(Node *head)
{
	int total = 0;
	
	while (head)
	{
		total += head->data;
		head = head->next;
	}
	return total;
}

int sumRec(Node *head)
{
	if (!head)
		return 0;
	
	return sumRec(head->next) + head->data;
}

int maxLL (Node *head)
{
	int max = INT_MIN;
	
	while (head)
	{
		if (head->data > max)
			max = head->data;
		
		head = head->next;
	}
	
	return max;
}

int maxLLRec(Node *head)
{
	if (!head)
		return INT_MIN;
	
	int x = maxLLRec(head->next);
	
	return (head->data > x) ? head->data : x;
}

Node *search(Node *head, int x)
{
	while (head)
	{
		if (x == head->data)
			return head;
		
		head = head->next;
	}
	return NULL;
}

Node *insert(Node *head, int index, int x)
{
	if (index < 0)
		return head;
	if (index == 0)
	{
		Node *tmp = new Node(x, NULL, head);
		if (head)
			head->prev = tmp;
		head = tmp;
		return head;
	}
	
	Node *p = head;
	for (int i = 1; (i < index) && p; i++)
		p = p->next;
	
	if (p)
	{
		Node *tmp = new Node(x, p, p->next);
		if (p->next)
			p->next->prev = tmp;
		p->next = tmp;
	}
	
	return head;
}

Node *insertSorted(Node *head, int x)
{
	Node *q = NULL;
	Node *p = head;
	Node *tmp = new Node(x);
	
	while (p && (p->data < x))
	{
		q = p;
		p = p->next;
	}
	
	if (!q)
	{
		// insert before first node
		tmp->next = p;
		return tmp;
	}
	// insert at other places
	tmp->next = p;
	q->next = tmp;
	
	return head;
}

Node *deleteNode(Node *head, int index)
{
	Node *p = head;
	Node *q = NULL;
	
	if (index <= 0 || !head)
		return NULL;
	
	for (int i = 0; i < (index - 1) && p; i++)
	{
		q = p;
		p = p->next;
	}
	
	if (!q)
	{
		// delete first node
		int x = head->data;
		head = head->next;
		delete p;
		cout << "Deleted : " << x << " at node : " << index << endl;

		return head;		
	}
	// delete node at other places
	int x = p->data;
	q->next = p->next;
	delete p;
	cout << "Deleted : " << x << " at node : " << index << endl;

	return head;		
}

bool isSorted(Node *head)
{
	int prev = INT_MIN;
	
	while (head)
	{
		if (prev > head->data)
			return false;
		
		prev = head->data;
		head = head->next;
	}
	return true;
}

// remove duplicates from sorted linked list
Node *removeDupl(Node *head)
{
	Node *p = head;
	Node *q = NULL;
	
	while (p)
	{
		if (q && (q->data == p->data))
		{
			q->next = p->next;
			delete p;
			p = q->next;
		}
		else {
			q = p;
			p = p->next;
		}		
	}
	return head;
}

Node *reverseLL(Node *head)
{
	Node *p = head;
	Node *q = NULL;
	Node *r = NULL;
	
	while (p)
	{
		r = q;
		q = p;
		p = p->next;
		q->next = r;
	}

	return q;
}

Node *reverseLLRec(Node *p, Node *q)
{
	if (!p)
	{
		return q;
	}
	Node *head = reverseLLRec(p->next, p);
	p->next = q;
	
	return head;
}

Node *concatenate(Node *l1, Node *l2)
{
	if (!l1)
		return l2;
	if (!l2)
		return l1;

	Node *p = l1;
	
	while(p->next)
	{
		p = p->next;
	}
	
	p->next = l2;

	return l1;
}

Node *merge(Node *l1, Node *l2)
{
	Node *r = NULL;
	Node *head = NULL;
	
	if (!l1)
		return l2;
	if (!l2)
		return l1;

	Node *p = l1;
	Node *q = l2;
	
	if (p->data <= q->data)
	{
		head = p;
		r = p;
		p = p->next;
	}
	else{
		head = q;
		r = q;
		q = q->next;
	}
//	r->next = NULL;

	while(p && q)
	{
		if (p->data <= q->data)
		{
			r->next = p;
			p = p->next;
		}
		else{
			
			r->next = q;
			q = q->next;
			
		}
		r = r->next;
//		r->next = NULL;
	}
	
	if (p)
		r->next = p;
	
	if (q)
		r->next = q;
	
	return head;
}

bool isLoop(Node *head)
{
	Node *p = head;
	Node *q = head ? head->next : head;
	
	while (p && q)
	{
		if (p == q) return true;
		
		p = p->next;
		q = q->next;
		if (q) q = q->next;
	}
	
	return false;
}

Node *insertCircular(Node *head, int index, int x)
{
	if (index < 0)
		return head;
	
	if (!head)
	{
		head = new Node(x);
		head->next = head;
		return head;
	}
	
	if (index == 0)
	{
		index = countCircular(head);
	}
	
	Node *p = head;
	for (int i = 0; i < (index - 1); i++)
		p = p->next;
	
	Node *tmp = new Node(x);
	tmp->next = p->next;
	p->next = tmp;
	
	return head;
}

Node *deleteNodeCircular(Node *head, int index)
{
	if (index < 0 || !head)
		return head;
	
	if (head == head->next)
	{
		delete head;
		return NULL;
	}
	
	if (index == 1)
	{
		index = countCircular(head);
//		cout << "index = " << index << endl;
		head = head->next;
	}

	Node *q = head;
	for (int i = 1; i < (index - 1); i++)
		q = q->next;
	
	Node *p = q->next;
	
	q->next = p->next;
	delete p;

	return head;
}

// doubly linked list
Node *deleteNodeDll(Node *head, int index)
{
	if ((index <= 0) || !head)
		return head;

	Node *p = head;
	for (int i = 1; (i < index) && p; i++)
		p = p->next;

	if (!p) return head;
	
	// p is the node we want to delete
	Node *q = p->prev;	// p->prev is NULL if we deleted first node
	cout << "delete node at index : " << index << endl;
	Node *temp = p;
	p = p->next;	// p->next is NULL if we deleted last node
	delete temp;
	
	if (q)	//	deleted first node
		q->next = p;
	
	if (p)	// deleted last node
		p->prev = q;
	return (q ? head : (p ? p : NULL));
}

Node *reverseDll(Node *head)
{
	if (!head)	return head;
	
	Node *p = head;
	Node *tmp = NULL;
	while(p)
	{
		tmp = p->next;
		p->next = p->prev;
		p->prev = tmp;
		
		if (!tmp) break;	// end reached
		p = tmp;
	}
	
	return p;
}

// reverse doubly linked list.
int32_t main()
{
	Node *ll = insert(NULL, 0, -10);

	ll = insert(ll, 1, 10);
	ll = insert(ll, 2, 20);
	ll = insert(ll, 3, 30);
	ll = insert(ll, 4, 40);
	ll = insert(ll, 5, 50);
	ll = insert(ll, 6, 60);
	
	printLL(ll);
	
	ll = reverseDll(ll);
	printLL(ll);

	deleteLL(ll);
	
	return 0;
}

// doubly linked list. insert and delete nodes
int32_t main_insert_delete_dll()
{
	Node *ll = insert(NULL, 0, -10);

	ll = insert(ll, 1, 10);
	ll = insert(ll, 2, 20);
	ll = insert(ll, 3, 30);
	ll = insert(ll, 4, 40);
	ll = insert(ll, 5, 50);
	ll = insert(ll, 6, 60);
	
	printLL(ll);
	
	ll = deleteNodeDll(ll, 0);
	printLL(ll);
	
	ll = deleteNodeDll(ll, 1);
	printLL(ll);
	ll = deleteNodeDll(ll, 2);
	printLL(ll);
	ll = deleteNodeDll(ll, 5);
	printLL(ll);

	deleteLL(ll);
	
	return 0;
}

// doubly linked list
int32_t main_dll()
{
	int arr[] = {5, -5, 10, -10, -20};
	int size = sizeof(arr) / sizeof(arr[0]);
	
	Node *ll = createLL(arr, size);

	printLL(ll);
	
	deleteLL(ll);
	
	return 0;
}


int32_t main_insert_circular()
{
	Node *ll = insertCircular(NULL, 0, 10);

	printCircularLL(ll);
	
	ll = insertCircular(ll, 0, -10);
	ll = insertCircular(ll, 1, -20);

	printCircularLL(ll);
	
	ll = deleteNodeCircular(ll, 2);

	printCircularLL(ll);
	
	deleteCircularLL(ll);
	
	return 0;
}

int32_t main_circular()
{
	int arr[] = {5, -5, 10, -10, -20};
	int size = sizeof(arr) / sizeof(arr[0]);
	
	Node *ll = createLL(arr, size);

	printLL(ll);
	
	// make linked list circular
	Node *t2 = ll->next->next->next->next;
	t2->next = ll;

	cout << "list is : " << (isLoop(ll) ? "LOOP" : "Not LOOP") << endl;
	
	printCircularLL(ll);
//	printCircularLLRec(ll);
	
	// make linked list linear and delete all the nodes of it
	t2->next = NULL;
	deleteLL(ll);
	
	return 0;
}

int32_t main_isLoop()
{
	int arr[] = {5, -5, 10, -10, -20};
	int size = sizeof(arr) / sizeof(arr[0]);
	
	Node *ll = createLL(arr, size);

	printLL(ll);
	
	cout << "list is : " << (isLoop(ll) ? "LOOP" : "Not LOOP") << endl;
	
	// make linked list a loop
	Node *t2 = ll->next->next->next->next;
	t2->next = ll->next->next;
	
	cout << "list is : " << (isLoop(ll) ? "LOOP" : "Not LOOP") << endl;
	
	// make linked list linear and delete all nodes of it
	t2->next = NULL;
	deleteLL(ll);
	
	return 0;
}


int32_t main_concat_merge()
{
	int arr1[] = {15, 25, 35, 45};
	int size1 = sizeof(arr1) / sizeof(arr1[0]);
	
	int arr2[] = {10, 20, 30, 40, 50, 60};
	int size2 = sizeof(arr2) / sizeof(arr2[0]);
	
	Node *ll1 = createLL(arr1, size1);
	Node *ll2 = createLL(arr2, size2);

	printLL(ll1);
	printLL(ll2);
	
//	Node *ll3 = concatenate(ll1, ll2);
	Node *ll3 = merge(ll1, ll2);

	printLL(ll3);

	deleteLL(ll3);
	
	return 0;
}

int32_t main_reverse()
{
	int arr[] = {5, -5, 10, -10, -20};
	int size = sizeof(arr) / sizeof(arr[0]);
	
	Node *ll = createLL(arr, size);

	printLL(ll);
	
	ll = reverseLL(ll);

	printLL(ll);

	ll = reverseLLRec(ll, NULL);

	printLL(ll);
	
	deleteLL(ll);
	
	return 0;
}


int32_t main_remove_dupl()
{
	int arr[] = {5, 5, 6, 6, 6, 6, 7, 8, 8, 8, 8, 9, 9, 10, 10, 10, 10};
	int size = sizeof(arr) / sizeof(arr[0]);
	
	Node *ll = createLL(arr, size);

	printLL(ll);
	
	ll = removeDupl(ll);

	printLL(ll);
	
	deleteLL(ll);
	return 0;
}

int32_t main_isSorted()
{
	int arrs[] = {5, 6, 8, 10};
	int arrns[] = {5, 7, 6, 8, 10, 9};
	int sizes = sizeof(arrs) / sizeof(arrs[0]);
	int sizens = sizeof(arrns) / sizeof(arrns[0]);
	
	Node *lls = createLL(arrs, sizes);
	Node *llns = createLL(arrns, sizens);
	
	printLL(lls);
	printLL(llns);
	
	cout << "arrs is : " << (isSorted(lls) ? "Sorted" : "Not Sorted") << endl;
	cout << "arrns is : " << (isSorted(llns) ? "Sorted" : "Not Sorted") << endl;

	deleteLL(lls);
	deleteLL(llns);
	return 0;
}

int32_t main_delete_node()
{
	Node *ll = NULL;
	
	ll = insert(ll, 0, 5);
	
	printLL(ll);
	
	ll = insert(ll, 1, 15);
	
	printLL(ll);
	
	ll = insert(ll, 2, -5);
	
	printLL(ll);
	
	ll = insert(ll, 2, -25);
	
	printLL(ll);
	
	ll = insert(ll, 2, -35);
	
	printLL(ll);
	
	ll = deleteNode(ll, 1);
	
	printLL(ll);
	
	ll = deleteNode(ll, 4);
	
	printLL(ll);
	
	ll = deleteNode(ll, 2);
	
	printLL(ll);
	
	deleteLL(ll);
	return 0;
}

int32_t main_insert_sorted()
{
	Node *ll = NULL;
	
	ll = insertSorted(ll, 5);
	
	printLL(ll);
	
	ll = insertSorted(ll, 15);
	
	printLL(ll);
	
	ll = insertSorted(ll, -5);
	
	printLL(ll);
	
	deleteLL(ll);
	return 0;
}

int32_t main_create_insert()
{
	Node *ll = NULL;
	
	ll = insert(ll, 0, 5);
	
	printLL(ll);
	
	ll = insert(ll, 0, 15);
	
	printLL(ll);
	
	ll = insert(ll, 0, 25);
	
	printLL(ll);
	
	ll = insert(ll, 0, 35);
	
	printLL(ll);
	
	ll = insert(ll, 4, 45);
	
	printLL(ll);
		
	deleteLL(ll);
	return 0;
}

int32_t main_m()
{
	int arr[] = {5, 7, 6, 8, 10, 9, 2};
	int size = sizeof(arr) / sizeof(arr[0]);
	
	Node *ll = createLL(arr, size);
	
	printLL(ll);
	
	cout << "Num nodes : " << count (ll) << endl;
	cout << "Sum nodes : " << sum (ll) << endl;
	cout << "Max Elem : " << maxLL (ll) << endl;
	
	int val = 10;
	
	cout << "value '" << val << "' is : " << (search (ll, val) ? "Found" : "Not Found") << endl;

	val = 100;
	
	cout << "value '" << val << "' is : " << (search (ll, val) ? "Found" : "Not Found") << endl;
	
	ll = insert(ll, -1, -20);
	
	printLL(ll);

	ll = insert(ll, 0, 20);
	
	printLL(ll);
	
	ll = insert(ll, 5, 30);
	
	printLL(ll);
	
	ll = insert(ll, 9, 40);
	
	printLL(ll);

	ll = insert(ll, 20, 50);
	
	printLL(ll);

//	cout << "Max Elem Rec : " << maxLLRec (ll) << endl;
//	cout << "Num nodes Rec : " << countRec (ll) << endl;
//	cout << "Sum nodes Rec : " << sumRec (ll) << endl;
	
//	printLLRec(ll);

	deleteLL(ll);
	
	return 0;
}
