#include<iostream>
using namespace std;
#include "BSTree.h"

void TestBSTree1()
{
	//int a[] = { 8,3,1,10,6,4,7,14,13 };
	int a[] = { 8,3 };
	BSTree<int> t1;
	for (auto e : a)
		t1.Insert(e);
	t1.InOrder();
	cout << endl;
	cout << t1.Find(13) << endl;
	cout << t1.Find(15) << endl;
	t1.Erase(3);
	t1.InOrder();
}
void TestBSTree2()
{
	int a[] = { 8,3,1,10,6,4,7,14,13 };
	BSTree<int> t1;
	for (auto e : a)
		t1.Insert(e);
	t1.InOrder();
	cout << endl;
	for (auto e : a)
	{
		t1.EraseR(e);
		t1.InOrder();
		cout << endl;
	}
}
int main()
{
	TestBSTree2();
	return 0;
}