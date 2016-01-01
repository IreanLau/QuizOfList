#include<iostream>
using namespace std;
#define __DEBUG__



//以升序为基准


/**************************************************************************************/

/*单链表排序*/
struct Node
{
	int key;
	Node* next;
	Node(int nKey, Node* pNext)
		: key(nKey)
		, next(pNext)
	{}
};

void show(Node* pBeign)
{
	Node* cur = pBeign;
	while (cur)
	{
		cout << cur->key << " ";
		cur = cur->next;
	}
}

/*****************************************************/
/*
	从尾到头打印
*/
void ResPrint(Node* pBegin)
{
	if (pBegin == NULL)
		return;

	else
	{
		ResPrint(pBegin->next);
		cout << pBegin->key << " ";
	}
}


/*
	删除一个无头链表的非尾节点（偷梁换柱）
\*/
#include <assert.h>
void DelNode(Node* Pos)
{
	assert(Pos&&Pos->next);

	Node* _Pnext = Pos->next;
	Pos->key = _Pnext->key;
	Pos->next = _Pnext->next;

	free(_Pnext);
	_Pnext = NULL;
}


/***************************************/
/*
	在一个无头链表的非头节点前插入一个节点
*/

void InsPrev(Node*_Pos, int _Key)
{
	assert(_Pos);

	Node* _Pnext = _Pos->next;
	Node* S = new Node(_Pos->key, _Pnext);
	 _Pos->key = _Key;

	S->next = _Pnext;
	_Pos->next = S;

	_Pnext = NULL;
	S = NULL;
}

/************************************/
/*
	逆置链表
*/
Node* _Reverse(Node *pBegin)
{
	if (pBegin == NULL || pBegin->next==NULL)//size=1或0时  返回
		return NULL;

	Node*NewHead = new Node(-1, pBegin);

	Node* NewBegin = pBegin->next;
	pBegin->next = NULL;


	while (NewBegin)
	{
		Node* Ins = NewBegin;
		NewBegin = NewBegin->next;

		Ins->next = NewHead->next;
		NewHead->next = Ins;
	}
	return NewHead;
}
/*******************************************************/

Node* GetPartion(Node* pBegin, Node* pEnd)
{
	Node* _key = pBegin;
	Node* prev = pBegin;
	Node* cur = prev->next;
	while (cur != pEnd)
	{
		if (cur->key < _key->key)
		{
			prev = prev->next;
			std::swap(prev->key, cur->key);
		}
		cur = cur->next;
	}
	std::swap(prev->key, pBegin->key);
	return prev;
}

void QuickSort(Node* pBeign, Node* pEnd)
{
	if (pBeign->next == pEnd || pBeign == NULL)
		return;
	if (pBeign != pEnd)
	{
		Node* partion = GetPartion(pBeign, pEnd);
		QuickSort(pBeign, partion);
		QuickSort(partion->next, pEnd);
	}
}
/*冒泡*/
void BubbleSort(Node* pBeign)
{
	if (pBeign == NULL)
		return;
	Node* tail = NULL;/*控制趟数*/
	while (tail != pBeign)
	{
		Node* prev = pBeign;
		Node* cur = prev->next;
		bool flag = true;/*标记 减少无效的比较*/

		while (cur != tail)/*一趟排序*/
		{
			if (cur->key < prev->key)
			{
				swap(cur->key, prev->key);
				flag = false;
			}
			prev = cur;
			cur = cur->next;
		}
		if (flag)
			return;

		tail = prev;
	}
}



void test1()
{
	Node *h = new Node(1, NULL);
	Node *g = new Node(0, h);
	Node *f = new Node(9, g);
	Node *e = new Node(7, f);

	Node *d = new Node(5, e);
	Node *c = new Node(3, d);
	Node *b = new Node(2, c);
	Node *a = new Node(4, b);

	show(a);

	cout << endl;
	Node* pBeign = a;


	cout << "QuickSort:> \t" << endl;
	QuickSort(pBeign, NULL);
	show(a);
	cout << endl;


	//cout << "BubbleSort for list:> \t" << endl;
	//BubbleSort(pBeign);
	//show(a);
	//cout << endl;
}
/*************************************************/
/*	
	合并两个有序链表，之后仍然有序
*/
Node* Merge(Node*Begin1,Node*Begin2)
{
	if(Begin1==Begin2 || Begin1 == NULL || Begin2 == NULL)
		return NULL;
	Node* NewHead=new Node(-1,NULL);
	Node* tail = NewHead;
	while (Begin1 && Begin2)
	{
		if (Begin1->key < Begin2->key)
		{
			Node* S = Begin1;
			Begin1 = Begin1->next;
			S->next = NULL;
			
			tail->next = S;
			tail = tail->next;
			S = NULL;
		}
		else
		{
			Node* S = Begin2;
			Begin2 = Begin2->next;
			S->next = NULL;
			
			tail->next = S;
			tail = tail->next;
			S = NULL;
		}
	}

	Node* Pa = NULL;
	if (Begin1)
		Pa = Begin1;
	else
		Pa = Begin2;

	tail->next = Pa;
	return NewHead;
}

Node* _Merge(Node*Begin1, Node*Begin2)
{
	if (Begin1 == NULL || Begin2 == NULL)
		return Begin1 == NULL ? Begin2 : Begin1;

	Node*cur = Begin1;
	if (Begin1->key > Begin2->key)
	{
		cur = Begin2;
		Begin2 = Begin2->next;
	}
	else
	{
		Begin1 = Begin1->next;
	}

	Node* NewHead = cur;
	while (Begin1 != NULL && Begin2 != NULL)
	{
		if (Begin1->key < Begin2->key)
		{
			cur->next = Begin1;
			Begin1 = Begin1->next;
		}
		else
		{
			cur->next = Begin2;
			Begin2 = Begin2->next;
		}
		cur = cur->next;
	}
	if (Begin1 != NULL)
		cur->next = Begin1;
	else
		cur->next = Begin2;

	return NewHead;
}

Node* __Merge(Node*Begin1, Node*Begin2)
{
	if (Begin1 == NULL || Begin2 == NULL)
		return Begin1 == NULL ? Begin2 : Begin1;

	Node* Head = NULL;
	if (Begin1->key < Begin2->key)
	{
		Head = Begin1;
		Head->next = __Merge(Begin1->next,Begin2);
	}
	else
	{
		Head = Begin2;
		Head->next = __Merge(Begin1, Begin2->next);
	}
	return Head;
}
void test3()
{
	Node *i = new Node(9, NULL);
	Node *h = new Node(7, i);
	Node *g = new Node(5, h);
	Node *f = new Node(3, g);
	Node *e = new Node(1, f);

	Node *d = new Node(6, NULL);
	Node *c = new Node(4, d);
	Node *b = new Node(2, c);
	Node *a = new Node(0, b);

	show(a);
	cout << endl;

	show(e);
	cout << endl;

	Node*NewHead = Merge(a, e);
	show(NewHead);
	cout << endl;
}
/*************************************************/
/*
	只遍历一边，找中间节点(快慢指针)

	有头结点  快慢指针指向头结点
	
*/
Node* FindMid(Node* pBegin)
{
	if (pBegin == NULL || pBegin->next == NULL)
		return pBegin;

	Node* left = new Node(-1, pBegin);//
	Node* right = new Node(-1, pBegin);

	while (right && right->next)
	{
		left = left->next;

		right = right->next;
		right = right->next;
	}
	return left;
}
void test2()
{
	/*4 2 3 5 7 9 0 1*/
	Node *h = new Node(1, NULL);
	Node *g = new Node(0, h);
	Node *f = new Node(9, g);
	Node *e = new Node(7, f);

	Node *d = new Node(5, e);
	Node *c = new Node(3, d);
	Node *b = new Node(2, c);
	Node *a = new Node(4, b);

	show(a);
	cout << endl;

	ResPrint(a);
	cout << endl;

	//DelNode(a);


	//InsPrev(h,8);

	/*Node*NewHead = _Reverse(a);
	show(NewHead);
	cout << endl;*/

	//Node*mid = FindMid(a);
	//cout << mid->key << endl;


	cout << endl;
}

/*************************************************/
/*
	查找单链表的倒数第K个节点，只能遍历一次
*/
Node* _FindTailKpos(Node* pBegin, size_t K)
{
	if (K == 0 || pBegin == NULL)
		return NULL;

	Node*fast = new Node(-1, pBegin);
	Node*slow = fast;

	for (size_t i = 0; i < K -1; ++i)
	{
		if (fast->next)
			fast = fast->next;
		else
		{
			cout << "ERROR!\n num K is too big! " << endl;
			exit(1);
		}
	}

	while (fast->next)
	{
		slow = slow->next;
		fast = fast->next;
	}
	return slow;
}
void test4()
{
	/*4 2 3 5 7 9 0 1*/
	Node *h = new Node(1, NULL);
	Node *g = new Node(0, h);
	Node *f = new Node(9, g);
	Node *e = new Node(7, f);

	Node *d = new Node(5, e);
	Node *c = new Node(3, d);
	Node *b = new Node(2, c);
	Node *a = new Node(4, b);

	show(a);
	cout << endl;


	Node*cur = _FindTailKpos(a,8);
	cout << cur->key << endl;


	cout << endl;
}

/*************************************************/
/*
	判断链表是否带环，若带环求长度，求环的入口，  并求每个方法的时/空复杂度
*/

/*
	判断带环（快慢指针），时：O(n)	空：O(1)
*/


bool JudgeRing(Node* pBegin)
{
	assert(pBegin);
	Node *slow = pBegin, *fast = pBegin;

	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast) break;
	}

	return !(fast == NULL || fast->next == NULL);
}
/*
找入口		时：O(n)	空：O(1)
*/
Node* FindPort(Node* pBegin)
{
	assert(pBegin);
	Node *slow = pBegin, *fast = pBegin;

	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast) break;
	}

	if (fast == NULL || fast->next == NULL)
	{
		cout << "No Loop! the proc will exit!" << endl;
		exit(1);
	}
		
	slow = pBegin;
	while (slow != fast)
	{
		fast = fast->next;
		slow = slow->next;
	}

	Node* Gurd = slow;
	size_t count = 1;
	slow = slow->next;
	while (slow != Gurd && ++count)
		slow = slow->next;
		
	cout << "The lenth of ring is:> " << count << endl;
	return slow;
}
void test5()
{
	/*4 2 3 5 7 9 0 1*/

	/*带环*/
	Node *h = new Node(1, NULL);
	Node *g = new Node(0, h);
	Node *f = new Node(9, g);
	Node *e = new Node(7, f);

	Node *d = new Node(5, e);
	Node *c = new Node(3, d);
	Node *b = new Node(2, c);
	Node *a = new Node(4, b);
	h->next = g;

	/*show(a);
	cout << endl;*/

	
	//cout << JudgeRing(a) << endl;

	Node* Find = FindPort(a);
	cout << "The port is :>"<<Find->key << endl;

	cout << endl;
}

/*************************************************/

/*
	判断两个链表是否相交（链表不带环）

	将链表1 首尾相接， 转化成判断 链表2 是否带环问题
*/

bool JudgeMeet(Node* pBegin1, Node*pBegin2)
{
	if (pBegin1 == NULL && pBegin2 == NULL)
		return false;
	
	Node* tail = pBegin1;
	while (tail->next)
		tail = tail->next;

	tail->next = pBegin1;

	return JudgeRing(pBegin2);
}
void test6()
{
	/*4 2 3 5 7 9 0 1*/

	/*带环*/
	Node *h = new Node(1, NULL);
	Node *g = new Node(0, h);
	Node *f = new Node(9, g);
	Node *e = new Node(7, f);

	Node *d = new Node(5, NULL);
	Node *c = new Node(3, d);
	Node *b = new Node(2, c);
	Node *a = new Node(4, b);
	d->next = g;

	cout << "The JudgeMeet is :>" << JudgeMeet(a,e) << endl;

	cout << endl;
}
/*************************************************/
/*
	Josephus：n个人围成圈，依次编号为1,2,..,n，现在从1号开始依次报数，
	当报到m时，报m的人退出，下一个人重新从1报起，
	循环下去，问最后剩下那个人的编号是多少？（环链表 模拟法）

*/

Node *_Josephus(Node* pBegin, size_t m)
{
	Node* cur = pBegin;
	if (cur == NULL)
		return NULL;
	while (1)
	{
		if (cur->next == cur)
		{
			return cur;
		}
		size_t num = m;
		while (--num)
		{
			cur = cur->next;
		}

		Node* del = cur->next;
		cur->key = del->key;
		cur->next = del->next;
		free(del);
	}
}

/*
	//数学法

	　
	 　int main(void)
	   　{
		 　int n, m, i, s=0;
		   printf ("N M = ");
			scanf("%d%d", &n, &m);
			for (i=2; i<=n; i++)
				s=(s+m)%i;
			printf ("The winner is %d\n", s);
			return 0 ;
			}
*/
//Josephus
void test7()
{

	Node *h = new Node(1, NULL);
	Node *g = new Node(0, h);
	Node *f = new Node(9, g);
	Node *e = new Node(7, f);

	Node *d = new Node(5, e);
	Node *c = new Node(3, d);
	Node *b = new Node(2, c);
	Node *a = new Node(4, b);
	h->next = a;

	Node* _key = _Josephus(a, 2);
	cout << "The Josephus owner is :>" << _key->key << endl;

	cout << endl;
}
/*************************************************/
void main()
{
	//test2();
	//test3();//归并
	//test6();
	//test7();
	test4();
}