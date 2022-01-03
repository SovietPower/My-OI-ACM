/*
61ms	7288KB
���Է��� $0$����������δƥ���$2$ƥ�� �� $0$�͵�һ��δƥ���$2$ƥ�� �š�
��ô $0$����������δƥ���$2$ƥ�� �󣬿��Եõ����ɿ��ܰ��������ཻ�����䡣
����$i$��������$j$ ��$i,j$�������$2020$������һ�����ԡ������䲻�ཻ����ת��������ÿ������$i$����С�İ���$i$��������Ϊ���ڵ㡣
����������������ǣ�ÿ������Ժͳ�����������е���ԣ�������������
��$mxd$Ϊ������ĳ��������ȣ�$n$Ϊ���������Է�����$mxd*2\leq n$��ȫ��������ԣ���Ϊ$\frac n2$��ÿ�����������$\frac n2$���㣬�㹻����������ȫ��ƥ�䣩�������Ϊ$n-mxd$��һ����$mxd$����+����С֧��$n-mxd$���㣬��Ȼֻ��$n-mxd$����ƥ�䣩��
so��һ�������Ⱦ�ok��
Ҳ���Զ��ִ𰸣�̰����Կ��Ƿ���С�
*/
#include <bits/stdc++.h>
#define gc() getchar()
typedef long long LL;
const int N=2e5+5;

int dep[N];
char s[N];
std::vector<int> e[N];
struct Node
{
	int l,r;
	bool operator <(const Node &x)const
	{
		return l==x.l?r<x.r:l<x.l;
	}
}A[N];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline void AE(int u,int v)
{
	e[u].push_back(v), e[v].push_back(u);
}
void DFS(int x,int fa)
{
	for(auto v:e[x])
		if(v!=fa) dep[v]=dep[x]+1, DFS(v,x);
}

int main()
{
	static int sk[N];
	int n;
	while(~scanf("%d",&n))
	{
		scanf("%s",s+1);
		int t=0,cnt=0;
		for(int i=1; i<=n; ++i)
			if(s[i]=='2') sk[++t]=i;
			else if(s[i]=='0'&&t) A[++cnt]=(Node){sk[t--],i};
		if(!cnt) {puts("0"); continue;}

		std::sort(A+1,A+1+cnt), A[sk[0]=0].r=2e9;
		for(int i=1,t=0; i<=cnt; ++i)
		{
			while(A[i].l>A[sk[t]].r) --t;
			AE(sk[t],i), sk[++t]=i;
		}
		DFS(0,0);
		int mxd=0;
		for(int i=1; i<=cnt; ++i) mxd=std::max(mxd,dep[i]);
		printf("%d\n",mxd<<1>cnt?cnt-mxd:cnt>>1);
		for(int i=0; i<=cnt; ++i) std::vector<int>().swap(e[i]);
		for(int i=0; i<=cnt; ++i) dep[i]=0;
	}

	return 0;
}
