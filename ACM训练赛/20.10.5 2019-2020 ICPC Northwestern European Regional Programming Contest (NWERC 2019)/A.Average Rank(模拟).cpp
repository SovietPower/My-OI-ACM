/*
��Ϊÿ��ֻ���һ�֣�ֻ��Ӱ�츽�����ˡ�
����ģ��һ�¾ͺ���.. ע��ά������ǣ��þ�ǰ���Ĳ���д�ˣ���
*/
#include <bits/stdc++.h>
#define gc() getchar()
typedef long long LL;
const int N=1e6+5;

int tag[N],las[N],sco[N];
LL ans[N],sum[N];

inline int read()
{
	int now=0; char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	int n=read(),W=read();
	for(int i=1; i<=W; ++i)
	{
		for(int k=read(); k--; )
		{
			int c=read(),s=sco[c]; ++sco[c];//LL
			ans[c]+=sum[s]+1ll*tag[s]*(i-las[s]);
			sum[s]+=1ll*tag[s]*(i-las[s]), ++tag[s], las[s]=i;
			++s, ans[c]-=sum[s]+1ll*tag[s]*(i-las[s]);
			sum[s]+=1ll*tag[s]*(i-las[s]), las[s]=i;
		}
	}
	for(int i=1,s; i<=n; ++i) s=sco[i], ans[i]+=sum[s]+1ll*tag[s]*(W+1-las[s])+W;
	for(int i=1; i<=n; ++i) printf("%.8f\n",1.0*ans[i]/W);
	

	return 0;
}
