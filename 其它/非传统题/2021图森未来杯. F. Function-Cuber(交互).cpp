/*
$Query(i,i+1)$���Եõ�$a_{i-1}-a_i+a_{i+1}-a_{i+2}-1$��$Query(i,i+2)$���Եõ�$a_{i-1}-a_{i+3}$��
ע���±�ȡ$0,n+1$ʱֵΪ$0$������$Query(1,3)$���Եõ�$-a_4$��$Query(n-2,n)=a_{n-3}$��
Ȼ����֪$a_4,a_{n-3}$����$n-3\neq 4$���õڶ���$Query$���Եõ�����$a_{4+4k}$��$a_{n-3-4k}$��
Ȼ��$a_1,a_2,a_3,a_4$�У����Ǿ���֪�������ˣ�$a_4$��$a_1$��$a_3$���������õ�һ��$Query$���Եõ�$a_1,a_2,a_3,a_4$��Ĺ�ϵ��
����ö��$a_2=[1,100]$���Ϳ��Եõ�$a_1,a_2,a_3,a_4$�������õڶ���$Query$�õ�����$a_i$���ж��Ƿ�Ϸ����ɡ�
���Ӷ�$O(100n)$����Ҫѯ��$n-1$�Ρ�

�����е���������Ҫȫ����������ö��$a_1,a_2,a_3,a_4$�е����������������������ܹ���
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb emplace_back
typedef long long LL;
const int N=1e5+5;

int D[N],A[N];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
int Query(int u,int v,int s)//v=u+2: A[i-1]-A[i+3];  v=u+1:A[i-1]-A[i]+A[i+1]-A[i+2]
{
	printf("? %d %d\n",u,v); fflush(stdout);
	int x; scanf("%d",&x); return x-s;
//	return read()-s;
}
int Calc(int n)
{
	int s=0;
	for(int i=1; i<n; ++i) s+=A[i]*A[i+1];
	return s;
}
void Output(int n)
{
	pc('!');
	for(int i=1; i<=n; ++i) printf(" %d",A[i]); pc('\n');
	fflush(stdout);
}

int main()
{
	int n=read(),s=read();
	if(n<=2)
	{
		int t=Query(1,2,s)+1;
		for(int i=1; i<=100; ++i)
			for(int j=1; j<=100; ++j)
				if(j-i==t && (A[1]=i,A[2]=j,Calc(n))==s)
					return Output(n),0;
	}

	A[4]=-Query(1,3,s);
	A[n-3]=Query(n-2,n,s);//A[1]||A[3]
	for(int i=1; i+3<n; ++i) D[i]=Query(i+1,i+3,s);//D[i]=A[i]-A[i+4]
	for(int i=4; i+4<=n; i+=4) A[i+4]=A[i]-D[i];
	for(int i=n-3; i-4>=1; i-=4) A[i-4]=A[i]+D[i-4];//D[i-4]=A[i-4]-A[i]

	int t=Query(2,3,s);//t=A[1]-A[2]+A[3]-A[4]-1;
	int pos=A[1]?3:1,val=A[1]?A[1]:A[3];

	for(int i=1; i<=100; ++i)
	{
		A[2]=i, A[pos]=t+1+A[2]+A[4]-val;
		for(int i=2; i+4<=n; i+=4) A[i+4]=A[i]-D[i];
		for(int i=pos; i+4<=n; i+=4) A[i+4]=A[i]-D[i];
		if(Calc(n)==s) return Output(n),0;
	}
	

	return 0;
}
