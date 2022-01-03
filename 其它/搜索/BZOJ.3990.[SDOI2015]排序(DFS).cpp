/*
836kb	164ms
�������е�˳����Ȼ���޹صģ�����ֻ�谴�ض�˳�����һ������Ϊ$l$�Ĳ������У����Դ𰸵Ĺ���Ϊ$l!$��
���Ǵ�С����ö������ѡ������ǰΪ��$i$���������һ�γ���Ϊ$2^i$����+1+1���������ģ���ô��Ҫ������Ϊ���γ���Ϊ$2^{i-1}$��Ȼ�󽻻�(�ڴ�֮ǰ�������г��ȸ�С����$2^{i-1}$����)��
��������γ���Ϊ$2^i$�ķ�ÿ�μ�1�ĵ����Σ����������������$3,8,\cdots,7,4$(Ҳ�����޽�:$8,3,\cdots,7,4$)�����������ηֳ��Ķγ���Ϊ$2^{i-1}$�ģ�Ȼ��ö���������(ֻ�������ֿ��з�����)���������������һ��DFS��
����������Σ��������н⡣
���û�У��ǲ��ܽ�������һ�㡣
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=(1<<12)+3;

int n,A[N],fac[15],bit[15];
long long Ans;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
bool Check(int p,int k)
{
	for(int i=p; i<p+k-1; ++i)
		if(A[i]+1!=A[i+1]) return 0;
	return 1;
}
void Swap(int p1,int p2,int k)
{
	for(int i=0; i<k; ++i)
		std::swap(A[p1+i],A[p2+i]);
}
void DFS(int p,int cnt)
{
	if(p>n) Ans+=fac[cnt];
	else
	{
		int p1=0,p2=0;
		for(int i=1; i<=bit[n]; i+=bit[p])
			if(!Check(i,bit[p])){
				if(!p1) p1=i;
				else if(!p2) p2=i;
				else return;
			}
		if(!p1&&!p2) DFS(p+1,cnt);
		else if(p1&&!p2)
			Swap(p1,p1+bit[p-1],bit[p-1]), DFS(p+1,cnt+1), Swap(p1,p1+bit[p-1],bit[p-1]);
		else
		{
			for(int i=0; i<=1; ++i)
				for(int j=0; j<=1; ++j)
				{
					Swap(p1+i*bit[p-1],p2+j*bit[p-1],bit[p-1]);
					if(Check(p1,bit[p])&&Check(p2,bit[p]))//����λ�ã�
					{
						DFS(p+1,cnt+1);
						Swap(p1+i*bit[p-1],p2+j*bit[p-1],bit[p-1]);
						break;
					}
					Swap(p1+i*bit[p-1],p2+j*bit[p-1],bit[p-1]);
				}
		}
	}
}

int main()
{
	fac[0]=fac[1]=1;
	for(int i=2; i<=12; ++i) fac[i]=fac[i-1]*i;
	for(int i=0; i<=12; ++i) bit[i]=1<<i;
	n=read();
	for(int i=1; i<=bit[n]; ++i) A[i]=read();
	DFS(1,0);
	printf("%lld",Ans);

	return 0;
}
