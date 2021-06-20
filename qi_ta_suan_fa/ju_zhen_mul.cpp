#include<iostream>
#include<vector>
using namespace std;

void matrixMul(vector<vector<int>>& A,vector<vector<int>>& B)
{
	vector<vector<int>>res(A.size(),vector<int>(B[0].size(),0));
	for(int i=0;i<A.size();i++)
	{
		for(int j=0;j<B[0].size();j++){
			for(int k = 0;k<A[0].size();k++){
				res[i][j] += A[i][k]*B[k][j];
			}
		}
	}

	cout<<"---------show--------"<<endl;
	for(int i=0;i<res.size();i++)
	{
		for(int j=0;j<res[0].size();j++){
			cout<<res[i][j]<<"  ";
		}
		cout<<endl;
	}
}

typedef int (*CALLBACK)(int a,int b);

int max(int a,int b){
	cout<<"max:: "<<endl;
	return (a>b?a:b);
}
int min(int a,int b){
	cout<<"min:: "<<endl;
	return (a<b?a:b);
}
int sum(int a,int b){
	cout<<"sum:: "<<endl;
	return (a+b);
}
//定义一个函数指针的数组
void test01()
{
	CALLBACK callback[3]; //定义一个函数指针数组 
	callback[1]=max;
	cout<<callback[1](3,9)<<endl;

	callback[0]=min;
	cout<<callback[0](2,45)<<endl;

	callback[2]=sum;
	cout<<callback[2](12,54)<<endl;
	return;
}
//定义一个指向数组的指针
void test02()
{
	int a[3][4] = {1,3,5,7,9,11,13,15,17,19,21,23};
	int (*p)[4];
	p=a;

	cout<<*(*(p+2)+3)<<endl;
}
/*
1. 定义一个有10个整形的数组，int a[10]
2. 定义一个有10个指针的数组，每个指针指向一个整形数 int* a[10]
3. 一个指向有10个整形数的数组的指针，int (*a)[10]
4.一个指向指针的指针，被指向的指针指向一个有10个整形数的数组 int (**a)[10]
5.一个指向数组的指针，该数组有10整形指针 int* (*a)[10]
6.一个指向函数的指针，该函数有一个整形参数，并返回一个整形数 int (*a)(int);
						typedef int (*CALLBACK)(int);
7. 一个有10个指针的数组，每个指针指向一个函数，该函数有一个整形参数并返回一个整形
	int (*a[10])(int);
8.一个函数的指针，指向的函数的类型有两个参数，并返回一个函数指针的函数，返回的函数指针有
一个整形参数并返回整形的函数
	int (*(*a)(int,int))(int);

9. 一个函数指针，参数int,返回值是一个指针，指向一个int数组 int (*(*p)(int))[10];


*/

//构造单链表
typedef struct{
	struct ListNode* next;
	int val;
}ListNode;

ListNode* CreateList(vector<int>& vec)
{
	ListNode* dummynode = new ListNode(-1);
	dummynode->next = nullptr;
	ListNode* pre = dummynode;

	for(int i=0;i<vec.size();i++){
		ListNode* temp = new ListNode(vec[i]);
		temp->next = nullptr;
		pre->next = temp;
		pre = pre->next;
	}
	return dummynode;
}

//构造双链表




int main()
{
	vector<vector<int>>A{{1,0},{0,1}};
	vector<vector<int>>B{{1,0},{0,1}};

	matrixMul(A,B);

	vector<vector<int>>C{{1,2,3},{1,1,1}};
	vector<vector<int>>D{{1},{2},{3}};

	matrixMul(C,D);
	cout<<"*****"<<endl;

	test01();

	cout<<"^^^^^^^"<<endl;
	test02();
	return 0;
}

