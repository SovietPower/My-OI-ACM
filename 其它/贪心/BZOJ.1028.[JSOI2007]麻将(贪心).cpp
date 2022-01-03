/*
828kb	396ms
ö�ٶ��ӣ�ö��ÿ���ƣ��ȳ������Ŀ��ӣ�ʣ�µĳ�˳�ӡ�$O(n^3)$.
�������� -> �������п��ӣ�����˳�ӡ�(�ճ�zz)
��������ͬ�ģ�Ȼ��˳�ӣ���һ����һ��Ҫ��һ�λ��Ჹ˳�ӵĿ�λ�����ѿ��ӻ��ɶ��ӡ�����������$O(n^2)$.
��д$O(n^2)$���ˣ�����֮���ŷǳ��鷳����
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#define gc() getchar()
const int N=407;

int n,m,tot,tmp[N],num[N],Ans[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
bool Check()
{
	for(int i=1; i<=n+2; ++i)//������ǰ��� �Ŵ������ų����ӣ�
		if((num[i]%=3)>0) num[i+1]-=num[i], num[i+2]-=num[i], num[i]=0;//ֱ�Ӹ��������а�����ʲô 
		else if(num[i]<0) return 0;
	return 1;
}

int main()
{
	n=read(),m=read(),tot=3*m+1;
	for(int i=1; i<=tot; ++i) ++tmp[read()];
	int cnt=0;
	for(int i=1; i<=n; ++i)
	{
		++tmp[i];
		for(int j=1; j<=n; ++j)
			if(tmp[j]>=2)
			{
				tmp[j]-=2, memcpy(num,tmp,sizeof num), tmp[j]+=2;
				if(Check()) {Ans[++cnt]=i; break;}
			}
		--tmp[i];
	}
	if(cnt) for(int i=1; i<=cnt; ++i) printf("%d ",Ans[i]);
	else puts("NO");

	return 0;
}
