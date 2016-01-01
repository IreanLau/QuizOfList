#include<iostream>
using namespace std;
#define __DEBUG__



//������Ϊ��׼


/**************************************************************************************/

/*����������*/
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
	��β��ͷ��ӡ
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
	ɾ��һ����ͷ����ķ�β�ڵ㣨͵��������
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
	��һ����ͷ����ķ�ͷ�ڵ�ǰ����һ���ڵ�
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
	��������
*/
Node* _Reverse(Node *pBegin)
{
	if (pBegin == NULL || pBegin->next==NULL)//size=1��0ʱ  ����
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
/*ð��*/
void BubbleSort(Node* pBeign)
{
	if (pBeign == NULL)
		return;
	Node* tail = NULL;/*��������*/
	while (tail != pBeign)
	{
		Node* prev = pBeign;
		Node* cur = prev->next;
		bool flag = true;/*��� ������Ч�ıȽ�*/

		while (cur != tail)/*һ������*/
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
	�ϲ�������������֮����Ȼ����
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
	ֻ����һ�ߣ����м�ڵ�(����ָ��)

	��ͷ���  ����ָ��ָ��ͷ���
	
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
	���ҵ�����ĵ�����K���ڵ㣬ֻ�ܱ���һ��
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
	�ж������Ƿ�������������󳤶ȣ��󻷵���ڣ�  ����ÿ��������ʱ/�ո��Ӷ�
*/

/*
	�жϴ���������ָ�룩��ʱ��O(n)	�գ�O(1)
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
�����		ʱ��O(n)	�գ�O(1)
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

	/*����*/
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
	�ж����������Ƿ��ཻ������������

	������1 ��β��ӣ� ת�����ж� ����2 �Ƿ��������
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

	/*����*/
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
	Josephus��n����Χ��Ȧ�����α��Ϊ1,2,..,n�����ڴ�1�ſ�ʼ���α�����
	������mʱ����m�����˳�����һ�������´�1����
	ѭ����ȥ�������ʣ���Ǹ��˵ı���Ƕ��٣��������� ģ�ⷨ��

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
	//��ѧ��

	��
	 ��int main(void)
	   ��{
		 ��int n, m, i, s=0;
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
	//test3();//�鲢
	//test6();
	//test7();
	test4();
}