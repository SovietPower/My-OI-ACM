/*
62ms	7800KB
������������Ȼ�����һ��λ����һ��ѭ���ڣ�ǰ׺�Ǹ�ѭ���ڣ��Ľ�β���Ϳ�����Ϊ�𰸣�����ö�ٸ�ѭ���ڳ��ȸ��´𰸼��ɡ�
���Ӷ�Ӧ����2n�ȡ�
*/
#include <bits/stdc++.h>
#define gc() getchar()
typedef long long LL;
const int N=1e6+5;

int f[N],A[N];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(; !isdigit(c); c=='-'&&(f=-1),c=gc());
	for(; isdigit(c); now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	std::reverse(A+1,A+1+n);
	for(int i=2,j=0; i<=n; ++i)
	{
		while(j&&A[i]!=A[j+1]) j=f[j];
		f[i]=A[i]==A[j+1]?++j:0;
	}
	int k=1e9,p=1e9;
	for(int i=1; i<=n; ++i)
		if(!(i%(i-f[i])))
		{
			int kk=n-i,pp=i-f[i];
			for(int j=i+1; j<i+i-f[i]; ++j)
				if(A[j]==A[j-i]) --kk;
				else break;
			if(kk+pp<k+p) k=kk, p=pp;
		}
	printf("%d %d\n",k,p);

	return 0;
}
