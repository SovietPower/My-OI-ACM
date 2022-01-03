/*
2188kb	108ms
�����뵽������������ǲ��Եģ�����2 3��1 3�������������Ի�3->1 2->3������3->3 2->1��Ȼ���š�
�������������ǿ>=�Է���ǿ�򿪴�Ҳ�ǲ��Եģ�����1 3��2 3�����ò��Ի�3->3 1->2��
�������ڣ��ڵ�һ������£�����������2����һ�����Եõ��ġ�
���ǵõ�̰�Ĳ��ԣ�1.����������ǿ�ڶԷ���������ȣ����ܾͼ���2��
2.��������ǿǿ�ڶԷ���ǿ����ȣ����ܾͼ���3��
3.���������ͶԷ���ǿ�ȡ��������п���Ӯ�ģ�
ע�⵽��֧������ܵ÷���2n����͵÷ֿ�����2n��ȥ�������ߵ÷֡�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 600000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e5+5;

int n,A[N],B[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Solve(int *a,int *b)
{
	int ans=0;
	for(int h1=1,h2=1,t1=n,t2=n; h1<=t1 && h2<=t2; )
	{
		if(a[h1]>b[h2]) ans+=2,++h1,++h2;
		else if(a[t1]>b[t2]) ans+=2,--t1,--t2;
		else ans+=(a[h1++]==b[t2--]);//���������...
	}
	return ans;
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i<=n; ++i) B[i]=read();
	std::sort(A+1,A+1+n), std::sort(B+1,B+1+n);
	printf("%d %d\n",Solve(A,B),2*n-Solve(B,A));

	return 0;
}
